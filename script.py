from subprocess import call
from progress.bar import PixelBar
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
import sys
mpl.rcParams['text.usetex'] == True


angles = np.linspace(0, 6.28, 360)

try:
    if sys.argv[1] == 'count':
        open("param_file", "w").close()
        with PixelBar('First calculation...', max=len(angles)) as bar:
            for angle in angles:
                call(["./a.out", str(1000), str(angle)])
                bar.next()
except IndexError:
    pass

ifile = open("param_file", "r")
y = np.array([])
for line in ifile:
    y = np.append(y, float(line.split()[1]))
ifile.close()



plt.scatter(angles, y)

plt.xlabel(r'$\varphi, rad$')
plt.ylabel(r'$v_{fin}$')
plt.yticks(np.linspace(np.min(y), np.max(y), 10))
plt.show()

