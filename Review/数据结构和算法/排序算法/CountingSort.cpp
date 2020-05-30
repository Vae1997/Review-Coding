//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
//计数排序
// 分类 ------------ 内部非比较排序
// 数据结构 --------- 数组
// 最差时间复杂度 ---- O(n + k)
// 最优时间复杂度 ---- O(n + k)
// 平均时间复杂度 ---- O(n + k)
// 所需辅助空间 ------ O(n + k)
// 稳定性 ----------- 稳定
/**
提示：
1 <= nums.length <= 50000
-50000 <= nums[i] <= 50000
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> sortArray(vector<int>& nums) {
    int n=nums.size();
    //计数数组直接取最大情况max-min+1，50000-（-50000）+1
    // int max=50000;int min=-50000;
    //也可通过max和min得到整个数组最大、最小值,缩小计数范围
    int max=*max_element(nums.begin(),nums.end());
    int min=*min_element(nums.begin(),nums.end());
    vector<int> counter(max-min+1);
    //从0号开始，每个元素值下标+50000避免负数情况，计数++
    for (int i = 0; i < n; i++) counter[nums[i]-min]++;
    //另一种，不借助New数组，也不需要挨个相加
    //从min~max遍历，如果counter值为0表示没有当前数字num，+1到下一个
    //counter值如果大于0，则为num出现的次数
    //内层循环挨个将数字num赋值到nums
    int i=0;
    for (int num = min; num <= max; num++)
        while (counter[num-min]-->0)
            nums[i++]=num;
    return nums;
    //传统方法
    //计数完毕后，从1号开始挨个相加，表示小于i的个数
    // for (int i = 1; i < max-min+1; i++) counter[i]+=counter[i-1];
    //相加完毕，counter即为nums中每个元素i所在位置
    //从后向前遍历nums，通过nums[i]的值寻找counter对应下标的值，该值即为排序后的下标
    //赋值后counter对应下标的值--，下次有同样下标值时，排在前一个位置，从而算法稳定
    // vector<int> numsNew(n);
    // for (int i = n-1; i >= 0; i--) numsNew[--counter[nums[i]-min]]=nums[i];   
    // return numsNew;
}
int main()
{
    vector<int> nums = {15, 22, 19, 46, 27, 73, 1, 19, 8};
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
