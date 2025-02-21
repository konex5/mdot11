import pytest


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
    # multiply_mp(dst, left, right, [2], [0])
