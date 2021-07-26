import numpy as np
from typing import Tuple

class canvas:
    def __init__(self, rangeX, rangeY, res: int):
        ar = abs(rangeX[0]-rangeX[1])/abs(rangeY[0]-rangeY[1])
        pX,pY = (int(ar*res),int(res))
        self.mapper = lambda x,y: ((rangeX[1]-rangeX[0])*(x/pX)+rangeX[0],(rangeY[1]-rangeY[0])*(y/pY)+rangeY[0])
        self.mat = np.zeros((pX,pY,3))

