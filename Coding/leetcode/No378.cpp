//有序矩阵中第K小的元素
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//排序，返回第k个元素(效率低)
int kthSmallest(vector<vector<int>>& matrix, int k) {
    vector<int> rec;
    for (auto& row : matrix) {
        for (int it : row) {
            rec.push_back(it);
        }
    }
    sort(rec.begin(), rec.end());
    return rec[k - 1];
}
//二分查找
//矩阵中比中间值小的元素个数
int getlowMidCount(vector<vector<int>>& matrix, int mid)
{
    //小元素整体在左上角，从左下角开始
    int i=matrix.size()-1;//最后一行
    int j=0;//第一列
    int count=0;
    while (i>=0 && j<=matrix.size()-1)
    {
        if(matrix[i][j]<=mid)
        {
            count+=i+1;
            j++;
        }
        else i--;
    }
    return count;
}
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n=matrix[0].size();
    int L=matrix[0][0];
    int R=matrix[n-1][n-1];
    int mid,lowMidCount;
    while (L<=R)
    {
        mid=L+((R-L)>>1);
        lowMidCount=getlowMidCount(matrix,mid);
        if(lowMidCount<k)//个数小于k，则第k小在“右侧”
            L=mid+1;
        else
            R=mid-1;
    }
    return L;
}
int main()
{
   return 0;
}
