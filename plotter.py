import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# ===== НАСТРОЙКИ =====
filePath = "results/phi_20.000000.txt"    # файл с данными
losStep = 0.3            # шаг линий визирования, сек
# =====================

# Чтение файла (табуляция)
df = pd.read_csv(filePath, sep="\t")

# Данные
t  = df.iloc[:, 0].to_numpy()
xi = df.iloc[:, 1].to_numpy()
yi = df.iloc[:, 2].to_numpy()
xt = df.iloc[:, 3].to_numpy()
yt = df.iloc[:, 4].to_numpy()

# Шаг интегрирования
dt = t[1] - t[0]
losEveryNSteps = int(round(losStep / dt))

# График
plt.figure(figsize=(8, 8))

# Траектории
plt.plot(xi, yi, label="Перехватчик", linewidth=5)
plt.plot(xt, yt, label="Цель", linewidth=5)

# Линии визирования + подписи
for i in range(0, len(t), losEveryNSteps):
    dx = xt[i] - xi[i]
    dy = yt[i] - yi[i]

    # угол линии визирования в градусах
    losAngleDeg = np.degrees(np.arctan2(dy, dx))

    # линия визирования
    plt.plot(
        [xi[i], xt[i]],
        [yi[i], yt[i]],
        "--",
        color="gray",
        alpha=0.6
    )

    # подпись: время + угол
    plt.text(
        xi[i],
        yi[i],
        f"{t[i]:.1f} s\n{losAngleDeg:.2f}°",
        fontsize=8
    )

# Оформление
plt.xlabel("x, м", fontsize=20)
plt.ylabel("y, м", fontsize=20)
plt.legend(fontsize=20)
plt.grid(True)
plt.axis("equal")
plt.tick_params(axis="both", labelsize=16)

plt.show()
