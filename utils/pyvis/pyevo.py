import numpy as np
import matplotlib.pyplot as plt


gc = lambda x: 0.7511255444649425 * np.exp(- x**2 / 2)

x = np.linspace(-10.0, 10.0)

psi = gc(x)

psi_c = np.fft.ftt(psi)

plt.plot(psi)
plt.show()