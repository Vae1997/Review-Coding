//单队列实现栈
//https://leetcode-cn.com/problems/implement-stack-using-queues/
#include<iostream>
#include<queue>
using namespace std;
class MyStack {
private:
    queue<int> Q;
public:
    MyStack() {}
    void push(int x) {
        Q.push(x);//先正常进队
        while(Q.front()!=x)//队头不是插入元素
        {
            Q.push(Q.front());//队头插队尾
            Q.pop();//弹队头
        } 
        //push结束，队头即为栈顶元素
    }
    int pop() {
        int top=Q.front();//队头即为栈顶元素
        Q.pop();//删除
        return top;
    }
    int top() {return Q.front();}//队头即为栈顶元素
    bool empty() {return Q.empty();}
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
