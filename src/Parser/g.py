class Solution(object):
    def makeSubsets(self, ind, cur):
        if ind == len(self.nums):
            self.output.append(cur.copy())
            return
        cur.append(self.nums[ind])
        self.makeSubsets(ind + 1, cur)
        cur.pop()
        self.makeSubsets(ind + 1, cur)
        
    def subsets(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        self.nums = nums
        self.output = []
        cur = []
        self.makeSubsets(0, cur)
        return self.output