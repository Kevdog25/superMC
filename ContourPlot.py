from numpy import *
import matplotlib.pyplot as plt 
import sys

data = loadtxt(sys.argv[1])
plt.imshow(data)
plt.savefig('Transverse Entropy Dist')