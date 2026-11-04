import re
import os
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
from scipy.interpolate import PchipInterpolator

ROOT_PATH = "."  # <-- замените на путь к папке с b=1, b=2, b=3

# Собираем данные: data[b][(k, a)] = solved
data = defaultdict(dict)

for b_dir in os.listdir(ROOT_PATH):
    b_match = re.match(r'b=([\d.]+)', b_dir)
    if not b_match:
        continue
    b_val = float(b_match.group(1))
    b_path = os.path.join(ROOT_PATH, b_dir)
    if not os.path.isdir(b_path):
        continue
    for name in os.listdir(b_path):
        match = re.match(r"k=([\d.]+)_a=([\d.]+)_is_solved=(True|False)", name)
        if match:
            k      = float(match.group(1))
            a      = float(match.group(2))
            solved = match.group(3) == "True"
            data[b_val][(k, a)] = solved

if not data:
    print("Данные не найдены. Проверьте ROOT_PATH.")
    exit()

styles = [
    {"color": "#D62728", "ls": "-",  "marker": "o"},
    {"color": "#1F77B4", "ls": "--", "marker": "s"},
    {"color": "#2CA02C", "ls": "-.", "marker": "^"},
    {"color": "#9467BD", "ls": ":",  "marker": "D"},
]

fig, ax = plt.subplots(figsize=(7, 5))

for i, b_val in enumerate(sorted(data.keys())):
    grid   = data[b_val]
    k_vals = sorted(set(k for k, a in grid))

    bx, by = [], []
    for k in k_vals:
        solved_a = [a for (kk, a), s in grid.items() if kk == k and s]
        if solved_a:
            bx.append(k)
            by.append(max(solved_a))

    if not bx:
        continue

    st = styles[i % len(styles)]
    bx_arr = np.array(bx)
    by_arr = np.array(by)

    ax.scatter(
        bx_arr,
        by_arr,
        marker=st['marker'],
        s=45,                  # размер маркеров
        facecolors='white',
        edgecolors=st['color'],
        linewidths=1.3,
        label=fr'$\Omega = {b_val}$',
    )

ax.set_xlabel("k", fontsize=13)
ax.set_ylabel("a", fontsize=13)
# ax.set_ylim(0, 0.25)
ax.grid(True, linestyle="--", alpha=0.4)
ax.legend(fontsize=12, loc="upper left")
plt.tight_layout()
plt.savefig("stability_boundaries_b.png", dpi=150)
plt.show()
print("Сохранено: stability_boundaries_b.png")