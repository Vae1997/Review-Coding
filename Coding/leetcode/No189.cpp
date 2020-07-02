//旋转数组
#include<iostream>
#include<vector>
using namespace std;
//反转三次
void rotate(vector<int>& nums, int k) {
    if(k%nums.size()==0)return;
    reverse(nums.begin(),nums.end());
    reverse(nums.begin(),nums.begin()+k%nums.size());
    reverse(nums.begin()+k%nums.size(),nums.end());
}
int main()
{
   
   return 0;
}
