import pytest

@pytest.fixture
def make_list_operator_name():
    def _make_list_operator_name():
        return ['sh-id','sh-sp','sh-sm','sh-sx','sh-sz'], ['sh-id-cplx','sh-sy']

    return _make_list_operator_name

@pytest.fixture
def make_list_real_operator_name(make_list_operator_name):
    return make_list_operator_name()[0]

@pytest.fixture
def make_list_cplx_operator_name(make_list_operator_name):
    return make_list_operator_name()[1]
