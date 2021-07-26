import sympy
import matplotlib.pyplot as plt
from math import log
import numpy as np 
import cmath
from plotter import canvas
from PIL import Image
from progressbar import ProgressBar
from multiprocessing import Process



if __name__ == '__main__': 

    
    pbar = ProgressBar()
    plot = canvas((-2,1),(-1.5,1.5),20000)

    for i in pbar(range(0,np.size(plot.mat,0))):
        for j in range(np.size(plot.mat,1)):
            x,y = plot.mapper(i,j)
            z = 0
            maxIter = 255
            for iter in range(maxIter):
                z = z**2 + complex(x,y)
                if (z*z.conjugate()).real > 4:
                    plot.mat[i][j][0]=iter
                    plot.mat[i][j][1]=iter
                    plot.mat[i][j][2]=iter
                    break


    img = Image.fromarray(np.rot90((np.uint8(plot.mat))),mode="RGB")
    img.save("large_format.png")
    img.show()