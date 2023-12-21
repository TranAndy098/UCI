from insertion_sort import insertion_sort
from hybrid_sort import hybrid_sort

def hybrid_sort1(nums):
	H = len(nums)**(1/2)
	nums = hybrid_sort(nums,H)
	return nums
