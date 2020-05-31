//第一个错误的版本
//https://leetcode-cn.com/problems/first-bad-version/
#include<iostream>
using namespace std;
// The API isBadVersion is defined for you.
bool isBadVersion(int version);
//没啥说的，二分查找的更简单版本
int firstBadVersion(int n) {
    int left,right,mid;
    left=1;right=n;
    while (left<=right)
    {
        mid=left+(right-left)/2;
        if(isBadVersion(mid))right=mid-1;
        else left=mid+1;
    }
    return left;
}
int main()
{
   return 0;
}
