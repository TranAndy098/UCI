from merge_sort import merge_sort
from CFloat import CFloat
from zzt_ff import FFZipZipTree

def first_fit_decreasing(items: list[float], assignment: list[int], free_space: list[float]):
    merge_sort(items)
    first_fit(items, assignment, free_space)

def first_fit(items: list[float], assignment: list[int], free_space: list[float]):
    tree = FFZipZipTree(10000)
    bins = 0
    for item in range(len(items)):
        ff_node = tree.find_first(items[item])
        if ff_node == None:
            tree.insert(bins, 1-items[item])
            free_space.append(1-items[item])
            assignment[item] = bins
            bins += 1
        else:
            bin_num = ff_node.key
            bin_val = ff_node.val.capacity.val - items[item]
            bin_rank = ff_node.rank
            tree.remove(bin_num)
            tree.insert(bin_num, bin_val, bin_rank)
            assignment[item] = bin_num
            free_space[bin_num] -= items[item]
