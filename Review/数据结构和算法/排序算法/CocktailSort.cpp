//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
//鸡尾酒（定向冒泡）排序
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- 如果序列在一开始已经大部分排序过的话,会接近O(n)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定
/**
提示：
1 <= nums.length <= 50000
-50000 <= nums[i] <= 50000
*/
#include<iostream>
#include<vector>
using namespace std;
vector<int> sortArray(vector<int>& nums) {
    int n=nums.size();
    int L,R;
    L=0;R=n-1;//左右俩下标
    while (L<R)
    {
        for (int i = L; i < R; i++)//从左到右
        {
            if(nums[i]>nums[i+1])//前者＞后者，则交换两者，如果=也交换，则不稳定
            {
                nums[i+1]^=nums[i];
                nums[i]^=nums[i+1];
                nums[i+1]^=nums[i];
            }
        }
        //打印
        cout<<"第"<<L<<"轮循环：";
        for (int i = 0; i < n; i++)
            printf("%d ", nums[i]);
        printf("\n");
        R--;//排除最右端的最大元素
        for (int i = R; i > L; i--)//从右到左
        {
            if(nums[i]<nums[i-1])//前者＞后者，则交换两者，如果=也交换，则不稳定
            {
                nums[i-1]^=nums[i];
                nums[i]^=nums[i-1];
                nums[i-1]^=nums[i];
            }
        }
        //打印
        cout<<"第"<<R<<"轮循环：";
        for (int i = 0; i < n; i++)
            printf("%d ", nums[i]);
        printf("\n");
        L++;//排除最左端的最小元素
    }
    return nums;
}
int main()
{
    vector<int> nums = {5,1,1,2,0,0};
    nums=sortArray(nums);
    printf("鸡尾酒（定向冒泡）排序结果：");
    int n=nums.size();
    for (int i = 0; i < n; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");//输出：[0,0,1,1,2,5]
    return 0;
}
