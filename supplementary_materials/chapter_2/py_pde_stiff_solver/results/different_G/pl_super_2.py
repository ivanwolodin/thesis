import re
import os
import matplotlib.pyplot as plt
from collections import defaultdict

FOLDER_PATH = "."  # <-- замените на ваш путь

# Собираем данные по каждому Ma
data = defaultdict(dict)  # data[Ma][(omfr, ampl)] = solved

for name in os.listdir(FOLDER_PATH):
    match = re.match(
        r"G0=([\d.]+)_ampl=([\d.]+)_omfr=([\d.]+)_is_solved=(True|False)",
        name
    )
    if match:
        ma   = float(match.group(1))
        ampl = float(match.group(2))
        omfr = float(match.group(3))
        solved = match.group(4) == "True"
        data[ma][(omfr, ampl)] = solved
#    print(match)
if not data:
    print("Папки не найдены. Проверьте FOLDER_PATH.")
    exit()
plt.rcParams.update(
    {
        'font.size': 16,
        'axes.labelsize': 16,
        'xtick.labelsize': 16,
        'ytick.labelsize': 16,
        'legend.fontsize': 16,
    }
)
fig, ax = plt.subplots(figsize=(12, 8))

# Цвета и стили для разных Ma
styles = [
    {"color": "#e74c3c", "ls": "-",  "lw": 2.2},
    {"color": "#2980b9", "ls": "--", "lw": 2.2},
    {"color": "#27ae60", "ls": "-.", "lw": 2.2},
    {"color": "#8e44ad", "ls": ":",  "lw": 2.5},
    {"color": "#f39c12", "ls": "-",  "lw": 2.2},
]

for i, ma in enumerate(sorted(data.keys())):
    print(ma)
    grid = data[ma]
    ampl_vals = sorted(set(k[1] for k in grid))
    omfr_vals = sorted(set(k[0] for k in grid))

    # Для каждой амплитуды ищем минимальный omfr, при котором solved=True
    boundary_x, boundary_y = [], []
    for ampl in ampl_vals:
        solved_omfrs = [omfr for omfr in omfr_vals if grid.get((omfr, ampl), False)]
        if solved_omfrs:
            boundary_x.append(min(solved_omfrs))
            boundary_y.append(ampl)

    if boundary_x:
        pairs = sorted(zip(boundary_y, boundary_x))
        by, bx = zip(*pairs)
        style = styles[i % len(styles)]
        ax.plot(bx, by,
                color=style["color"],
                linestyle=style["ls"],
                linewidth=style["lw"],
                label=f"G = {ma}",
                marker="o", markersize=5, markerfacecolor="white",
                markeredgecolor=style["color"], markeredgewidth=1.5)
ax.set_xlabel(fr"$\Omega$", fontsize=20)
ax.set_ylabel(fr"$B$", fontsize=20)
# ax.set_title("Границы устойчивости при разных числах Маха", fontsize=15, fontweight="bold")

# # Пояснение направлений
# ax.text(0.98, 0.05, "← неустойчиво  |  устойчиво →",
#         transform=ax.transAxes, ha="right", va="bottom",
#         fontsize=10, color="gray", style="italic")

ax.grid(True, linestyle="--", alpha=0.4)
ax.legend(fontsize=20, loc="upper right")
# Подписи областей
ax.text(0.05, 0.05, "Unstable region",
        transform=ax.transAxes, ha="left", va="bottom",
        fontsize=26, color="gray", style="italic")

ax.text(0.55, 0.55, "Stable region",
        transform=ax.transAxes, ha="left", va="top",
        fontsize=26, color="gray", style="italic")
plt.tight_layout()
plt.savefig("stability_boundaries.png", dpi=150)
plt.show()
print("Сохранено: stability_boundaries.png")
