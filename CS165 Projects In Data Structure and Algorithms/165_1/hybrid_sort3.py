from insertion_sort import insertion_sort
from hybrid_sort import hybrid_sort

def hybrid_sort3(nums):
	H = len(nums)**(1/6)
	nums = hybrid_sort(nums,H)
	return nums
