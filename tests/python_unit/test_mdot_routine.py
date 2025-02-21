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
    mps_left = make_random_blocs(20, 4)
    mps_right = make_random_blocs(20, 4)
    import mdot_routine
    dst = {}
    # routine(dst, mps_left, mps_right, conserve_left_right=True)
    a = mdot_routine.routine(mps_left, mps_right, True)
    pass


