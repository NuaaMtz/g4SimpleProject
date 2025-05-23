'''
Author: mtz nuaamzt@nuaa.edu.cn
Date: 2025-05-22 12:37:44
LastEditors: mtz nuaamzt@nuaa.edu.cn
LastEditTime: 2025-05-22 12:41:55
FilePath: /betatron/mac/edepDisij.py
Description: Visualize energy deposition distribution in detector cells
'''

import uproot
import numpy as np
import matplotlib.pyplot as plt

# Detector parameters
nrows, ncols = 10, 6
xDetec = 0.5  # unit: m
yDetec = 0.5  # unit: m
cell_width = xDetec / ncols
cell_height = yDetec / nrows

# Open ROOT file
# file = uproot.open("rt/output_target0.root")
file = uproot.open("rt/merge.root")
tree = file["stepDataDec"]

# Read data
i = tree["i"].array(library="np")
j = tree["j"].array(library="np")
edep = tree["edep"].array(library="np")

edep_map = np.zeros((nrows, ncols))

# Accumulate energy deposition for each cell
for x, y, e in zip(i, j, edep):
    if 0 <= x < nrows and 0 <= y < ncols:
        edep_map[x, y] += e

# Calculate physical coordinate range
x_min = -xDetec / 2
x_max =  xDetec / 2
y_min = -yDetec / 2
y_max =  yDetec / 2

plt.imshow(
    edep_map,
    origin="upper",  # row index i from top to bottom, consistent with Geant4
    cmap="viridis",
    extent=[x_min, x_max, y_min, y_max],
    aspect=cell_width / cell_height
)
plt.colorbar(label="Energy deposition (MeV)")
plt.xlabel("x (m)")
plt.ylabel("y (m)")
plt.title("Detector Energy Deposition Map (Physical Size)")

plt.savefig("edepDisij.svg")
plt.savefig("edepDisij.pdf")
plt.show()
