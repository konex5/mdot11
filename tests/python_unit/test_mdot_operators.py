import pytest


def test_single_operator():
    import mdot_operators
    from pyfhmdot.models.pyoperators import single_operator
    from numpy import all

    operator_names = [
        "sh_id_no",
        "sh_sz_no",
        "sh_sx_no",
        "sh_sp_no",
        "sh_sm_no",
        "sh_id_u1",
        "sh_sz_u1",
        "sh_sx_u1",  # , "sh_sp_u1", "sh_sm_u1"
    ]
    for name in operator_names:
        pyop = single_operator(name, coef=1)
        cppop = mdot_operators.single_operator_real(name)
        for key in pyop.keys():
            assert all(pyop[key] == cppop[key])

    operator_names = ["sh_id-cplx_no", "sh_sy_no", "sh_id-cplx_u1", "sh_sy_u1"]

    for name in operator_names:
        pyop = single_operator(name, coef=1)
        cppop = mdot_operators.single_operator_cplx(name)
        for key in pyop.keys():
            assert all(pyop[key] == cppop[key])
