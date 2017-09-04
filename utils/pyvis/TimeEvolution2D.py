from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np


class TimeEvolutionOperator2D:

    def __init__(self,E,dt):
        self.E = E
        self.dt = dt

    def ev(self, n, data):

        return np.exp(-1j*n*self.dt*self.E)*data

gauss = lambda x: np.exp(-0.5*x)*((1/np.pi)**0.25)**2

gauss2D = lambda x, y, gauss: gauss(x) * gauss(y)

def main():

    x = np.linspace(-6,6,1000)
    y = np.linspace(-6,6,1000)

    X,Y = np.meshgrid(x,y)

    grid = gauss(X**2+Y**2)
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    U = TimeEvolutionOperator2D(1.0, 0.001)
    grid = U.ev(20, grid)

    surf = ax.plot_surface(X,Y,grid.imag,cmap=cm.magma_r,linewidth=1,antialiased=False)
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()


if __name__ == "__main__":
    main()