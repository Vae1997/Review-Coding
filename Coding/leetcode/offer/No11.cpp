//https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/
#include<iostream>
#include<vector>
using namespace std;
//顺序查找
int minArrayOrder(vector<int> numbers) {
    for(int i=0;i<numbers.size()-1;i++)
        if(numbers[i]>numbers[i+1])return numbers[i+1];
    return numbers[0];
}
//二分查找,如果某次二分left=mid=right，则只能顺序查找
//因为此时无法判断mid位于左侧还是右侧，无法缩减范围
//将此时的范围构造为新的查找数组，采用顺序查找
int minArray(vector<int>& numbers) {
    int size=numbers.size()-1;
    if(numbers[0]<numbers[size] || size==0)return numbers[0];
    int left=0;
    int right=size;
    int mid;
    while (left+1!=right)
    {
        mid=left+(right-left)/2;
        if(numbers[mid]==numbers[left]&&numbers[left]==numbers[right])
            return minArrayOrder(vector<int>(numbers.begin()+left,numbers.begin()+right));
        if(numbers[mid]>=numbers[left])left=mid;
        if(numbers[mid]<=numbers[right])right=mid;
    }
    return numbers[right];
}
int main()
{
    return 0;
}
