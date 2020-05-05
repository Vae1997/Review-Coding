#include<iostream>
using namespace std;
#define HASHSIZE 1000005
#define NULLKEY -1
int Hash(int key)
{
    return key%HASHSIZE;//除留余数法
}
class MyHashSet {
private:
    int *elem;//哈希表
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        elem=(int *)malloc(HASHSIZE*sizeof(int));
        for (int i = 0; i < HASHSIZE; i++)
            elem[i]=NULLKEY;
    }   
    void add(int key) {
        int index=Hash(key);
        while(elem[index]!=NULLKEY)//key通过Hash后冲突
            index=(index+1)%HASHSIZE;//开放定址、线性探测
        elem[index]=key;//找到一个未分配的index
    }   
    void remove(int key) {//当add相同的key后，删除是删除所有的key
        while(contains(key))//循环，直到不包含key为止
        {
            int index=Hash(key);
            while(elem[index]!=key)//循环，直到找到key所在index
                index=(index+1)%HASHSIZE;
            elem[index]=NULLKEY;//置空，表示删除
        }
    }    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int index=Hash(key);
        while(elem[index]!=key)//循环，查找key的index
        {
            index=(index+1)%HASHSIZE;//修正index
            //修正的index位置存储为空、或等于第一次Hash值，遍历结束，表示没有找到key
            if(elem[index]==NULLKEY || index==Hash(key))
                return false;
        }
        return true;
    }
};
int main()
{
    MyHashSet *hashSet = new MyHashSet();
    hashSet->add(1);
    hashSet->add(2);
    hashSet->contains(1);// 返回 true
    hashSet->contains(3);// 返回 false (未找到)
    hashSet->add(2);
    hashSet->contains(2);// 返回 true
    hashSet->remove(2);
    hashSet->contains(2);// 返回  false (已经被删除)
}
