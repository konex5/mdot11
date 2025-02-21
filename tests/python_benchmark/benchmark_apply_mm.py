import tracemalloc
import time
import numpy as np

from pyfhmdot.algorithm import apply_mm as py_apply_mm
from mdot_routine import apply_mm as cpp_apply_mm
from copy import deepcopy

add_header = True

datalist = [2 ** _ for _ in range(2, 10)]  # N


def create_random_matrix(chi, d):
    return np.random.random(chi * d * chi).reshape(chi, d, chi)


def create_random_blocs(chi, max_index=3):
    blocs = {}  # sh
    for i in range(max_index):
        for j in range(max_index):
            blocs[(i, 0, j)] = create_random_matrix(chi, d=1)
            blocs[(i, 1, j)] = create_random_matrix(chi, d=2)
            blocs[(i, 2, j)] = create_random_matrix(chi, d=1)
    return blocs


def create_gate():
    from pyfhmdot.initialize import create_hamiltonian_gates

    return create_hamiltonian_gates(
        "sh_xxz-hz_u1",
        {"Jxy": 0.25, "Jz": 0.25, "hz": 0},
        3,
        dbeta=0.0125,
        is_dgate=True,
        in_group=True,
    )[0][1]


with open("/tmp/mdot11_benchmark_apply_mm.txt", "w") as f:
    if add_header:
        f.write("N,py_time[ms],py_memory[KiB],cpp_time[ms],cpp_memory[KiB]\n")
    th = [create_gate()]
    for N in datalist:
        mp = [create_random_blocs(N), create_random_blocs(N)]
        mp_left = deepcopy(mp[0])
        mp_right = deepcopy(mp[0])
        #
        tracemalloc.start()
        time_start = time.time()
        #
        _, __ = py_apply_mm(
            mp_left,
            mp_right,
            {"dw_one_serie": 0},
            N,
            True,
            10 ** -62,
            is_um=None,
            conserve_left_right_before=False,
            direction_right=-1,
        )
        #
        time_end = time.time()
        print("elapsed time {} sec", time_end - time_start)
        memory_snapshot = tracemalloc.take_snapshot()
        top_stats = memory_snapshot.statistics("lineno")
        size = sum(stat.size for stat in top_stats[3:])
        print("%s other: %.1f KiB" % (len(top_stats[3:]), size / 1024))
        total = sum(stat.size for stat in top_stats)
        print("Total allocated size: %.1f KiB" % (total / 1024))
        py_elapsed_time = time_end * 10 ** -4  # ms
        py_memory = total
        #
        mp_left = deepcopy(mp[0])
        mp_right = deepcopy(mp[0])
        #
        tracemalloc.start()
        time_start = time.time()
        #
        _, __,___ = cpp_apply_mm(
            mp_left,
            mp_right,
            N,
            10 ** -62,
            True,
            is_um=0,
            direction_right=-1,
        )
        #
        time_end = time.time()
        print("elapsed time {} sec", time_end - time_start)
        memory_snapshot = tracemalloc.take_snapshot()
        top_stats = memory_snapshot.statistics("lineno")
        size = sum(stat.size for stat in top_stats[3:])
        print("%s other: %.1f KiB" % (len(top_stats[3:]), size / 1024))
        total = sum(stat.size for stat in top_stats)
        print("Total allocated size: %.1f KiB" % (total / 1024))
        cpp_elapsed_time = time_end * 10 ** -4  # ms
        cpp_memory = total
        #
        f.write(f"{N},{py_elapsed_time},{py_memory},{cpp_elapsed_time},{cpp_memory}\n")
