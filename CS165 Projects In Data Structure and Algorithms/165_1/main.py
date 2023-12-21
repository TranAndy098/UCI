from data import get_data

import numpy as np
import matplotlib.pyplot as plt
import scipy
from scipy import stats

#get_data()


def ploting(suffix, file, destination, color, label):
    f = open(file+suffix+".txt", "r")

    sizes = []
    times = [] #times may need to be average to have less pointes per size

    for x in f:
        r = x.rstrip().split()
        sizes.append(int(r[0]))
        times.append(float(r[1]))
    f.close()

    sizes_new = []
    times_new = []


    for j in range(len(sizes)):
        if sizes[j] in sizes_new:
            times_new[-1].append(times[j])

        else:
            sizes_new.append(sizes[j])
            times_new.append([times[j]])

    times = []
    sizes = sizes_new
    for j in range(len(times_new)):
        total = 0
        size = len(times_new[j])
        for time in times_new[j]:
            total += time
        times.append(total/size)


    #last part is figure out how to make plot and lines the same color
    lg_sizes, lg_times = np.log(sizes), np.log(times)

    m, b = np.polyfit(lg_sizes, lg_times, 1)
    fit = np.poly1d((m,b))

    plt.loglog(sizes, times, '.', color=color, base = 2)
    expected_y = fit(lg_sizes)

    _, _, r_value, _, _ = scipy.stats.linregress(sizes, times)

    plt.loglog(sizes, np.exp(expected_y), color=color, label=f"{label}: y = {round(m, 3)}x + {round(b, 3)} ; R^2 = {round(r_value**2, 3)}", base = 2)

    plt.xlabel("sizes")
    plt.ylabel("time")

    #plt.show()
    plt.legend(loc="upper left")
    plt.savefig(destination+suffix+".png")


files = ["insertion_sort_data", "merge_sort_data", "shell_sort1_data", "shell_sort2_data", "shell_sort3_data", "shell_sort4_data", "hybrid_sort1_data", "hybrid_sort2_data", "hybrid_sort3_data"]
destinations_files = ["insertion_sort_vs_merge_sort_plot", "shell_sorts_plot", "hybrid_sorts_plot"]
names = ["insertion_sort vs merge_sort", "shell_sorts", "hybrid_sorts"]

suffixes = ["_uniform", "_almost", "_reversed"]

for suffix in suffixes:
    plt.figure()
    plt.title(names[0]+suffix)
    ploting(suffix, "insert_merge/"+files[0], "insert_merge/"+destinations_files[0], "red", "insertion_sort")
    ploting(suffix, "insert_merge/"+files[1], "insert_merge/"+destinations_files[0], "blue", "merge_sort")

for suffix in suffixes:
    plt.figure()
    plt.title(names[1]+suffix)
    ploting(suffix, "shell/"+files[2], "shell/"+destinations_files[1], "red", "shell_sort1")
    ploting(suffix, "shell/"+files[3], "shell/"+destinations_files[1], "blue", "shell_sort2")
    ploting(suffix, "shell/"+files[4], "shell/"+destinations_files[1], "green", "shell_sort3")
    ploting(suffix, "shell/"+files[5], "shell/"+destinations_files[1], "magenta", "shell_sort4")

for suffix in suffixes:
    plt.figure()
    plt.title(names[2]+suffix)
    ploting(suffix, "hybrid/"+files[6], "hybrid/"+destinations_files[2], "red", "hybrid_sort1")
    ploting(suffix, "hybrid/"+files[7], "hybrid/"+destinations_files[2], "blue", "hybrid_sort2")
    ploting(suffix, "hybrid/"+files[8], "hybrid/"+destinations_files[2], "green", "hybrid_sort3")