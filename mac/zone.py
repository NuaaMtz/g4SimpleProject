'''
Author: mtz nuaamzt@nuaa.edu.cn
Date: 2025-05-21 20:52:34
LastEditors: mtz nuaamzt@nuaa.edu.cn
LastEditTime: 2025-05-21 20:56:16
FilePath: /betatron/mac/zone.py
Description:发散角三维空间意义演示

'''
# 发散角三维空间意义演示
import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D

# 设置发散角（最大极角，单位：弧度）
theta_max = np.deg2rad(20)  # 20度发散角

# 随机生成N个方向向量
N = 1000
phi = np.random.uniform(0, 2*np.pi, N)
cos_theta = np.random.uniform(np.cos(theta_max), 1, N)
theta = np.arccos(cos_theta)

# 球坐标转直角坐标
x = np.sin(theta) * np.cos(phi)
y = np.sin(theta) * np.sin(phi)
z = np.cos(theta)

# 绘制三维散点图
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x, y, z, s=5, alpha=0.5)

# 画出z轴和锥体边界
ax.plot([0, 0], [0, 0], [0, 1.2], color='k', lw=2)
cone_h = 1.0
cone_r = np.tan(theta_max) * cone_h
u = np.linspace(0, 2 * np.pi, 100)
ax.plot(cone_r * np.cos(u), cone_r * np.sin(u), [cone_h]*100, 'r--', lw=1)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('三维空间下的发散角（锥体内均匀分布方向）')
ax.set_xlim(-1, 1)
ax.set_ylim(-1, 1)
ax.set_zlim(0, 1.2)
plt.show()