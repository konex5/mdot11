import pytest


@pytest.fixture
def make_gate():
    from numpy import array

    old_theta = {
        (0, 0, 0, 0): array([[[[0.99483226]]]]),
        (0, 0, 1, 1): array([[[[0.99226175, 0.0], [0.0, 1.00780536]]]]),
        (0, 0, 2, 2): array([[[[1.00520133]]]]),
        (0, 1, 0, 1): array([[[[-0.00257052, 0.0]], [[0.0, -0.00261078]]]]),
        (0, 1, 1, 2): array([[[[0.0], [-0.00260404]], [[-0.00260404], [0.0]]]]),
        (0, 2, 0, 2): array([[[[6.74591518e-06]]]]),
        (1, 0, 1, 0): array([[[[-0.00257052], [0.0]]], [[[0.0], [-0.00261078]]]]),
        (1, 0, 2, 1): array([[[[0.0, -0.00260404]]], [[[-0.00260404, 0.0]]]]),
        (1, 1, 0, 0): array([[[[0.99226175]], [[0.0]]], [[[0.0]], [[1.00780536]]]]),
        (1, 1, 1, 1): array(
            [
                [
                    [[9.79488739e-01, 0.00000000e00], [0.00000000e00, 1.00520133e00]],
                    [[0.00000000e00, 6.74591518e-06], [0.00000000e00, 0.00000000e00]],
                ],
                [
                    [[0.00000000e00, 0.00000000e00], [6.74591518e-06, 0.00000000e00]],
                    [[1.00520133e00, 0.00000000e00], [0.00000000e00, 1.01041614e00]],
                ],
            ]
        ),
        (1, 1, 2, 2): array([[[[0.99226175]], [[0.0]]], [[[0.0]], [[1.00780536]]]]),
        (1, 2, 0, 1): array([[[[0.0, -0.00260404]]], [[[-0.00260404, 0.0]]]]),
        (1, 2, 1, 2): array([[[[-0.00257052], [0.0]]], [[[0.0], [-0.00261078]]]]),
        (2, 0, 2, 0): array([[[[6.74591518e-06]]]]),
        (2, 1, 1, 0): array([[[[0.0], [-0.00260404]], [[-0.00260404], [0.0]]]]),
        (2, 1, 2, 1): array([[[[-0.00257052, 0.0]], [[0.0, -0.00261078]]]]),
        (2, 2, 0, 0): array([[[[1.00520133]]]]),
        (2, 2, 1, 1): array([[[[0.99226175, 0.0], [0.0, 1.00780536]]]]),
        (2, 2, 2, 2): array([[[[0.99483226]]]]),
    }

    new_theta = {
        (0, 0, 0, 0): array([[[[0.99483226]]]]),
        (0, 0, 1, 1): array([[[[1.00780536, 0.0], [0.0, 0.99226175]]]]),
        (0, 0, 2, 2): array([[[[1.00520133]]]]),
        (0, 1, 0, 1): array([[[[-0.00261078, 0.0]], [[0.0, -0.00257052]]]]),
        (0, 1, 1, 2): array([[[[0.0], [-0.00260404]], [[-0.00260404], [0.0]]]]),
        (0, 2, 0, 2): array([[[[6.74591518e-06]]]]),
        (1, 0, 1, 0): array([[[[-0.00261078], [0.0]]], [[[0.0], [-0.00257052]]]]),
        (1, 0, 2, 1): array([[[[0.0, -0.00260404]]], [[[-0.00260404, 0.0]]]]),
        (1, 1, 0, 0): array([[[[1.00780536]], [[0.0]]], [[[0.0]], [[0.99226175]]]]),
        (1, 1, 1, 1): array(
            [
                [
                    [[1.01041614e00, 0.00000000e00], [0.00000000e00, 1.00520133e00]],
                    [[0.00000000e00, 6.74591518e-06], [0.00000000e00, 0.00000000e00]],
                ],
                [
                    [[0.00000000e00, 0.00000000e00], [6.74591518e-06, 0.00000000e00]],
                    [[1.00520133e00, 0.00000000e00], [0.00000000e00, 9.79488739e-01]],
                ],
            ]
        ),
        (1, 1, 2, 2): array([[[[1.00780536]], [[0.0]]], [[[0.0]], [[0.99226175]]]]),
        (1, 2, 0, 1): array([[[[0.0, -0.00260404]]], [[[-0.00260404, 0.0]]]]),
        (1, 2, 1, 2): array([[[[-0.00261078], [0.0]]], [[[0.0], [-0.00257052]]]]),
        (2, 0, 2, 0): array([[[[6.74591518e-06]]]]),
        (2, 1, 1, 0): array([[[[0.0], [-0.00260404]], [[-0.00260404], [0.0]]]]),
        (2, 1, 2, 1): array([[[[-0.00261078, 0.0]], [[0.0, -0.00257052]]]]),
        (2, 2, 0, 0): array([[[[1.00520133]]]]),
        (2, 2, 1, 1): array([[[[1.00780536, 0.0], [0.0, 0.99226175]]]]),
        (2, 2, 2, 2): array([[[[0.99483226]]]]),
    }

    # from pyfhmdot.initialize import create_hamiltonian_gates

    # new_theta = create_hamiltonian_gates(
    #     "sh_xxz-hz_u1",
    #     {"Jxy": 0.25, "Jz": 0.5, "hz": 1.5},  # 1/4.*1, 1/4.*2, 1/2.*3
    #     4,
    #     dbeta=0.025,
    #     is_dgate=True,
    #     in_group=True,
    # )[0][1]
    # old_theta = {}
    # for key in new_theta:
    #     old_theta[key] = new_theta[key][::-1, ::-1, ::-1, ::-1]

    return lambda: new_theta


@pytest.fixture
def make_env_m():
    from numpy import array

    def create_env_m(mps_left, mps_right):
        from pyfhmdot.intense.mul_mp import multiply_mp, permute_blocs

        new_dummy_env = {
            (0, 0, 0, 0, 0, 0): array([[[[[[-5.0]]]]]]),
            (0, 0, 0, 0, 1, 1): array([[[[[[-3.0]]]]]]),
            (0, 0, 0, 1, 0, 1): array([[[[[[2.0]]]]]]),
            (0, 0, 1, 0, 1, 0): array([[[[[[2.0]]]]]]),
            (0, 0, 1, 1, 0, 0): array([[[[[[-7.0]]]]]]),
            (0, 0, 1, 1, 1, 1): array([[[[[[3.0]]]]]]),
            (0, 1, 0, 1, 0, 0): array([[[[[[2.0]]]]]]),
            (0, 1, 0, 1, 1, 1): array([[[[[[2.0]]]]]]),
            (1, 0, 1, 0, 0, 0): array([[[[[[2.0]]]]]]),
            (1, 0, 1, 0, 1, 1): array([[[[[[2.0]]]]]]),
            (1, 1, 0, 0, 0, 0): array([[[[[[-3.0]]]]]]),
            (1, 1, 0, 0, 1, 1): array([[[[[[-1.0]]]]]]),
            (1, 1, 0, 1, 0, 1): array([[[[[[2.0]]]]]]),
            (1, 1, 1, 0, 1, 0): array([[[[[[2.0]]]]]]),
            (1, 1, 1, 1, 0, 0): array([[[[[[3.0]]]]]]),
            (1, 1, 1, 1, 1, 1): array([[[[[[13.0]]]]]]),
        }
        tmp = {}
        multiply_mp(tmp, mps_left, mps_left, [0], [0])
        tmp_tmp = {}
        multiply_mp(tmp_tmp, tmp, new_dummy_env, [0, 2], [0, 1])
        tmp.clear()
        multiply_mp(tmp, mps_right, mps_right, [2], [2])
        dst = {}
        multiply_mp(dst, tmp_tmp, tmp, [4, 5], [1, 3])
        dst_dst = {}
        permute_blocs(dst_dst, dst, [(0, 2, 4, 1, 3, 5), (0, 1, 2, 3, 4, 5)])
        return dst_dst

    return create_env_m


@pytest.fixture
def make_env_mm():
    from numpy import array

    def create_env_m(mps_left, mps_right):
        from pyfhmdot.intense.mul_mp import multiply_mp, permute_blocs

        new_dummy_env = {
            (0, 0, 0, 0, 0, 0, 0, 0): array([[[[[[[[-6.0]]]]]]]]),
            (0, 0, 0, 0, 0, 0, 1, 1): array([[[[[[[[-4.0]]]]]]]]),
            (0, 0, 0, 0, 0, 1, 0, 1): array([[[[[[[[2.0]]]]]]]]),
            (0, 0, 0, 0, 1, 0, 1, 0): array([[[[[[[[2.0]]]]]]]]),
            (0, 0, 0, 0, 1, 1, 0, 0): array([[[[[[[[-8.0]]]]]]]]),
            (0, 0, 0, 0, 1, 1, 1, 1): array([[[[[[[[2.0]]]]]]]]),
            (0, 0, 0, 1, 1, 0, 0, 0): array([[[[[[[[2.0]]]]]]]]),
            (0, 0, 0, 1, 1, 0, 1, 1): array([[[[[[[[2.0]]]]]]]]),
            (0, 0, 1, 0, 0, 1, 0, 0): array([[[[[[[[2.0]]]]]]]]),
            (0, 0, 1, 0, 0, 1, 1, 1): array([[[[[[[[2.0]]]]]]]]),
            (0, 0, 1, 1, 0, 0, 0, 0): array([[[[[[[[-8.0]]]]]]]]),
            (0, 0, 1, 1, 0, 0, 1, 1): array([[[[[[[[-6.0]]]]]]]]),
            (0, 0, 1, 1, 0, 1, 0, 1): array([[[[[[[[2.0]]]]]]]]),
            (0, 0, 1, 1, 1, 0, 1, 0): array([[[[[[[[2.0]]]]]]]]),
            (0, 0, 1, 1, 1, 1, 0, 0): array([[[[[[[[-2.0]]]]]]]]),
            (0, 0, 1, 1, 1, 1, 1, 1): array([[[[[[[[8.0]]]]]]]]),
            (0, 1, 0, 1, 0, 0, 0, 0): array([[[[[[[[2.0]]]]]]]]),
            (0, 1, 0, 1, 0, 0, 1, 1): array([[[[[[[[2.0]]]]]]]]),
            (0, 1, 0, 1, 1, 1, 0, 0): array([[[[[[[[2.0]]]]]]]]),
            (0, 1, 0, 1, 1, 1, 1, 1): array([[[[[[[[2.0]]]]]]]]),
            (1, 0, 1, 0, 0, 0, 0, 0): array([[[[[[[[2.0]]]]]]]]),
            (1, 0, 1, 0, 0, 0, 1, 1): array([[[[[[[[2.0]]]]]]]]),
            (1, 0, 1, 0, 1, 1, 0, 0): array([[[[[[[[2.0]]]]]]]]),
            (1, 0, 1, 0, 1, 1, 1, 1): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 0, 0, 0, 0, 0, 0): array([[[[[[[[-4.0]]]]]]]]),
            (1, 1, 0, 0, 0, 0, 1, 1): array([[[[[[[[-2.0]]]]]]]]),
            (1, 1, 0, 0, 0, 1, 0, 1): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 0, 0, 1, 0, 1, 0): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 0, 0, 1, 1, 0, 0): array([[[[[[[[-6.0]]]]]]]]),
            (1, 1, 0, 0, 1, 1, 1, 1): array([[[[[[[[4.0]]]]]]]]),
            (1, 1, 0, 1, 1, 0, 0, 0): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 0, 1, 1, 0, 1, 1): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 1, 0, 0, 1, 0, 0): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 1, 0, 0, 1, 1, 1): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 1, 1, 0, 0, 0, 0): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 1, 1, 0, 0, 1, 1): array([[[[[[[[4.0]]]]]]]]),
            (1, 1, 1, 1, 0, 1, 0, 1): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 1, 1, 1, 0, 1, 0): array([[[[[[[[2.0]]]]]]]]),
            (1, 1, 1, 1, 1, 1, 0, 0): array([[[[[[[[8.0]]]]]]]]),
            (1, 1, 1, 1, 1, 1, 1, 1): array([[[[[[[[18.0]]]]]]]]),
        }

        tmp = {}
        multiply_mp(tmp, mps_left, mps_left, [0], [0])
        tmp_tmp = {}
        multiply_mp(tmp_tmp, tmp, new_dummy_env, [0, 2], [0, 1])
        tmp.clear()
        multiply_mp(tmp, mps_right, mps_right, [2], [2])
        dst = {}
        multiply_mp(dst, tmp_tmp, tmp, [6, 7], [1, 3])
        dst_dst = {}
        permute_blocs(
            dst_dst, dst, [(0, 2, 4, 6, 1, 3, 5, 7), (0, 1, 2, 3, 4, 5, 6, 7)]
        )
        return dst_dst

    return create_env_m


@pytest.fixture
def make_random_blocs():
    def create_random_blocs(chi, max_index=3):
        def create_random_matrix(chi, d):
            from numpy.random import random

            return random(chi * d * chi).reshape(chi, d, chi)

        blocs = {}  # sh
        for i in range(max_index):
            for j in range(max_index):
                blocs[(i, 0, j)] = create_random_matrix(chi, d=1)
                blocs[(i, 1, j)] = create_random_matrix(chi, d=2)
                blocs[(i, 2, j)] = create_random_matrix(chi, d=1)
        return blocs

    return create_random_blocs


@pytest.fixture
def make_random_mps():
    def create_random_mps(chi, max_index=3):
        def create_random_matrix(chi, d):
            from numpy.random import random

            return random(chi * d * chi).reshape(chi, d, chi)

        blocs = {}  # sh
        for i in range(max_index):
            for j in range(max_index):
                blocs[(i, 0, j)] = create_random_matrix(chi, d=1)
                blocs[(i, 1, j)] = create_random_matrix(chi, d=1)
        return blocs

    return create_random_mps
