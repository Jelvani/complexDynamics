import sympy
import matplotlib.pyplot as plt
from math import log
import numpy as np 
import cmath
from progressbar import ProgressBar

'''
z_n+1 = z^2 + C 

'''

'''
l = list(sympy.primerange(0, 20))

l2 = [1/log(y,10) for y in l]
plt.plot(l2, l,linestyle='--', marker='o', color='b')
plt.ylabel('Primes')

plt.show()
'''
#my julia: (-0.235 - 0.4379i)^0.65
#range of x and y axis
minX, maxX = (-1.5,1.5)
minY, maxY = (-1.5,1.5)

#dimension of canvas
ar = abs(minX-maxX)/abs(minY-maxY)
size = 2000
pX,pY = (int(ar*size),int(size))


#takes in a coordinate and returns index of numpy grid
#mapper1 = lambda x,y: ((pX/gX)*x+pX/2,(pY/gY)*y+pY/2)

#takes in numpy index and converts to decimal
mapper2 = lambda x,y: ((maxX-minX)*(x/pX)+minX,(maxY-minY)*(y/pY)+minY)

mat = np.zeros((pX,pY))

pbar = ProgressBar()

for i in pbar(range(pX)):
    for j in range(pY):
        x,y = mapper2(i,j)
        
        c = complex(-0.4,-0.59)
        iter = 0
        z = complex(x,y)
        while(True):
            iter+=1
            z = z**2 + c
            if (z*z.conjugate()).real > 100:
                mat[i][j]=iter
                break
            if iter > 255:
                break
       
        


plt.matshow(np.rot90(mat,axes=(-2,-1)), cmap=plt.cm.afmhot)
plt.savefig('testing.png',dpi=1200, bbox_inches='tight', pad_inches=0)
plt.show()
