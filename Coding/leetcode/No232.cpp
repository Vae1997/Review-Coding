//用栈实现队列
//https://leetcode-cn.com/problems/implement-queue-using-stacks/
#include<iostream>
#include<stack>
using namespace std;
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {}    
    /** Push element x to the back of queue. */
    void push(int x) {inStack.push(x);}    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
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
    /** Get the front element. */
    int peek() {
        //outStack非空，直接返回top
        if(!outStack.empty())return outStack.top();
        //inStack有元素而outStack无元素，查询之前先压入outStack
        while(!inStack.empty())
        {
            outStack.push(inStack.top());
            inStack.pop();
        }
        //压完之后，返回top
        return outStack.top();;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        //队列中无元素
        if(inStack.empty() && outStack.empty())return true;
        return false;
    }
private:
    stack<int> inStack;
    stack<int> outStack;
};
int main()
{
   return 0;
}
