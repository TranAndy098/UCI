from data import get_data

import numpy as np
import matplotlib.pyplot as plt
import scipy
from scipy import stats

get_data()


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


files = ["next_fit_data.txt", "first_fit_data.txt", "first_fit_decreasing_data.txt", "best_fit_data.txt", "best_fit_decreasing_data.txt"]
destinations_files = ["next_fit_plot.png", "first_fit_plot.png", "first_fit_decreasing_plot.png", "best_fit_plot.png", "best_fit_decreasing_plot.png"]
titles = ["Next Fit Waste", "First Fit Waste", "First Fit Decreasing Waste", "Best Fit Waste", "Best Fit Decreasing Waste"]
folders = ["next_fit/", "first_fit/", "first_fit_decreasing/", "best_fit/", "best_fit_decreasing/"]



for i in range(5):
    plt.figure()
    ploting(folders[i]+files[i], folders[i]+destinations_files[i], "red", titles[i])