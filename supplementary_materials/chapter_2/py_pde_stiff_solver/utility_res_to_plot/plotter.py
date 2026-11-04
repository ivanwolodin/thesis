import numpy as np
import matplotlib.pyplot as plt
import re
import glob


# --- Функция для извлечения параметров a и w из имени файла ---
def parse_params(filename):
    # примеры имён:  h_a=1_w_0.5.txt
    m = re.search(r'a=(\d+(?:\.\d+)?)_w_(\d+(?:\.\d+)?)', filename)
    if not m:
        return None, None
    a = float(m.group(1))
    w = float(m.group(2))
    return a, w


# --- Собираем все файлы координат поверхностей ---
files = glob.glob('T_a=*_w_*.txt')


plt.figure(figsize=(10, 6))

for f in files:
    # читаем данные
    data = np.loadtxt(f)

    # параметры из имени файла
    a, w = parse_params(f)

    # строим график
    plt.plot(data, label=f'a={a}, w={w}')

plt.xlabel('X, Node')
plt.ylabel('Temperature')
plt.title('Temperature profiles for different (a, w)')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
