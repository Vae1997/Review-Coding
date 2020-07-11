//计算右侧小于当前元素的个数
#include<iostream>
#include<vector>
using namespace std;
//从右到左，依次在v中排序右侧元素，v中二分查找i，下标即为小于i的个数
vector<int> countSmaller(vector<int>& nums) {
    vector<int> v,res(nums.size());
    for (int i = nums.size()-1; i >= 0; --i)
    {
        int L=0,R=v.size();
        while (L<R)
        {
            int mid=L+(R-L)/2;
            if(v[mid]<nums[i])
                L=mid+1;
            else R=mid;    
        }
        res[i]=R;
        v.insert(v.begin()+R,nums[i]);
    }
    return res;
}
int main()
{
   return 0;
}
