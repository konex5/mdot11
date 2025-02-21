import pytest


def test_mdot_routine_mm_to_theta_no_gate(make_random_blocs):
    mps_left = make_random_blocs(20, 4)
    mps_right = make_random_blocs(20, 4)
    import mdot_routine

    dst = {}
    a = mdot_routine.mm_to_theta_no_gate(mps_left, mps_right, True)
    pass


def test_mdot_routine_mm_to_theta_no_gate_compare(make_random_blocs):
    mps_left = make_random_blocs(20, 4)
    mps_right = make_random_blocs(20, 4)
    import mdot_routine
    from pyfhmdot.routine.interface import mm_to_theta_no_gate
    dst = {}
    mm_to_theta_no_gate(dst, mps_left, mps_right, conserve_left_right=True)
    a = mdot_routine.mm_to_theta_no_gate(mps_left, mps_right, True)
    pass


def test_mdot_routine_routine(make_random_blocs):
    mps_left = make_random_blocs(20, 2)
    mps_right = make_random_blocs(20, 1)
    import mdot_routine
    from pyfhmdot.algorithm import apply_mm
    from copy import deepcopy
    dw_dict = {"dw_one_serie":0}
    m_left, m_right = apply_mm(deepcopy(mps_left), deepcopy(mps_right),dw_dict,8,True,10**-8,is_um=True,conserve_left_right_before=False,direction_right=1)
    left,right,dw = mdot_routine.apply_mm(deepcopy(mps_left), deepcopy(mps_right), 8,True,10**-8,1,1)
    pass
