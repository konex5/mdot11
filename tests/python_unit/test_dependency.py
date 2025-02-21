import pytest

def test_mdot_operators_dep():
    from mdot_operators import single_operator_real, single_operator_blocs_real
    
    _ = single_operator_real()
    _ = single_operator_blocs_real()