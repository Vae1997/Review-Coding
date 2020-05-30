# 排序算法实现
- 注：所有代码已在[LeetCode 912：排序数组](https://leetcode-cn.com/problems/sort-an-array/)中运行，```冒泡```、```选择```、```插入```等时间复杂度为```O(n^2)```的相关排序算法均超时
- 代码参考：[常用排序算法总结](https://www.cnblogs.com/eniac12/p/5329396.html)
## 冒泡排序[(Bubble Sort)](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/BubbleSort.cpp):O(n^2),稳定
- 经典的双层循环解法，以及几种优化方案，如```通过标记判断本轮循环是否发生交换```
- [鸡尾酒排序](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/CocktailSort.cpp):O(n^2)，稳定，基于冒泡排序，不同处在于从低到高然后从高到低，如此来回操作进行排序
- 稳定：当交换元素的判断条件不包括=时，才稳定
## 选择排序[(Selection Sort)](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/SelectionSort.cpp):O(n^2),不稳定
- 经典解法：每轮循环只需要在最后进行交换，但是只将最大或最小值进行交换
- 优化方法：每轮不光记录最小元素进行交换，同时找到最大元素放在队尾，需要注意：```交换最小元素后，最大元素标记的指向```
- 不稳定：发生在交换的时候，可能会导致同样的元素前后次序发生改变
## 插入排序[(Insertion Sort)](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/InsertionSort.cpp):O(n^2),稳定
- 经典解法：当前元素从后往前逐个比较移动，直至发现首个较小元素为止；适用于数据量小的场景
- [二分插入排序](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/InsertionSortDichotomy.cpp):O(n^2)，基于插入排序，不同之处在于插入时使用二分查找法寻找插入位置
- 稳定：每次插入的位置是在前一个元素之后，元素相等时则不会破坏原有次序
## 希尔排序[(Shell Sort)](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/ShellSort.cpp),不稳定
- 基于插入排序，时间复杂度取决于选择的```递减增量序列(gap*3-1)```
- 不稳定：相同的元素可能在各自的插入排序中移动
## 归并排序[(Merge Sort)](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/MergeSort.cpp),O(nlogn),稳定
- 递归：依次对半拆分，直至一个元素；对比左右数组，挨个Merge；注意：```如果左数组末尾≤右侧数组起始，则不需要归并```
- 迭代：两两并；四四并，直至整个数组；外层通过size*=2控制每次归并的数组大小，内层通过数组首尾下标挨个归并
- 稳定：归并时的比较判断包含=时，由于先存入左侧元素，因此稳定
## 快速排序[(Quick Sort)](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/QuickSort.cpp),O(nlogn),不稳定
- 递归：先根据左右下标进行Partition返回基准下标，再依次递归基准左右两侧的数组
- 迭代：每次先将数组右端下标压入栈，再压左侧下标，根据左右下标进行Partition，栈空为止
- 不稳定：发生在交换基准元素的时候，可能改变相同元素的原有次序
- 最差时间复杂度：每次选取的基准都是最值，每次只划一个分区，进行n-1次划分结束递归，复杂度为O(n^2)
  - 优化1：基准选取方法采用三数取中法，避免基准选择不当（最大、最小、有序数组），其他：固定、随机
  - 优化2：数组分割方法采用挖坑替换，避免交换操作带来的时间开销，其他：经典的双指针、前后指针
  - 优化3：递归时判断当前操作数组大小（right-left），数组元素较少时采用插入排序
  - 优化4：递归时采用尾递归，减少递归空间开销
  - 优化5：使用栈模拟递归，避免递归空间开销
  - 优化6：针对大量重复的数组元素，使用三路快排（即增加相等区间数组），需特别注意```三个数组的首尾下标```
## 堆排序[(Heap Sort)](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/HeapSort.cpp),O(nlogn),不稳定
- 递归：从n/2处，最后一个非叶节点向上Heapify建堆；将堆顶换到末尾后继续Heapify剩余元素，直至满足定义
- 迭代：Heapify方法中每次步长```j*2+1```，挨个判断左右节点并始终保留较大元素覆盖之前的下标j，满足定义后再将初始值覆盖
- 不稳定：发生在堆顶元素的交换之时
## 计数排序[(Counting Sort)](https://github.com/Vae1997/Review-Coding/blob/master/Review/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%92%8C%E7%AE%97%E6%B3%95/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/CountingSort.cpp),O(n + k),稳定
- 经典方法：
  - 根据数组max和min元素确定counter数组大小；
  - ```counter[nums[i]-min]++```统计元素出现次数；
  - counter挨个相加确定元素位置；
  - 逆序遍历原数组，将结果存入新数组返回；
- 变式方法：计完数之后从min~max遍历，并将counter中的非零位置对应的下标元素，按照具体出现次数挨个从0赋值到原数组
- 稳定：计完数之后，逆序遍历原先数组，始终使得下标靠前的元素位于相等元素之前；但注意```变式方法无法保证稳定```
