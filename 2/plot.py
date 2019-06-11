import sys
import numpy as np
import matplotlib.pyplot as plt

# Load data
#bf = np.loadtxt('data/times/brute_force.txt')
#cp = np.loadtxt('data/times/closest_pair.txt')
bf = np.loadtxt(sys.argv[1])
cp = np.loadtxt(sys.argv[2])

# Reshape data
bf = bf.reshape(6, len(bf) // 6)
cp = cp.reshape(6, len(cp) // 6)

# Average times
bf_mean = np.mean(bf[:,1:], axis=1)
cp_mean = np.mean(cp[:,1:], axis=1)

# N sims
N = np.array([10**i for i in range(1, 7)])

# Plots
plt.plot(N, bf_mean, "r-x", label="Brute Force")
plt.plot(N, cp_mean, "b-o", label="Closest Pair")
plt.plot(N,1e-8*N**2, "r-.", label=r"$O(n^2)$")
plt.plot(N,1.5e-7*N*np.log(N)/np.log(2), "b-.", label=r"$O(n\log_2n)$")
plt.xscale('log')
plt.yscale('log')
plt.xlabel("N Aircrafts")
plt.ylabel("Time [s]")
plt.grid(True)
plt.legend()
plt.show()