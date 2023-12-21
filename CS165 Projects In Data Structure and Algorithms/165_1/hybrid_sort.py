from insertion_sort import insertion_sort

def hybrid_sort(nums, H):
	if len(nums) <= H:
		return insertion_sort(nums)
	half = len(nums)//2
	new_nums = list(nums)
	begin = hybrid_sort(new_nums[:half], H)
	end = hybrid_sort(new_nums[half:], H)
	
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