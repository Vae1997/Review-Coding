//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
//选择排序
// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- O(n^2)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定
//不稳定发生在最小元素与A[i]交换的时刻。
//比如序列：{ 5, 8, 5, 2, 9 }，
//一次选择的最小元素是2，然后把2和第一个5进行交换，从而改变了两个元素5的相对次序。
/**
提示：
1 <= nums.length <= 50000
-50000 <= nums[i] <= 50000
*/
#include<iostream>
#include<vector>
using namespace std;
//选择排序每轮循环只需要在最后进行交换
vector<int> sortArray2(vector<int>& nums) {
    int n=nums.size();
    int minIndex=0;//最小数的下标
    int temp;//临时存储的最小数下标
    while (n-1)//n个数，n-1轮循环
    {
        //从最小下标+1开始到末尾，寻找最小元素所在下标
        temp=minIndex;
        for (int i = minIndex+1; i < nums.size(); i++)
            if(nums[i]<nums[temp])temp=i;//发现小的，记录下标
        //temp发生改变，则交换
        if(temp!=minIndex)
        {
            nums[temp]^=nums[minIndex];
            nums[minIndex]^=nums[temp];
            nums[temp]^=nums[minIndex];
        }
        minIndex++;//交换完成，最小下标++
        //打印
        cout<<"第"<<n-1<<"轮循环：";
        for (int i = 0; i < nums.size(); i++)
            printf("%d ", nums[i]);
        printf("\n");
        n--;//轮次--
    }
    return nums;
}
//改进：每轮不光记录最小元素进行交换，同时找到最大元素放在队尾
vector<int> sortArray(vector<int>& nums) {
    int n=nums.size();
    int min,t1,max,t2;
    min=0;max=n-1;
    while (min<max)
    {
        t1=min;
        t2=min;
        for (int i = min+1; i <= max; i++)
        {
            if(nums[i]<nums[t1])t1=i;
            else if(nums[i]>nums[t2])t2=i;
        }
        if(t1!=min)
        {
            nums[t1]^=nums[min];
            nums[min]^=nums[t1];
            nums[t1]^=nums[min];
            //注意，如果max对应下标没变，但是交换后min下标已经改变，t2需要指向原来的min，即t1
            if(t2==min)t2=t1;
        }
        if(t2!=max)
        {
            nums[t2]^=nums[max];
            nums[max]^=nums[t2];
            nums[t2]^=nums[max];
        }
        min++;max--;
        //打印
        cout<<"第"<<n-1<<"轮循环：";
        for (int i = 0; i < nums.size(); i++)
            printf("%d ", nums[i]);
        printf("\n");
        n--;//轮次--
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
