import numpy as np
import matplotlib.pyplot as plt


def fft_mcoeff(psi, x, ind0):
    """

    :param psi:
    :param x:
    :param ind0:
    :return:
    """
    ind_s = ind0 - (x.size/2 + 1)
    res = np.zeros(x.size)
    for i in range(0, res.size):

        for j in range(0, x.size):

            res[i] += psi(x[j]) * np.exp(2*np.pi*1j * ind_s * )

psi = lambda x: 0.7511255444649425 * np.exp(- x**2 / 2)

x = np.linspace(-10.0, 10.0)