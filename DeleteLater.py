import matplotlib
import matplotlib.pyplot as plt
import math


x_array = []
y_array = []
for i in range(360):
	x_array.append(i)
	y_array.append(math.sin(i * math.pi / 180))


plt.subplot(1, 1, 1)
plt.plot(x_array, y_array)
plt.show()