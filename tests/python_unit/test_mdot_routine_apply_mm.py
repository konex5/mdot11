from copy import deepcopy
import pytest

def test_mdot_routine_apply_mm_empty():
    import mdot_routine
    
    mdot_routine.apply_mm({},{},8,10**-8,True,1,1)

def test_mdot_routine_apply_mm_minimal(make_random_blocs):
    import mdot_routine
    from pyfhmdot.algorithm import apply_mm
    import numpy as np

    a = make_random_blocs(1,1)
    dw_dict = {"dw_one_serie":0}
    left,right = apply_mm(deepcopy(a),deepcopy(a),dw_dict,8,True,10**-8,is_um=True,conserve_left_right_before=False,direction_right=1)
    m_left, m_right, dw = mdot_routine.apply_mm(deepcopy(a),deepcopy(a),8,10**-8,True,1,1)
    #assert dw <= dw_dict["dw_one_serie"]
    for key in left.keys():
        assert np.all(np.abs(np.abs(left[key]) - np.abs(m_left[key])) < 10**-8)
    for key in right.keys():
        assert np.all(np.abs(np.abs(right[key]) - np.abs(right[key])) < 10**-8)
        


def test_mdot_routine_routine(make_random_blocs):
    mps_left = make_random_blocs(20, 2)
    mps_right = make_random_blocs(20, 3)
    import mdot_routine
    from pyfhmdot.algorithm import apply_mm
    from pyfhmdot.intense.mul_mp import multiply_mp
    from copy import deepcopy
    #import numpy as np

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
        deepcopy(mps_left), deepcopy(mps_right), 8, 10**-8, True, 1, 1
    )
    # assert dw_dict["dw_one_serie"] == dw
    # for key in m_left.keys():
    #     m_left[key].transpose() == left[key]
    # for key in m_right.keys():
    #     m_right[key] == right[key]
    
    # for key in left.keys():
    #     assert np.all(np.abs(np.abs(left[key]) - np.abs(m_left[key])) < 10**-8)
    # for key in right.keys():
    #     assert np.all(np.abs(np.abs(right[key]) - np.abs(right[key])) < 10**-8)
        


    m_dst = {}
    multiply_mp(m_dst, m_left, m_right, [2], [0])
    dst = {}
    multiply_mp(dst, left, right, [2], [0])
