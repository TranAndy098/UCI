import random
import math

def fisher_yates(nums):

    for i in range(len(nums)-1, -1, -1):
        j = random.sample(range(0, i+1), 1)[0]
        nums[j], nums[i] = nums[i], nums[j]

    return nums

def almost_sorted(nums):

    n = len(nums)
    for _ in range(2*int(math.log2(n))):
        i = random.sample(range(0, n), 1)[0]
        j = random.sample(range(0, n), 1)[0]
        nums[j], nums[i] = nums[i], nums[j]

    return nums
