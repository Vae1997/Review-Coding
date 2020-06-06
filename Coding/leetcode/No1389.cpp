//https://leetcode-cn.com/problems/create-target-array-in-the-given-order/
#include<iostream>
#include<vector>
using namespace std;
vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
    int size=nums.size();
    vector<int> res;
    for (int i = 0; i < size; i++)
        res.insert(res.begin()+index[i],nums[i]);
    return res;
}
//自己实现insert
vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
    int size=nums.size();
    vector<int> res(size,-1);
    for (int i = 0; i < size; i++)
    {
        if(index[i]!=-1)
        {
            for (int j= res.size()-1; j > index[i]; j--)
                res[j]=res[j-1];
        }
        res[index[i]]=nums[i];
    }
    return res;
}
int main()
{
   
   return 0;
}
