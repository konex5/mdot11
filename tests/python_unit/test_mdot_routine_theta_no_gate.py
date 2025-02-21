import pytest


def test_mdot_routine_mm_to_theta_no_gate():
    import mdot_routine
    cpp_dst = mdot_routine.mm_to_theta_no_gate({}, {}, True)
    assert cpp_dst == {}


def test_mdot_routine_mm_to_theta_no_gate_compare(make_random_blocs):
    mps_left = make_random_blocs(20, 4)
    mps_right = make_random_blocs(20, 4)
    from mdot_routine import mm_to_theta_no_gate as cpp_apply
    from pyfhmdot.routine.interface import mm_to_theta_no_gate as py_apply
    from copy import deepcopy
    from numpy import all

    dst = {}
    py_apply(dst, deepcopy(mps_left), deepcopy(mps_right), conserve_left_right=True)
    cpp_dst = cpp_apply(deepcopy(mps_left), deepcopy(mps_right), True)
    for key in dst.keys():
        assert all(dst[key] == cpp_dst[key])

    dst = {}
    py_apply(dst, deepcopy(mps_left), deepcopy(mps_right), conserve_left_right=False)
    cpp_dst = cpp_apply(deepcopy(mps_left), deepcopy(mps_right), False)
    for key in dst.keys():
        assert all(dst[key] == cpp_dst[key])
