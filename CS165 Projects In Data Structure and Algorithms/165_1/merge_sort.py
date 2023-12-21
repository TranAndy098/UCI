def merge_sort(nums):
	nums = merge_sort_breaking(nums)
	return nums


def merge_sort_breaking(nums):
	if len(nums) <= 1:
		return nums
	half = len(nums)//2
	new_nums = list(nums)
	begin = merge_sort_breaking(new_nums[:half])
	end = merge_sort_breaking(new_nums[half:])
	
	index = 0

	begin_index = 0
	end_index = 0
	while (begin_index < len(begin) and end_index < len(end)):
		if begin[begin_index] < end[end_index]:
			nums[index] = begin[begin_index]
			index += 1
			begin_index += 1
		else:
			nums[index] = end[end_index]
			index += 1
			end_index += 1
	
	while (begin_index < len(begin)):
		nums[index] = begin[begin_index]
		index += 1
		begin_index += 1

	while (end_index < len(end)):
		nums[index] = end[end_index]
		index += 1
		end_index += 1

	return nums