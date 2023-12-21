import math

def shell_sort2(nums):
	if len(nums) > 1:
		gaps = []
		k = int(math.log2(len(nums)))
		a = (2**k) + 1
		while a > 1:
			gaps = gaps + [a]
			a = ((a-1) // 2) + 1
		gaps += [1]
			
		for gap in gaps:
			for i in range(len(nums)-gap):
				j = i + gap
				while (j > 0 and nums[j] < nums[j-gap]):
					nums[j], nums[j-gap] = nums[j-gap], nums[j]
					j -= gap
	return nums
