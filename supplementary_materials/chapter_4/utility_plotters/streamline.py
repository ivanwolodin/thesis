import numpy as np
import matplotlib.pyplot as plt

def load_stream_function(filename):
    data = np.loadtxt(filename)
    
    i = data[:, 0].astype(int)
    j = data[:, 1].astype(int)
    psi = data[:, 2]
    
    # определяем размеры сетки
    nx = i.max() + 1
    ny = j.max() + 1
    
    # создаем поле
    Psi = np.zeros((nx, ny))
    
    for k in range(len(psi)):
        Psi[i[k], j[k]] = psi[k]
    
    return Psi


def plot_streamlines(Psi, levels=30):
    nx, ny = Psi.shape
    Lx = 200
    Ly = 500
    x = np.linspace(0, Lx, nx)
    y = np.linspace(0, Ly, ny)
    X, Y = np.meshgrid(x, y)
    
    plt.figure(figsize=(6, 6))
    
    contours = plt.contour(
            X, Y, Psi.T,
            levels=levels,
            colors='black',
            linewidths=0.7
        )
        
    plt.clabel(
        contours,
        inline=True,
        fontsize=8,
        fmt="%.3f"
        # fmt="%.2e"   
    )
    
    plt.gca().set_aspect('equal')
    plt.xlabel('x')
    plt.ylabel('y')
    # plt.title('Stream function isolines')
    
    plt.show()


if __name__ == "__main__":
    filename = "res/streamline_25000.txt"  # подставь нужный step
    Psi = load_stream_function(filename)
    plot_streamlines(Psi, levels=10)