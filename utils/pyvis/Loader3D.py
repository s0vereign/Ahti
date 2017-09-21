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

def Gaussian3D(x,y,z):

    return np.exp(-(x**2+y**2+z**2)/2.0)*((1/np.pi)**(3.0/4.0))


def H_0(x):

    return 1

def H_1(x):

    return 2 * x

def H_2(x):

    return (4*x**2 - 2)

def Psi_0(x):
    return (np.pi)**(-0.25) * np.exp(-x**2*0.5)

def Psi_1(x):
    return 1/np.sqrt(2) * H_1(x) * Psi_0(x)

def Psi_2(x):
    return (1/np.sqrt(2**2*2)) * H_2(x) * Psi_0(x)

def Psi3D(x,y,z):
    return Psi_0(x) * Psi_0(y) * Psi_0(z)

def main():

    nx = 200
    ny = 200
    nz = 200
    nt = 100
    dt = 0.001
    l = CLoader3D(nx, ny, nz, "../../cmake-build-default/bin/test.h5")
    d = (l.get_complex_data("/real", "/imag"))

    x = np.linspace(-6.0, 6.0, nx, endpoint=False)
    y = np.linspace(-6.0, 6.0, ny, endpoint=False)
    
    x_mesh, y_mesh = np.meshgrid(x,y)
    an = Psi3D(x_mesh, y_mesh, 0) + 0* 1j

    
    an *= np.exp(-1j * 1.5 * nt * dt)
    d = d[:,:,int(nz/2)]
    print("Maximum numerical: {}".format(np.max(np.abs(d)**2)))
    print("Maximum analytical: {}".format(np.max(np.abs(an)**2)))

    fig = plt.figure(figsize=(10,6))
    ax = fig.gca(projection='3d')
    
    surf = ax.plot_surface(x_mesh, y_mesh, np.abs(d.imag - an.imag),
                           cmap=cm.magma_r,linewidth=1,antialiased=False)

    plt.title("Time evolution 3D Harm. Osc.")
    ax.set_xlabel(r"$x \; (a.u.)$")
    ax.set_xlabel(r"$y \; (a.u.)$")
    ax.set_zlabel(r"$|\Psi|^2$")

    fig.colorbar(surf, shrink=0.5, aspect=5)


    plt.show()

if __name__ == "__main__":
    main()