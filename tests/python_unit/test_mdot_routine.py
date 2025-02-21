import pytest


def test_mdot_routine_mm_to_theta_no_gate(make_random_blocs):
    mps_left = make_random_blocs(20, 4)
    mps_right = make_random_blocs(20, 4)
    import mdot_routine

    dst = {}
    mdot_routine.mm_to_theta_no_gate(dst, mps_left, mps_right, True)
    pass
