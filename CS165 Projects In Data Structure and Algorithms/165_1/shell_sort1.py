def shell_sort1(nums):
	gap = len(nums)
	while (gap >= 1):
		gap = gap // 2
		for i in range(len(nums)-gap):
			j = i + gap
			while (j > 0 and nums[j] < nums[j-gap]):
				nums[j], nums[j-gap] = nums[j-gap], nums[j]
				j -= gap
	return nums
