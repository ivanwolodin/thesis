"""
Построение кривой λ(k) из уравнения:
  λ² + (C₂/48 - C₁)λ - (1/48)(C₁C₂) + C₃ = 0

В каждом сценарии меняется один параметр,
остальные берутся из BASE_PARAMS.

Запуск:
  python linear_stability.py            # все три графика
  python linear_stability.py omega      # только Ω
  python linear_stability.py Ma b       # Ma и B
"""
import argparse

import numpy as np
import matplotlib.pyplot as plt


def compute_m(omega):
    theta = -np.sqrt(1j * omega)    # theta^2 = i*Omega
    ratio = np.tanh(theta) / theta
    return ratio.real


def compute_pq(k_arr, G, C, b, omega, A, Ma, Pr, beta):
    """Коэффициенты уравнения λ² + pλ + q = 0."""
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
    return p, q


def compute_lambdas(k_arr, **params):
    p, q = compute_pq(k_arr, **params)
    D = p**2 - 4 * q

    sqrtD = np.sqrt(np.abs(D))

    # Вещественные корни — только там где D >= 0
    re1 = np.where(D >= 0, (-p + sqrtD) / 2.0, np.nan)
    re2 = np.where(D >= 0, (-p - sqrtD) / 2.0, np.nan)

    # Мнимые части — только там где D < 0
    im1 = np.where(D < 0, (-p + sqrtD) / 2.0, np.nan)
    im2 = np.where(D < 0, (-p - sqrtD) / 2.0, np.nan)

    return re1, re2, im1, im2


# ======================================================
# Параметры
# ======================================================
# Значения по умолчанию; в сценарии переопределяется только варьируемый параметр
BASE_PARAMS = dict(
    G=3.0,
    C=2.5,
    omega=1.5,
    A=0 * 10**-6,
    Ma=5.5,
    b=1.0,
    Pr=7.0,
    beta=1,
)

# param  — имя варьируемого параметра (ключ BASE_PARAMS)
# values — его значения (по одной кривой на значение, максимум 3)
SCENARIOS = {
    'omega': dict(param='omega', values=[0.5, 1.5, 2.0], label=r'$\Omega={}$', k_max=4),
    'Ma': dict(param='Ma', values=[5.0, 5.5, 6.0], label=r'$Ma={}$', k_max=7),
    'b': dict(param='b', values=[0.1, 1.0, 2.0], label='B={}', k_max=4),
}

PLOT_IM = False

COLORS = ['tab:blue', 'tab:orange', 'tab:green']
LINESTYLES = ['-', '--', '-.']

plt.rcParams.update(
    {
        'font.size': 16,
        'axes.labelsize': 16,
        'xtick.labelsize': 16,
        'ytick.labelsize': 16,
        'legend.fontsize': 16,
    }
)


# ======================================================
# Построение
# ======================================================
def plot_scan(param, values, label, k_max, base_params=BASE_PARAMS, plot_im=PLOT_IM):
    k_arr = np.linspace(0, k_max, 1000)
    fig, (ax_re, ax_im) = plt.subplots(1, 2, figsize=(14, 5))

    for value, color, ls in zip(values, COLORS, LINESTYLES):
        params = {**base_params, param: value}
        re1, re2, im1, im2 = compute_lambdas(k_arr, **params)
        text = label.format(value)

        ax_re.plot(k_arr, re1, color=color, linestyle=ls, label=text)
        if plot_im:
            ax_im.plot(k_arr, im1, color=color, linestyle=ls, label=text)

    for ax in (ax_re, ax_im):
        ax.axhline(0, color='black', linewidth=0.8)
        ax.set_xlabel('k')
        ax.set_ylabel('λ')
        ax.set_xlim(0, k_max)
        ax.set_ylim(-2, 2)
        if ax.get_legend_handles_labels()[0]:
            ax.legend(fontsize=14)
        ax.grid()

    fig.tight_layout()
    return fig


def main():
    parser = argparse.ArgumentParser(description=__doc__.split('\n')[1])
    parser.add_argument(
        'scenarios',
        nargs='*',
        help=f'какие сценарии строить: {", ".join(SCENARIOS)} (по умолчанию все)',
    )
    args = parser.parse_args()

    names = args.scenarios or list(SCENARIOS)
    unknown = [n for n in names if n not in SCENARIOS]
    if unknown:
        parser.error(f'неизвестный сценарий: {", ".join(unknown)}')

    for name in names:
        plot_scan(**SCENARIOS[name])

    plt.show()


if __name__ == '__main__':
    main()