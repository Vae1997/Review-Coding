//搜索插入位置
#include<iostream>
#include<vector>
using namespace std;
int searchInsert(vector<int>& nums, int target) {
    if(target<nums[0])return 0;
    int L=0,R=nums.size()-1;
    while (L<=R)
    {
        int mid=L+(R-L)/2;
        if(nums[mid]<target)
            L=mid+1;
        else if(nums[mid]>target)
            R=mid-1;
        else return mid;    
    }
    return R+1;
}
int main()
{
   return 0;
}
