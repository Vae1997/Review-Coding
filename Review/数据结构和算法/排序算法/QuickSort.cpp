//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
//快速排序
// 分类 ------------ 内部比较排序
// 数据结构 --------- 数组
// 最差时间复杂度 ---- 每次选取的基准都是最大（或最小）的元素（包括元素全相等），导致每次只划分出了一个分区，需要进行n-1次划分才能结束递归，时间复杂度为O(n^2)
// 优化1：基准选取方法采用三数取中法，避免基准选择不当（最大、最小、有序数组）
// 优化2：数组分割方法采用挖坑替换，避免交换操作带来的时间开销
// 优化3：递归时判断当前操作数组大小（right-left），小于10个元素时采用插入排序
// 优化4：递归时采用尾递归，减少递归空间开销
// 优化5：使用栈模拟递归，避免递归空间开销
// 优化6：针对大量重复数组，三路快排（增加相等区间数组）
// 最优时间复杂度 ---- 每次选取的基准都是中位数，这样每次都均匀的划分出两个分区，只需要logn次划分就能结束递归，时间复杂度为O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ 主要是递归造成的栈空间的使用(用来保存left和right等局部变量)，取决于递归树的深度，一般为O(logn)，最差为O(n)       
// 稳定性 ---------- 不稳定
//不稳定发生在基准元素与A[tail+1]交换的时刻。
//比如序列：{ 1, 3, 4, 2, 8, 9, 8, 7, 5 }，基准元素是5，一次划分操作后5要和第一个8进行交换，从而改变了两个元素8的相对次序。
/**
提示：
1 <= nums.length <= 50000
-50000 <= nums[i] <= 50000
*/
//阮一峰快速排序
//https://www.ruanyifeng.com/blog/2011/04/quicksort_in_javascript.html
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
//基准选取：三数取中法
void changePivot(vector<int>& nums, int left, int right)
{
    int mid=left+(right-left)/2;
    if(nums[left]>nums[mid])swap(nums[left],nums[mid]);//left为较小值
    if(nums[left]>nums[right])swap(nums[left],nums[right]);//left为最小值
    if(nums[right]>nums[mid])swap(nums[right],nums[mid]);//mid为最大值，right为中间值
}
//分割方式1：标准法，双指针i、j
int Partition1(vector<int>& nums, int left, int right)
{
    int pivot=nums[right];//选择最后一个元素作为当前分割数组的基准
    cout<<"pivot:"<<pivot<<endl;
    int i=left;
    int j=right;
    while (i<j)
    {
        while (i<j && nums[i]<=pivot)i++;//从左到右，找比基准大的
        cout<<"i:"<<i<<endl;
        while (i<j && nums[j]>=pivot)j--;//从右到左，找比基准小的
        cout<<"j:"<<j<<endl;
        if(i<j)swap(nums[i],nums[j]);//i大于基准的和j小于基准的交换
    }//循环结束，i=j
    cout<<"交换："<<nums[i]<<"和"<<nums[right]<<endl;
    //j没动，说明当前选的基准为最大值，则直接返回，不需要交换
    if(j!=right)swap(nums[i],nums[right]);  
    return i;
}
//分割方式2：挖坑法，将交换操作改为赋值
int Partition(vector<int>& nums, int left, int right)
{
    changePivot(nums,left,right);//调整后，数组右侧即为三数取中的中间值
    int pivot=nums[right];//选择最后一个元素作为当前分割数组的基准
    while (left<right)
    {
        while (left<right && nums[left]<=pivot)left++;
        if(left<right)nums[right]=nums[left];
        while (left<right && nums[right]>=pivot)right--;
        if(left<right)nums[left]=nums[right];
    }
    nums[left]=pivot;
    return left;
}
//分割方式3：前后指针
int Partition3(vector<int>& nums, int left, int right)
{
    int pivot=nums[right];//选择最后一个元素作为当前分割数组的基准
    int small_index=left;//比基准小的数组末尾下标，即前指针
    for (int i = left; i < right; i++)//从头到尾，i为后指针
        //当前元素小于基准，交换到小数组尾部，尾部下标++
        if(nums[i]<=pivot)swap(nums[i],nums[small_index++]);
    //循环结束，则尾部下标位置即为分割位置，交换基准元素
    swap(nums[small_index],nums[right]);
    return small_index;
}
//递归函数
void QuickSort2(vector<int>& nums, int left, int right)
{
    int pivot_index;
    //传统递归方式
    // if (left<right)
    // {
    //     pivot_index=Partition(nums,left,right);//分割
    //     QuickSort(nums,left,pivot_index-1);//快排前半个
    //     QuickSort(nums,pivot_index+1,right);//快排后半个
    // }
    /*if(right-left<=10)InsertionSort(nums);小数组选择插入排序*/
    //尾递归方式
    while (left<right)
    {
        pivot_index=Partition(nums,left,right);//分割
        QuickSort2(nums,left,pivot_index-1);//快排前半个
        left=pivot_index+1;
    }
}
//递归方式
vector<int> sortArray2(vector<int>& nums) {
    QuickSort2(nums,0,nums.size()-1);
    return nums;
}
/*三路快排递归*/
void QuickSort3(vector<int>& nums, int left, int right)
{
    if(left<right)
    {
        //分割方式4：三路快排
        int pivot=nums[right];//选择最后一个元素作为当前分割数组的基准
        int lt=left-1;//小于基准的数组尾
        int rt=right;//大于基准的数组头
        int i=left;//从i到rt遍历
        while (i < rt)
        {
            if(nums[i]<pivot)//小于基准
                swap(nums[++lt],nums[i++]);//交换到小数组尾部
            else if(nums[i]>pivot)//大于基准
                swap(nums[--rt],nums[i]);//交换到大数组头部
            else i++;//和基准相等时，略过
        }
        //循环结束，i=rt，将基准交换到大数组头部
        swap(nums[rt],nums[right]);
        QuickSort3(nums,left,lt);//快排小数组
        QuickSort3(nums,rt+1,right);//快排大数组
    }
}
//三路快排递归方式
vector<int> sortArray(vector<int>& nums) {
    QuickSort3(nums,0,nums.size()-1);
    return nums;
}
//迭代方式
vector<int> sortArray1(vector<int>& nums) {
    stack<int> s;
    s.push(nums.size()-1);//先右后左
    s.push(0);
    int left,right,pivot;
    while (s.size())
    {
        left=s.top();s.pop();
        right=s.top();s.pop();
        pivot=Partition(nums,left,right);
        if(left<pivot)//压栈小数组
        {
            s.push(pivot-1);
            s.push(left);
        }
        if(pivot<right)//压栈大数组
        {
            s.push(right);
            s.push(pivot+1);
        }
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
