//https://leetcode-cn.com/problems/merge-sorted-array/
//合并两个排序数组
/*
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，
使 nums1 成为一个有序数组。

初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3
输出: [1,2,2,3,5,6]
*/
#include<iostream>
#include<vector>
using namespace std;
//从后往前，大的赋值
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int newend=m+n-1;//末尾
    int end1=m-1;
    int end2=n-1;
    while(newend>=0)//循环赋值
    {
        if(end1<0)//1已经赋值完毕，直接挨个赋值2
        {
            nums1[newend--]=nums2[end2--];
            continue;
        }
        if(end2<0)//2已经赋值完毕，直接挨个赋值1
        {
            nums1[newend--]=nums1[end1--];
            continue;
        }
        //比较，大的赋值
        nums2[end2]>=nums1[end1]?nums1[newend--]=nums2[end2--]:nums1[newend--]=nums1[end1--];
    }
    for (int i = 0; i < nums1.size(); i++)
        cout<<nums1[i]<<endl;
}
int main()
{
    vector<int> v1,v2;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(0);
    v1.push_back(0);
    v1.push_back(0);
    v2.push_back(2);
    v2.push_back(5);
    v2.push_back(6);
    merge(v1,3,v2,3);
   return 0;
}
