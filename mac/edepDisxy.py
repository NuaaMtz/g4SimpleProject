'''
Author: mtz nuaamzt@nuaa.edu.cn
Date: 2025-05-22 10:33:54
LastEditors: mtz nuaamzt@nuaa.edu.cn
LastEditTime: 2025-05-22 12:44:28
FilePath: /betatron/mac/edepDis.py
Description: Visualize energy deposition distribution based on (x, y) coordinates
'''

import uproot
import numpy as np
import matplotlib.pyplot as plt

# Open ROOT file
file = uproot.open("rt/output_target0.root")
tree = file["SetpData"]

x = tree["x"].array(library="np")
y = tree["y"].array(library="np")
edep = tree["edep"].array(library="np")

# Set canvas range and resolution
xmin, xmax, ymin, ymax = -200, 200, -200, 200
nxbins, nybins = 100, 100

# Create 2D histogram
H, xedges, yedges = np.histogram2d(x, y, bins=[nxbins, nybins],
                                   range=[[xmin, xmax], [ymin, ymax]],
                                   weights=edep)

plt.imshow(H.T, origin="lower", extent=[xmin, xmax, ymin, ymax], aspect="auto", cmap="viridis")
plt.colorbar(label="Energy deposition (MeV)")
plt.xlabel("X (mm)")
plt.ylabel("Y (mm)")
plt.title("Detector Energy Deposition Map (x, y)")
plt.savefig("edepDisxy.svg")
plt.savefig("edepDisxy.pdf")
plt.show()
