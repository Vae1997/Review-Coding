# 排序

[力扣传送门](https://leetcode-cn.com/problems/sort-an-array/)

## 归并

最差时间复杂度 ---- O(nlogn)

最优时间复杂度 ---- O(nlogn)

平均时间复杂度 ---- O(nlogn)

所需辅助空间 ------ O(n)

稳定性 ------------ 稳定

### Merge操作

归并两个有序数组

```cpp
vector<int> t;//临时存储合并好的数组
void Merge(vector<int>& nums, int left, int mid, int right)
{
    int L=left;//左数组起始位
    int R=mid+1;//右数组起始位
    while (L<=mid && R<=right)//两个数组都还有元素
    {
        //左边≤右边，左侧进队，=确保稳定
        if(nums[L]<=nums[R])
            t.push_back(nums[L++]);
        else 
            t.push_back(nums[R++]);//否则右侧进队
    }//遍历终止，说明有一侧的数组已经没有可以比较的元素
    //表示右侧数组比较完毕，直接将左侧剩余元素直接挨个进队
    while (L<=mid)
        t.push_back(nums[L++]);
    //表示左侧数组比较完毕，直接将右侧剩余元素直接挨个进队
    while (R<=right)
        t.push_back(nums[R++]);
    //将排序的数组挨个赋值到原来数组对应位置
    for (int i = 0; i < t.size(); i++)
        nums[left+i]=t[i];
    t.clear();//清空临时数组，以备下次归并记录
}
```

递归

```cpp

void MergeSortRecursion(vector<int>& nums, int left, int right)
{
    if(left>=right)return;//只有一个元素，则递归结束，开始回溯
    int mid=(left+right)/2;//否则，拆分为左右两个数组
    MergeSortRecursion(nums,left,mid);//左侧递归，拆分
    MergeSortRecursion(nums,mid+1,right);//右侧递归，拆分
    if(nums[mid]>nums[mid+1])//如果左数组末尾≤右侧数组起始，则不需要归并
        Merge(nums,left,mid,right);//拆分结束，归并
}
vector<int> sortArray(vector<int>& nums) {
    MergeSortRecursion(nums,0,nums.size()-1);
    return nums;
}
```

迭代

```cpp
vector<int> MergeSort(vector<int>& nums)
{
    int left,mid,right;
    int n=nums.size();
    for(int size=1;size<n;size*=2)
    {
        left=0;
        while(left+size<n)
        {
            mid=left+size-1;
            right=mid+size<n?mid+size:n-1;
            if(nums[mid]>nums[mid+1])
                Merge(nums,left,mid,right);
            left=right+1;
        }
    }
    return nums;
}
```

## 快排

内部比较排序

`最差时间复杂度O( n^2 )`

- 每次选取的基准都是最大（或最小）的元素（包括元素全相等）
- 导致每次只划分出了一个分区，需要进行n-1次划分才能结束递归，时间复杂度为O(n^2)

`最优/平均时间复杂度O(nlogn)`

- 每次选取的基准都是中位数
- 这样每次都均匀的划分出两个分区，只需要logn次划分就能结束递归，时间复杂度为O(nlogn)

所需辅助空间

- 主要是递归造成的栈空间的使用(用来保存left和right等局部变量)
- 取决于递归树的深度，一般为O(logn)，最差为O(n)

稳定性：不稳定

不稳定发生在基准元素与A[tail+1]交换的时刻

{ 1, 3, 4, 2, 8, 9, 8, 7, 5 }，基准元素是5，一次划分操作后5要和第一个8进行交换，从而改变了两个元素8的相对次序

优化：

- 优化1：基准选取方法采用三数取中法，避免基准选择不当（最大、最小、有序数组）

- 优化2：数组分割方法采用挖坑替换，避免交换操作带来的时间开销

- 优化3：递归时判断当前操作数组大小（right-left），小于10个元素时采用插入排序

- 优化4：递归时采用尾递归，减少递归空间开销

- 优化5：使用栈模拟递归，避免递归空间开销

- 优化6：针对大量重复数组，三路快排（增加相等区间数组）

普通实现：

```cpp
void QuickSort(vector<int>& nums,int L,int R)
{
    if(L>=R)return;
    int P=nums[R];//右端元素作为中枢
    int left=L,right=R;//保存左右端点
    while(L<R)
    {
        while(L<R && nums[L]<=P)L++;//找到左侧大于中枢的位置
        nums[R]=nums[L];//覆盖到右侧
        while(L<R && nums[R]>=P)R--;//找到右侧小于中枢的位置
        nums[L]=nums[R];//覆盖到左侧
    }
    nums[L]=P;//L==R的位置即为中枢元素位置
    QuickSort(nums,left,L-1);//递归快排左侧
    QuickSort(nums,L+1,right);//递归快排右侧
}
vector<int> sortArray(vector<int>& nums) {
    QuickSort(nums,0,nums.size()-1);
    return nums;
}
```

## 堆排序

内部比较排序

最差时间复杂度 ---- O(nlogn)

最优时间复杂度 ---- O(nlogn)

平均时间复杂度 ---- O(nlogn)

所需辅助空间 ------ O(1)

稳定性 ------------ 不稳定

不稳定发生在堆顶元素与A[i]交换的时刻

{ 9, 5, 7, 5 }，堆顶元素是9，堆排序下一步将9和第二个5进行交换，得到序列 { 5, 5, 7, 9 }，再进行堆调整得到{ 7, 5, 5, 9 }，

重复之前的操作最后得到{ 5, 5, 7, 9 }从而改变了两个5的相对次序

:warning:从``最后一个非叶节点``开始向上建堆

```cpp
void Heap(vector<int>& nums,int i,int n)
{
    int L=2*i+1;//左节点下标
    int R=2*i+2;//右节点下标
    int max=i;//最大元素下标
    if(L<n && nums[L]>nums[max])max=L;
    if(R<n && nums[R]>nums[max])max=R;
    if(max!=i)//表示需要进行调整
    {
        swap(nums[i],nums[max]);//交换i位置和max元素
        Heap(nums,max,n);
    }
}
vector<int> sortArray(vector<int>& nums) {
    int n=nums.size();
    for(int i=n/2-1;i>=0;--i)
    {//从最后一个节点n的父节点向上构建堆
        Heap(nums,i,n);
    }
    while(n>1)//调整到只有一个节点
    {
        swap(nums[0],nums[--n]);//将堆顶的最大元素交换到最后一个节点位置
        Heap(nums,0,n);//从堆顶继续调整
    }
    return nums;
}
```

# 哈希表

:link:https://juejin.im/post/6844903885287637006

## 原理

存储：数组

![哈希](https://user-gold-cdn.xitu.io/2019/7/8/16bd1006f29c29d1?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

存/取：

1. 将Key通过Hash函数计算得到Hash值
2. Hash值 % 数组大小 = 存放下标
3. 如果匹配，则说明查找成功，返回k:v

## 实现

- Hash函数：尽可能减少冲突次数
- 解决冲突：发生冲突时的手段
- 实现相关操作：实现基本操作方法

## 冲突解决

发生因素：Hash函数、数组容量

负载因子：存储的键值对数目与数组容量的比值

- 存入元素少，浪费空间

- 当存入过多元素，负载因子变大，冲突概率提高

扩容：Java的HashMap将原来的key`重新映射到容量为2倍的数组`

### 拉链法

基于数组和链表的组合来解决冲突

- 发生冲突时，将冲突的键值对插入链表

:red_circle:当元素个数和“篮子”数一致时，发生扩容，一般为下一个素数值，之后所有元素重新进行键值对映射

### 开放定址法

发生冲突时，直接去寻找下一个空的地址（探测）

- 只要底层的表足够大，就总能找到空的地址

# 红黑树

作者：小谷围coder
链接：https://www.nowcoder.com/discuss/489210?channel=666&source_id=home_feed
来源：牛客网

红黑树是一种特殊的二叉查找树，它在每一个节点上都使用红色或黑色进行标记，通过一些性质确保它是始终平衡的。
它的性质是这样的：

1. 每个节点不是红色就是黑色。 
2. 根节点是黑色的。 
3. 叶节点的空节点是黑色的。 
4. 如果一个节点是红色的，那么它的两个子节点是黑色的。 
5. 对于任意节点，从它到叶节点的每条路径上都有相同数目的黑色节点。 

红黑树的插入，查询，删除在一般情况和最坏情况下的时间复杂度都是O(log(n))

应用场景主要是STL中map，set的实现，优点在于支持频繁的修改，因为查询删除插入时间复杂度都是logN

# 二叉搜索树

将给定数组元素构建为二叉搜索树，[力扣](https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/)

- 排序后，从中间开始递归构建

```cpp
TreeNode* dfs(vector<int>& nums,int L,int R)
{
    if(L>R)return nullptr;
    int mid = L+(R-L)/2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = dfs(nums,L,mid-1);
    root->right = dfs(nums,mid+1,R);
    return root;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    return dfs(nums,0,nums.size()-1);
}
```

# 最小生成树

找到可以将n个点以最小代价链接起来的n-1条边

https://www.jianshu.com/p/a5f0f46be8e2

## Kruskal算法

1. 找一条最小边，这条边的两个点不在一棵树上，则链接
2. 找次小边，两个点不是同一个树链接，以此类推，直至n-1条边

:warning:当一条边的两个点在同一个树中，则需找下一个次小的边

## Prim算法

1. 任选一点作为起点，并选择与其相连的最小代价的点为下一起点
2. 从新起点继续选择最小代价进行链接，以此类推，直到选择n个节点

:warning:分别保存已选择的节点和未选择的节点，当一个节点所链接的节点均已经选择后，需检查是否存在未选择的节点，直到未选择节点为空

# 最短路径

## Dijkstra算法

1. 选取一个起点，并检测链接的边，取最短
2. 加入最短边的节点，再分别检测每个点链接的边取最短
3. 排除已经检测过的节点，直到加入所有的节点

# 优先队列

[力扣传送门](https://leetcode-cn.com/problems/top-k-frequent-elements/)

priority_queue：默认为大顶堆，适合求前k小

改为小顶堆：```priority_queue<E, vector<E>, greater<E>>```

也可以自定义：```priority_queue<pair<int,int>,vector<pair<int,int>>,cmp> pq;```

其中的cmp如下：pair的first表示频次，second表示元素

- pair默认以first排前k小，相同时再排second

## 情况1

全使用默认设置：```priority_queue<pair<int,int>> pq;```

输入：[1,1,1,2,2,2,3,3,4,4,5] 3，输出：[4,3,5]

频次前三小的元素为：3，4，5，根据输出判断出：

1. 频次按照从大到小输出，因此4，3排在5之前
2. 频次相同时，按照元素从大到小输出，4排在3之前输出

## 情况2

使用greater：```priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;```

输入：[1,1,1,2,2,2,3,3,4,4,5] 3，输出：[4,1,2]

频次前三大的元素：1，2，4

1. 频次按照从小到大输出，4排在1，2之前
2. 频次相同时，优先选取较大元素，因此选4不选3
3. 频次相同时，元素从小到大排序输出，1在2之前输出

使用less：```priority_queue<pair<int,int>,vector<pair<int,int>>,less<pair<int,int>>> pq;```

输入：[1,1,1,2,2,2,3,3,4,4,5,6] 3 输出：[3,6,5]

频次前三小的元素：5，6，3

1. 频次按照从大到小输出，3排在5，6之前
2. 频次相同时，优先选取较小元素，因此选3不选4
3. 频次相同时，元素从大到小排序输出，6在5之前输出

## 情况3

自定义比较方法（单一维度比较）

```cpp
struct cmp{
    bool operator()(pair<int,int>& p1,pair<int,int>& p2){
        //比较
    };
};
```

### 直接```return p1.first<p2.first;```

[1,1,1,2,2,2,3,3,4,4,5,6] 3 => [4,5,6]

1. 前三小：4，5，6；频次从大到小输出
2. 频次相同，选较大元素；按照从小到大输出

如果改为second则为前三小的元素，按照从大到小输出[3,2,1]

### 直接```return p1.first>p2.first;```

[1,1,1,2,2,2,3,3,4,4,5] 3 => [4,2,1]

1. 前三大：4，2，1；频次从小到大输出
2. 频次相同，选较大元素；按照从大到小输出

如果改为second则为前三大的元素，按照从小到大输出[4,5,6]

## 情况4

自定义比较方法（多维度比较）

```cpp
struct cmp{
    bool operator()(pair<int,int>& p1,pair<int,int>& p2){
        if(p1.first>p2.first)return true;//表示先按照频率排，找前k大的频率，频次从小到大
        else if(p1.first<p2.first)return false;
        else{//频率相同
            if(p1.second>p2.second)return true;//按照元素大小排，从小到大输出
            else return false;
        }
    };
};
```

[1,1,1,2,2,2,3,3,4,4,5,6] 3 => [4,1,2]
