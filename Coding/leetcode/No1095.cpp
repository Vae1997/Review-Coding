//山脉数组中查找目标值
//https://leetcode-cn.com/problems/find-in-mountain-array/
#include<iostream>
using namespace std;
class MountainArray {
  public:
    int get(int index);
    int length();
};
//找峰值->搜左侧->搜右侧
int findInMountainArray(int target, MountainArray &mountainArr) {
    if(mountainArr.get(0)==target)return 0;
    int left=0;
    int right=mountainArr.length()-1;
    int mid,midV,midRV;
    while (left<=right)//二分找峰值
    {
        mid=left+(right-left)/2;
        midV=mountainArr.get(mid);
        midRV=mountainArr.get(mid+1);
        //V和RV不可能相等
        if(midV<midRV)left=mid+1;
        else right=mid-1;
    }//循环结束，left位置最大
    if(mountainArr.get(left)==target)return left;
    int max=left;
    //right=max-1;//max已经判断，right已经是max-1
    left=1;//二分搜索左侧,0号下标开始已经判断
    while (left<=right)
    {
        mid=left+(right-left)/2;
        midV=mountainArr.get(mid);
        if(midV==target)return mid;
        if(midV<target)left=mid+1;
        else right=mid-1;
    }//循环结束，还需找右侧,注意是逆序
    left=max+1;//max已经判断
    right=mountainArr.length()-1;
    if(mountainArr.get(right)==target)return right;
    right--;
    while (left<=right)
    {
        mid=left+(right-left)/2;
        midV=mountainArr.get(mid);
        if(midV==target)return mid;
        if(mid<target)right=mid-1;
        else left=mid+1;
    }//循环结束则表示没找到
    return -1;
}
int main()
{
    return 0;
}
