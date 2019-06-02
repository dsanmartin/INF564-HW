#%%
import numpy as np
import scipy.spatial.distance as sp_dist
import matplotlib.pyplot as plt
from random import shuffle

def createInput(heights=9, n1=5, n2=11):
  data = dict()
  for i in range(heights):
    n = np.random.randint(n1, n2)
    data[i] = np.random.uniform(low=0,high=1000,size=(n,2))
  return data

def distance(planes):
  dist = sp_dist.cdist(planes, planes, metric='euclidean')
  np.fill_diagonal(dist, np.inf)
  i, j = np.unravel_index(dist.argmin(), dist.shape)
  return dist[i, j], i, j

def saveInput(data, filename="input.txt"):
  file = open(filename, 'w')
  height = list(data)
  shuffle(height)
  for h in height:
    file.write("{0}\n".format(len(data[h])))
    for x, y in data[h]:  
      file.write("{0} {1}\n".format(x, y))
  file.close()

def loadInput(filename="input.txt"):
	file = open(filename)
	data = dict()
	id = -1
	for l in file:
		l = l.strip().split()
		if len(l) == 1:
			id += 1
			data[id] = list()
		else:
			data[id].append([float(l[0]), float(l[1])])
	file.close()
	return data

#%%
data = createInput(n1=100, n2=200)
#%%
saveInput(data, filename="input_2.txt")

#%%
#for i in range(9):
# i = 3
# points = data[i]
# plt.scatter(points[:,0], points[:,1])
# plt.show()
# m, p1, p2 = distance(points)
# print(points)
# print(points[p1])
# print(points[p2])

#%%
# data = loadInput()
# for d in data:
# 	ps = np.array(data[d])
# 	m, p1, p2 = distance(ps)
# 	print("Min:", m, "p1", ps[p1], "p2", ps[p2])