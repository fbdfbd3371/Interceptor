import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# ===== НАСТРОЙКИ =====
filePath = "output.txt"    # файл с данными
losStep = 1.0            # шаг линий визирования, сек
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
plt.plot(xi, yi, label="Interceptor", linewidth=2)
plt.plot(xt, yt, label="Target", linewidth=2)

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
plt.xlabel("X, m")
plt.ylabel("Y, m")
plt.title("Trajectories and Line-of-Sight")
plt.legend()
plt.grid(True)
plt.axis("equal")

plt.show()
