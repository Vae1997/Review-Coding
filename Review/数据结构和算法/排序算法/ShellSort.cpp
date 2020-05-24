//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
//希尔排序(leetcode通过)
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- 根据步长序列的不同而不同。已知最好的为O(n(logn)^2)
// 最优时间复杂度 ---- O(n)
// 平均时间复杂度 ---- 根据步长序列的不同而不同。
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定
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
    //初始化增量
    int gap=0;
    while (gap<=n)
    {
        gap=gap*3+1;
    }
    cout<<"初始化gap:"<<gap<<endl;
    while (gap>=1)//gap==1为最后一轮插入，即对一整个部分有序的数组插入排序
    {
        for (int i = gap; i < n; i++)//当前位置i即为需要插入的元素
        {
            int num=nums[i];//保存当前元素
            int start=i-gap;//起始比较位置
            //当前位置元素num挨个和start、start-gap、start-2*gap位置元素比较
            //如果比较小，元素顺便依次后移
            //直到找到一个比他大的位置插入
            while (start>=0 && nums[start]>num)
            {
                nums[start+gap]=nums[start];
                start-=gap;
            }//迭代完毕，start+gap位置即为插入位置
            nums[start+gap]=num;
        }//当前轮，划分的每组插入排序结束，缩减增量
        gap=(gap-1)/3;
    }
    return nums;
}
int main()
{
    vector<int> nums = {5,1,1,2,0,0};
    nums=sortArray(nums);
    printf("排序结果：");
    int n=nums.size();
    for (int i = 0; i < n; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");//输出：[0,0,1,1,2,5]
    return 0;
}
