import numpy as np
import matplotlib.pyplot as plt

def plot_x_section_many(files, y_fixed):
    plt.figure()

    for filename in files:
        data = np.loadtxt(filename)

        x = data[:, 0]
        y = data[:, 1]
        rho = data[:, 2]

        # если y целочисленный — можно ==
        # если сомневаешься, используй np.isclose
        mask = (y == y_fixed)

        x_sel = x[mask]
        rho_sel = rho[mask]

        # сортировка по x
        order = np.argsort(x_sel)
        x_sel = x_sel[order]
        rho_sel = rho_sel[order]

        # подпись — имя файла (или шаг времени)
        label = filename.split('/')[-1]
        plt.plot(x_sel, rho_sel, label=label)

    plt.xlabel('x')
    plt.ylabel(r'$\rho$')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()


# пример использования
files = [
    'res/rho_181000.txt',
    'res/rho_183000.txt',
    'res/rho_185000.txt',
    'res/rho_188000.txt'
]

plot_x_section_many(files, y_fixed=157)
