import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import griddata
from matplotlib.colors import BoundaryNorm

# ---- параметры цветовой шкалы ----
levels = [0, 90.0, 100]   # границы уровней
cmap = plt.get_cmap("viridis", len(levels) - 1)
norm = BoundaryNorm(levels, cmap.N)

# ---- загрузка данных ----
field = "rho"
time_step = "15000"

data = np.loadtxt(f"res/{field}_{time_step}.txt")

x = data[:, 0]
y = data[:, 1]
values = data[:, 2]

# ---- создание регулярной сетки ----
resolution = 500  # можно менять

xi = np.linspace(np.min(x), np.max(x), resolution)
yi = np.linspace(np.min(y), np.max(y), resolution)
Xi, Yi = np.meshgrid(xi, yi)

# ---- интерполяция ----
Zi = griddata((x, y), values, (Xi, Yi), method="linear")

# ---- визуализация ----
plt.figure(figsize=(8, 6))

Lx = 200
Ly = 500
im = plt.imshow(
    Zi,
    origin="lower",
    extent=[0, Lx, 0, Ly],
    cmap=cmap,
    norm=norm,
    
)

plt.gca().set_aspect('equal', adjustable='box')
# plt.colorbar(im, ticks=levels)

plt.xlabel("x")
plt.ylabel("y")

# plt.title(f"Density field ({field}) at t = {time_step}")

plt.tight_layout()
# plt.show()

plt.savefig(f"density_field_{field}_{time_step}.png")