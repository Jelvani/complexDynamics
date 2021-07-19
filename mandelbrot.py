import sympy
import matplotlib.pyplot as plt
from math import log
import numpy as np 
import cmath

#range of x and y axis
minX, maxX = (-1,1)
minY, maxY = (-1,1)

#dimension of canvas
ar = abs(minX-maxX)/abs(minY-maxY)
size = 500
pX,pY = (int(ar*size),int(size))


#takes in numpy index and converts to decimal
mapper2 = lambda x,y: ((maxX-minX)*(x/pX)+minX,(maxY-minY)*(y/pY)+minY)

mat = np.zeros((pX,pY))


for i in range(pX):
    for j in range(pY):
        x,y = mapper2(i,j)
        
        z = 0
        iter = 0
        while(True):
            iter+=1
            z = z**2 + complex(x,y)
            if (z*z.conjugate()).real > 100:
                mat[i][j]=iter
                break
            if iter > 100:
                break
       
        

plt.matshow(mat, cmap=plt.cm.afmhot)

plt.show()
