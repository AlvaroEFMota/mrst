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

x2d_fixed_vertex = []
y2d_fixed_vertex = []
x2d_fixed_edge = []
y2d_fixed_edge = []
n_vertices = 1632
m_arestas = 2800
with open("src/time_complexity/complexity.data", encoding = 'utf-8') as file:
    count = 0
    for line in file:
            data = line.split()
            count+=1
            if count%1 == 0:
                X.append(float(data[0]))
                Y.append(float(data[1]))
                Z.append(float(data[2])*1000)
            if (int(data[0]) == n_vertices):
                x2d_fixed_vertex.append(float(data[1]))
                y2d_fixed_vertex.append(float(data[2])*1000)
            if (int(data[1]) == m_arestas):
                x2d_fixed_edge.append(float(data[0]))
                y2d_fixed_edge.append(float(data[2])*1000)
            

X = np.array(X)
Y = np.array(Y)
Z = np.array(Z)

# y2d = np.array(y2d, dtype='float')
# x2d = np.array(x2d, dtype='float')
# for i in range(len(x2d)):
    # print(f'| x = {x2d[i]}  y = {y2d[i]}')

ax.plot(X, Y, Z, '.', label='measured time', color="red")
# ax.plot_surface(x, y, z, cmap='viridis')
ax.legend()

ax.set_xlabel('vértices')
ax.set_ylabel('arestas')
ax.set_zlabel('tempo (milisegundos)')
ax.yaxis._axinfo['label']['space_factor'] = 3.0

plt.show()


# middle_idx = int(len(y2d_fixed_vertex)/2)
# n = n_vertices
# m = x2d_fixed_vertex[middle_idx]
# y = y2d_fixed_vertex[middle_idx]



# constant = y/(n*m**3)

# x_fixed_vertex = np.linspace(0, 1500, 10000)
# y_fixed_vertex = constant*n*x**3



# plt.title(f'Grafos com {n} vértices')
# plt.xlabel('Arestas')
# plt.ylabel('Tempo (milissegundos)')
# plt.xlim(0,1500)
# plt.ylim(0,1500)
# plt.plot(x2d_fixed_vertex,y2d_fixed_vertex, '.')
# plt.plot(x_fixed_vertex,y_fixed_vertex)
print(len(y2d_fixed_edge))
middle_idx = int(len(y2d_fixed_edge)/2)
m = m_arestas
n = x2d_fixed_edge[middle_idx]
y = y2d_fixed_edge[middle_idx]
constant = y/(n*m**3)
print(f'middle point = {n}, {y} with idx = {middle_idx}  total elements = {len(x2d_fixed_edge)}  constant = {constant}  inal data[{n}\t{m}\t{y}]')

x_fixed_edge = np.linspace(0, 6000, 1000)
y_fixed_edge = constant*x_fixed_edge*m**3

n_adjust = 1.1
constant_adjust = 1
y1_fixed_edge = constant_adjust*constant*(x_fixed_edge**n_adjust)*m**3

plt.figure(figsize = (10,6))
plt.title(f'Grafos com {m} arestas')
plt.xlabel('n = Vértices')
plt.ylabel('t = Tempo (milissegundos)')
plt.xlim(0,6000)
plt.ylim(0,1000)
plt.plot(x2d_fixed_edge,y2d_fixed_edge, '.')
plt.plot(x_fixed_edge,y_fixed_edge, label = f't=({"{:.3e}".format(constant)})·n({m_arestas}^3)')
plt.plot(x_fixed_edge,y1_fixed_edge, label=f't=({constant_adjust})({"{:.3e}".format(constant)})·(n^{n_adjust})·({m_arestas}^3)')
plt.legend()
plt.grid()
plt.show()