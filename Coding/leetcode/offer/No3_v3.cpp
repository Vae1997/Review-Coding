//面试题3：数组中重复的数字
/*
不改动数组进行
*/
#include<iostream>
#include<vector>
using namespace std;
//类似二分查找（注意不能找到所有重复数字,数字范围1~n，长度n+1）
int findRepeatNumber(vector<int>& nums) {
    if(nums.size()<2)return -1;//排除空、单个元素的情况
    for (int i = 0; i < nums.size(); i++)//排除数据大于size-1、小于0的情况
        if(nums[i]<0 || nums[i]>nums.size()-1)return -1;
    //leetcode题目范围包括0，如果有0，则调用下一个方法
    int turnto=0;
    for (int i = 0; i < nums.size(); i++)
        if(nums[i]==0)turnto=1;
    if(!turnto)
    {
        int start=1;
        int end=nums.size()-1;
        while(end>=start)
        {
            int mid=(start+end)/2;
            // cout<<mid<<endl;
            int count=0;
            for (int i = 0; i < nums.size(); i++)
            {
                if(nums[i]>=start && nums[i]<=mid)
                count++;
            }
            // cout<<count<<endl;
            if(end==start)
            {
                if(count>1)return start;
                else break;
            }
            if(count>(mid-start)+1)end=mid;
            else start=mid+1;
        }
        return -1;
    }
    else return findRepeatNumber2(nums);
}
//通过辅助数组进行，需要O(n)辅助空间
int findRepeatNumber2(vector<int>& nums) {
    if(nums.size()<2)return -1;//排除空、单个元素的情况
    for (int i = 0; i < nums.size(); i++)//排除数据大于size-1、小于0的情况
        if(nums[i]<0 || nums[i]>nums.size()-1)return -1;
    //辅助数组
    int *elem=(int*)malloc(nums.size()*sizeof(int));
    //初始化
    for (int i = 0; i < nums.size(); i++)
        elem[i]=-1;
    for (int i = 0; i < nums.size(); i++)
    {
        int temp=nums[i];//从第一个开始
        if(elem[temp]==-1)elem[temp]=temp;//空位，存入对应下标位置
        else return temp;//对应下标已有数字，表示重复
    }
    return -1;
}
int main()
{
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(1);
    nums.push_back(0);
    nums.push_back(2);
    nums.push_back(5);
    nums.push_back(3);
    cout<<findRepeatNumber(nums)<<endl;
    return 0;
}
