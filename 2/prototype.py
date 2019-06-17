#%%
import numpy as np
import scipy.spatial.distance as sp_dist
import matplotlib.pyplot as plt
from random import shuffle
#%% DATA MANIPULATION
def createInput(heights=9, n1=5, n2=11):
  data = dict()
  for i in range(heights):
    n = np.random.randint(n1, n2)
    data[i] = np.random.uniform(low=0,high=1000,size=(n,2))
  return data

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

#%% ALGORITHMS
def distance(planes):
  dist = sp_dist.cdist(planes, planes, metric='euclidean')
  np.fill_diagonal(dist, np.inf)
  i, j = np.unravel_index(dist.argmin(), dist.shape)
  return dist[i, j], planes[i], planes[j]


def bruteForce(p):
  d_min = np.inf
  p1 = p[0]
  p2 = p[0]
  for i in range(len(p)):
    for j in range(i+1, len(p)):
      dist = np.linalg.norm(p[i] - p[j])
      if dist < d_min:
        d_min = dist
        p1 = p[i]
        p2 = p[j]
  return d_min, p1, p2


def divide(p):
  if len(p) == 1:
    return np.inf, p[0], p[0]
#  if len(p) == 2:
#    return np.linalg.norm(p[0] - p[1])
  
  d1, p1_l, p2_l = closestPair(p[:len(p)//2])
  d2, p1_r, p2_r = closestPair(p[len(p)//2:])
  
#  print(len(p), d1, p1_l, p2_l)
#  print(len(p), d2, p1_r, p2_r)
  
  #d = min(d1, d2)
  if d1 < d2:
    d = d1
    p1 = p1_l
    p2 = p2_l
  else:
    d = d2
    p1 = p1_r
    p2 = p2_r
    
  
  tmp = []
  for i in range(len(p)):
    if abs(p[i,0] - p[len(p)//2,0]) < d:
      tmp.append(p[i])
      
  Sy = np.array(tmp)
  
  ps_y = Sy[Sy[:,1].argsort()]
  
  for i in range(1, len(ps_y)):
    dist = np.linalg.norm(ps_y[i] - ps_y[i-1])
    if dist < d:
      d = dist
      p1 = ps_y[i]
      p2 = ps_y[i-1]
  
  return d, p1, p2

def closestPair(p):
  p = p[p[:,0].argsort()] # 
  return divide(p)
#%%
data = createInput(heights=10, n1=10, n2=501)
#%%
saveInput(data, 'data/test/input_4.txt')
#%%
#saveInput(data, filename="input_2.txt")

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
data = loadInput('input_2.txt')

#%%
print("Numpy-Scipy")
for d in data:
  ps = np.array(data[d])
  m, p1, p2 = distance(ps)
  print("Min:", m, "p1", p1, "p2", p2)
  
print("Brute Force")
for d in data:
  ps = np.array(data[d])
  m, p1, p2 = bruteForce(ps)
  print("Min:", m, "p1", p1, "p2", p2)
  
print("Closest Pair")
for d in data:
  ps = np.array(data[d])
  m, p1, p2 = closestPair(ps)
  print("Min:", m, "p1", p1, "p2", p2)
  
#%%
ps = np.array(data[0])
m, p1, p2 = bruteForce(ps)
print("Min:", m, "p1", p1, "p2", p2)

#%%
ps = np.array(data[0])
m, p1, p2 = closestPair(ps)
print("Min:", m, "p1", p1, "p2", p2)

#%%
ps = np.array(data[0])
m, p1, p2 = distance(ps)
print("Min:", m, "p1", p1, "p2", p2)

#%% INSERTION
def insertion(A):
  for i in range(len(A)):
    x = A[i]
    j = i
    while j > 0 and A[j-1] > x:
      A[j] = A[j-1]
      j = j - 1
    A[j] = x
    
def insertion2(A):
  n = len(A)
  #B = [None] * n
  i = 1
  while A[i-1] < A[i] and i < n-1:
    #B[i] = A[i]
    i += 1
  for j in range(i, n):
    x = A[j]
    k = j
    while k > 0 and A[k-1] > x:
      A[k] = A[k-1]
      k = k - 1
    A[k] = x
  
def insertion3(A):
  n = len(A)
  i = 0
  for i in range(len(A)):
    while A[i-1] < A[i] and i < n-1:
      i += 1
    x = A[i]
    j = i
    while j > 0 and A[j-1] > x:
      A[j] = A[j-1]
      j = j - 1
    A[j] = x
    
#%%
a = [8,9,10,11,12,3,4,5,18,19,20,16,17,13,14,15,16]
b = [8,11,15,16,3,4,5,18,20,21,25,26,27,7,10,14]
c = [8,11,15,16,19,5,4,3,1,27,23,21,20,18,17,13,14,22,24]
#%%
%timeit insertion(a)
%timeit insertion(b)
%timeit insertion(c)

#%%
%timeit insertion3(a)
#%%
%timeit insertion3(b)
#%%
%timeit insertion3(c)