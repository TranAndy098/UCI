from next_fit import next_fit
from first_fit import first_fit
from first_fit import first_fit_decreasing
from best_fit import best_fit
from best_fit import best_fit_decreasing
import random


algorithms = [next_fit, first_fit, first_fit_decreasing, best_fit, best_fit_decreasing]
sizes = [25,75,250,750,2500,7500,25000,75000,250000]
names = ["next_fit_data.txt", "first_fit_data.txt", "first_fit_decreasing_data.txt", "best_fit_data.txt", "best_fit_decreasing_data.txt"]
files = []
folders = ["next_fit/", "first_fit/", "first_fit_decreasing/", "best_fit/", "best_fit_decreasing/"]

def is_equal(v1: list[float], v2: list[float]) -> bool:
	for a, b in zip(v1, v2):
		if abs(a - b) > 1e-6:
			return False
	return True

def generate_lists(size):
    items = []
    for _ in range(size):
        items.append(round(random.uniform(0.0, 0.7), 2))
    return items

def benchmark(algorithm, size, test, file):

    assignments = [0] * size
    free_space = list()

    algorithm(test, assignments, free_space)

    waste = max(assignments) + 1 - sum(test)
    s = f"{size} {waste}\n"

    file.write(s)

def get_data():
    
    for i in range(5):
        files.append(open(folders[i]+names[i] , "w"))

    for size in sizes:
        for _ in range(10):
            items = generate_lists(size)
            for i in range(5):
                algo = algorithms[i]
                file = files[i]
                print(names[i], size)
                benchmark(algo, size, items.copy(), file)

    for i in range(5):
        files[i].close()