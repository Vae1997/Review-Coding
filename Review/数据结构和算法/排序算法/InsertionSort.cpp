//排序数组
//十大排序算法参考链接：
/*
https://www.cnblogs.com/eniac12/p/5329396
*/
//插入排序
// 分类 ------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- 最坏情况为输入序列是降序排列的,此时时间复杂度O(n^2)
// 最优时间复杂度 ---- 最好情况为输入序列是升序排列的,此时时间复杂度O(n)
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
//插入排序用于少量元素
vector<int> sortArray(vector<int>& nums) {
    int n=nums.size();
    int start=0;//每次选择插入位置时的起始比较位置
    while (n-1)//n个数，n-1次插入操作
    {
        int move=0;//记录插入时的移动次数
        for (int i = start; i >= 0; i--)
        {
            if(nums[i]>nums[start+1])move++;//需要后移较大元素，记录移动次数
            else break;//只要≤，跳出
        }
        if(move)//如果需要移动
        {
            int num=nums[start+1];//保存需要移动的元素
            nums.erase(nums.begin()+start+1);//删除
            nums.insert(nums.begin()+(start+1-move),num);//插入
        }
        //打印
        cout<<"第"<<n-1<<"轮循环：";
        for (int i = 0; i < nums.size(); i++)
            printf("%d ", nums[i]);
        printf("\n");
        start++;n--;//插入完毕
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
