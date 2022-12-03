import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

mpl.rcParams['legend.fontsize'] = 10
mpl.rcParams["figure.figsize"] = (20,20)

fig = plt.figure()
ax = fig.gca(projection='3d')

np.linspace(0, 100, 100)
x = np.linspace(0, 2000, 50)
y = np.linspace(0, 2000, 50)
x, y = np.meshgrid(x, y)
# z = 0.000000166535065*x*y**3
z = 0.00000002211524*x*y**3

X = []
Y = []
Z = []
with open("src/time_complexity/complexity.data", encoding = 'utf-8') as file:
    count = 0
    for line in file:
            data = line.split()
            count+=1
            if count%1 == 0:
                X.append(float(data[0]))
                Y.append(float(data[1]))
                Z.append(float(data[2])*1000000)

X = np.array(X)
Y = np.array(Y)
Z = np.array(Z)

ax.plot(X, Y, Z, '.', label='measured time', color="red")
ax.plot_surface(x, y, z, cmap='viridis')
ax.legend()

ax.set_xlabel('vértices')
ax.set_ylabel('arestas')
ax.set_zlabel('tempo (milisegundos)')
ax.yaxis._axinfo['label']['space_factor'] = 3.0

plt.show()