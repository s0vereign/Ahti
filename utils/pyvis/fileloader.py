import numpy as np
import matplotlib.pyplot as plt
import h5py
import time
import progressbar
import sys

def load_timestep(filepath,nt,t0=0,):
    """
    Load a timestep from a result file
    and returns it as a complex numpy array.
    """

    file = h5py.File(filepath)
    rl = "/dset"+str(nt)+"real"
    im = "/dset"+str(nt)+"imag"
    if (rl in file) and (im in file):
        imag = np.array(file[rl])
        real = np.array(file[im])
        res = real + 1j * imag
        file.close()
        return res
    else:
        print("Error timestep "+str(nt)+" not found!")
        file.close()
        sys.exit("Data does not exist or is corrupted")
        return -1



