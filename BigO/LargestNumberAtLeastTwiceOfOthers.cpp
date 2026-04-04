// You are given an integer array nums where the largest integer is unique.

// Determine whether the largest element in the array is at least twice as much as every other number in the array. If it is, return the index of the largest element, or return -1 otherwise.
//

class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        int index = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > nums[index]) {
                index = i;
            }
        }
        
        for (int i = 0; i < nums.size(); i++) { 
            if (nums[i] * 2 > nums[index] && i != index) return -1;
        }
        return index;
    }
};
