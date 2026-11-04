"""
Построение кривой λ(k) из уравнения:
  λ² + (C₂/48 - C₁)λ - (1/48)(C₁C₂) + C₃ = 0
"""
import numpy as np
import matplotlib.pyplot as plt


def compute_m(omega):
    # delta = np.sqrt(omega) / np.sqrt(2)
    # numerator = np.sin(delta) * np.cos(delta) + np.sinh(delta) * np.cosh(delta)
    # denominator = np.cos(delta) ** 2 + np.cosh(delta) ** 2 - 1
    theta = np.sqrt(1j * omega)                 # theta^2 = i*Omega
    ratio = np.tanh(theta) / theta              # комплексное число
    Re_ratio = ratio.real                       # действительная часть
    return Re_ratio  # (1.0 / (2 * delta)) * (numerator / denominator)


def compute_lambdas(k_arr, G, C, b, omega, A, Ma, Pr, beta):
    m = compute_m(omega)
    k2 = k_arr**2
    k4 = k_arr**4
    C1 = (
        -1.0 / 3.0 * G * k2
        - 1.0 / 3.0 * C * k4
        + 1.0 / 6.0 * b**2 * omega**2 * k4 * (m - 1)
        + A * k2
        + 0.5 * Ma * k2
    )
    C2 = (1.0 / Pr) * (8 * Ma * Pr * k2 + 48.0 * k2 + 48.0 * beta)
    C3 = (Ma * k2 / 96.0) * (18.0 * (C1 - 0.5 * Ma * k2) + C2 - 48.0 * k2 / Pr)
    p = C2 / 48.0 - C1
    q = C3 - C1 * C2 / 48.0
    D = p**2 - 4 * q

    sqrtD = np.sqrt(np.abs(D))

    # Вещественные корни — только там где D >= 0
    re1 = np.where(D >= 0, (-p + sqrtD) / 2.0, np.nan)
    re2 = np.where(D >= 0, (-p - sqrtD) / 2.0, np.nan)

    # Мнимые части — только там где D < 0
    im1 = np.where(D < 0, (-p + sqrtD) / 2.0, np.nan)
    im2 = np.where(D < 0, (-p - sqrtD) / 2.0, np.nan)

    return re1, re2, im1, im2


k_x_lim = 4
k_arr = np.linspace(0, k_x_lim, 1000)


plt.rcParams.update(
    {
        'font.size': 16,
        'axes.labelsize': 16,
        'xtick.labelsize': 16,
        'ytick.labelsize': 16,
        'legend.fontsize': 16,
    }
)

fig, axes = plt.subplots(1, 2, figsize=(14, 5))
ax_re, ax_im = axes

colors = ['tab:blue', 'tab:orange', 'tab:green']
linestyles = ['-', '--', '-.']   # разные стили


# ======================================================
# different external amplitude
# ======================================================
# Значения b и визуальные настройки для каждого

dim_params = dict(
    G=3.0,
    C=2.5,
    omega=1.5,
    A=0 * 10**-6,
    Ma=5.5,
    Pr=7.0,
    beta=1,
)
b_values = [
    0.1,
    1.0,
    2.0,
]
for b, color, ls in zip(b_values, colors, linestyles):
    re1, re2, im1, im2 = compute_lambdas(k_arr, b=b, **dim_params)

    ax_re.plot(k_arr, re1, color=color, linestyle=ls, label=rf'B={b}')

# for b, color in zip(b_values, colors):
#     re1, re2, im1, im2 = compute_lambdas(k_arr, b=b, **dim_params)

#     # Re(λ) — две ветки одним цветом, разным стилем линии
#     ax_re.plot(k_arr, re1, color=color, linestyle='-.',  label=fr'Re($λ_1$), b={b}')
#     ax_re.plot(k_arr, re2, color="tab:orange", linestyle=':', label=fr'Re($λ_2$), b={b}')

#     # Im(λ)
#     ax_im.plot(k_arr, im1, color="tab:blue", linestyle='-.',  label=fr'Im($λ_1$), b={b}')
#     ax_im.plot(k_arr, im2, color="tab:orange", linestyle=':', label=fr'Im($λ_2$), b={b}')

for ax, title in zip(axes, ['Re(λ)', 'Im(λ)']):
    ax.axhline(0, color='black', linewidth=0.8)
    ax.set_xlabel('k')
    ax.set_ylabel('λ')
    # ax.set_title(f'λ(k) — {title}')
    ax.set_xlim(0, k_x_lim)
    ax.set_ylim(-2, 2)
    ax.legend(fontsize=14)
    ax.grid()
# ======================================================
# ======================================================


plt.tight_layout()
plt.show()
