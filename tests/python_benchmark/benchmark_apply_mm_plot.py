from matplotlib.pyplot import legend
import numpy as np
import matplotlib.pyplot as plt

add_header = True

N_arr = []
py_time_arr = []
py_mem_arr = []
cpp_time_arr = []
cpp_mem_arr = []


with open("/tmp/mdot11_benchmark_apply_mm.txt", "r") as f:
    if add_header:
        print(f.readline())

    for line in f.readlines():
        N, py_sec, py_mem, cpp_sec, cpp_mem = line.split(",")
        N_arr.append(int(N))
        py_time_arr.append(float(py_sec))
        py_mem_arr.append(float(py_mem))
        cpp_time_arr.append(float(cpp_sec))
        cpp_mem_arr.append(float(cpp_mem))

    plt.figure(1)
    plt.subplot(1, 2, 1)
    plt.plot(N_arr, py_time_arr, "bx", label="time [s]")
    plt.plot(N_arr, cpp_time_arr, "rx", label="time [s]")
    plt.grid()
    plt.ylabel("time [s]")
    plt.subplot(1, 2, 2)
    plt.plot(N_arr, py_mem_arr, "bx", label="memory [KiB]")
    plt.plot(N_arr, cpp_mem_arr, "rx", label="memory [KiB]")
    plt.grid()
    plt.ylabel("memory [KiB]")
    plt.show()
    pass
