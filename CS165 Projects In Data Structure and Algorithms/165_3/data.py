from graph_algorithms import get_diameter
from graph_algorithms import get_clustering_coefficient
from graph_algorithms import get_degree_distribution
import random
from generate import erdos, barabasi


algorithms = [get_diameter, get_clustering_coefficient, get_degree_distribution]
generators = [erdos, barabasi]
sizes = [10,50,100,500,1000] #,5000,10000,50000,100000]
names = ["get_diameter.txt", "get_clustering_coefficient.txt", "get_degree_distribution_1000.txt", "get_degree_distribution_10000.txt", "get_degree_distribution_100000.txt"]
files = []
folders = ["get_diameter/", "get_clustering_coefficient/", "get_degree_distribution/", "get_degree_distribution/", "get_degree_distribution/"]


def generate_lists(size):
    items = []
    for _ in range(size):
        items.append(round(random.uniform(0.0, 0.7), 2))
    return items

def benchmark(algorithm, size, file, generator):

    results = algorithm(generator(size))

    s = f"{size} {results}\n"

    file.write(s)

def get_data():
    gen = "erdos_"
    files = []
    for generator in generators:
    
        for i in range(5):
            files.append(open(folders[i]+gen+names[i] , "w"))

        for size in sizes:
            for _ in range(15):
                for i in range(2):
                    algo = algorithms[i]
                    file = files[i]
                    benchmark(algo, size, file, generator)
                    print(names[i], size)
        
        for _ in range(15):
            size = 1000
            for i in [2,3,4]:
                algo = algorithms[2]
                file = files[i]
                benchmark(algo, size, file, generator)
                print(names[i], size)
                size *= 10

        for i in range(5):
            files[i].close()

        gen = "barabasi_"
        files = []

get_data()