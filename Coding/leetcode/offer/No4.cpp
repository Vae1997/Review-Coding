//面试题4：二维数组中的查找
/*
在一个 n * m 的二维数组中，
每一行都按照从左到右递增的顺序排序，
每一列都按照从上到下递增的顺序排序。
请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

示例:
现有矩阵 matrix 如下：
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定 target = 5，返回 true。
给定 target = 20，返回 false。

限制：
0 <= n <= 1000
0 <= m <= 1000
*/
#include<iostream>
#include<vector>
using namespace std;
//从右上角开始
bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    //先处理特殊情况
    if(matrix.size()==0)return false;//排除[]
    if(matrix[0].size()==0)return false;//排除[[]]
    if(target==matrix[0][0]||target==matrix[matrix.size()-1][matrix[0].size()-1])return true;
    if(target<matrix[0][0]||target>matrix[matrix.size()-1][matrix[0].size()-1])return false;
    int start=matrix[0][matrix[0].size()-1];//右上角元素
    int col=matrix[0].size()-1;//当前列数
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = col; j >= 0; j--)
        {
            if(target==matrix[i][j])return true;//找到
            else if(target>matrix[i][j])//目标大，保存当前列，跳出循环，行数++
            {
                col=j;break;
            }    
            //目标小，则列数直接--       
        }
    }   
    return false;
}
int main()
{
    vector<vector<int>> matrix;
    vector<int> v1,v2,v3,v4;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(8);
    v1.push_back(9);
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(9);
    v2.push_back(12);
    v3.push_back(4);
    v3.push_back(7);
    v3.push_back(10);
    v3.push_back(13);
    v4.push_back(6);
    v4.push_back(8);
    v4.push_back(11);
    v4.push_back(15);
    matrix.push_back(v1);
    matrix.push_back(v2);
    matrix.push_back(v3);
    matrix.push_back(v4);
    cout<<findNumberIn2DArray(matrix,7)<<endl;
    cout<<findNumberIn2DArray(matrix,1)<<endl;
    cout<<findNumberIn2DArray(matrix,15)<<endl;
    cout<<findNumberIn2DArray(matrix,0)<<endl;
    cout<<findNumberIn2DArray(matrix,16)<<endl;
    cout<<findNumberIn2DArray(matrix,3)<<endl;
    return 0;
}
