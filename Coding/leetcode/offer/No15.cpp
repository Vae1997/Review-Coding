//二进制1的个数
#include<iostream>
using namespace std;
//想法1：将原数字与1按位&，原数字右移一位，原数字到0为止
//缺点：负数最高位为1，最后数字为11111造成死循环
//想法2：原数字不动，每次将1左移一位进行&操作，循环次数为原数字二进制位数
int hammingWeight(uint32_t n) {
    int count=0;
    uint32_t compare=1;
    while (compare)
    {
        if(n&compare)count++;
        compare = compare<<1;
    }
    return count;
}
//想法3：n&(n-1),循环次数即为1的个数
int hammingWeight(uint32_t n) {
    int count=0;
    while (n)
    {
        count++;
        n&=(n-1);
    }
    return count;
}
int main()
{
   
   return 0;
}
