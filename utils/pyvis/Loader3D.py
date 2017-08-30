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

        data = self.get_dset(idr).reshape((self.nx, self.ny, self.nz)) +\
               1j * self.get_dset(idi).reshape((self.nx, self.ny, self.nz))
        print("Data has shape" + str(data.shape))
        return data

def main():

    nx = 300
    ny = 300
    nz = 300
    l = CLoader3D(nx, ny, nz, "../../cmake-build-debug/bin/test.h5")
    d = (l.get_complex_data("/real", "/imag"))
    x = np.arange(-6.0, 6.0, 12.0/nx)
    y = np.arange(-6.0, 6.0, 12.0/ny)
    x_mesh, y_mesh = np.meshgrid(x,y)
    print(x_mesh.shape)

#    x_mesh.reshape((nx, ny))
#    y_mesh.reshape((nx, ny))


    d = d[:,:,int(nz/2)]
    print(d.shape)

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    surf = ax.plot_surface(x_mesh, y_mesh, d.imag, cmap=cm.magma_r,linewidth=1,antialiased=False)

    fig.colorbar(surf, shrink=0.5, aspect=5)


    plt.show()

if __name__ == "__main__":
    main()