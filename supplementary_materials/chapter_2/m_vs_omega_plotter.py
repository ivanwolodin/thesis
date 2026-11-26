import numpy as np
import matplotlib.pyplot as plt


# def L(omega):
#     """Вычисляет L(ω)"""
#     omega = np.asarray(omega, dtype=float)
#     delta = np.sqrt(omega) / np.sqrt(2)

#     numerator = np.sin(delta) * np.cos(delta) + np.sinh(delta) * np.cosh(delta)
#     denominator = np.cos(delta) ** 2 + np.cosh(delta) ** 2 - 1
    
#     result = numerator / (2 * delta * denominator)
#     return result


def L(omega):
    theta = np.sqrt(1j * omega)                 # theta^2 = i*Omega
    ratio = np.tanh(theta) / theta              # комплексное число
    Re_ratio = ratio.real                       # действительная часть
    return Re_ratio  # (1.0 / (2 * delta)) * (numerator / denominator)


OMEGA_MIN = 0.2
OMEGA_MAX = 20.0
N_POINTS = 2000


omega = np.linspace(OMEGA_MIN, OMEGA_MAX, N_POINTS)
values = L(omega)

plt.figure(figsize=(9, 5))
plt.plot(omega, values, linewidth=2, color="tab:blue")
plt.xlabel(r"$\omega$")
plt.ylabel(r"$L(\omega)$")
plt.grid(True, alpha=0.3)
plt.axhline(0, color="black", linewidth=0.7)
plt.tight_layout()

# plt.savefig("L_vs_omega.png", dpi=150)
plt.show()