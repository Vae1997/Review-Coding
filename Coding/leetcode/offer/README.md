# 剑指offer
leetcode上的剑指offer题目,[官方代码链接](https://github.com/zhedahht/CodingInterviewChinese2).

[No1.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No1.cpp)：赋值运算符函数，[官方测试代码](https://github.com/zhedahht/CodingInterviewChinese2/blob/master/01_AssignmentOperator/AssignmentOperator.cpp)

[No2.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Review/C%2B%2B/singletonC11.cpp)：c++11线程安全的单例设计模式,另外还有常见的[单线程不安全的实现](https://github.com/Vae1997/Review-Coding/blob/master/Review/C%2B%2B/singleton.cpp)

[No2_expand.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No2_expand.cpp)：面试题2最后扩展：可继承单例，使用模板的实现方法参考[C++可继承的单例基类模板](https://www.cnblogs.com/sunchaothu/p/10353507.html)

[面试题3](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)：数组中重复的数字
- [No3_v1.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No3_v1.cpp)：常规解法（排序、哈希表）
- [No3_v2.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No3_v2.cpp)：改进解法（交换nums[i]和nums[nums[i]]）
- [No3_v3.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No3_v3.cpp)：不修改数组解法（辅助数组、二分法），注意二分法不能找到所有重复数字，数字范围为1~n，n+1个数

[面试题4](https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/)：二维数组中的查找，本题与主站 [240题](https://leetcode-cn.com/problems/search-a-2d-matrix-ii/)相同
- [No4.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No4.cpp)：从右上角开判断

[面试题5](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)：替换空格
- [No5_v1.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No5_v1.cpp)：借助辅助字符数组
- [No5_v2.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No5_v2.cpp)：在源字符串上修改

[面试题6](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)：从尾到头打印链表
- [No6.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No6.cpp)：辅助数组、递归

[面试题7](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/)：重建二叉树，本题与主站 [105题](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)相同
- [No7.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No7.cpp)：递归实现，[官方的迭代实现](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/solution/mian-shi-ti-07-zhong-jian-er-cha-shu-by-leetcode-s/)

[面试题8](https://www.nowcoder.com/questionTerminal/9023a0c988684a53960365b889ceaf5e)：二叉树中序遍历的下一个节点
- [No8.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No8.cpp)：分情况讨论（有无右节点、有无父节点、是父节点的左/右孩子）

[面试题9](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)：双栈实现队列
- [No9.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No9.cpp)：inStack负责插入、outStack负责删除

[面试题10](https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/)：斐波那契数列，同主站[70题](https://leetcode-cn.com/problems/climbing-stairs/)、[509题](https://leetcode-cn.com/problems/fibonacci-number/)
- [No10.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No10.cpp)：递归，记忆递归，迭代
- [面试题10.2](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)：青蛙跳台

[面试题11](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/)：旋转数组的最小数字，同主站[153题](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)、[154题](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/)
- [No11.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No11.cpp)：注意加入元素相等时的条件判断

[面试题12](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/)：矩阵中的路径，同主站[79题](https://leetcode-cn.com/problems/word-search/)
- [No12.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No12.cpp)：回溯法解题

[面试题13](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/)：机器人的运动范围
- [No13.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No13.cpp)：回溯法解题

[面试题14](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/)：剪绳子1，同主站[343题](https://leetcode-cn.com/problems/integer-break/)
- [No14.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No14.cpp)：递归、动态规划、贪心

[面试题22](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)：返回链表倒数第k个节点
- [No22_v1.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No22_v1.cpp)：直接返回链表的第count-k个节点
- [No22_v2.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No22_v2.cpp)：快慢指针解法

[面试题64](https://leetcode-cn.com/problems/qiu-12n-lcof/)：求1+2+…+n
- [No64.cpp](https://github.com/Vae1997/Review-Coding/blob/master/Coding/leetcode/offer/No64.cpp)：包括多种解法（&&或||、构造函数、虚函数、函数指针）
