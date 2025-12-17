import pandas as pd
import matplotlib.pyplot as plt

# ===== НАСТРОЙКИ =====
filePath = "output.txt"   # путь к файлу
losStep = 1.0            # шаг линий визирования, сек
# =====================

# Чтение файла (табуляция!)
df = pd.read_csv(filePath, sep="\t")

# Извлекаем данные
t   = df.iloc[:, 0]
xi  = df.iloc[:, 1]
yi  = df.iloc[:, 2]
xt  = df.iloc[:, 3]
yt  = df.iloc[:, 4]

# Построение траекторий
plt.figure(figsize=(8, 8))
plt.plot(xi, yi, label="Interceptor", linewidth=2)
plt.plot(xt, yt, label="Target", linewidth=2)

# Линии визирования
t0 = t.iloc[0]
for i in range(len(t)):
    if abs((t.iloc[i] - t0) % losStep) < 1e-6:
        plt.plot(
            [xi.iloc[i], xt.iloc[i]],
            [yi.iloc[i], yt.iloc[i]],
            linestyle="--",
            color="gray",
            alpha=0.7
        )

# Оформление
plt.xlabel("X, m")
plt.ylabel("Y, m")
plt.title("Trajectories and Line-of-Sight")
plt.legend()
plt.grid(True)
plt.axis("equal")

plt.show()
