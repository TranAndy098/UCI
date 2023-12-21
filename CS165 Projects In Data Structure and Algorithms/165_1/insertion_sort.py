# Example file: insertion_sort.py

# Each sorting function should accept a list of integers as the single required
# parameter, as shown below. The input list should be sorted upon completion.
def insertion_sort(nums):
	for i in range(len(nums)-1):
		j = i + 1
		while (j > 0 and nums[j] < nums[j-1]):
			nums[j], nums[j-1] = nums[j-1], nums[j]
			j -= 1
	return nums
