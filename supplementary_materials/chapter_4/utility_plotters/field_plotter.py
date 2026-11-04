import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import griddata

field = "rho"
time_step = "0"
data = np.loadtxt(f"res/{field}_{time_step}.txt")

# Исходные данные
x = data[:, 0]
y = data[:, 1]
values = data[:, 2]

# Создаем новую сетку с более высоким разрешением
x_min, x_max = np.min(x), np.max(x)
y_min, y_max = np.min(y), np.max(y)

# Определяем плотность сетки (увеличивайте для большей детализации)
resolution = 500

x_new = np.linspace(x_min, x_max, resolution)
y_new = np.linspace(y_min, y_max, resolution)
x_grid, y_grid = np.meshgrid(x_new, y_new)

# Интерполируем значения на новую сетку
grid = griddata((x, y), values, (x_grid, y_grid), method="linear")

# Визуализация
plt.imshow(
    grid,
    origin="lower",
    extent=(x_min, x_max, y_min, y_max),
    cmap="viridis",
    interpolation="none",
    aspect="auto",
)
plt.colorbar(label="Value")
plt.xlabel("X")
plt.ylabel("Y")
plt.title(f"field {field}. t={time_step}")
plt.show()
