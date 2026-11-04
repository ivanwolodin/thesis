"""
Построение кривой λ(k) из уравнения:
  λ² + (C₂/48 - C₁)λ - (1/48)(C₁C₂) + C₃ = 0
"""
import numpy as np
import matplotlib.pyplot as plt


def compute_m(omega):
    delta = omega / np.sqrt(2)
    numerator = np.sin(delta) * np.cos(delta) + np.sinh(delta) * np.cosh(delta)
    denominator = np.cos(delta) ** 2 + np.cosh(delta) ** 2 - 1
    return (1.0 / (2 * delta)) * (numerator / denominator)


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

    # D >= 0: два вещественных корня, Im = 0
    re1 = np.where(D >= 0, (-p + sqrtD) / 2.0, np.nan)
    re2 = np.where(D >= 0, (-p - sqrtD) / 2.0, np.nan)

    # D < 0: комплексные корни λ = re_c ± i·im_c
    re_c = np.where(
        D < 0, -p / 2.0, np.nan
    )  # вещественная часть (общая для обоих корней)
    im_c = np.where(
        D < 0, sqrtD / 2.0, np.nan
    )  # мнимая часть (модуль; второй корень: −im_c)

    return re1, re2, re_c, im_c


# ─────────────────────────────────────────────
dim_params = dict(
    G=3.0,
    C=2.5,
    omega=1.1,
    A=0 * 10**-6,
    Ma=5.3,
    Pr=7.0,
    beta=0.80,
)

k_x_lim = 4
k_arr = np.linspace(0, k_x_lim, 1000)

b_values = [1.071]
colors = ['tab:blue', 'tab:orange', 'tab:green']

fig, axes = plt.subplots(1, 2, figsize=(14, 5))
ax_re, ax_im = axes

for b, color in zip(b_values, colors):
    re1, re2, re_c, im_c = compute_lambdas(k_arr, b=b, **dim_params)

    # ── Re(λ) ──────────────────────────────────────────────────────────────
    # При D >= 0: два разных вещественных корня
    ax_re.plot(
        k_arr,
        re1,
        color='tab:blue',
        linestyle='-.',
        label=rf'Re($\lambda_1$), b={b}',
    )
    ax_re.plot(
        k_arr,
        re2,
        color='tab:orange',
        linestyle=':',
        label=rf'Re($\lambda_2$), b={b}',
    )
    # При D < 0: оба корня имеют одинаковую вещественную часть re_c
    ax_re.plot(
        k_arr,
        re_c,
        color='tab:green',
        linestyle='-',
        label=rf'Re($\lambda_{{1,2}}$) [complex], b={b}',
    )

    # ── Im(λ) ──────────────────────────────────────────────────────────────
    # При D >= 0: Im = 0 (вещественные корни) — не рисуем отдельно
    # При D < 0: Im = ±im_c
    ax_im.plot(
        k_arr,
        im_c,
        color='tab:blue',
        linestyle='-.',
        label=rf'Im($\lambda_1$)=+im_c, b={b}',
    )
    ax_im.plot(
        k_arr,
        -im_c,
        color='tab:orange',
        linestyle=':',
        label=rf'Im($\lambda_2$)=−im_c, b={b}',
    )

for ax, title in zip(axes, ['Re(λ)', 'Im(λ)']):
    ax.axhline(0, color='black', linewidth=0.8)
    ax.set_xlabel('k')
    ax.set_ylabel('λ')
    ax.set_title(f'λ(k) — {title}')
    ax.set_xlim(0, k_x_lim)
    ax.set_ylim(-2, 2)
    ax.legend(fontsize=8)
    ax.grid()

plt.tight_layout()
plt.savefig('lambda_curves.png', dpi=150)
plt.show()
