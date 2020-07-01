//删除排序数组重复项
#include<iostream>
#include<vector>
using namespace std;
//双指针
int removeDuplicates(vector<int>& nums) {
    int len=nums.size();
    if(len==0)return 0;
    int L,R;
    L=0;R=1;
    int overIndex=0;
    while(R<len)
    {
        if(nums[L]<nums[R])
        {
            overIndex=R;
            L++;R++;
        }
        else
        {
            while(R<len && nums[L]==nums[R])
            {
                R++;
            }
            if(R==len)break;
            nums[overIndex+1]=nums[R];
            overIndex++;
            L=R;
        }
    }
    return overIndex+1;
}
//简化
int removeDuplicates(vector<int>& nums) {
    int len=nums.size();
    if(len==0)return 0;
    int i=0;
    for (int j = 1; j < len; j++)//相等则j++
    {
        if(nums[i]!=nums[j])//不相等，i++位置赋值为j
        {
            i++;
            nums[i]=nums[j];
        }
            
    }
    return i+1;
}
int main()
{
   
   return 0;
}
