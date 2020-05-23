//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
#include<iostream>
#include<vector>
using namespace std;
/**
提示：
1 <= nums.length <= 50000
-50000 <= nums[i] <= 50000
*/
//冒泡排序(leetcode超时)
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- 如果能在内部循环第一次运行时,使用一个旗标来表示有无需要交换的可能,可以把最优时间复杂度降低到O(n)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定
vector<int> sortArray(vector<int>& nums) {
    int n=nums.size();//每轮循环需要比较的元素个数
    int i;//每次比较的两个下标:i、i+1
    /*传统嵌套循环
    while (n-1)//n个数，n-1轮循环
    {
        for (i = 0; i <= n-2; i++)//每轮循环，i从下标0开始，直到下标n-2和n-1比较为止
        {
            if(nums[i]>nums[i+1])//前者＞后者，则交换两者，如果=也交换，则不稳定
            {
                int temp=nums[i];
                nums[i]=nums[i+1];
                nums[i+1]=temp;
            }
        }//一轮循环结束，最大的数在末尾
        n--;//排除最大的数，不再比较，比较的元素个数--
    }*/
    //-----------------------------------------------------------------------
    //进一步改为单层循环，但实质还是双层
    //增加标记，判断当前轮次是否发生交换，没交换说明已经有序，则直接跳出循环
    //单层循环+交换标记+缩小范围
    int lastchangedPos,lastchangedPos_temp;//默认没发生交换
    lastchangedPos=lastchangedPos_temp=0;
    for (i = 0; i <= n-2; i++)//每轮循环，i从下标0开始，直到下标n-2和n-1比较为止
    {
        if(nums[i]>nums[i+1])//前者＞后者，则交换两者，如果=也交换，则不稳定
        {
            nums[i+1]^=nums[i];
            nums[i]^=nums[i+1];
            nums[i+1]^=nums[i];
            lastchangedPos_temp=i;//发生交换,记录本轮循环最后一次交换位置
        }
        if(i==n-2)//一轮循环结束
        {
            //没交换说明已经有序，则直接跳出循环
            if(lastchangedPos==lastchangedPos_temp)break;
            i=-1;//重置i
            lastchangedPos=lastchangedPos_temp;//记录交换位置
            n=lastchangedPos+1;//缩减比较范围
            //打印
            cout<<"第"<<n-1<<"轮循环：";
            for (int i = 0; i < n; i++)
                printf("%d ", nums[i]);
            printf("\n");
        }
    }
    return nums;
}
int main()
{
    vector<int> nums = {5,1,1,2,0,0};
    nums=sortArray(nums);
    printf("冒泡排序结果：");
    int n=nums.size();
    for (int i = 0; i < n; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");//输出：[0,0,1,1,2,5]
    return 0;
}
