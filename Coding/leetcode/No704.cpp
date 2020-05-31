//二分查找
//https://leetcode-cn.com/problems/binary-search/
/*
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target，
写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
*/
#include<iostream>
#include<vector>
using namespace std;
//局限性：包含重复元素时，无法确定其区间
int search(vector<int>& nums, int target) {
    if(nums.empty() || target<nums.front() || target>nums.back())return -1;
    int left=0;//左闭
    int right=nums.size()-1;//右闭
    int mid;
    while (left<=right)//注意等号，没有=会遗漏left=right时的下标值，return之前还需要单独和target对比一下
    {
        //和 (left + right) / 2 的结果相同
        mid=left+(right-left)/2;//但是有效防止 left 和 right 太大直接相加导致溢出
        if(nums[mid]==target)return mid;
        else if(nums[mid]<target)left=mid+1;
        else if(nums[mid]>target)right=mid-1;
    }
    return -1;
}
int main()
{
   return 0;
}
