import numpy as np
import matplotlib.pyplot as plt
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

    def get_complex_data(self,idr,idi):

        data = (self.get_dset(idr) + 1j*  self.get_dset(idi)).reshape((self.nx,self.ny))
        print("Max = {}".format(np.max(np.abs(data)**2)))
        return data

def main():

    l = CLoader2D(1000,1000,"../../cmake-build-debug_tests/bin/test.h5")
    d = l.get_complex_data("/real","/imag")
    x = np.linspace(-6.0,6.0,500,retstep=True)
    plt.imshow(np.abs(d),interpolation="nearest")
    plt.colorbar()
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()