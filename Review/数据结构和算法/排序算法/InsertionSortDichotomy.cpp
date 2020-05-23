//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
//二分插入排序
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- O(nlogn)
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
//在有序数组中选择插入位置时，使用二分查找插入
vector<int> sortArray(vector<int>& nums) {
    int n=nums.size();
    for (int i = 1; i < n; i++)
    {
        int right=i-1;//每次选择插入位置时的起始比较位置
        int left=0;
        while (left<=right)//二分查找
        {
            int mid=(right+left)/2;
            if(nums[mid]>nums[i])right=mid-1;
            else left=mid+1;
        }//查找结束，left或right即为插入位置
        //插入操作也可以先保存、再erase，最后insert
        int num=nums[i];//保存
        for (int j = i - 1; j >= left; j--)//将插入位置到当前位置数据整体后移
            nums[j + 1] = nums[j];
        nums[left] = num; //插入
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
