import matplotlib.pyplot as plt
import numpy as np

f = open("output.txt")
s = f.readlines()
d = {}
for i in s:
        n = int(i[:-1])
        try:
                d[n] += 1
        except:
                d[n] = 1
        

x = np.array(list(d.keys()))
y = np.array(list(d.values()))

plt.ylim(0, 1000000)

plt.scatter(x, y)
plt.show()
