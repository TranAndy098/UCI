def next_fit(items: list[float], assignment: list[int], free_space: list[float]):
	item_idx = 0
	current_bin = -1
	while item_idx < len(items):
		if len(free_space) == 0 or items[item_idx] > free_space[current_bin]:
			current_bin += 1
			free_space.append(1-items[item_idx])
		else:
			free_space[current_bin] -= items[item_idx]
		
		assignment[item_idx] = current_bin
		item_idx += 1
		

