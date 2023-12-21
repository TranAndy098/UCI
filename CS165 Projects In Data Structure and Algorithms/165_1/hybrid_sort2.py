from insertion_sort import insertion_sort
from hybrid_sort import hybrid_sort

def hybrid_sort2(nums):
	H = len(nums)**(1/4)
	nums = hybrid_sort(nums,H)
	return nums
