//面试题9：双栈实现队列
/*
用两个栈实现一个队列。
请实现它的两个函数 appendTail 和 deleteHead ，
分别完成在队列尾部插入整数和在队列头部删除整数的功能。
(若队列中没有元素，deleteHead 操作返回 -1 )
输入：
["CQueue","appendTail","deleteHead","deleteHead"]
[[],[3],[],[]]
输出：[null,null,3,-1]
示例 2：
输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]
提示：
1 <= values <= 10000
最多会对 appendTail、deleteHead 进行 10000 次调用
*/
#include<iostream>
#include<stack>
using namespace std;

class CQueue {
public:
    CQueue() {}
    //插入直接进inStack
    void appendTail(int value) {inStack.push(value);}
    int deleteHead() 
    {
        //队列中无元素，删除返回-1
        if(inStack.empty() && outStack.empty())return -1;
        //outStack中有元素，直接弹出
        if(!outStack.empty())
        {
            int head=outStack.top();
            outStack.pop();
            return head;
        }
        //inStack有元素而outStack无元素，删除之前先压入outStack
        while(!inStack.empty())
        {
            outStack.push(inStack.top());
            inStack.pop();
        }
        //压完之后，弹出
        int head=outStack.top();
        outStack.pop();
        return head;
    }
private:
    stack<int> inStack;
    stack<int> outStack;
};
int main()
{
   return 0;
}
