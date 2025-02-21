from copy import deepcopy
import pytest


def test_mdot_routine_apply_mm_empty():
    import mdot_routine

    mdot_routine.apply_gate_on_mm({}, {}, {}, 8, 10**-8, True, 1, 1)


def test_mdot_routine_apply_mm_minimal(make_random_blocs, make_gate):
    import mdot_routine
    from pyfhmdot.algorithm import apply_gate_on_mm
    from pyfhmdot.intense.mul_mp import multiply_mp

    import numpy as np

    a = make_random_blocs(1, 1)
    gate = make_gate()
    dw_dict = {"dw_one_serie": 0}
    left, right = apply_gate_on_mm(
        deepcopy(a),
        deepcopy(a),
        deepcopy(gate),
        dw_dict,
        8,
        True,
        10**-8,
        is_um=True,
        conserve_left_right_after_gate=False,
        direction_right=1,
    )
    m_left, m_right, dw = mdot_routine.apply_gate_on_mm(
        deepcopy(a), deepcopy(a), deepcopy(gate), 8, 10**-8, True, 1, 1
    )
    assert abs(dw - dw_dict["dw_one_serie"]) < 10**-8
    for key in left.keys():
        assert np.all(np.abs(np.abs(left[key]) - np.abs(m_left[key])) < 10**-8)
    # for key in right.keys():
    #     assert np.all(np.abs(np.abs(right[key]) - np.abs(m_right[key])) < 10**-8)

    m_dst = {}
    multiply_mp(m_dst, m_left, m_right, [2], [0])
    dst = {}
    multiply_mp(dst, left, right, [2], [0])
    for key in m_dst.keys():
        np.all(np.abs(m_dst[key] - dst[key]) < 10**-8)


def test_mdot_routine_apply_mm(make_random_blocs, make_gate):
    mps_left = make_random_blocs(20, 2)
    mps_right = make_random_blocs(20, 3)
    gate = make_gate()
    import mdot_routine
    from pyfhmdot.algorithm import apply_gate_on_mm
    from pyfhmdot.intense.mul_mp import multiply_mp
    from copy import deepcopy

    import numpy as np

    dw_dict = {"dw_one_serie": 0}
    m_left, m_right = apply_gate_on_mm(
        deepcopy(mps_left),
        deepcopy(mps_right),
        deepcopy(gate),
        dw_dict,
        8,
        False,
        10**-62,
        is_um=True,
        conserve_left_right_after_gate=False,
        direction_right=1,
    )
    left, right, dw = mdot_routine.apply_gate_on_mm(
        deepcopy(mps_left),
        deepcopy(mps_right),
        deepcopy(gate),
        8,
        10**-62,
        False,
        1,
        1,
    )
    assert abs(dw - dw_dict["dw_one_serie"]) < 10**-8
    for key in left.keys():
        np.all(np.abs(np.abs(left[key]) - np.abs(m_left[key])) < 10**-8)
    for key in right.keys():
        np.all(right[key] == m_right[key])

    m_dst = {}
    multiply_mp(m_dst, m_left, m_right, [2], [0])
    dst = {}
    multiply_mp(dst, left, right, [2], [0])
    for key in m_dst.keys():
        np.all(np.abs(m_dst[key] - dst[key]) < 10**-8)
