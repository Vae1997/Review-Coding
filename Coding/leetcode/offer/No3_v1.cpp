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
#include<algorithm>
using namespace std;
//哈希表
int findRepeatNumber(vector<int>& nums) {
    //初始化
    int HashSize=nums.size();
    int *elem=(int*)malloc(HashSize*sizeof(int));
    for (int i = 0; i < HashSize; i++)
        elem[i]=-1;
    int key,index;
    for (int i = 0; i < HashSize; i++)
    {
        key=nums.at(i);//取值
        index=key%HashSize;//哈希，除留余数
        if(elem[index]!=-1)return key;//冲突，表示重复，返回即可
        else elem[index]=key;//否则填入哈希表
    }
    return -1;
}
//排序后，相邻比较
int findRepeatNumber1(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    int res=nums.front();
    for (int i = 1; i < nums.size(); i++)
    {
        int temp=nums.at(i);
        if(temp==res)return res;
        else res=temp;
    }
    return -1;
}
//双重循环，超时
int findRepeatNumber2(vector<int>& nums) {
    for (int i = 0; i < nums.size()-1; i++)
    {
        int res=nums.at(i);
        for (int j = i+1; j < nums.size(); j++)
        {
            int temp=nums.at(j);
            if(temp==res)return res;
        }       
    }
    return -1;    
}
//迭代，超时
int findRepeatNumber3(vector<int>& nums) {
    while(!nums.empty())
    {
        int end=nums.back();
        nums.pop_back();
        vector<int>::iterator it = find(nums.begin(), nums.end(), end);
        if (it != nums.end())
            return *it;
    }
    return -1;
}
int main()
{
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(8);
    nums.push_back(6);
    nums.push_back(7);
    nums.push_back(8);
    nums.push_back(9);
    nums.push_back(10);
    cout<<findRepeatNumber(nums)<<endl;
    return 0;
}
