import numpy as np
import matplotlib.pyplot as plt
import matplotlib


matplotlib.rcParams['text.usetex'] = True

def prop_time(psi0, nt, dt, V, x):

    psi = psi0(x+0*1j)
    dp = 2*np.pi/(x[-1] - x[0])
    n = x.size
    p0 = -x.size/2 * dp
    p1 = x.size/2 * dp
    p = np.zeros(n)
    for i in range(0, int(n/2-1)):
        p[i] =  i * dp

    for i in range(int(n/2),n):
        p[i] = -(n/2)*dp + (i-n/2)*dp


    #p = np.linspace(p0,p1,n)

    for i in range(0, nt):
        psi *= np.exp(- 1j * dt/2 * V(x))
        psi_ft = np.fft.fft(psi)
        psi_ft *= np.exp(- 1j * p**2/2 * dt)
        psi = np.fft.ifft(psi_ft)
        psi *= np.exp(- 1j * dt/2 * V(x))



    return psi

def main():

    n = 3000
    x = np.linspace(-10.0,10.0,n)
    psi = lambda x : 0.7511255444649425 * np.exp(-x**2/2.0)
    V = lambda x:  0.5 * x**2
    nt = 100
    dt = 0.001
    print(x[int(n/2)+1:][0])
    res = prop_time(psi, nt, dt, V, x)
    psi_an = psi(x) * np.exp(-1j * 0.5 * dt * nt)

    plt.xlabel(r"Location ($a.u.$)",size=14)
    plt.ylabel(r"$\psi$ ($a.u.^{-1}$)",size=14)
    plt.plot(x,res.imag, label="Real numericals")
    plt.plot(x,res.real, label="Imag numerical")
    plt.plot(x,psi_an.real, label="Real analytical")
    plt.plot(x,psi_an.imag, label="Imag analytical")
    plt.legend(loc='best')
    plt.show()

if __name__ == '__main__':
    main()