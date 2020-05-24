//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
//归并排序
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(nlogn)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ O(n)
// 稳定性 ------------ 稳定
/**
提示：
1 <= nums.length <= 50000
-50000 <= nums[i] <= 50000
*/
#include<iostream>
#include<vector>
using namespace std;
// 归并操作
// 合并两个已排好序的数组[left...mid]和[mid+1...right]
vector<int> t;//临时存储合并好的数组
void Merge(vector<int>& nums, int left, int mid, int right)
{
    int L=left;//左数组起始位
    int R=mid+1;//右数组起始位
    while (L<=mid && R<=right)//两个数组都还有元素
    {
        //左边≤右边，左侧进队，=确保稳定
        if(nums[L]<=nums[R])t.push_back(nums[L++]);
        else t.push_back(nums[R++]);//否则右侧进队
    }//遍历终止，说明有一侧的数组已经没有可以比较的元素
    //表示右侧数组比较完毕，直接将左侧剩余元素直接挨个进队
    while (L<=mid)t.push_back(nums[L++]);
    //表示左侧数组比较完毕，直接将右侧剩余元素直接挨个进队
    while (R<=right)t.push_back(nums[R++]);
    //将排序的数组挨个赋值到原来数组对应位置
    for (int i = 0; i < t.size(); i++)
        nums[left+i]=t[i];
    t.clear();//清空临时数组，以备下次归并记录
    //打印本次归并结果
    cout<<"Merge over:"<<endl;
    for (int i = 0; i < nums.size(); i++)
        cout<<nums[i]<<" ";
    cout<<endl;
}
void MergeSortRecursion(vector<int>& nums, int left, int right)
{
    if(left>=right)return;//只有一个元素，则递归结束，开始回溯
    cout<<"当前递归下标："<<left<<"~"<<right<<endl;
    for (int i = 0; i < nums.size(); i++)
        cout<<nums[i]<<" ";
    cout<<endl;
    int mid=(left+right)/2;//否则，拆分为左右两个数组
    MergeSortRecursion(nums,left,mid);//左侧递归，拆分
    MergeSortRecursion(nums,mid+1,right);//右侧递归，拆分
    Merge(nums,left,mid,right);//拆分结束，归并
}
//递归实现
vector<int> sortArray(vector<int>& nums) {
    MergeSortRecursion(nums,0,nums.size()-1);
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
