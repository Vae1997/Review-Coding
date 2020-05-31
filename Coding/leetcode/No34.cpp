//在排序数组中查找元素的第一个和最后一个位置
//https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/
/*
给定一个按照升序排列的整数数组 nums，和一个目标值 target。
找出给定目标值在数组中的开始位置和结束位置。
你的算法时间复杂度必须是O(log n) 级别。
如果数组中不存在目标值，返回[-1, -1]。
*/
#include<iostream>
#include<vector>
using namespace std;
//O(n)：二分查找到后，左右比较，不符合要求
//O(logn)：找到后right=mid-1向左收缩找到左边界；L=mid+1向右收缩找右边界
vector<int> searchRange(vector<int>& nums, int target) {
    if(nums.empty() || target<nums.front() || target>nums.back())return vector<int>{-1,-1}; 
    int left=0;
    int right=nums.size()-1;//闭区间
    int mid,L,R,M;
    L=left;R=right;
    while (left<=right || L<=R)//注意=，l和L分别进行二分查找
    {
        if(left<=right)
        {
            mid=left+(right-left)/2;
            if(nums[mid]==target)right=mid-1;//找到目标后向左收缩
            else if(nums[mid]<target)left=mid+1;
            else if(nums[mid]>target)right=mid-1;
        }
        else if(L<=R)
        {
            M=L+(R-L)/2;
            if(nums[M]==target)L=M+1;//找到目标后向右收缩
            else if(nums[M]<target)L=M+1;
            else if(nums[M]>target)R=M-1;
        }
    }//注意循环终止条件：left=right+1 && L=R+1，即右下标均在左下标前一个位置
    //由于每次定位到target时，左侧right标记-1，右侧L标记+1
    //因此如果目标存在，则一定位于left~R区间，还需判断，left或R均可
    if(nums[left]!=target)return vector<int>{-1,-1}; 
    //目标存在，左下标left，右下标R
    else return vector<int>{left,R};
}
int main()
{
   return 0;
}

