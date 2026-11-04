import re
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

# Вставьте сюда вывод ls или укажите путь к папке
import os

# Можно либо парсить строки напрямую, либо читать из папки
# Вариант 1: читать из папки (укажите путь)
FOLDER_PATH = '.'  # <-- замените на ваш путь

data = []

for name in os.listdir(FOLDER_PATH):
    match = re.match(
        r'Ma=([\d.]+)_ampl=([\d.]+)_omfr=([\d.]+)_is_solved=(True|False)', name
    )
    if match:
        ma = float(match.group(1))
        ampl = float(match.group(2))
        omfr = float(match.group(3))
        solved = match.group(4) == 'True'
        data.append((omfr, ampl, solved))

if not data:
    print('Папки не найдены. Проверьте FOLDER_PATH.')
    exit()

omfr_vals = sorted(set(d[0] for d in data))
ampl_vals = sorted(set(d[1] for d in data))

# Строим сетку
grid = {}
for omfr, ampl, solved in data:
    grid[(omfr, ampl)] = solved

# --- Визуализация ---
fig, ax = plt.subplots(figsize=(12, 8))

for (omfr, ampl), solved in grid.items():
    color = '#2ecc71' if solved else '#e74c3c'
    ax.scatter(
        omfr,
        ampl,
        c=color,
        s=120,
        marker='s',
        edgecolors='white',
        linewidths=0.4,
        zorder=3,
    )

# Граница устойчивости (приближённая)
# Для каждого ampl найдём минимальный omfr, при котором solved=True
boundary_x, boundary_y = [], []
for ampl in ampl_vals:
    solved_omfrs = [
        omfr for omfr in omfr_vals if grid.get((omfr, ampl), False)
    ]
    if solved_omfrs:
        boundary_x.append(min(solved_omfrs))
        boundary_y.append(ampl)

if boundary_x:
    # Сортируем по ampl
    pairs = sorted(zip(boundary_y, boundary_x))
    by, bx = zip(*pairs)
    ax.plot(
        bx, by, 'k--', linewidth=1.5, label='Граница устойчивости', zorder=4
    )

ax.set_xlabel('Частота  ωfr', fontsize=13)
ax.set_ylabel('Амплитуда  A', fontsize=13)
ax.set_title(
    f'Карта устойчивости   Ma = 5.382', fontsize=15, fontweight='bold'
)

ax.set_xticks(omfr_vals)
ax.set_yticks(ampl_vals)
ax.grid(True, linestyle='--', alpha=0.4)

stable_patch = mpatches.Patch(color='#2ecc71', label='Устойчиво (True)')
unstable_patch = mpatches.Patch(color='#e74c3c', label='Неустойчиво (False)')
ax.legend(
    handles=[
        stable_patch,
        unstable_patch,
        plt.Line2D([0], [0], ls='--', color='k', label='Граница устойчивости'),
    ],
    fontsize=11,
    loc='upper left',
)

plt.tight_layout()
plt.savefig('stability_map.png', dpi=150)
plt.show()
print('Сохранено: stability_map.png')
