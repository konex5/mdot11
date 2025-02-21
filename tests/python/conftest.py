import pytest
import numpy as np


@pytest.fixture
def make_mps():
    def _make_mps(d=None):
        i = np.random.randint(100)
        if d is None:
            d = np.random.randint(5)
        j = np.random.randint(100)
        mps = np.random.random.rand(i * d * j, dtype="u8").reshape(i, d, j)
        return mps

    return _make_mps


def mps(make_mps):
    return make_mps()
