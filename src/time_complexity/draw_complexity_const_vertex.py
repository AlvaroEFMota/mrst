import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

x2d_fixed_vertex = []
y2d_fixed_vertex = []
n_vertices = 8000
with open("src/time_complexity/vertex8000.data", encoding = 'utf-8') as file:
    for line in file:
            data = line.split()
            if (int(data[0]) == n_vertices):
                x2d_fixed_vertex.append(float(data[1]))
                y2d_fixed_vertex.append(float(data[2]))
            

print(len(y2d_fixed_vertex))
middle_idx = int(len(y2d_fixed_vertex)/2)
n = n_vertices
m = x2d_fixed_vertex[middle_idx]
y = y2d_fixed_vertex[middle_idx]
constant = y/(n*m**3)
print(f'middle point = {n}, {y} with idx = {middle_idx}  total elements = {len(x2d_fixed_vertex)}  constant = {constant}  Final data[{n}\t{m}\t{y}]')

x_fixed_vertex = np.linspace(0, 20000, 1000)
y_fixed_edge = constant*n_vertices*x_fixed_vertex**3

constant2 = y/(n**3*m)
y1_fixed_edge = constant2*(n_vertices**3)*x_fixed_vertex

plt.figure(figsize = (10,6))
plt.title(f'Grafos com {n} Vértices')
plt.xlabel('m = Arestas')
plt.ylabel('t = Tempo (segundos)')
plt.xlim(0,10000)
plt.ylim(0,3)
plt.plot(x2d_fixed_vertex,y2d_fixed_vertex, '.')
plt.plot(x_fixed_vertex,y1_fixed_edge, label=f'O(n³m) t=({"{:.3e}".format(constant2)})·{n_vertices}³m')
plt.plot(x_fixed_vertex,y_fixed_edge, label = f'O(nm³) t=({"{:.3e}".format(constant)})·{n_vertices}m³)')
plt.legend()
plt.grid()
plt.show()