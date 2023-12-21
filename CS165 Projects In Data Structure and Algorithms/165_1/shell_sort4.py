def shell_sort4(nums):
	if len(nums) > 1:
		n = len(nums)
		gaps = [17179475969, 9663381505, 4294770689, 2415771649, 1073643521, 603906049, 268386305, 150958081, 67084289, 37730305, 16764929, 9427969, 4188161, 2354689, 1045505, 587521, 260609, 146305, 64769, 36289, 16001, 8929, 3905, 2161, 929, 505, 209, 109, 41, 19, 5, 1]
		
		for gap in gaps:
			if gap < n:
				for i in range(len(nums)-gap):
					j = i + gap
					while (j > 0 and nums[j] < nums[j-gap]):
						nums[j], nums[j-gap] = nums[j-gap], nums[j]
						j -= gap
	return nums