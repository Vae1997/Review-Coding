`B站侯捷C++11`[:tv:](https://www.bilibili.com/video/BV1p4411v7Dh?from=search&seid=11158986983875788976)

# auto

通过编译器自动获取变量类型，:warning:常在类型长/复杂(lambda)的情况下使用

```cpp
vector<string> v;
auto pos = v.begin();//迭代器类型vector<string>::iterator
auto l = [](int x) -> bool {···};//获取lambda的返回类型
```

# =default & =delete

:book:https://www.ibm.com/developerworks/cn/aix/library/1212_lufang_c11new/index.html

简单理解为：
* =default：需要用编译器默认生成的（Big-Three）特殊成员函数
* =delete：禁止使用当前修饰的函数

## =default

- 类中的特殊成员函数（构造、析构、拷贝、赋值）显式定义后，编译器默认生成的将失效
- 若仍需使用默认的函数，则必须显式定义，`增加编码工作量`
- 此外，显式定义的函数`效率低于`编译器自动生成的
- :warning:可在类外定义，但只能修饰类的特殊成员函数，且该函数没有默认参数

## =delete

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
# decltype

简单理解为：用于获取对象类型
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

# initialization

C++11之前初始化可以使用（）、{ }、=，C11提出一致使用{ }进行初始化

:warning:编译器看到{ }，实际生成的是initializer_list<T>，即`初始化列表`

:warning:初始化列表背后关联`array<T,n>`容器（仅包含array的头部指针），并将容器中的值挨个传递到`构造函数`

:warning:如果构造函数的参数本身就是initializer_list<T>，则整体直接传递，不再进行拆解

## initializer_list

使用{ }设置默认初值

```cpp
int i;//未定义的初值
int j{};//j为int，默认0
int* p;//未定义的初值
int* q{};//q为int*，默认nullptr
char c{99999};//原则上不可以，根据编译器而定error/warning
```

initializer_list<T>作为函数参数，接收任意个T类型的参数

```cpp
void print(initializer_list<int> vals);
print({1,2,3,4,5});//必须使用{ }传参
```

# lambda

可以简单当作是inline函数，格式如下：

  ```cpp
[Ⅰ] (Ⅱ) mutable throw -> retType {Ⅲ}
  ```

  - []：导入器，捕获外部变量，传值(默认)/传引用

  - ()：参数，当需要传参，或指定mutable、throw、retType之一时，则必须有

  - mutable：决定[]中的值是否可以进行修改，可选

    ```cpp
    int id=0;
    auto f1 = [id]()mutable{//id为值传递，指定mutable则内部可以修改id值
        //但注意此时，id作为0传递进来
        cout<<id<<endl;
        ++id;
    };
    id=42;
    f1();//调用lambda，值传递传入的id为0，但不影响外面的id值42
    auto f2 = [&id]()mutable{···};//传引用，则lambda内部的id和外部“共享”
    auto f3 = [=,&id]{···};//除id外的其余变量均为默认的值传递，没有mutable不能进行修改
    ```

  - throw：抛出异常，可选

  - retType：返回类型，可选

:warning:默认情况下，``lambda函数总是一个const函数``，mutable可以取消其常量性

# rvalue references

:book:https://www.cnblogs.com/qicosmos/p/3369940.html

:book:https://www.cnblogs.com/qicosmos/p/3376241.html

:book:https://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/index.html

:book:https://segmentfault.com/a/1190000016041544 (**更为详细全面**)

- 减少不必要的对象拷贝；使泛函定义更简洁

- 实现移动语义（Move Sementics）和完美转发（Perfect Forwarding）

## lvalue & rvalue

- 左值：表达式结束后依然存在的`持久化对象`

- 右值：常表现为`临时对象`，只在当前语句中有效

  ```cpp
  int a = get_a();//a为左值，非引用返回的get_a()返回的临时变量为右值（纯右值）
  int b = std::move(a);//通过move返回的右值（将亡值）
  ```

- 区分方法：若可对表达式`用 & 符取址`，则为左值，否则为右值

- 右值也可以被修改：

  ```cpp
  //T()生成临时对象（右值），并将对象内部的变量通过set方法进行修改
  T().set().get();
  ```
## lvalue references & rvalue references

- 左值赋值左值引用（变量别名），右值赋值右值引用（临时变量的别名，生命周期延长）

  ```cpp
  int a = 1;
  int& refa = a;//左值引用refa，只能被左值a赋值，refa为左值
  //！int& b = 1; 左值引用b不能被右值1赋值
  //！int&& b = a; 右值引用b不能被左值a赋值
  int&& b = 1;//右值引用b，只能被右值1赋值，但注意此时b本身为左值
  ```

- const lvalue references

  ```cpp
  const int& a = 1;//const左值引用可以接收右值
  ```

## Move Sementics

- 对于右值的拷贝和赋值会调用`移动构造函数`和`移动赋值操作符`

- 若没有定义，则`拷贝构造函数`和`拷贝赋值操作符`会被调用

  ```cpp
  //拷贝构造，若没有移动构造，当参数使用move或传递右值时，由于拷贝构造参数为const T&，因此才会接受右值进行调用
  MyString(const MyString& str): _len(str._len) {
      _data = new char[_len+1]; //新开辟空间
      memcpy(_data, str._data, _len); //拷贝操作 
     	_data[_len] = '\0';
  }
  //移动构造，当vector/deque扩容时，移动构造使用noexcept确保成功扩容
  //str需要修改，因此不加const，但需要noexcept（表明一定不会发生异常）
  MyString(MyString&& str) noexcept : _len(str._len) {
      _data = str._data; //直接将传入的str赋值
      str._len = 0; //传入的str长度置0
      str._data = NULL; //打断！将传入的str置空
  }
  //拷贝赋值
  MyString& operator=(const MyString& str) {
      if(this != &str){
          if(_data) delete _data;
          _len = str._len;
          _data = new char[_len+1]; //新开辟空间
          memcpy(_data, str._data, _len); //拷贝操作 
          _data[_len] = '\0';
      }
      return *this;
  }
  //移动赋值
  MyString& operator=(MyString&& str) noexcept {
      if(this != &str){
          if(_data) delete _data;
          _len = str._len;
          _data = str._data; //直接将传入的str赋值
          str._len = 0; //传入的str长度置0
          str._data = NULL; //打断！将传入的str置空
      }
      return *this;
  }
  ```

- 普通的函数和操作符也可以利用右值引用操作符实现转移语义

## std::move

- 希望将左值转为右值：

```cpp
void fun(int& i) {···} //①
void fun(int&& i) {···} //②重载①
int main() { 
	int a = 0; 
	fun(a);//左值，调用①
	fun(std::move(a));//右值，调用②
}
```
- 使用move后，原对象并非立即析构

```cpp
string b="123";
string c = std::move(b);
cout<<"B:"<<b<<" "<<&b<<endl;//B: 0x61fe10，move后b对象依旧在，只是内容为空
cout<<"C:"<<c<<" "<<&c<<endl;//C:123 0x61fdf0
std::move(c);//只是调用move而不进行移动构造或移动赋值，则原对象没有影响
cout<<"C:"<<c<<" "<<&c<<endl;//C:123 0x61fdf0
```

## universal reference

通用引用T&&不一定为右值引用，取决于`初始化`，以及是否发生`类型推导`

```cpp
template <typename T>
void fun(T&& param){···}//T类型需要推导，T&&为通用引用
fun(10);//param被右值10初始化
int x = 10;
fun(x);//param被左值x初始化
void fun(const T&& param){···};//const T&&不需要推导，为右值引用
void fun(vector<T>&& param){···};//右值引用
```

引用折叠：只有右值引用推导为右值引用时，得到的还是右值引用；否则将变为左值

```cpp
template <typename T>
void f(T&& param){···}
int a = 1;
int& ra=a;
int&& aa = 1;
//a,ra,aa均为左值，传入f()，T&&则为左值引用
string str = "hello";
f(string("hello")); //参数是右值，T&&为右值引用 
f(std::move(str));//参数是右值，T&&为右值引用 
```

## Perfect Forwarding

```cpp
void fun(int& i) {···} //①
void fun(int&& i) {···} //②重载①
void forward(int&& i) {fun(i);}//经过传递，临时对象i成为命名对象，内部调用①
void forward_value(int&& i) {//int&&类型确定，因此只能传递右值
    fun(std::forward<int>(i));//std::forward实现右值的完美转发
}
int main() { 
	int a = 0; 
	fun(a);//左值，调用①
	fun(1);//右值，调用②
	forward(2);//2传入forward内部后调用①，不完美的转发！
	forward_value(3);//3传入内部后，std::forward确保调用②
}
```

上述情况虽然使用forward可以将右值进行完美传递，但类型还是有局限性

```cpp
//通用引用+forward进行完美转发
void f(int& p){···}//传入左值时
void f(int&& p){···}//传入右值时
void f(const int& p){···}//传入const左值时
void f(const int&& p){···}//传入const右值时
template <typename T>
void perfect_forward(T&& t) {
    f(std::forward<T>(t));//使用forward但此时T类型不确定，则f()接收的是通用引用
}
```

# smart pointer

侯捷的C++11视频缺失，但在[:tv:](https://www.bilibili.com/video/BV14s411E772?p=17) 中有所提及
:book:https://simonfang1.github.io/blog/2018/08/23/smart-pointer/  
:book:http://www.cplusplus.com/reference/memory/auto_ptr/  
:book:https://interview.huihut.com/#/?id=%e6%99%ba%e8%83%bd%e6%8c%87%e9%92%88  
:book:https://www.jianshu.com/p/e4919f1c3a28

## auto_ptr（C11弃用）

* auto_ptr对象间赋值拷贝后所有权将被转移，且原来的指针将被`置空`

  ```cpp
  //auto_ptr以值传递方式作为参数
  void Fun(auto_ptr<T> tp){···}
  void main()
  {
      std::auto_ptr<T> p(new T); 
  	Fun(p);//p传入时发生拷贝，此时p已经为nullptr
  	//! p->xxx;
  } 
  ```

* auto_ptr对象`仅使用delete`析构，无法管理数组

  ```cpp
  //! std::auto_ptr<T> p(new T[5]);
  ```

* 不能和标准容器一起使用

## unique_ptr（代替auto_ptr）

- 不支持赋值拷贝，但可以使用`move`显式转移所有权

  ```cpp
  std::unique_ptr<T> p1(new T);
  //! std::unique_ptr<T> p2 = p1;
  std::unique_ptr<T> p2 = std::move(p1); // ok
  ```

- 析构时可以delete，也可delete[]，因此可以管理数组

  ```cpp
  std::unique_ptr<T> p1(new T);// delete p1
  std::unique_ptr<T[]> p2(new T[5]);//delete[] p2
  ```

- `release()`仅释放所有权，而`reset()`同时会释放资源

## shared_ptr（基于`引用计数`实现）

- 多个shared_ptr指向同一对象时，共享一个引用计数器并记录shared_ptr实例数量

- 当最后一个指向对象的shared_ptr销毁时，会自动销毁其所指对象

  ```cpp
  std::shared_ptr<int> p1(new int);//直接创建
  std::shared_ptr<int> p2 = make_shared<int>(100);//make_shared高效创建
  ```

- `use_count()`方法得到强引用计数值

- 默认使用delete析构，析构数组需显式指定

  ```cpp
  //使用lambda表达式指定delete[]析构
  std::shared_ptr<T> p1(new T[5],[](T* p){delete[] p;});
  ```

- 避免不同的share_ptr指向同一资源

  ```cpp
  int* p = new int;
  std::shared_ptr<int> p1(p);//p1计数1，p1析构后销毁p
  std::shared_ptr<int> p2(p);//p2计数1，p2析构时p已经被销毁
  ```

- `循环引用问题`

  ```cpp
  class B;
  class A
  {
  public:
  	A():m_sptrB(nullptr){};
  	~A(){}
  	shared_ptr<B> m_sptrB;//A中包含B类型的share_ptr
  };
  class B
  {
  public:
  	B():m_sptrA(nullptr){};
  	~B(){}
  	shared_ptr<A> m_sptrA;//B中包含A类型的share_ptr
  };
  void main()
  {
  	shared_ptr<A> pA(new A);//A类型的share_ptr，pA计数1
  	shared_ptr<B> pB(new B);//B类型的share_ptr，pB计数1
  	pA->m_sptrB = pB;//m_sptrB引用pB，pB计数2，pA析构后计数1
  	pB->m_sptrA = pA;//m_sptrA引用pA，pA计数2，pB析构后计数1
  }
  ```

- 多线程情况:link:https://www.jianshu.com/p/c75a0d33655c

  - 共享指针本身的``引用计数``操作是``原子的``，不会有内存泄漏
  - 对共享指针内部封装的``原始指针``进行操作时，则``需要加锁``
  - 当同时读写同一个共享指针时，不能确定``编译器操作引用计数和原始指针的先后顺序``

  解决方法：运用weak_ptr检测指针是否被释放，有两种方法：

  1. 使用**weak_ptr.lock**函数得到一个shared_ptr指针，如果已经释放返回空
  2. 直接使用weak_ptr.expired()来判断一个指针是否被释放

## weak_ptr（解决循环引用问题）

- 指向shared_ptr管理的对象，但不会增减`强引用`计数器

- 调用`expired()`比调用`use_count()`方法速度更快，以确定是否指向有效资源

- 调用`lock()`将weak_ptr转型为share_ptr

  ```cpp
  std::shared_ptr<T> sp1(new T);//直接创建share_ptr，强引用计数1
  std::weak_ptr<T> wp1(sp1);//使用share_ptr创建weak_ptr，弱引用计数1，强引用计数1
  std::weak_ptr<T> wp2 = wp1;//使用weak_ptr创建weak_ptr，弱引用计数2，强引用计数1
  std::shared_ptr<T> sp2 = wp2.lock();//将weak_ptr转型为share_ptr
  ```

- 解决循环引用

  ```cpp
  class B;
  class A
  {
  public:
  	weak_ptr<B> m_sptrB;//A中包含B类型的weak_ptr
      void PrintpB()
      {
          if(!m_sptrB.expired())//弱引用B有效，则lock为强引用
              cout<< m_sptrB.lock( )->m_b<<endl;
      }
  };
  class B
  {
  public:
  	weak_ptr<A> m_sptrA;//B中包含A类型的weak_ptr
  	int m_b;
  };
  void main( )
  {
  	shared_ptr<A> pA(new A);//A类型的share_ptr，pA强引用计数1
  	shared_ptr<B> pB(new B);//B类型的share_ptr，pB强引用计数1
  	pA->m_sptrB = pB;//弱引用m_sptrB引用pB，pB强引用计数1，弱引用计数1，pA析构->强计数0->释放对象->弱引用无效
  	pB->m_sptrA = pA;//弱引用m_sptrA引用pA，pA强引用计数1，弱引用计数1，pB析构->强计数0->释放对象->弱引用无效
  	pA->PrintpB(); 
  }
  ```

# 面试补充

## shared_ptr初始化unique_ptr?

```cpp
shared_ptr<int> sp=make_shared<int>(100);
unique_ptr<int> u=make_unique<int>(1);
// unique_ptr<int> up=move(sp);！！！编译错误
//不存在用户定义的从 "std::shared_ptr<int>" 到 
//"std::unique_ptr<int, std::default_delete<int>>" 的适当转换
unique_ptr<int> up=move(u);
```

## 手撕智能指针

:link:https://blog.csdn.net/yanchenzhi/article/details/107591037

### unique_ptr

```cpp
template <typename T>
class UniquePtr
{
private:
    T* m_p;//裸指针，智能指针内部包含的普通指针
    //禁止拷贝构造
    UniquePtr(const UniquePtr<T>& p)=delete;
    //禁止赋值
    UniquePtr<T>& operator=(const UniquePtr<T>& p)=delete;
public:
    //构造方法，使用普通指针初始化，默认值nullptr
    UniquePtr(T* p=nullptr):m_p(p){};
    ~UniquePtr()//析构函数，delete指针释放资源
    {
        if(m_p)
        {
            delete m_p;
            m_p=nullptr;
        }
    }
    //重载*运算符
    T& operator*(){return *m_p;}
    //重载->运算符
    T* operator->(){return m_p;}
};
```

### shared_ptr

```cpp
template <typename T>
class SharedPtr
{
private:
    T* m_p;//裸指针
    int* count;//int指针指向共享的计数值
public:
    //无参构造，计数0(nullptr)，普通指针根据具体类型T*置为0，nullptr
    SharedPtr():count(0),m_p((T*)0){};
    //使用普通指针构造，时刻注意count是指针，因此new int
    SharedPtr(T* p):count(new int(1)),m_p(p){}
    //拷贝构造
    //1.参数p同样为shared_ptr，因此需要取p.m_p裸指针赋值
    //2.拷贝后，参数p的引用计数++，count先指向参数的count
    //可以直接在初始化形参列表中：count(&(++ *p.count))
    //先p.count取得参数的int计数指针
    //再*操作取得计数的值，并++
    //最后&操作取得参数计数指针的地址，并赋值给count
    SharedPtr(const SharedPtr<T>& p):count(p.count),m_p(p.m_p)
    {
        ++(*count);//*取count值后++
    }
    //重载赋值=运算符
    //1.赋值m_p
    //2.赋值count
    //由于是将参数所在的指针赋给当前指针，因此当前指针的引用计数需要--，而参数指针的计数++
    //因此还需判断当前指针计数，为零则需析构
    SharedPtr<T>& operator=(const SharedPtr<T>& p)
    {
        //如果自赋值，直接返回本身*this
        if(this == &p) return *this;
        //参数指针的引用计数++，p.count获取参数的int指针，*取引用计数的值，最后++
        ++(*(p.count));
        //是否析构
        if(m_p && --(*count) == 0)
        {
            delete m_p;
            delete count;//此时析构并不置空
        }
        //进行赋值操作
        count = p.count;
        m_p = p.m_p;
        return *this;
    }
    //重载*运算符
    T& operator*(){return *m_p;}
    //重载->运算符
    T* operator->(){return m_p;}
    //析构，计数为0时才析构，否则计数值--即可
    ~SharedPtr()
    {
        //m_p为空则不需要操作
        //否则先--count，如果不为零也不需要操作
        //否则析构，释放资源
        if(m_p && --(*count) == 0)
        {
            delete m_p;
            delete count;
        }
    }
    //返回引用计数值
    int getCount(){return *count;}
};
```

