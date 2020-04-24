//sizeof相关
//sizeof是编译期计算出结果的
//返回一个对象或者类型所占的内存字节数
//https://blog.csdn.net/weixin_44233929/article/details/105607670
//https://blog.csdn.net/Hello_Hwc/article/details/41170719
#include<iostream>
using namespace std;
class Empty{
public:
    Empty(){}
    ~Empty(){}
    static void f1(){}
    void f2(){}
};
class WithVirtual{
public:
    virtual void f(){}
    virtual ~WithVirtual(){}
};
long long foo(){return (long long)1;}
void f(){}
void test(char a[]){//or a[]
	printf("%d\n",sizeof(a));
}
typedef struct {
    int a;//4，但是每个量分配8
    double b;//8
}S1;//最宽的8*2=16
typedef struct {
    char a;//1，但是每个量分配8，填充7字节
    S1 s1;//s1中最宽的double为8字节
}S2;//s1=16 + 8 =24
typedef struct
{
  int f1:4;	//f1分配4bit
  int f2:6;
  int f3:8;
}S3;//一共4+6+8=18bit<int4字节*8bit=32bit,只需分配1个int4字节
typedef struct
{
  int f1:4;	
  int f2;   //有穿插，失效，4*3=12字节
  char f4:1;//不同类型的位域，失效，最宽字节4*4=16
  int f3:8;
}S4;
typedef struct{
	int a;  //4字节
	char b; //1字节
	char d; //1字节 //b,d由于连续，因此合并分配到一个4字节的单元
	long c;//4字节
}S5;//最宽4字节，两个char连续可以对齐到4字节中，因此合并，一共12字节
typedef struct{
	int a;
	char b;//b,d不连续，因此均分配4字节，一共4*4=16字节
	long c;
	char d;
}S6;
class Base{
public:
	virtual  ~Base(){}//虚指针8字节
private:
	int base;//int 8字节
};//共16字节
 
class SubFirst:Base{
public:
	~SubFirst(){}//不分配
private:
	int sub;//继承int+int=16字节
};//共16字节
 
class SubSecond:Base{
public:
	~SubSecond(){}//不分配
private:
	int sub;//继承int+int=16字节
	char sub2;//内存对齐。分配8字节
};//共24字节
struct stcTest3
{
    int a;
    char b[5];//相当于5个char类型的成员，前四个4字节一组，最后一个内存对齐，单独一个字节
    int c;
};
int main()
{
    Empty *e=new Empty();
    int *i;
    cout<<"64位指针类型8字节 "<<sizeof(e)<<" "<<sizeof(i)<<endl;//64位指针类型8字节
    Empty ee;
    cout<<"空类型（结构体）至少分配1字节 "<<sizeof(ee)<<endl;//空类型（结构体）至少分配1字节
    WithVirtual wv;
    cout<<"实例增加虚指针，64位指针类型8字节 "<<sizeof(wv)<<endl;//实例增加虚指针，64位指针类型8字节
    cout<<"基本数据类型sizeof："<<endl;
    printf("char:%d\n",sizeof(char));//1
	printf("short:%d\n",sizeof(short));//2
	printf("int:%d\n",sizeof(int));//4
	printf("float:%d\n",sizeof(float));//4
	printf("long:%d\n",sizeof(long));//4 
	printf("double:%d\n",sizeof(double));//8
    //foo()的返回值类型为char，所以sz=sizeof(char)，foo()并不会被调用
    printf("sizeof(foo())=%d\n",sizeof(foo()));
    //不允许使用不完整的类型void
    //printf("sizeof(f())=%d\n",sizeof(f()));
    cout<<"sizeof 数组"<<endl;
    char a[] ="123";
	int b[3];
	double c[3];
	char d[10] ="123";
	printf("%d\n",sizeof(a));	//4	=> 123+\0   
	printf("%d\n",sizeof(b));	//12	=>   3*4
	printf("%d\n",sizeof(c));	//24	=>	 3*8
	printf("%d\n",sizeof(d));	//10 不受内容影响
    cout<<"函数中传递的数组，就是指针"<<endl;
	test(a);	//64位下输出8
    cout<<"结构体的sizeof："<<endl;
    S1 s1;int s=s1.a;
    cout<<"sizeof(s1.a):"<<sizeof(s1.a)<<endl;
    cout<<"sizeof(S1):"<<sizeof(S1)<<endl;   
    cout<<"sizeof(s):"<<sizeof(s)<<endl;
    cout<<"sizeof(S2):"<<sizeof(S2)<<endl; 
    cout<<"结构体包含位域"<<endl;
    cout<<"sizeof(S3):"<<sizeof(S3)<<endl; 
    cout<<"sizeof(S4):"<<sizeof(S4)<<endl; 
    cout<<"sizeof(S5):"<<sizeof(S5)<<endl; 
    cout<<"sizeof(S6):"<<sizeof(S6)<<endl;
    cout<<"字符串与char*和char数组"<<endl;
    string ss = "hellohwcxxxxxxxxxxxxxxxxxx";
	char * ss1 = "hellohwc";
	char s2[] = "1234567890";
	char s3[100];
	char* s4=(char*)malloc(100);
	void *s5=(void*)malloc(100);
	cout<<sizeof(ss)<<endl;//string和编译器有关，32
	cout<<sizeof(ss1)<<endl;//指针，64位8字节
	cout<<sizeof(s2)<<endl;//char（1字节）*数组长度10+\0=11字节
	cout<<sizeof(s3)<<endl;//char（1字节）*数组长度100
	cout<<sizeof(s4)<<endl;//指针
	cout<<sizeof(s5)<<endl;//指针
    cout<<"继承的sizeof"<<endl;
    cout<<sizeof(Base)<<endl;
	cout<<sizeof(SubFirst)<<endl;
	cout<<sizeof(SubSecond)<<endl;
    cout<<sizeof(stcTest3)<<endl;
    return 0;
}
