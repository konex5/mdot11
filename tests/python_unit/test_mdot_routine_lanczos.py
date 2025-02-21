from copy import deepcopy
import pytest


def test_mdot_routine_apply_mm_empty():
    import mdot_routine

    mdot_routine.apply_mm({}, {}, 8, 10**-8, True, 1, 1)


def test_mdot_routine_lanczos_m(make_random_mps, make_env_m):
    mps_left = make_random_mps(20, 2)
    mps_right = make_random_mps(20, 2)
    mps_middle = make_random_mps(20, 2)
    env_bloc = make_env_m(mps_left, mps_right)

    import mdot_routine

    mdot_routine.minimize_lanczos_on_m(env_bloc, mps_middle, 3, 10**-6)

    pass
