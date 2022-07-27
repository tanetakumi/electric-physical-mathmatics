import math
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import copy
import numpy as np

# Calculate RSS
def RSS(f1, f2):
    sum = 0
    for i in range(1,101):
        for j in range(1,101):
            sum += (f2[i][j]-f1[i][j])**2
    print(sum)
    return sum

f = [[0] * 102 for i in range(102)]
f_pre = copy.deepcopy(f)

for j in range(1,30):
    f[50][j] = 0
for j in range(70,101):
    f[50][j] = 100

# 残差平方和
while RSS(f,f_pre) > 100:
    f_tmp = copy.deepcopy(f)
    for i in range(1,101):
        for j in range(1,101):
            f[i][j]=(f_pre[i-1][j] + f_pre[i+1][j] + f_pre[i][j-1] + f_pre[i][j+1])/4      
    f_pre = f_tmp


X, Y = np.meshgrid(np.arange(0,102), np.arange(0,102))
Z = np.array(f)
fig = plt.figure(figsize=(6,6))
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, Z, cmap=cm.jet, linewidth=0)
plt.show()