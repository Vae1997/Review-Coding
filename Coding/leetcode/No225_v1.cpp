//双队列实现栈
//https://leetcode-cn.com/problems/implement-stack-using-queues/
#include<iostream>
#include<queue>
using namespace std;
//总之确保有一个空队列
class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {}    
    /** Push element x onto stack. */
    void push(int x) {//往非空队列中插入元素
        if(!q1.empty())q1.push(x);
        if(!q2.empty())q2.push(x);
        //都为空，默认往q1插入
        if(q1.empty()&&q2.empty())q1.push(x);
    }    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int top=-1;
        if(q2.empty())//q2空，则将q1元素压入q2
        {
            while(q1.size()!=1)//q1保留最后一个元素，即为栈顶元素
            {
                q2.push(q1.front());
                q1.pop();
            }
            top=q1.front();//返回栈顶
            q1.pop();//q1弹出最后一个元素，q1为空
            return top;            
        }
        if(q1.empty())//q1空，则将q2元素压入q1
        {
            while(q2.size()!=1)//q2保留最后一个元素，即为栈顶元素
            {
                q1.push(q2.front());
                q2.pop();
            }
            top=q2.front();//返回栈顶
            q2.pop();//q2弹出最后一个元素，q2为空
            return top;
        }
        return top;
    }    
    /** Get the top element. */
    int top() {//类似删除,需在pop之前先将元素存入另一个队列
        int top=-1;
        if(q2.empty())//q2空，则将q1元素压入q2
        {
            while(q1.size()!=1)//q1保留最后一个元素，即为栈顶元素
            {
                q2.push(q1.front());
                q1.pop();
            }
            top=q1.front();//返回栈顶
            q2.push(q1.front());//q2压入最后一个元素
            q1.pop();//q1弹出最后一个元素，q1为空
            return top;
        }
        if(q1.empty())//q1空，则将q2元素压入q1
        {
            while(q2.size()!=1)//q2保留最后一个元素，即为栈顶元素
            {
                q1.push(q2.front());
                q2.pop();
            }
            top=q2.front();//返回栈顶
            q1.push(q2.front());//q1压入最后一个元素
            q2.pop();//q2弹出最后一个元素，q2为空
            return top;
        }
        return top;
    }   
    /** Returns whether the stack is empty. */
    bool empty() {
        if(q1.empty()&&q2.empty())return true;
        return false;
    }
private:
    queue<int> q1;
    queue<int> q2;
};
int main()
{
    MyStack* obj = new MyStack();
    obj->push(1);
    obj->push(2);
    obj->push(3);
    cout<<obj->top()<<endl;//3
    cout<<obj->pop()<<endl;//3
    cout<<obj->top()<<endl;//2
    cout<<obj->empty()<<endl;//0
    cout<<obj->pop()<<endl;//2
    cout<<obj->pop()<<endl;//1
    cout<<obj->empty()<<endl;//1
   return 0;
}
