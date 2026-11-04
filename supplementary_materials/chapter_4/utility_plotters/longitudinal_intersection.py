import numpy as np
import matplotlib.pyplot as plt

def plot_x_section(filename, y_fixed):
    # Загружаем данные
    data = np.loadtxt(filename)

    x = data[:, 0]
    y = data[:, 1]
    rho = data[:, 2]

    # Фильтрация по фиксированному y
    mask = (y == y_fixed)

    x_sel = x[mask]
    rho_sel = rho[mask]

    # Сортировка по x
    order = np.argsort(x_sel)
    x_sel = x_sel[order]
    rho_sel = rho_sel[order]

    # Построение графика
    plt.figure()
    plt.plot(x_sel, rho_sel, marker='o', linestyle='-')
    plt.xlabel('x')
    plt.ylabel(r'$ \rho - $')
    # plt.title(f'Section at y = {y_fixed}')
    plt.grid(True)
    plt.show()


# пример использования
plot_x_section('res/rho_129000.txt', y_fixed=98)
