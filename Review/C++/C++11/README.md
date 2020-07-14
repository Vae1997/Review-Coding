# 汇总记录C++11相关内容
###### B站侯捷C++11[:tv:](https://www.bilibili.com/video/BV1p4411v7Dh?from=search&seid=11158986983875788976)
## =default & =delete
:book:https://www.ibm.com/developerworks/cn/aix/library/1212_lufang_c11new/index.html
* 简单理解为：
  * =default：需要用编译器默认生成的（Big-Three）特殊成员函数
  * =delete：禁止使用当前修饰的函数
- =default
  - 类中的特殊成员函数（构造、析构、拷贝、赋值）显式定义后，编译器默认生成的将失效
  - 若仍需使用默认的函数，则必须显式定义，```增加编码工作量```
  - 此外，显式定义的函数```效率低于```编译器自动生成的
  - :warning:可在类外定义，但只能修饰类的特殊成员函数，且该函数没有默认参数
- =delete
  - 为禁止类对象之间的拷贝、赋值，或禁用不期望的转换和操作符
  - :warning:适用于普通函数，若修饰成员函数则只能在类中定义
```cpp
class A
{
public:
    A()=default; //inline default
    A(const A&)=delete;//delete只能在类中定义
    A& operator=(const A&)=delete;
    int func()=delete;//普通函数也可delete
    virtual ~A();
};
A::~A()=default;//Out-of-line default
```
## decltype
* 简单理解为：用于获取对象类型
  * 用于说明返回类型：
  ```cpp
  template<typename T1, typename T2>
  // decltype(x+y)add(T1 x, T2 y); add函数返回类型为x+y的返回类型
  //但是x+y先于声明，编译无法通过，因此使用如下方法
  auto add(T1 x, T2 y) -> decltype(x+y);//使用->，指定add函数的返回类型
  ```
  * 用于模板中：
  ```cpp
  //obj为容器，则获取类型后可以进一步获取相关属性
  decltype(obj)::iterator
  ```
  * 获取lambda表达式的类型：
  ```cpp
  //定义用于对象比较的lambda
  auto cmp=[](const Obj& obj1, const Obj& obj2){return ···};
  //在set中根据cmp比较对象大小
  std::set<Obj, decltype(cmp)> coll(cmp);
  ```
## lambda表达式

## 智能指针
###### 侯捷的C++11视频缺失，但在[:tv:](https://www.bilibili.com/video/BV14s411E772?p=17)**pointer-like classes**中有所提及
:book:https://simonfang1.github.io/blog/2018/08/23/smart-pointer/

:book:http://www.cplusplus.com/reference/memory/auto_ptr/

:book:https://interview.huihut.com/#/?id=%e6%99%ba%e8%83%bd%e6%8c%87%e9%92%88

:book:https://www.jianshu.com/p/e4919f1c3a28
* auto_ptr（C11弃用）:
  * 支持赋值拷贝，操作后所有权被转移，但原来的对象被置为null
  * 对象仅使用delete析构，无法管理数组
- unique_ptr（代替auto_ptr）
  - 不支持赋值拷贝，但使用move显式转移所有权
  - 析构时可以delete，也可delete[]，因此可以管理数组
- share_ptr（基于**引用计数**实现）
  - 多个shared_ptr可指向同一对象，并维护一个共享的引用计数器，记录了引用同一对象的shared_ptr实例的数量
  - 当最后一个指向对象的shared_ptr销毁时，会自动销毁其所指对象
- weak_ptr（解决**循环引用**问题）
  - 指向shared_ptr管理的对象，但不会增减引用计数器
