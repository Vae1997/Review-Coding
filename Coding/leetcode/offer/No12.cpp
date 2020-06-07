//https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/
#include<iostream>
#include<vector>
using namespace std;
bool hasPath(vector<vector<char>>& board, int rows, int cols, int x, int y, string word, bool* visited, int pathIndex)
{
    //递归到字符串末尾，路径找到return true
    if(word[pathIndex]=='\0')return true;
    bool haspath=false;
    //下标在有效范围&&没有访问的下标&&是当前遍历的字符
    if(x>=0&&x<rows&&y>=0&&y<cols&&!visited[x*cols+y]&&board[x][y]==word[pathIndex])
    {
        pathIndex++;//有效字符数++
        visited[x*cols+y]=true;//标记当前位置已访问
        //当前下标的上、下、左、右只要有一个满足条件，则返回true
        haspath=hasPath(board,rows,cols,x-1,y,word,visited,pathIndex)||//上
                hasPath(board,rows,cols,x+1,y,word,visited,pathIndex)||//下
                hasPath(board,rows,cols,x,y-1,word,visited,pathIndex)||//左
                hasPath(board,rows,cols,x,y+1,word,visited,pathIndex);//右
        if(!haspath)//如果都不满足条件
        {
            pathIndex--;//回溯，有效--
            visited[x*cols+y]=false;//重置访问下标为false
        }
    }
    return haspath;
}
bool exist(vector<vector<char>>& board, string word) {
    int rows,cols;
    rows=board.size();
    cols=board[0].size();
    bool *visited = new bool[rows*cols];//访问数组
    memset(visited,0,rows*cols);
    int pathIndex=0;//当前字符串下标，即需要比较的字符
    for (int x = 0; x < rows; x++)//遍历矩阵，寻找起始位置
        for (int y = 0; y < cols; y++)//找到一条路径return true
            if(hasPath(board,rows,cols,x,y,word,visited,pathIndex))return true;
            //x，y为当前起始下标
    delete[] visited;
    return false;
}
int main()
{
   return 0;
}
