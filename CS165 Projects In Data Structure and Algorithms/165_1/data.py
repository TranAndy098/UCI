from insertion_sort import insertion_sort
from merge_sort import merge_sort
from shell_sort1 import shell_sort1
from shell_sort2 import shell_sort2
from shell_sort3 import shell_sort3
from shell_sort4 import shell_sort4
from hybrid_sort1 import hybrid_sort1
from hybrid_sort2 import hybrid_sort2
from hybrid_sort3 import hybrid_sort3

from shuffle import fisher_yates, almost_sorted

import time

algorithms = [insertion_sort, merge_sort, shell_sort1, shell_sort2, shell_sort3, shell_sort4, hybrid_sort1, hybrid_sort2, hybrid_sort3]
running_times = [[],[],[],[],[],[],[],[],[]]

def generate_lists(n):
    
    list_1 = list(range(n))
    fisher_yates(list_1)

    list_2 = list(range(n))
    almost_sorted(list_2)

    list_3 = list(range(n-1,-1,-1))

    return [list_1, list_2, list_3]

def benchmark(algorithm, size, entry, file):

    tests = []
    for _ in range(10): #could be 5-10 for amount of times
        tests = generate_lists(size)
        for i in range(3):

            begin = time.process_time()

            algorithm(tests[i])

            end = time.process_time()
            s = f"{size} {end-begin}\n"
            file[i].write(s)

def get_data():

    sizes = [25,50,100,250,500,1000,2500,5000,10000,25000]
    names = ["insertion_sort_data", "merge_sort_data", "shell_sort1_data", "shell_sort2_data", "shell_sort3_data", "shell_sort4_data", "hybrid_sort1_data", "hybrid_sort2_data", "hybrid_sort3_data"]
    folder = ["insert_merge/", "insert_merge/", "shell/", "shell/", "shell/", "shell/", "hybrid/", "hybrid/", "hybrid/"]
    files = [] 
    for i in range(9):
        files.append([open(folder[i]+names[i] + "_uniform.txt" , "w"), open(folder[i]+names[i] + "_almost.txt", "w"), open(folder[i]+names[i] + "_reversed.txt", "w")])


    for i in range(9):
        algo = algorithms[i]
        entry = running_times[i]
        file = files[i]

        for size in sizes:
            print(names[i], size)
            benchmark(algo, size, entry, file)

    for i in range(9):
        for j in range(3):
            files[i][j].close()