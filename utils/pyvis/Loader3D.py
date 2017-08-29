from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np
import h5py

class Loader3D:

    def __init__(self, nx, ny, nz, loc):
        self.nx = nx
        self.ny = ny
        self.nz = nz
        self.file = 0
        self.loc = loc

    def get_dset(self,id):

        data = 0

        try:
            self.file = h5py.File(self.loc,"r")
        except:
            print("Error! File does not exist")
            exit()

        try:
            data = np.array(self.file[id])
        except:
            print("Error! DatasetID not found!")
            self.file.close()
        return data

class CLoader3D(Loader3D):

    def get_complex_data(self, idr, idi):

        data = self.get_dset(idr).reshape((self.nx,self.ny,self.nz)) +\
               1j * self.get_dset(idi).reshape((self.nx, self.ny, self.nz))

        return data

def main():

    l = CLoader3D(500, 500, 500, "../../cmake-build-debug/bin/test.h5")
    d = (l.get_complex_data("/real", "/imag"))
    x = np.arange(-6.0, 6.0, 12.0/500)
    y = np.arange(-6.0, 6.0, 12.0/500)
    X, Y = np.meshgrid(x,y)
    print(d.shape)
    d = d[:,:,249]
    print(d)

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(X,Y, np.abs(d)**2, cmap=cm.magma_r,linewidth=1,antialiased=False)

    fig.colorbar(surf, shrink=0.5, aspect=5)

    #ax = fig.gca()
    #ax.plot(x, np.abs(d[:][249])**2)

    plt.show()

if __name__ == "__main__":
    main()