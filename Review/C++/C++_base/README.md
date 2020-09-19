:link:[c++那些事](https://light-city.club/sc/)、[interview](https://interview.huihut.com/#/)

# 从cpp到exe

:link:https://www.cnblogs.com/mhq-martin/p/11898245.html

:link:https://my.oschina.net/u/920274/blog/3126740/print

| 过程     | 编写源程序 | 预编译 | 编译 | 汇编 | 链接 |
| -------- | ---------- | ------ | ---- | ---- | ---- |
| 文件后缀 | .cpp       | .i     | .s   | .o   | .exe |

## 预编译

- 展开头文件：将`#include`中指定的代码写入当前文件
- 宏替换：将源程序中使用宏定义`#define`修饰的宏名称，替换为对应的字符串文本
- 条件编译：根据[C++条件编译](https://blog.csdn.net/ForestRound/article/details/52717968)指令`#ifndef`等，判断将要进行编译的代码块，``防止头文件被重复引用``
- 去掉注释：将`//`或`/**/`内容忽略

预编译结束后，生成的文件后缀`.i`

## 编译

- 根据`编译原理`那一套，检查代码规范性、是否有语法错误等（词法、语法、语义分析+优化）
- 接着将.i文件编译，生成一个用汇编语言描述的`.s`文件

:warning:此处只进行编译生成汇编代码，而不真正的进行汇编

## 汇编

- 把.s文件翻译成二进制机器指令`.o`文件

:warning:直接打开将乱码，使用反汇编工具才可以读懂

## 链接

- 链接所有的函数、全局变量，将所有的.o文件链接成一个可执行文件

:warning:当.o文件太多，链接不方便，因此将常用/共享的.o目标文件打包，就出现了静/动态链接库

### 静态库和动态库

:link:https://www.cnblogs.com/skynet/p/3372855.html

Windows下为.lib和.dll文件，Linux下为.a和.so文件

静态链接库：

- 链接时将汇编生成的目标文件 .o 与引用的库（函数库等）一起链接打包到可执行文件中，`体积大`
- 程序运行时，与函数库再无关联，因此``移植性好``
- 不同程序链接相同的静态库，因此内存中有多份拷贝，``浪费资源空间``
- 当静态库进行更新，则所有链接静态库的程序均需要重新编译链接（`全量更新`）

动态链接库：

- 程序编译为可执行文件后，可执行文件并未链接需要的函数库，`体积小`
- 只有当程序开始运行时，才会搜索文件系统，将需要的函数库动态加载进来（``移植性差``）
- 不同程序可以共享一份动态库，``节省资源空间``
- 只需要进行动态库本身的更新，程序不需要改动（`增量更新`）

# 程序内存分配

:link:https://blog.csdn.net/u010594850/article/details/25512269

:link:https://chenqx.github.io/2014/09/25/Cpp-Memory-Management/

![程序内存](images/20180122125137873.png)

Linux 系统中的``每个段``都是从 0 地址开始的整个 `4GB 虚拟空间`（32 位环境下），内核1G+用户空间3G

用户空间中的3G虚拟地址空间，地址从低到高依次被分配为：

- 程序代码区：存放函数体（成员函数、全局函数）编译后的二进制可执行代码，只读（注意地址并非从0x0开始）

- 常量区：存放=（赋值符号）右边的立即数、字面量、字符串常量等（右值），只读，:rotating_light:和const修饰与否无关！

- 全局数据区：存放全局变量、静态变量，程序运行期间一直存在

  ```cpp
  //验证环境vscode，gcc version 8.1.0 (x86_64-posix-seh-rev0, Built by MinGW-W64 project)
  int d;
  static int e;
  int f;
  int a=1;
  static int b=2;
  int c=3;
  int main()
  {
      cout<<&a<<" "<<&b<<" "<<&c<<"　"<<&d<<" "<<&e<<" "<<&f<<endl;
      //0x403010 0x403014 0x403018　0x407030 0x40703c 0x407034
      static int g;
      static int h=4;
      cout<<&g<<" "<<&h<<endl;
      //0x407040 0x40301c
      return 0;
  }
  ```

  - 全局数据区内，初始化的变量位于低地址，未初始化的位于高地址
  - 所有初始化的全局变量（无论static）按照定义先后顺序，向着地址增长的方向存放
  - `未初始化的全局变量，static全局变量和普通全局变量地址也是分开的`，目前来看中间隔了8个字节
  - `未初始化的普通全局变量位于低地址，而static在高地址`，两部分也分别按照定义先后顺序，地址向上增长

- 堆：包括``动态分配的内存``，从低地址开始向上增长

- 文件映射段：包括动态库、共享内存等，从低地址开始向上增长（跟硬件和内核版本有关）

- 栈：包括``局部变量``和``函数调用的上下文``等，栈的大小是固定的，一般是 `8 MB`，可配置修改，``地址向下增长``

## 堆和栈的区别

申请方式：

- 堆由new/delete，malloc/free等方法动态分配，容易出现内存泄漏
- 栈由系统自动分配（:warning:栈区的内存空间也可使用alloca动态分配，但会自动释放）

申请后系统的响应：

- 栈只要剩余空间大于申请空间，即可分配，直到异常提示栈溢出

> 操作系统有一个记录空闲内存地址的链表

- 堆申请时遍历空闲链表，找到首个满足分配大小的内存块进行分配，并从空闲链表中删除
  - 如果分配的内存块有剩余，则将剩余部分加入空闲链表
  - 分配的内存首地址一般记录分配的大小，delete时才能正确释放

申请大小限制：栈的大小一般较小，而堆32位理论可分配4G

生长方向：栈向下（地址下降），堆向上（地址上升）

碎片化：栈每次分配连续的内存，无碎片问题；堆如果频繁new/delete势必造成内存不连续，产生大量碎片

分配效率：栈的分配往往对应CPU指令级别的操作，效率高；堆往往由库函数提供分配方法，效率低

## [对象创建的两种方式](https://www.cnblogs.com/lfri/p/12593582.html)

- 静态建立：``A a;``
  - 对象分配在``栈空间``
  - 编译器移动栈顶指针腾出空间，再``直接调用构造函数``创建对象
  - 对象生命结束，编译器调用析构函数释放栈空间
- 动态建立：``A* a = new A();``
  - 执行``operator new()``函数，在``堆空间``中寻找内存分配
  - 调用构造函数，在分配的内存中创建对象

> C++是静态绑定语言，编译器管理了对象的整个生命周期

:link:https://blog.csdn.net/qq_40840459/article/details/80079608

### 只在栈上生成对象的类

- `将new和delete操作符重载为私有`
- 此时使用new创建对象，编译器无法进行访问

### 只在堆上生成对象的类

- ``将析构函数设为私有``，最好设为protected，确保多态时正常执行父类的虚析构函数
- 此时使用静态创建对象，编译器无法进行访问

:warning:此时需要单独定义一个函数，执行delete进行内存空间的释放

```cpp
class A 
{
private:
    void* operator new(size_t t){}      // 注意函数的第一个参数和返回值都是固定的   
    void  operator delete(void* ptr){}  // 重载了new就需要重载delete     
};
class B  
{  
public :
    void  destory(){ delete this;}  
protected :  
    virtual ~B(){}  
};
class C:public B{};
int main() 
{
    A a;//0x61fe2f
    cout<<&a<<endl;
    //!!! A* a2 = new A();             //函数 "A::operator delete" 不可访问
    //!!! B b;                         //"B::~B() noexcept" 不可访问
    B* b = new B();//0x7c1700
    cout<<b<<endl;
    b->destory();
    C c1;//0x61fe20
    C* c2 = new C();//0x7c1700
    cout<<&c1<<" "<<c2<<endl;
} 
```

## new/delete和malloc/free区别

:link:https://www.cnblogs.com/qg-whz/p/5140930.html

|        特征        |                    new/delete                    |             malloc/free              |
| :----------------: | :----------------------------------------------: | :----------------------------------: |
|   分配内存的位置   |           自由存储区(C++基于new的概念)           |         堆(C/操作系统的概念)         |
| 内存分配成功返回值 |                   完整类型指针                   | void*，一般需要强制转换为需要的类型  |
| 内存分配失败返回值 |              默认抛出bac_alloc异常               |               返回NULL               |
|   分配内存的大小   |             由编译器根据类型计算得出             |          必须显式指定字节数          |
|      处理数组      |           有处理数组的new[]和delete[]            | 需要用户计算数组的大小后进行内存分配 |
|  已分配内存的扩充  |                  无法直观地处理                  |         使用realloc简单完成          |
|    是否相互调用    | 可以，operator new/delete实现底层调用malloc/free |             不可调用new              |
| 分配内存时内存不足 |       客户能够指定处理函数或重新制定分配器       |       无法通过用户代码进行处理       |
|      函数重载      |                       允许                       |                不允许                |
| 构造函数与析构函数 |                       调用                       |                不调用                |

有了malloc为什么还需要new？

- 对于``非内部数据类型的对象``而言，用maloc/free无法满足动态对象的要求
- 对象在创建的同时要自动执行构造函数，对象在消亡之前要自动执行析构函数
- 由malloc/free是库函数而不是运算符，不在编译器控制权限之内

# 内存对齐

:link:https://zhuanlan.zhihu.com/p/101140160

:link:https://www.jianshu.com/p/49ddb946a226

对齐：内存中数据首地址是CPU单次获取数据大小的整数倍

目的

- 平台原因(移植原因)：代码移植时硬件平台不同，内存地址不能随便访问

- 性能原因：加快CPU寻址，确保一次访问内存就能获取到完整的数据

``#pragma pack(n)``：设定结构体、联合以及类成员变量以 n 字节方式对齐

关于该指令其他用法，参考[#pragma pack 指令详解](https://www.jianshu.com/p/90a6eef329ec)

## sizeof()

:warning:运算符/关键字，判断数据类型或者表达式长度

```cpp
cout << sizeof(char) << endl;  // 1
cout << sizeof(short) << endl;  // 2
cout << sizeof(int) << endl;  // 4
cout << sizeof(double) << endl;  // 8
```

## 对齐规则

- 基本类型的对齐值就是其sizeof值
- 数据成员对齐规则：结构(struct)(或联合(union))的数据成员
  - 第一个数据成员放在offset为0的地方
  - 以后每个数据成员的对齐按照#pragma pack指定的数值和这个数据成员自身长度中，比较小的那个进行

- 结构(或联合)的整体对齐规则：
  - 数据成员完成各自对齐
  - 结构(或联合)本身也要进行对齐
  - 对齐将按照#pragma pack指定的数值和结构(或联合)最大数据成员长度中，比较小的那个进行;

关于共用体和结构体，参考[C语言中关于sizeof(struct)和sizeof(union)](:link:https://juejin.im/post/6844904022877405191)

关于虚函数、虚继承，参考[c++普通继承、虚继承、虚函数对sizeof的影响](https://blog.csdn.net/fuhuixin7497/article/details/78198287)

关于位域的sizeof，参考[含位域结构体的sizeof](http://blog.chinaunix.net/uid-20726927-id-2455478.html)、[C/C++ 位域知识小结](https://www.cnblogs.com/zlcxbb/p/6803059.html)

# 面向对象特性

封装：将事物抽象为类，对不可信的类/对象隐藏自身属性/方法，使得代码模块化

继承：使用现有类的全部功能，并在不改动原有类的前提下对功能进行扩展

多态：不同对象调用同一个方法而表现出不同的行为

# C++类访问控制

https://blog.csdn.net/shuzfan/article/details/68954774

|                            | public    | protected | private |
| -------------------------- | --------- | --------- | ------- |
| 类成员是否可以访问         | Yes       | Yes       | Yes     |
| 友元是否可以访问           | Yes       | Yes       | Yes     |
| 子类是否可以访问           | Yes       | Yes       | No      |
| 类的实例化对象是否可以访问 | Yes       | No        | No      |
| public继承                 | public    | protected | private |
| protected继承              | protected | protected | private |
| private继承                | private   | private   | private |

# [C++类间关系]([https://www.fa1c0n.cn/2020/03/08/C++%E9%9D%A2%E5%90%91%E5%AF%B9%E8%B1%A1%E9%AB%98%E7%BA%A7%E5%BC%80%E5%8F%91-%E7%BB%A7%E6%89%BF%E3%80%81%E5%A4%8D%E5%90%88%E3%80%81%E5%A7%94%E6%89%98%E4%B8%8E%E7%BB%84%E5%90%88%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/](https://www.fa1c0n.cn/2020/03/08/C++面向对象高级开发-继承、复合、委托与组合设计模式/))

:link:https://www.jianshu.com/p/4d2e63e71a07

:link:https://www.cnblogs.com/narutow/p/8117352.html

## 继承

从内存的角度上讲，子类拥有父类的成员变量，对于成员函数来说，继承代表子类拥有函数的调用权

变量的初始化顺序：

- 基类的静态变量或全局变量按照定义

- 派生类的静态变量或全局变量按照定义

- 基类的成员变量

- 派生类的成员变量

## Composition 组合

当一个类中``包含另外一个类对象``时，可称为组合

- 构造由内而外：先调用包含的那个类的构造方法，在调用自身的构造
- 析构由外而内：先调用自身析构，再调用内部包含的

:warning:创建对象时，两个类的对象同时会创建，因此两个类对象的生命周期是一致的

### 组合+继承

- 子类继承父类，父类存在组合
  - 构造：组合的类构造=>父类=>子类
  - 析构：子类析构=>父类析构=>组合类析构
- 子类继承父类，子类存在组合
  - 构造：父类构造=>组合类构造=>子类
  - 析构：子类析构=>组合类析构=>父类

## Delegation 委托

Composition by reference：一个类中只记录另一个类的指针，并不是包含关系

- 当前类只是将部分功能委托给另一个类实现
- 被委托的类对象，生命周期不被限制，等到需要用到的时候才去创建

### 委托+继承

观察者模式的实现方式

- 委托类即为观察目标
- 观察者抽象类即为被委托的父类
- 具体的观察者即为继承父类的子类

![观察者](images/image-20200807195739441.png)

# C++对象模型

:link:https://cloud.tencent.com/developer/article/1155155

![对象模型](images/image-20200802195850936.png)

## 多态与虚表

C++ 多态分类及实现：

1. 重载多态（编译期）：函数重载、运算符重载
2. 参数多态（编译期）：类模板、函数模板
3. 强制多态（编译期/运行期）：基本类型转换、自定义类型转换
4. 子类多态（运行期）：虚函数，由于在运行期间才能确定，因此为``动态多态``

虚函数：用 virtual 修饰的``非静态成员函数``

- static修饰的函数在对象构造之前已经存在，不能为虚函数
- 构造函数出现在对象生成之前，因此不能为虚函数
- 析构函数指定为虚函数，当析构发生了多态的对象时（父类指针指向子类），正常调用子类析构函数，防止内存泄漏

:rotating_light:当没有虚函数时，父类指针可以指向子类，:link:https://blog.csdn.net/FX677588/article/details/77727110

- 基类指针指向子类，该指针只能访问基类方法（静态绑定）
- 子类指针指向基类，必须先做强制转型动作（不建议）
- 基类和子类定义了同名成员函数，指针类型是谁就调用谁

`如果编译器能明确知道调用的是哪个虚函数，则不用查虚表，直接调用`

## 虚指针、虚表存放位置

:link:https://cloud.tencent.com/developer/article/1394319

- 虚指针：一般在对象内存的起始位置，即就是对象的地址（32位占4字节），保证多层/多重继承下获得虚表效率高
- 虚表：应用程序的常量区，虚指针指向的地址（首个虚函数地址）

## 非继承

- 非静态数据成员：位于每一个对象内存中
- 静态数据成员、静态成员函数、非静态成员函数：位于对象内存之外
- 虚函数：虚指针指向的虚函数表

虚函数表：

- 每个具有虚函数的类，和类绑定（所有该类对象``共用一个虚表``）
- 表中按照虚函数在类中的``定义顺序``，依次存放对应的指向虚函数地址的指针
- 虚函数表之前设置一个指向type_info的指针，用以支持RTTI（运行时类型识别），用于描述对象继承关系等

虚表指针：

- 每个对象都有虚表指针(vptr)，由编译器为其生成

## 单继承

- 子类和父类各拥有自己的虚函数表
- 子类若``重写父类的虚函数``，则子类虚函数将``覆盖虚表中对应的父类虚函数``
- 若子类声明自己``新的虚函数``，则该虚函数地址将``扩充到虚函数表最后``

## 多继承

- 子类``新增的虚函``数被放在声明的``第一个基类``的虚函数表中
- 发生``重写``时，``所有基类``的虚函数都被子类``覆盖``
- 内存布局中，``父类按照其声明顺序排列``

## 虚继承

虚继承解决了菱形继承中``最派生类``拥有``多个间接父类实例``的情况

- 虚继承的子类也``保留父类的vprt与虚函数表``，与子类内容`以一个四字节的0`来分界

- 若发生虚函数``重写``，同样地将``覆盖``父类中的虚函数表对应位置
- 若声明``新的虚函数``，则编译器将为子类增加一个`新的虚表指针vptr`，对应新的虚函数表

虚继承中的子类，生成一个隐藏的``虚基类指针``， 指向``虚基类表``，存放的是**偏移值**

偏移值：

- 第一个条目存放``虚基类指针所在地址``到该类``对象内存首地址``的偏移值
- 如果有虚函数指针，值为-4；否则为0
- 其余条目为该类的``最左``虚继承父类、``次左``虚继承父类...的内存地址``相对于虚基类指针``的偏移值

## 菱形虚继承

- 在子类对象内存中，基类出现的顺序是：``最左父类、次左父类、虚祖父类``
- 子类对象的``数据成员放在虚祖父类前面``，两部分数据依旧以``0来分隔``
- 子类``覆盖并扩展最左父类的虚函数表``，与简单继承的对象模型相同
- 虚祖父类的内容放到了子类对象内存布局的最后

# 指针VS引用

https://cloud.tencent.com/developer/article/1021622

- 指针有自己的大小（32位4字节），而引用只是一个别名（汇编角度也占内存），sizeof是被引用对象的大小

- 指针可以被初始化为NULL，而引用必须声明时初始化

- 作为参数传递时，指针需要被解引用才可以对对象进行操作，引用不发生拷贝

- 指针在使用中可以指向其它对象，但是引用只能是一个对象的引用，不能被改变

- 指针可以有多级指针（**p），而引用至于一级

- 指针++指向下一个地址，引用++则是对被引用对象++

# ++i VS i++

++i 实现：

```cpp
int& int::operator++()
{
    *this +=1;
    return *this;
}
```

i++ 实现：

```cpp
const int int::operator++(int)
{
    int oldValue = *this;
    ++(*this);
    return oldValue；
}
```

https://www.zhihu.com/question/19811087

i++ 最后返回的是一个临时变量，而**临时变量是右值**

## 效率

:link:https://blog.51cto.com/genwoxuevc/499483

- 对于基本类型，效率无差异
- 对于自定义类型，++i更好，返回对象的引用，无拷贝开销

## 线程安全

线程不安全，非原子操作

# 宏

## #include

#include< >：引用的是编译器的``类库路径里面的头文件``，一般是引用自带的一些头文件

#include" "：引用的是程序目录的``相对路径中的头文件``，一般是用来引用自己写的一些头文件

:warning:使用 #include" " 先在项目当前目录查找是否有对应头文件，如果没有再去类库路径下找

## #define

:link:https://www.cnblogs.com/zhizhiyu/p/10155614.html

不带参数的宏定义：#define 宏名 字符串

- 使用宏可提高程序的通用性和易读性，减少不一致性，减少输入错误和便于修改。例如：数组大小常用宏定义
- 预处理阶段进行展开和替换，因此``不做语法检查``
- 可以用#undef命令终止宏定义的作用域

- 宏定义``不分配内存``

带参数的宏定义：#define 宏名（参数表） 字符串

- 宏名和参数的括号间不能有空格
- 宏替换只作替换，不做计算，不做表达式求解

- 宏展开不占运行时间，只占编译时间

宏比较大小：``` #define MIN(A,B)  ((A)<=(B)?(A):(B))```

#  const

## const和#define区别

:link:https://blog.csdn.net/love_gaohz/article/details/7567856

- const有具体类型，``分配内存``；宏定义没有，仅仅是展开，不分配内存
- const编译期间进行``类型检查``；宏定义位于预处理阶段，没有类型检查
- const在内存中只有``一份拷贝``；宏定义在替换后会出现多个拷贝

:warning:编译器通常不为普通const常量分配存储空间，而是将它们保存在符号表中，没有存储与读内存的操作，效率很高

## 基本说明

- const普通变量``当且仅当``在定义的时候进行初始化，一旦初始化之后就不能被再次赋值

- const成员变量只能在``初始化形参列表``中进行初始化操作

- const可用于对重载函数的区分

- const成员函数内部不能修改类的任何成员变量

  ```cpp
  class A
  {
  private:
      const int a;                // 常对象成员，只能在初始化列表赋值
  public:
      A(int x) : a(x) { };        // 初始化列表
      // const可用于对重载函数的区分
      int getValue();             // 普通成员函数
      int getValue() const;       // 常成员函数，不得修改类中的任何数据成员的值
  };
  ```

:red_circle:同时存在同名的const和非const成员函数时

- const对象只能调用const成员函数
- 非const只能调用非const成员函数

## 修饰指针和引用

```cpp
A b;                        // 普通对象，可以调用全部成员函数、更新常成员变量
const A a;                  // 常对象，只能调用常成员函数
const A* p = &a;            // 指针变量，指向常对象，即指向的对象不能变，指针本身可以变
A* const p = &b;            // 常量指针，即指针本身不能变，但可以指向不同对象
const A& q = a;             // 指向常对象的引用

char greeting[] = "Hello";
char* p1 = greeting;                // 指针变量，指向字符数组变量
const char* p2 = greeting;          // 指针变量，指向的字符char不可改变
char* const p3 = greeting;          // 自身是常量的指针，p3指针自身不可改变
const char* const p4 = greeting;    // 自身是常量的指针，指向字符数组常量，都不能变
```

:warning:主要判断const后面修饰的对象，如果是类型(int/class)即指向的对象不可变；如为变量名称即为指针/引用本身不能变

### const多级指针

:link:https://blog.csdn.net/SoYangA/article/details/80292025

- 一级指针
  - ``` const int* p```：p指向的int型数不能变
  - `int const *p`：同上，p指向的int型数不能变（可认为修饰*p，其中\*表示取值，即为int型数）
  - `int* const p`：p指针本身不可变
  - `const int* const p`：p指针本身不可变，p指向的int型数也不能变
- 二级指针
  - `const int** p`：p指向的int型数不能变
  - `int** const p`：二级指针p本身不可变
  - `int* const *p`：二级指针p指向的一级指针*p本身不可变
  - `const int* const * const p`：一级指针*p，二级指针p，指向的值均不可变

## 修饰函数参数

```cpp
void f1(const int Var);           // 传递过来的参数在函数内不可变
void f2(const char* Var);         // 参数指针所指内容为常量
void f3(char* const Var);         // 参数指针为常量
void f4(const int& Var);          // 引用参数在函数内为常量
```

:warning:`const int&`常引用作为函数参数，既避免了参数的拷贝，又避免了函数内部对实参值的修改

## 修饰函数返回值

```cpp
const int f5();      // 返回一个常数
const int* f6();     // 返回一个指向常量的指针变量，使用：const int *p = f6();
int* const f7();     // 返回一个指向变量的常指针，使用：int* const p = f7();
```

# extern "C"

作用：编译器将 `extern "C"` 声明的代码当作 C 语言代码处理（按照 C 语言方式编译和链接）

- 可以避免 C++ 因符号修饰导致代码不能和C语言库中的符号进行链接的问题

[关于extern](https://cloud.tencent.com/developer/article/1496000)

修饰的变量或函数，表示在其他文件中定义

关键字extern用于扩展变量和函数的可见性。 

由于函数默认存在extern,不需要再定义和声明的时候使用extern。 

当变量使用extern时，它只是声明没有定义。 

当变量用extern声明并且有初始化时，和变量的定义一样

# inline

作用：减少函数调用时的消耗，是否对函数内联，决定权在于编译器

- 一般不内联包含循环、递归、switch 等复杂操作的内联函数

- 在类声明中定义的函数，除了虚函数的其他函数都会自动隐式地当成内联函数

编译器处理步骤：

1. 将 inline 函数体复制到 inline 函数调用点处
2. 为所用 inline 函数中的局部变量分配内存空间
3. 将 inline 函数的输入参数和返回值映射到调用方法的局部变量空间中
4. 如果 inline 函数有多个返回点，将其转变为 inline 函数代码块末尾的分支（使用 GOTO）

优点

- 在被调用处进行代码展开，省去了参数压栈、栈帧开辟与回收，结果返回等，从而提高程序运行速度

- 在代码展开时，会做安全检查或自动类型转换（同普通函数），而宏定义则不会

- 内联函数在运行时可调试，而宏定义不可以

缺点

- 代码膨胀。内联是以代码膨胀（复制）为代价，消除函数调用带来的开销。如果执行函数体内代码的时间，相比于函数调用的开销较大，那么效率的收获会很少。另一方面，每一处内联函数的调用都要复制代码，将使程序的总代码量增大，消耗更多的内存空间。

- inline 函数无法随着函数库升级而升级。inline函数的改变需要重新编译，不像 non-inline 可以直接链接

虚函数内联：当虚函数表现多态性的时候不能内联

# static

https://blog.csdn.net/cc198877/article/details/8844729

修饰局部对象：延长局部对象生命周期（直到程序结束）

修饰全局对象：限制全局对象的作用域（仅在本文件内访问）

修饰普通变量：

- 声明时未赋初值，编译器根据类型会自动初始化
- 生命周期直到程序运行结束，不随函数运行结束而结束
- 只在当前文件可见（多人开发防止重名）

修饰成员变量：

- 只能在类外通过类名初始化`int A::a = 1;`

- 只有一个拷贝（和类绑定），一个对象的修改会影响其他对象（可以理解为共享）

  :warning:因为对象共享静态成员变量，因此`不能使用构造函数初始化`静态成员变量

- 一般通过`A::a`进行访问，也可以使用对象访问
- 可以作为成员函数的默认参数，但是普通的数据成员不行

  ```c++
  class A
  {
    int x;
    static int y;
    void add(int z=y){}  //可以，但是int z=x不行
  };
  ```

修饰普通函数：只在当前文件可见（多人开发防止重名）

修饰成员函数：

- 函数内部只能访问类的静态成员（变量/函数），但可以通过对象来引用非静态成员

  ```cpp
  class A{
  public:
      A(int x):s(x){}
      static void f(A& a)
      {
          cout<<a.s;//通过引用对象来操作非静态成员
          //cout<<s;
      }
      int s;
  };
  int main() 
  {
      A a(1);
      A::f(a);
  } 
  ```

  :warning:``非静态成员函数``可以``任意访问静态成员``

- 一般通过`A::f()`进行访问，也可以使用对象访问

## static成员函数this？

无this，static修饰后和类绑定，而this和对象绑定

## static成员函数virtual？

不可以，因为static编译期间就确定，virtual运行时才动态绑定

# this

指针，指向``调用非静态成员函数``的对象

1. 先将对象的地址赋给this指针
2. this指针作为非静态成员函数的``隐含参数``传递（由编译器完成）
3. 函数内部对成员变量操作时，都隐式使用this指针

this类型：

- this指针被隐含地声明为: `ClassName* const this`，this指针本身不能变
- 当调用const成员函数时，this指针的类型为：`const ClassName* const`，表明指针本身和指向的对象均不能改变

:warning:this是右值，不能取地址

需要显式使用this指针：

1. 为实现对象的链式引用
2. 为避免对同一对象进行赋值操作
3. 在实现一些数据结构时，如list

# friend

https://blog.csdn.net/u012796139/article/details/46404401

友元函数：本身是普通的函数，在类外定义

- 在类中通过friend修饰，类外通过对象访问类中的成员

友元成员函数：本身是成员函数，在另一个类中指定为友元函数

友元类：在类中使用friend修饰另一个类为友元类

- 在友元类中可以访问当前类中的成员

```cpp
class B;
class A{
public:
    virtual void vfa(){}
    void f(){}
};
void f(){}
class B{
    friend class A;//可在A中访问B的私有成员
    friend void f();//可在类外的普通函数中访问B的私有成员
    friend void A::vfa();//将A的虚函数指定为B的友元函数，该方法中可对B私有成员修改
    friend void A::f();//将A的成员函数指定为B的友元函数，该方法中可对B私有成员修改
};
```

## delete this

:link:https://blog.csdn.net/u010013164/article/details/38713083

:link:http://blog.sina.com.cn/s/blog_4b4cf2af0100ywgv.html#commonComment

构造函数中delete this：

- A a；试图delete一个未经new得到的指针，崩溃
- A* a = new A；合法

析构函数中delete this：

- delete先调用析构，再释放内存
- 析构中又delete，因此无限递归调用，栈溢出

在成员函数中delete this合法，但：

1. 保证this对象是通过 `new`分配的（不是 `new[]`、不是 placement new、不是栈上、不是全局、不是其他对象成员）
2. 必须保证调用 `delete this` 的成员函数是最后一个调用 this 的成员函数
3. 必须保证成员函数的 `delete this` 后面没有调用 this 了
4. 必须保证 `delete this` 后没有人使用了

# 4种强制类型转换

## C类型转换

`TYPE b = (TYPE) a`，可进行任意类型转换

- 转换不明确，不能进行错误检查，易出错

## static_cast

静态类型转换

静态：在``编译期间就可以决定``，使用率最高

- 用于各种隐式转换，比如非const转const，void*转指针等

- 不执行运行时类型检查（转换安全性不如 dynamic_cast）
- 通常用于转换数值数据类型（如 float -> int）
- 可以在整个类层次结构中移动指针
  - 子类转化为父类安全（向上转换）
  - 父类转化为子类虽然成功，但不安全（因为子类可能有不在父类的字段或方法）

## dynamic_cast

用于多态类型的转换，``执行行运行时类型检查``

- 只适用于指针或引用
  - 对不明确的``指针``的转换将失败，返回 `nullptr`
  - 对不明确的``引用``的转换将失败，引发``bad_cast异常``
- 可以在整个类层次结构中移动指针，包括向上转换、向下转换

## const_cast

用于删除 const、volatile 和 __unaligned 特性

- 目标类类型只能是指针或引用

## reinterpret_cast

`数据的二进制形式重新解释`，但不改变其值，其本身并不安全，不建议使用

- 滥用 reinterpret_cast 运算符可能很容易带来风险
- reinterpret_cast 运算符不能丢掉 const、volatile 或 __unaligned 特性
- reinterpret_cast 的一个实际用途是在哈希函数中
  - 通过让两个不同的值几乎不以相同的索引结尾的方式将值映射到索引

# 重载/隐藏/重写覆盖

https://cloud.tencent.com/developer/article/1177174

# STL

[侯捷STL](https://www.bilibili.com/video/BV1db411q7B8?p=3)

:link:https://blog.csdn.net/u012370255/article/details/40541499

| 容器                                                         | 底层数据结构      | 时间复杂度                      | 有无序 | 可不可重复 | 其他                                                         |
| ------------------------------------------------------------ | ----------------- | ------------------------------- | ------ | ---------- | ------------------------------------------------------------ |
| [array](https://github.com/huihut/interview/tree/master/STL#array) | 定长数组          | O(1)查询                        | 无序   | 可重复     | 支持随机访问                                                 |
| [vector](https://github.com/huihut/interview/tree/master/STL#vector) | 变长数组          | 尾部插入/删除O(1)其余O(n)       | 无序   | 可重复     | 支持随机访问                                                 |
| [deque](https://github.com/huihut/interview/tree/master/STL#deque) | 双端队列          | 头尾插入/删除 O(1)其余O(n)      | 无序   | 可重复     | 一个中央控制器 + 多个缓冲区，支持首尾快速增删，支持随机访问  |
| [forward_list](https://github.com/huihut/interview/tree/master/STL#forward_list) | 单向链表          | 插入、删除 O(1)                 | 无序   | 可重复     | 不支持随机访问                                               |
| [list](https://github.com/huihut/interview/tree/master/STL#list) | 双向链表          | 插入、删除 O(1)                 | 无序   | 可重复     | 不支持随机访问                                               |
| [stack](https://github.com/huihut/interview/tree/master/STL#stack) | deque / list      | 顶部插入、顶部删除 O(1)         | 无序   | 可重复     | deque 或 list 封闭头端开口，不用 vector 的原因应该是容量大小有限制，扩容耗时 |
| [queue](https://github.com/huihut/interview/tree/master/STL#queue) | deque / list      | 尾部插入、头部删除 O(1)         | 无序   | 可重复     | deque 或 list 封闭头端开口，不用 vector 的原因应该是容量大小有限制，扩容耗时 |
| [priority_queue](https://github.com/huihut/interview/tree/master/STL#priority_queue) | vector + max-heap | 插入、删除 O(log2n)             | 有序   | 可重复     | vector容器+heap处理规则                                      |
| [set](https://github.com/huihut/interview/tree/master/STL#set) | 红黑树            | 插入、删除、查找 O(log2n)       | 有序   | 不可重复   |                                                              |
| [multiset](https://github.com/huihut/interview/tree/master/STL#multiset) | 红黑树            | 插入、删除、查找 O(log2n)       | 有序   | 可重复     |                                                              |
| [map](https://github.com/huihut/interview/tree/master/STL#map) | 红黑树            | 插入、删除、查找 O(log2n)       | 有序   | 不可重复   |                                                              |
| [multimap](https://github.com/huihut/interview/tree/master/STL#multimap) | 红黑树            | 插入、删除、查找 O(log2n)       | 有序   | 可重复     |                                                              |
| [unordered_set](https://github.com/huihut/interview/tree/master/STL#unordered_set) | 哈希表            | 插入、删除、查找 O(1) 最差 O(n) | 无序   | 不可重复   |                                                              |
| [unordered_multiset](https://github.com/huihut/interview/tree/master/STL#unordered_multiset) | 哈希表            | 插入、删除、查找 O(1) 最差 O(n) | 无序   | 可重复     |                                                              |
| [unordered_map](https://github.com/huihut/interview/tree/master/STL#unordered_map) | 哈希表            | 插入、删除、查找 O(1) 最差 O(n) | 无序   | 不可重复   |                                                              |
| [unordered_multimap](https://github.com/huihut/interview/tree/master/STL#unordered_multimap) | 哈希表            | 插入、删除、查找 O(1) 最差 O(n) | 无序   | 可重复     |                                                              |

:link:https://blog.csdn.net/Virtual_Func/article/details/49724135

:red_circle:无法存放引用类型

## Array（C11）

数组：定长数组，初始化开辟空间后就不能改动

## Vector

变长数组，堆中开辟连续内存

使用三个指针确定空间范围：首、尾、容量大小

### resize()和reserve()

- `resize`：增加容器的size和capacity
- `reserve`：方法仅进行扩容

## 模拟Vector

https://blog.csdn.net/shanghx_123/article/details/86662085

1. 私有成员为三个普通指针：start、finish、end
2. begin返回start，end返回finish
3. size返回finish-start，capacity返回end-start
4. 重载[]运算符，返回start[pos]
5. 实现erase：将删除位置pos之后的数据向前覆盖，返回pos指针
6. 析构：delete[] start;再将三个指针置空
7. 实现reserve：开辟新空间n，赋值所有数据，重新定位三个指针
8. 实现resize：
   - 如果n小于size，调整finish=start+n
   - 如果n大于capacity，调用reserve(n)
   - 否则调整finish指针，新位置和旧位置之间使用参数指定的值覆盖
9. 实现insert：
   - 如果元素已达到容量，则2倍扩容，重置pos=start+size
   - 将pos之后的元素后移一位，在pos位置插入新元素

## map和unordered_map

使用场景：

除了有顺序要求和有单词操作时间要求的场景下用map，其他场景都使用unordered_map

# 面试补充

## if else 和 switch case

分支较多时，效率上：switch高

- if else 需要挨个判断，时间换空间，分支太多代码可读性差
- switch case 则直接跳转到对应case执行，空间换时间，代码可读性好

类型上：if 更灵活

- if else 判断条件为逻辑表达式，只要最终是bool类型即可
- swatch case 表达式类型受限：枚举/整型（int、 short、 char 、 byte）

## 递归、迭代、遍历和循环

- 循环(loop)：最基础的概念, 所有重复的行为
- 递归(recursion)：在函数内``调用自身``, 将复杂情况逐步转化成基本情况
- (数学)迭代(iterate)：在多次循环中逐步接近结果
- (编程)迭代(iterate)：按``顺序访问线性结构``中的每一项，迭代器（顺序、线性）
- 遍历(traversal)：``按规则访问非线性结构``中的每一项，树的遍历（前中后为规则，非线性）

迭代：轮番交替，并替代

循环：只是单一重复执行，中间没有替代操作

## 堆栈溢出

可能的原因

- 递归深度：函数每次被调用时都会将局部数据（在函数内部定义的变量、参数、数组、对象等）放入栈中
- 局部变量：存放在栈，大数据结构的局部变量

## 二维数组行列遍历

二维数组是按行存储的，按行遍历的效率更高 [参考链接1](https://blog.csdn.net/weixin_40497678/article/details/80733915)、 [参考链接2](https://blog.csdn.net/Shuffle_Ts/article/details/89420651)

## 抽象类和接口

:link:https://blog.csdn.net/hanxueyu666/article/details/75712917

能否取代？同名方法？

## 字符串拼接效率

## Union

数据覆盖时，考虑大端小端

https://blog.csdn.net/xiao3404/article/details/22276485

```cpp
union T
{
   int a;
   char b[2];
};
int main()
{
   T t;
   t.a=0;
   t.b[0]=1;
   t.b[1]=2;
   printf("v.l is %d\n",t.a);
   return 0;
}
```

输出513，分析：

1. t.a=0；将int的4字节（32位）全赋值为0
2. t.b[0]=1；注意`小端存储`，首个字节8位二进制覆盖为0000 0001
3. t.b[1]=2；第二个8位覆盖为0000 0010
4. 剩余2个字节的高地址依旧全0
5. 因此此时，0000 0000 + 0000 0000 + 0000 0010 + 0000 0001
6. 16进制数为201，10进制对应513
