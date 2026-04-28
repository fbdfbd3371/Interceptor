import numpy as np
import matplotlib.pyplot as plt

# ===============================
# Загрузка данных
# ===============================
Data = np.loadtxt("zone.txt")

Angles = Data[:, 0]   # радианы
Hits = Data[:, 1]     # 0 / 1

# ===============================
# Ограничение диапазона углов
# ===============================
ThetaMin = np.deg2rad(10.0)
ThetaMax = np.deg2rad(170.0)

Mask = (Angles >= ThetaMin) & (Angles <= ThetaMax)
Angles = Angles[Mask]
Hits = Hits[Mask]

# ===============================
# Параметры
# ===============================
Radius = 200.0  # м
Delta = np.min(np.diff(Angles))

# ===============================
# Построение
# ===============================
Fig = plt.figure(figsize=(8, 8))
Ax = plt.subplot(111, polar=True)

for Angle, Hit in zip(Angles, Hits):
    Color = "green" if Hit == 1 else "red"
    Ax.bar(
        x=Angle,
        height=Radius,
        width=Delta,
        bottom=0.0,
        color=Color,
        alpha=0.7,
        edgecolor="black"
    )

# ===============================
# Оформление
# ===============================
Ax.set_thetamin(10)
Ax.set_thetamax(170)
Ax.set_rmax(Radius)

Ax.set_title(
    "Зона достижимости при R = 150 м\n"
    "Угол визирования отсчитывается от горизонтали"
)

plt.show()
