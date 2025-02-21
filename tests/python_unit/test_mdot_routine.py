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


def test_mdot_routine_routine(make_random_blocs):
    mps_left = make_random_blocs(20, 2)
    mps_right = make_random_blocs(20, 1)
    import mdot_routine
    from pyfhmdot.algorithm import apply_mm
    from pyfhmdot.intense.mul_mp import multiply_mp
    from copy import deepcopy

    dw_dict = {"dw_one_serie": 0}
    m_left, m_right = apply_mm(
        deepcopy(mps_left),
        deepcopy(mps_right),
        dw_dict,
        8,
        True,
        10**-8,
        is_um=True,
        conserve_left_right_before=False,
        direction_right=1,
    )
    left, right, dw = mdot_routine.apply_mm(
        deepcopy(mps_left), deepcopy(mps_right), 8, True, 10**-8, 1, 1
    )
    m_dst = {}
    multiply_mp(m_dst, m_left, m_right, [2], [0])
    dst = {}
    multiply_mp(dst, left, right, [2], [0])
    pass
