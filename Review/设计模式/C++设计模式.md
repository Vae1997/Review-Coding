:link:https://segmentfault.com/a/1190000010706695

:link:https://design-patterns.readthedocs.io/zh_CN/latest/index.html

# 单例模式

:link:[简书](https://www.jianshu.com/p/edab2673ee6c),[牛客](https://www.nowcoder.com/tutorial/93/f982cd252694499181bcf1bb83780cad),[CSDN](https://www.cnblogs.com/sunchaothu/p/10389842.html)

保证一个类仅有一个实例，并提供一个该实例的全局访问点

三要素：

- 类只能有一个实例
- 类自行创建这个实例
- 类自行向系统提供这个实例

## C++11线程安全方式

```cpp
class Singleton final//final禁止继承
{
public:
    static Singleton& GetInstance(){//返回值为&类型
        static Singleton instance;//静态局部变量，当且仅当首次调用时创建一次
        return instance;
    }
private:
    Singleton() = default;//保留默认无参构造，置为private
    ~Singleton() = default;//保留默认析构
    //禁止拷贝构造、拷贝赋值、移动构造、移动赋值 
    Singleton(const CSingleton&) = delete;
    Singleton& operator=(const CSingleton&) = delete;
    Singleton(CSingleton&&) = delete;
    Singleton& operator=(CSingleton&&) = delete;
};
Singleton& instance = Singleton::GetInstance();
```

- 提供一个静态方法，让外界访问它的唯一实例

- 在静态方法内部定义了一个Singleton类型的静态局部对象，作为外部共享的唯一实例

  :warning:只有调用时才创建对象，节约系统资源

- 为防止在外部对其实例化，将其构造函数设计为私有

:rotating_light:线程安全仅针对GetInstance方法而言，多线程操作Singleton类时也需加锁进行同步

适应场景/优缺点：

- 节约资源：系统内存中只有一个对象，避免全局使用的对象频繁创建和销毁造成的性能损失
- 没有抽象层，扩展困难
- 违背单一职责原则：既对外提供访问方法，内部又自行创建对象，创建和使用没有分离

# 工厂模式

## 简单工厂模式

- 工厂类：实现所有产品实例的创建逻辑，直接被外界调用用来创建具体实例
- 抽象产品类：所有产品的抽象类，仅描述所有实例的公共接口
- 具体产品类：具体的一个产品类，继承抽象类并实现定义的接口

```cpp
//创建一个工厂对象
Factory* factory = new Factory;
//根据参数（往工厂添加的原料）使用工厂创建不同的对象
//发生多态，父类指针指向子类对象
Fruit* pear = factory->createFruit("pear");
```

适应场景/优缺点：

- 对象创建和使用分离
  - 只关心往工厂添加的原料（传入的参数），而不关心它们是如何加工的（工厂内部对象具体的创建逻辑）
- 工厂的负担随着对象类型的增加而增加
  - 工厂一旦出问题，整个系统则无法工作
  - 具体的对象类型过多，复杂度增加
  - 每添加一个新的类型，就需要修改工厂类，工厂越来越臃肿（违反“开闭原则”）

## 工厂模式

简单理解为：简单工厂+开闭原则=工厂模式

- 抽象工厂类：具体工厂的抽象类，不创建产品，只是描述工厂用来创建产品的接口
- 具体工厂类：继承抽象工厂类，实现父类接口，负责创建具体的产品
- 抽象产品类和具体产品类不变

:warning:此时如果新增产品类型，只需要增加新的工厂类型及对应的新产品类型即可

```cpp
//创建具体的工厂类，发生多态
AbstractFactory* pearFactory = new PearFactory;
//使用具体的工厂类，创建对应的产品，发生多态
Fruit* pear = pearFactory->createFruit();
```

适应场景/优缺点：

- 系统可扩展性较好，无需修改接口和原类
- 系统类个数增加，复杂度、抽象性增加
- 每个工厂只创建一类产品，随着产品类型增加，工厂类型随之增加，系统开销增加

## 抽象工厂模式

在工厂模式基础上，使得一个具体工厂可创建多个产品对象

- 抽象工厂类：定义创建不同抽象产品的``一组接口``
- 具体工厂类：继承抽象工厂，负责具体创建不同的抽象产品
- 抽象产品类：每种产品均有自己的抽象类，定义产品具体功能
- 具体产品类：继承抽象产品，实现自身需要的功能

```cpp
//创建具体工厂（产品族为China）
AbstractFactory* factory = new ChinaFactory;
//通过具体工厂创建具体产品（工厂为China，则抽象产品Pear多态转换为China的Pear）
AbstractPear* pear = factory->createPear();
```

:warning:注意与工厂模式的区别：

- 抽象工厂是针对不同的产品族（中国、美国），每个产品族中又包含不同的抽象产品（桃子、梨）

适应场景/优缺点：

- 增加产品族很方便，只需添加新的具体工厂，继承抽象工厂实现不同产品的创建方法
- 增加新产品困难，需在抽象工厂类中增加新产品对应的创建方法

# 观察者模式

定义对象间的一种一对多依赖关系，使得每当一个对象状态发生改变时，其相关依赖对象皆得到通知并被自动更新

- 目标：抽象类，定义维护（增加、删除、监听）观察者的方法以及目标的状态
- 具体目标：具体实现增加、删除观察当前目标的观察者，或是向观察者发送通知以及目标状态的修改
- 观察者：抽象类，用于定义当目标发生变化时，具体观察者需要处理的业务
- 具体观察者：当观察者收到通知后，实现具体业务的处理

```cpp
//创建一个具体目标，发生多态
Subject * subject = new ConcreteSubject();
//创建两个具体观察者，发生多态
Obeserver * objA = new ConcreteObeserver("A");
Obeserver * objB = new ConcreteObeserver("B");
//A、B均观察目标
subject->attach(objA);
subject->attach(objB);
//目标状态改变，并发送通知
subject->setState(1);
subject->notify();//打印出观察者A和B均检测到目标状态的改变
//目标移除观察者B
subject->detach(objB);
subject->setState(2);//目标状态再次改变
subject->notify();//此时只有观察者A监测到目标状态的改变
```

适应场景/优缺点：

- 表示层和数据逻辑层分离
- 支持广播，简化一对多系统设计难度
- 一个目标有很多直接和间接的观察者，广播通知会花很多时间
- 观察者和观察目标之间出现循环依赖，则可能导致系统崩溃
- 观察者只知道目标发生变化，不知道目标是怎么变的