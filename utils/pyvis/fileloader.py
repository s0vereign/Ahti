import numpy as np
import matplotlib.pyplot as plt
import h5py
import time
import progressbar
import sys

def load_timestep(filepath,nt,dtype="wf"):
    """
    Load a timestep from a result file
    and returns it as a complex numpy array.
    """
    print("Using dtype={}".format(dtype))
    file = h5py.File(filepath)
    if dtype=="wf":
        rl = "/dset"+str(nt)+"real"
        im = "/dset"+str(nt)+"imag"
    elif dtype=="co":
        rl = "/dreal"
        im = "/dimag"
    else:
        print("Error unsupported filetype!")
        file.close()
        sys.exit("dtype not recognized")
        return -1
    if (rl in file) and (im in file):
        imag = np.array(file[im])
        real = np.array(file[rl])
        res = real + 1j * imag
        file.close()
        return res
    else:
        print("Error timestep "+str(nt)+" not found!")
        file.close()
        sys.exit("Data does not exist or is corrupted")
        return -1



