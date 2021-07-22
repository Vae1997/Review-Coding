//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
//堆排序
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(nlogn)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定
//不稳定发生在堆顶元素与A[i]交换的时刻。
//比如序列：{ 9, 5, 7, 5 }，堆顶元素是9，堆排序下一步将9和第二个5进行交换，
//得到序列 { 5, 5, 7, 9 }，再进行堆调整得到{ 7, 5, 5, 9 }，
//重复之前的操作最后得到{ 5, 5, 7, 9 }从而改变了两个5的相对次序。
/**
提示：
1 <= nums.length <= 50000
-50000 <= nums[i] <= 50000
*/
#include<iostream>
#include<vector>
using namespace std;
// 从nums[i]向下进行堆调整，递归实现
void Heapify2(vector<int>& nums, int i, int size)
{
    int left=2*i+1;//左节点
    int right=2*i+2;//右节点
    int max=i;//最大节点
    if(left < size && nums[left] > nums[i]) max=left;
    if(right < size && nums[right] > nums[max]) max=right;
    if(max != i)//max==i表明当前已经满足最大堆定义
    {
        swap(nums[i],nums[max]);//将最大者和i节点交换
        Heapify(nums,max,size);//max指向i节点，从i开始递归，继续调整堆
    }
}
//迭代实现堆的调整
void Heapify(vector<int>& nums, int i, int size)
{
    int ti=nums[i];//保存初始位置的值
    //左节点开始，每次j*2+1到左节点的左节点
    for (int j = 2*i+1; j < size; j=j*2+1) 
    {
        //右节点j+1，j=size-1时无右节点，j存储左右节点较大者
        if(j<size-1 && nums[j]<nums[j+1])++j;
        //如果保存的ti最大，表示已经调整完毕
        if(ti>=nums[j])break;
        //否则，将最大值覆盖到当前i节点位置
        nums[i]=nums[j];
        //覆盖后，初始位置i改为j
        i=j;
    }//j>=size表示已经到叶节点，调整完毕
    nums[i]=ti;//将初始值覆盖到i位置
}
// 建堆，时间复杂度O(n)
void BuildHeap(vector<int>& nums, int n)
{
    //注意i从n/2-1开始调整
    for (int i = n/2-1; i >= 0; i--)
        Heapify(nums,i,n);
    //完全二叉树，1≤i≤n，节点i的父节点为i/2
    //最后一个节点n的父节点为n/2，即最后一个非叶节点
    //-1因为数组下标起始为0
    //综上，遍历是从最后一个非叶节点开始向头节点遍历进行构建堆
}
vector<int> sortArray(vector<int>& nums) {
    int n=nums.size();
    BuildHeap(nums,n);//构建大顶堆
    while (n>1)//n=1时，堆调整完毕
    {
        swap(nums[0],nums[--n]);//交换堆顶（最大元素）到末尾
        Heapify(nums,0,n);//元素数--，由于堆顶发生改变，需要从堆顶继续调整，构建堆
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
