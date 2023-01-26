import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

x = []
y = []
# test = "n^(1,5)"
test = "10n"
with open("src/time_complexity/mgn_const_density-4.data", encoding = 'utf-8') as file:
    for line in file:
            data = line.split()
            x.append(float(data[0]))
            y.append(float(data[2]))
            

# X = np.array(X)
# Y = np.array(Y)
# Z = np.array(Z)


# ax.plot(X, Y, Z, '.', label='measured time', color="red")
# #ax.plot_surface(x, y, z, cmap='viridis')
# ax.legend()

# ax.set_xlabel('vértices')
# ax.set_ylabel('arestas')
# ax.set_zlabel('tempo (milisegundos)')
# ax.yaxis._axinfo['label']['space_factor'] = 3.0

# plt.show()


print(len(y))
middle_idx = int(len(y)/2)
n_mid = x[middle_idx]
y_mid = y[middle_idx]
#constant = y_mid/(n_mid**4)
constant = 5.5e-26
print(f'middle point = {n_mid}, {y_mid} with idx = {middle_idx}  total elements = {len(x)}  constant = {constant}')

x_function = np.linspace(0, 7000000, 100000)
y_function = constant*x_function**4

#constant2 = y/(n**3*m)
#y1_fixed_edge = constant2*(x_fixed_edge**3)*m

plt.figure(figsize = (10,6))
plt.title(f'Grafos com densidade constante m={test}')
plt.xlabel('n = Vértices')
plt.ylabel('t = Tempo (segundos)')
plt.xlim(0, 175000)
plt.ylim(0, 0.5)
plt.plot(x, y, '.')
#plt.plot(x_fixed_edge,y1_fixed_edge, label=f'O(n³m) t=({"{:.3e}".format(constant2)})·n³({m_arestas})')
plt.plot(x_function, y_function, label = f'O(nm³) t=({"{:.3e}".format(constant)})·n({test})³')
plt.legend()
plt.grid()
plt.show()