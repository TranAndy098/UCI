from data import get_data

import numpy as np
import matplotlib.pyplot as plt
import scipy
from scipy import stats

#get_data()


def ploting(file, destination, color, label):
    f = open(file, "r")

    sizes = []
    waste = [] 

    for x in f:
        r = x.rstrip().split()
        sizes.append(int(r[0]))
        waste.append(float(r[1]))
    f.close()
    
    sizes_new = []
    waste_new = []


    for j in range(len(sizes)):
        if sizes[j] in sizes_new:
            waste_new[-1].append(waste[j])

        else:
            sizes_new.append(sizes[j])
            waste_new.append([waste[j]])

    waste = []
    sizes = sizes_new
    
    for j in range(len(waste_new)):
        total = 0
        size = len(waste_new[j])
        for w in waste_new[j]:
            total += w
        waste.append(total/size)
    

    #last part is figure out how to make plot and lines the same color
    lg_sizes, lg_times = np.log(sizes), np.log(waste)

    m, b = np.polyfit(lg_sizes, lg_times, 1)
    fit = np.poly1d((m,b))

    plt.loglog(sizes, waste, '.', color=color, base = 2)
    expected_y = fit(lg_sizes)

    _, _, r_value, _, _ = scipy.stats.linregress(sizes, waste)

    plt.loglog(sizes, np.exp(expected_y), color=color, label=f"{label}: y = {round(m, 3)}x + {round(b, 3)} ; R^2 = {round(r_value**2, 3)}", base = 2)

    plt.xlabel("sizes")
    plt.ylabel("waste")

    #plt.show()
    plt.legend(loc="upper left")
    plt.savefig(destination)


files = ["get_diameter.txt", "get_clustering_coefficient.txt", "get_degree_distribution_1000.txt", "get_degree_distribution_10000.txt", "get_degree_distribution_100000.txt"]
destinations_files = ["get_diameter.png", "get_clustering_coefficient.png", "get_degree_distribution_1000.png", "get_degree_distribution_10000.png", "get_degree_distribution_100000.png"]
folders = ["get_diameter/", "get_clustering_coefficient/", "get_degree_distribution/", "get_degree_distribution/", "get_degree_distribution/"]
titles = ["Next Fit Waste", "First Fit Waste", "First Fit Decreasing Waste", "Best Fit Waste", "Best Fit Decreasing Waste"]
generates = ["Erdos ","Barabasi "]
generators = ["erdos_","barabasi_"]

for generator in generators:
    for i in range(5):
        plt.figure()
        ploting(folders[i]+generator+files[i], folders[i]+generator+destinations_files[i], "red", generates[i]+titles[i])