from numpy import dtype
from fhm import is_floating_precision

import numpy as np


def test_precision_library():
    precision = is_floating_precision()
    assert isinstance(precision, bool)


def test_precision():
    for dt in [np.dtype(_) for _ in ["float32", "float64", "complex64", "complex128"]]:
        arr = np.array([1, 2, 3], dtype=dt)
        # assert is_complex(arr) == np.iscomplexobj(arr)
        # assert is_float(arr) == (arr.dtype in [np.float32, np.complex64])
