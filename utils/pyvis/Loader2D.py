from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np
import h5py


class Loader2D:
    
    def __init__(self,nx,ny,loc):
        
        self.nx = nx
        self.ny = ny
        self.loc = loc
        self.file = 0
       
            
    def get_dset(self, id):
        
        data = 0
        try:
            self.file = h5py.File(self.loc,"r")
        except:
            print("Error! File does not exist!")
            exit()
        try:
            data = np.array(self.file[id])
        except:
            print("Error! DatasetID not found!")
            self.file.close()
        return data


class CLoader2D(Loader2D):

    def get_complex_data(self, idr, idi):

        data = self.get_dset(idr).reshape((self.nx, self.ny)) + 1j * self.get_dset(idi).reshape((self.nx, self.ny))

        return data



def main():

    l = CLoader2D(1000,1000,"../../cmake-build-default/bin/first.h5")
    d = l.get_complex_data("/real","/imag")
    x = np.arange(-6.0,6.0,12.0/1000)
    y = np.arange(-6.0,6.0,12.0/1000)
    gaussian = lambda x: 0.7511255444649425*np.exp(-0.5*x**2)
    psi_1 = lambda x,g: g(x) * 1/np.sqrt(2) * 2 * x
    X,Y = np.meshgrid(x,y)

    analytic = gaussian(X) * gaussian(Y)
    analytic = np.complex128(analytic)
    analytic *= np.exp(-1j *0.0001 * 1000)

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    #ax = fig.gca()
    surf = ax.plot_surface(X,Y, np.abs(analytic.imag - d.imag ),cmap=cm.magma_r,linewidth=1,antialiased=False)

    #im = plt.imshow(d.real - analytic.real, )
    fig.colorbar(surf, shrink=0.5, aspect=5)
    ax.set_title(r"Time evolution for system $ V(x,y) = \frac{1}{2} (x^2+y^2)$ for y = 0")
    ax.set_xlabel(r"x $(a.u.)$")
    ax.set_ylabel(r"$\Psi$ $(a.u.)$")
    ax.set_zlabel(r"$|\psi|^2$")
    #plt.legend(loc='best')

    plt.show()
if __name__ == "__main__":
    main()