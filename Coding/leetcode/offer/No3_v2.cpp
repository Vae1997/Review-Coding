//面试题3：数组中重复的数字
/*
在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。
数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。
请找出数组中任意一个重复的数字。

示例 1：

输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 
*/
#include<iostream>
#include<vector>
using namespace std;
//时间复杂度O(n),空间O(1)
/*
    数组每个元素数字都在 0～n-1 的范围内
*/
int findRepeatNumber(vector<int>& nums) {
    if(nums.size()<2)return -1;//排除空、单个元素的情况
    for (int i = 0; i < nums.size(); i++)//排除数据大于size-1、小于0的情况
        if(nums[i]<0 || nums[i]>nums.size()-1)return -1;
    for (int i = 0; i < nums.size(); i++)
    {
        int temp=nums[i];//从第一个开始
        while(i!=temp)//和下标比较，相等略过
        {
            if(temp!=nums[temp])//当前元素值和所在下标的数字不等
            {
                nums[i]=nums[temp];//交换
                nums[temp]=temp;
            }
            else return temp;//如果相等，则为重复
            temp=nums[i];//注意将temp重新赋值进行判断
        }
    }
    return -1;
}
int main()
{
    vector<int> nums;
    cout<<findRepeatNumber(nums)<<endl;
    nums.push_back(1);
    cout<<findRepeatNumber(nums)<<endl;
    nums.push_back(2);
    nums.push_back(3);
    cout<<findRepeatNumber(nums)<<endl;
    nums.push_back(2);
    cout<<findRepeatNumber(nums)<<endl;
    nums.push_back(3);
    cout<<findRepeatNumber(nums)<<endl;
    return 0;
}
