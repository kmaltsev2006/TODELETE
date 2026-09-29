import numpy as np
from sympy import Matrix

A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
M = len(A)


def txt_to_mtx(s, n):
    s = s.upper().replace(" ", "")
    while len(s) % n != 0:
        s += "X"
    idx = [A.index(c) for c in s]
    return np.array(idx).reshape(-1, n)


def mtx_to_txt(mtx):
    return "".join(A[int(i)] for i in mtx.flatten())


def get_inv(mtx, m):
    return np.array(Matrix(mtx).inv_mod(m)).astype(int)

def enc(s, k):
    b = txt_to_mtx(s, len(k))
    res = [np.dot(k, x) % M for x in b]
    return mtx_to_txt(np.array(res))


def dec(s, k):
    b = txt_to_mtx(s, len(k))
    k_inv = get_inv(k, M)
    res = [np.dot(k_inv, x) % M for x in b]
    return mtx_to_txt(np.array(res))


if __name__ == "__main__":
    K = np.array([[6, 24, 1], [13, 16, 10], [20, 17, 15]])
    msg = "HELLOWORLD"

    res_enc = enc(msg, K)
    print(res_enc)

    res_dec = dec(res_enc, K)
    print(res_dec)
