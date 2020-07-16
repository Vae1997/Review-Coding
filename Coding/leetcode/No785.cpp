//判断二分图
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
//DFS
void dfs(int node,int c,vector<vector<int>>& graph,vector<int>& color,bool& valid)
{
    color[node]=c;
    int toColor=color[node]==0?1:0;//确定关联的节点颜色
    for (int neibor : graph[node])//遍历关联节点
    {
        if(color[neibor]==-1)//关联节点未访问
        {
            dfs(neibor,toColor,graph,color,valid);
            if (!valid) {
                return;
            }
        }
        else//关联节点访问过
        {
            if(color[node]==color[neibor])//颜色一致，则不可能二分
            {
                valid=false;
                return;
            }
                
        }
    }
}
bool isBipartite(vector<vector<int>>& graph) {
    int n=graph.size();
    vector<int>color(n,-1);//将所有节点标记为-1，表示未访问
    bool valid=true;
    for (int i = 0; i < n && valid; i++)
    {
        if(color[i]==-1)
            dfs(i,0,graph,color,valid);
    }
    
    return valid;
}
//BFS
bool isBipartite(vector<vector<int>>& graph) {
    int n=graph.size();
    vector<int>color(n,-1);//将所有节点标记为-1，表示未访问
    for (int i = 0; i < n; i++)//遍历每个节点，确保没有遗漏
    {
        if(color[i]==-1)//如果不为-1，表示已经访问过
        {
            color[i]=0;//标记当前节点颜色为0
            queue<int> q;
            q.push(i);//当前节点进队
            while (!q.empty())//挨个将关联节点入队
            {
                int node=q.front();//保存队头节点
                q.pop();//队头出队
                int toColor=color[node]==0?1:0;//确定关联的节点颜色
                for (int neibor : graph[node])//遍历关联节点
                {
                    if(color[neibor]==-1)//关联节点未访问
                    {
                        q.push(neibor);//入队
                        color[neibor]=toColor;//上色
                    }
                    else//关联节点访问过
                    {
                        if(color[node]==color[neibor])//颜色一致，则不可能二分
                            return false;
                    }
                }
            }
        }
    }
    return true;
}
int main()
{
   return 0;
}
