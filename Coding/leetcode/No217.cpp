//存在重复元素
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//先排序再挨个找
bool containsDuplicate(vector<int>& nums) {
    if(nums.size()<2)return false;
    sort(nums.begin(),nums.end());
    vector<int>::iterator i=nums.begin()+1;
    while(i!=nums.end())
    {
        if(*i==*(i-1))return true;
        i++;
    }
    return false;
}
int main()
{
   
   return 0;
}


//----------------------
//存在重复元素 II
#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
using namespace std;
//set集合大小为k
bool containsNearbyDuplicate(vector<int>& nums, int k) {
   unordered_set<int>set;//存放元素值
   for (int i = 0; i < nums.size(); i++)
   {
      if(set.find(nums[i])!=set.end())//集合中已有
         return true;
      set.insert(nums[i]);
      if(set.size()>k)//窗口大于k
         set.erase(nums[i-k]);//set中删除第i-k个元素值
   }
   return false;
}
//map实现
bool containsNearbyDuplicate(vector<int>& nums, int k) {
   unordered_map<int,int>map;//key为元素值，value为下标值
   int len=nums.size();
   for (int i = 0; i < len; ++i)
   {
      if(map.count(nums[i])==0)//map中没有
         map[nums[i]]=i;
      else if(i-map[nums[i]]<=k)//存在相同元素，且下标距离不超过k
         return true;
      else map[nums[i]]=i;//超过k，此前的下标已经没意义，更新下标
   }
   return false;
}
int main()
{
   
   return 0;
}



//-----------------------
//存在重复元素 III
#include<iostream>
#include<vector>
#include<unordered_set>
#include<set>
using namespace std;
//超时
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    if(nums.size()<1 || t<0 || k<0)
        return false;
    if(k==0 && t==1)
        return false;
    unordered_set<long long int>set;
    set.insert(nums[0]);//先插入第一个数
    int len=nums.size();
    long long int L;
    for (int i = 1; i < len; i++)//挨个插入set
    {
        if(set.find(nums[i])!=set.end())//集合中已有
        {
            // cout<<"ok1"<<endl;
            return true;
        }
            
        for (long long int j : set)//依次比较
        {
            // cout<<"num:"<<nums[i]<<" ,*j:"<<*j<<" ,t:"<<t<<endl;
            // cout<<"abs:"<<abs(nums[i] - (*j))<<endl;
            //元素差的绝对值不超过t
            L=nums[i] - j;
            if(abs(L) <= t)
            {
                // cout<<"ok2"<<endl;
                return true;
            }
        }
        //不符合条件，插入
        set.insert(nums[i]);
        if(set.size()>k)//窗口大于k
            set.erase(nums[i-k]);//set中删除第i-k个元素值
    }
    return false;
    }

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<long long>s;
    for (int i = 0; i < nums.size(); i++)
    {
        //找到>=nums[i]-t的最小值
        set<long long>::iterator l=s.lower_bound((long long)nums[i]-t);
        if(l!=s.end() && (*l)<=(long long)nums[i]+t)
            return true;
        s.insert(nums[i]);
        if(s.size()>k)
            s.erase(nums[i-k]);
    }
    return false;
}
int main()
{
   
   return 0;
}
