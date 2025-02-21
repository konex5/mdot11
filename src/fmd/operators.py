import numpy as np


def single_operator_real(name: str):
    if name == "sh-id":
        return np.array([1, 0, 0, 1], dtype="float64").reshape(2, 2)
    elif name == "sh-sm":
        return np.array([0, 0, 1, 0], dtype="float64").reshape(2, 2)
    elif name == "sh-sp":
        return np.array([0, 1, 0, 0], dtype="float64").reshape(2, 2)
    elif name == "sh-sx":
        return np.array([0, 1, 1, 0], dtype="float64").reshape(2, 2)
    elif name == "sh-sz":
        return np.array([1, 0, 0, -1], dtype="float64").reshape(2, 2)
    else:
        raise (
            ValueError(
                "The single operator {name} is not available.\n"
                + "\t\t- Available operators are sh-id, sh-sp, sh-sm, sh-sx, sh-sz, ..."
            )
        )


def single_operator_cplx(name: str):
    if name == "sh-id":
        return np.array([1, 0, 0, 1], dtype="float64").reshape(2, 2)
    elif name == "sh-sy":
        return np.array([0, -1j, 1j, 0], dtype="float64").reshape(2, 2)  # to check
    else:
        raise (
            ValueError(
                "The single operator {name} is not available.\n"
                + "\t\t- Available operators are sh-id, sh-sp, sh-sm, sh-sx, sh-sz, ..."
            )
        )
