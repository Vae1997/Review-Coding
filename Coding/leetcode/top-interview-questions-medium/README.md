:link:[力扣传送门](https://leetcode-cn.com/leetbook/read/top-interview-questions-medium)

# 数组和字符串

## 三数之和

判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组

- 暴力超时：排序后固定一个，双指针检查剩余两个（还得判断是否重复）

考虑去重：参考[吴彦祖](https://leetcode-cn.com/problems/3sum/solution/pai-xu-shuang-zhi-zhen-zhu-xing-jie-shi-python3-by/)和[iiame](https://leetcode-cn.com/problems/3sum/comments/223610)

1. 外层循环固定的数如果>0，由于已经排序，后面的数也大于0，和不可能为0，直接结束循环
2. 固定的数和上一个数相同，则后两个搜索完毕也相同，因此直接略过去重
3. 当找到和为0后，原则上直接++L和--R
   1. 左侧数字一致时，右侧数字也一样
   2. 因此L继续右移++，直到不同的一个；R继续左移--，直到不同的一个

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    if(nums.size()<3)return {};
    sort(nums.begin(),nums.end());
    vector<vector<int>>res;
    for(int i=0;i<nums.size()-2 && nums[i]<=0;++i)//优化1
    {
        if(i>0 && nums[i] == nums[i-1])continue;//优化2
        int L=i+1,R=nums.size()-1;
        while(L<R)
        {
            if(nums[L]+nums[R]==-nums[i])
            {
                res.push_back({nums[i],nums[L],nums[R]});
                while(L<R && nums[L]==nums[L+1])++L;//优化3
                while(L<R && nums[R]==nums[R-1])--R;//优化3
                ++L;--R;
            }
            else if(nums[L]+nums[R]<-nums[i]) ++L;
            else --R;
        }
    }
    return res;
}
```

## 矩阵置零

给定一个 *m* x *n* 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用**[原地](http://baike.baidu.com/item/原地算法)**算法**。**

- 朴素算法：直接一遍记录0的位置，再读取位置置为0，空间O(m*n)
- 分别记录行列坐标，再分别将对应的行列置为0，空间O(m+n)

考虑直接修改原数组：

1. 遍历数组，i，j为零，则i行j列均要置为零，先将首个元素置为0作为标记，即[i]\[0]和[0]\[j]
2. 但需注意如果0行、0列本身就存在0，则需记录并对应置为0
3. 分别从第二行、第二列开始，如果当前行/列首元素为0，则挨个遍历置为0
4. 最后，判断首行/列是否出现过0，对应置为0

注意:rotating_light:

- 行和列从第二行/列判断，否则如果首行/列出现0，则全置为0，抹去了之前的标记
- 先判断行列后，最后判断首行/列；否则首行/列出现0，同样全为0，抹去了标记

```cpp
void setZeroes(vector<vector<int>>& matrix) {
    int m=matrix.size(),n=matrix[0].size();
    bool raw=false,col=false;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            if(matrix[i][j]==0){
                if(i==0)raw=true;//0行中有0
                if(j==0)col=true;//0列中有0
                matrix[i][0]=0;//i行首位置0
                matrix[0][j]=0;//j列首位置0
            }
        }
    }
    for(int i=1;i<m;++i){//注意i=1开始
        if(matrix[i][0]==0){//i行首位是0，说明当前行需要全为0
            for(int j=1;j<n;++j)
                matrix[i][j]=0;
        }
    }
    for(int j=1;j<n;++j){//注意j=1开始
        if(matrix[0][j]==0){//j列首位是0，说明当前列需要全为0
            for(int i=1;i<m;++i)
                matrix[i][j]=0;
        }
    }
    if(raw){//首行出现0，则全置为0
        for(int j=0;j<n;++j)
            matrix[0][j]=0;
    }
    if(col){//首列出现0，则全置为0
        for(int i=0;i<m;++i)
            matrix[i][0]=0;
    }
}
```

## 字母异位词分组

给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

示例:

输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
说明：

所有输入均为小写字母。
不考虑答案输出的顺序。

- 将每个字符串按照字母排序，作为key，对应的下标作为value

```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> v;
    map<string,int> m;
    int i=-1;//记录下标
    for(string s:strs){
        string t=s;//临时保存
        sort(t.begin(),t.end());//排序
        if(!m.count(t))//新的字符串
        {
            v.push_back(vector<string>{s});//创建新元素，压入字符串
            m[t]=++i;//设置排序的字符串t为key，下标i为value，++i更新下标
        }
        else v[m[t]].push_back(s);//如果存在，则直接找到下标m[t]的数组加入s
    }
    return v;
}
```

## 无重复字符的最长子串

给定一个字符串，请你找出其中不含有重复字符的 **最长子串** 的长度

1. 使用map存放每个字符及对应的下标

2. 新字符，直接记录下标，增加字符串长度

3. 对于已经存在的字符：

   - 首先max更新最长的结果

   - 确定之前出现的位置，map查找为m[s[i]]

   - 因此从m[s[i]]+1到当前位置i之间，不存在重复字符

   - 则将下一轮判断的子串的起始位置t，修正为m[s[i]]+1

     :rotating_light:但注意会出现t倒退的情况，如abba

     - 第一次重复位置b为2，b上次的位置为1，因此t=1+1=2
     - L长度置为i-t+1=2-2+1=1
     - 当i为3，是a时，map中重复，上次a位置是0，t=0+1=1<上一轮的t=2
     - 当更新L时，L=i-t+1=3-1+1=3，出错

   - 因此t应该为``max(t,m[s[i]]+1)``，确保t不会退回

   - 接着更新当前字符s[i]，map中存i

   - 最后更新长度L，当前位置i-上个不重复的位置t，+1

```cpp
int lengthOfLongestSubstring(string s) {
    if(s.length()<2)return s.length();
    int res=0,L=0,t=0;//L累加长度，t为不重复字串的起始位置
    map<char,int>m;//每个字符对应的位置
    for(int i=0;i<s.length();++i)
    {
        if(!m.count(s[i]))//新的字符
        {
            m[s[i]]=i;//记录位置
            ++L;//字串长度++
        }
        else//字符重复
        {
            res=max(res,L);//更新结果
            t=max(t,m[s[i]]+1);//t不应该往回走，因此取当前t和上次记录当前字符位置+1中的max
            m[s[i]]=i;//更新当前字符的位置
            L=i-t+1;//计算新一轮字符串初始长度
        }
    }
    return max(res,L);
}
```

## 最长回文子串

给定一个字符串 `s`，找到 `s` 中最长的回文子串。你可以假设 `s` 的最大长度为 1000

中心扩散法：

- 从0下标开始，依次进行扩散，注意奇数和偶数区分
- 左右下标范围内的回文长度大于此前的记录，则更新
- 最后直接substr原始字符串，注意左边参数为起始位置，右边参数为截取的字符数

```cpp
string longestPalindrome(string s) {
    int L=0,R=0;
    for(int i=0;i<s.length();++i)
    {
        auto [a,b]=count(s,i,i,res);//如果回文子串为奇数，从第i位开始向两边扩展
        auto [c,d]=count(s,i,i+1,res);//若为偶数，从i和i+1扩展
        if(b-a>R-L)//更新
        {
            L=a;R=b;
        }
        if(d-c>R-L)//更新
        {
            L=c;R=d;
        }
    }
    return s.substr(L,R-L+1);//截取
}
pair<int,int> count(string s,int L,int R,string& res){
    while(L>=0 && R<s.length() && s[L]==s[R]){//下标合法，并且字符相同，开始扩散
        --L;
        ++R;
    }
    return {L+1,R-1};//返回当前回文的左右下标
}
```

## 递增的三元子序列
给定一个未排序的数组，判断这个数组中是否存在长度为 3 的递增子序列。

数学表达式如下:

如果存在这样的 i, j, k,  且满足 0 ≤ i < j < k ≤ n-1，
使得 arr[i] < arr[j] < arr[k] ，返回 true ; 否则返回 false 。
说明: 要求算法的``时间复杂度为 O(n)``，``空间复杂度为 O(1) ``

普通做法：动态规划

1. dp[i]表示以字符i结尾的最大长度，初始化为1
2. 外层循环i从1到n；内层循环j从0到i，挨个计算dp[i]
3. 当nums[j]<nums[i]时，则可以在dp[j]的基础上+1
4. 但需时刻更新j~i之间最大的dp，因此``dp[i]=max(dp[i],dp[j]+1)``
5. 当某个dp[i]==3，直接返回true；否则双层循环完毕返回false

```cpp
bool increasingTriplet(vector<int>& nums) {
    if(nums.size()<3)return false;
    int n=nums.size();
    vector<int>dp(n,1);
    for(int i=1;i<n;++i)
    {
        for(int j=0;j<i;++j)
        {
            if(nums[j]<nums[i])
                dp[i]=max(dp[i],dp[j]+1);
        }
        if(dp[i]==3)return true;
    }
    return false;
}
```

符合时空复杂度的做法：保存最小和次小的两个数，出现大于两个数的即为true，参考[正直清澈方欣欣鸭ʚɞ](https://leetcode-cn.com/problems/increasing-triplet-subsequence/solution/c-xian-xing-shi-jian-fu-za-du-xiang-xi-jie-xi-da-b/)的题解

# 链表

## 两数相加

给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和

您可以假设除了数字 0 之外，这两个数都不会以 0 开头

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

- 从头相加，记录进位即可，需注意特殊情况

1. 每次需确定两个链表是否已经到达末尾
2. sum计算求和，并整除10确定进位标记
3. sum % 10得到当前节点的值
4. l1，l2，head后移
5. 特别注意循环结束后，如果还有add则添加值为1的节点

```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* ph = new ListNode(-1);
    ListNode* head = ph;
    int sum,x,y,add=0;
    while(l1 || l2)
    {
        x = l1 ? l1->val : 0;
        y = l2 ? l2->val : 0;
        sum = x + y + add;
        add = sum / 10;
        if(l1)
            l1 = l1->next;
        if(l2)
            l2 = l2->next;
        head->next = new ListNode(sum%10);
        head = head->next;
    }
    if(add) head->next = new ListNode(1);
    return ph->next;
}
```

## 奇偶链表

给定一个单链表，把所有的奇数节点和偶数节点分别排在一起

空间复杂度应为 O(1)，时间复杂度应为 O(nodes)，nodes 为节点总数

- 依次遍历修改对应节点指向

1. R存储偶数节点的头节点
2. p、q分别指向奇数偶数节点

```cpp
ListNode* oddEvenList(ListNode* head) {
    if(!head)return head;
    ListNode* R = head->next;
    ListNode* p = head;
    ListNode* q = R;
    while(p->next && q->next)
    {
        p->next = q->next;//p指向下一个奇数节点
        p = q->next;//更新p位置
        q->next = p->next;//q指向下一个偶数节点
        q = p->next;//更新偶数节点
    }
    p->next = R;//连接两个链表
    return head;
}
```

## 相交链表

编写一个程序，找到两个单链表相交的起始节点

朴素想法：快慢指针

1. 遍历两个链表得到长度
2. 快指针先走长的节点多出的步数
3. 之后快慢指针一起后移，指针指向相等时则已找到

另外想法：同时移动，一个指针到达末尾后，指向另一个链表首部继续遍历

原因：两个指针交换走的链表，则总长度是一致的

```cpp
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode* p=headA;
    ListNode* q=headB;
    int haveChanged = 0;//如果有交集，则两次交换后必能找到
    while(p && q && haveChanged<3)
    {
        if(p == q)return p;
        p=p->next;
        q=q->next;
        if(!p){//p已经走到头，交换，计数
            p=headB;
            ++haveChanged;
        }
        if(!q){//q已经走到头，交换，计数
            q=headA;
            ++haveChanged;
        }
    }
    return nullptr;
}
```

# 树和图

## 二叉树的中序遍历

给定一个二叉树，返回它的*中序* 遍历

简单的递归：

```cpp
vector<int> v;
vector<int> inorderTraversal(TreeNode* root) {
    if(root)
    {
        inorderTraversal(root->left);
        v.emplace_back(root->val);//前序在上，后序在下
        inorderTraversal(root->right);
    }
    return v;
}
```

需要掌握的迭代：栈模拟

:rotating_light:前序中序后序，统一写法，参考[PualKing](https://leetcode-cn.com/problems/binary-tree-postorder-traversal/solution/mo-fang-di-gui-zhi-bian-yi-xing-by-sonp/)

```cpp
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> v;
    stack<TreeNode*> s;
    if(root) s.push(root);
    while(!s.empty())
    {
        TreeNode* n = s.top();
        s.pop();
        if(n)
        {
            if(n->right)s.push(n->right);
            s.push(n);//前序这两句放下面
            s.push(nullptr);//后序放上面
            if(n->left)s.push(n->left);
        }
        else{
            v.emplace_back(s.top()->val);
            s.pop();
        }
    }
    return v;
}
```

## 二叉树的层序遍历

一般使用队列模拟，注意size记录每层的节点数

```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> v;
    queue<TreeNode*> q;
    if(root)q.push(root);
    while(!q.empty())
    {
        int size = q.size();
        vector<int> tv;
        while(size--)
        {
            root = q.front();
            q.pop();
            tv.push_back(root->val);//构造每层的节点
            if(root->left) q.push(root->left);
            if(root->right) q.push(root->right);
        }
        v.push_back(tv);
    }
    return v;
}
```

## 二叉树的锯齿形层次遍历

给定一个二叉树，返回其节点值的锯齿形层次遍历

朴素想法：在层序遍历基础上，记录深度，偶数时，tv数组反转后加入结果v

另外想法：参考[BAKE ZQ](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/comments/206797)，直接赋值即可

## 从前序与中序遍历序列构造二叉树

根据一棵树的前序遍历与中序遍历构造二叉树

朴素想法：每次递归时，分别重新构造左右子树的前序中序数组

改进：参考[小占同学](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--22/267679)

1. 递归之前遍历中序序列，使用map存放节点值与下标的映射
2. 递归参数通过前序中序的左右下标，从而限定左右子树的前序中序序列

```cpp
unordered_map<int,int> m;
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int index=0;
    for(int n:inorder)//存放映射
        m[n]=index++;
    //注意区间，左闭右开
    return dfs(preorder,0,preorder.size(),inorder,0,inorder.size());
}
TreeNode* dfs(vector<int>& preorder, int pl, int pr, vector<int>& inorder,int il, int ir)
{
    if(pl == pr)return nullptr;
    TreeNode* root = new TreeNode(preorder[pl]);//前序的首个元素即为当前节点
    int index = m[preorder[pl]];//获取中序对应下标
    int Lnum = index - il;//左子树序列长度
    root->left = dfs(preorder,pl+1,pl+1+Lnum,inorder,il,index);
    root->right = dfs(preorder,pl+1+Lnum,pr,inorder,index+1,ir);
    return root;
}
```

注意左右子树的两个序列下标：

- 左子树：
  - 前序下标范围：pl+1~pl+1+Lnum
  - 中序下标范围：il+index
- 右子树：
  - 前序下标范围：pl+1+Lnum~pr
  - 中序下标范围：index+1~ir

## 填充每个节点的下一个右侧节点指针
给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL

初始状态下，所有 next 指针都被设置为 NULL

朴素想法：类似层序遍历，每一次的当前层节点数size减到0时，next置空；否则指向队首元素即可

```cpp
Node* connect(Node* root) {
    if(!root)return nullptr;
    queue<Node*> q;
    q.push(root);
    Node* res = root;
    while(!q.empty())
    {
        int size = q.size();
        while(size--)
        {
            root = q.front();
            q.pop();
            if(!size)//层需遍历增加的判断
                root->next=nullptr;
            else root->next=q.front();
            if(root->left)
                q.push(root->left);
            if(root->right)
                q.push(root->right);
        }
    }
    return res;
}
```

不考虑递归空间，O(1)空间复杂度解法：参考[shicheng](https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/comments/10182)

主要思想：通过上一层的next指针，访问非同一root节点的子节点

## 二叉搜索树中第K小的元素

给定一个二叉搜索树，编写一个函数 `kthSmallest` 来查找其中第 **k** 个最小的元素

普通思路：中序遍历，存入数组，返回k-1下标元素(也可使用stack迭代到第k个返回)

二分查找：确定左右节点的个数，再通过k比较进行二分查找，参考[li-fang-fang-fang-fang-ge](https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/comments/113629)

```cpp
int kthSmallest(TreeNode* root, int k) {
    int Lc = count(root->left);//左侧节点数
    if(Lc+1 == k)return root->val;
    else if(Lc < k)return kthSmallest(root->right,k-Lc-1);//查找右侧
    else if(Lc >= k)return kthSmallest(root->left,k);//左侧
    return -1;
}
int count(TreeNode* root)//以root为根的子树，节点个数
{
    if(!root)return 0;
    return count(root->left)+count(root->right)+1;
}
```

## 岛屿数量
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量

岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成

此外，你可以假设该网格的四条边均被水包围

DFS遍历：参考[mata川](https://leetcode-cn.com/problems/number-of-islands/comments/42148)，可以创建访问数组标记，更为直接是修改源数组标记即可

```cpp
int numIslands(vector<vector<char>>& grid) {
    int m = grid.size();if(m==0)return 0;
    int n = grid[0].size();
    int count=0;
    for(int i=0;i<m;++i)//双层循环挨个确定
    {
        for(int j=0;j<n;++j)
        {
            if(grid[i][j]!='1')continue;//0；非岛屿，-1：已访问
            dfs(grid,m,n,i,j);
            ++count;//此处++
        }
    }
    return count;
}
void dfs(vector<vector<char>>& grid,int& m,int& n,int i,int j)
{
    if(i>=m || j>=n || i<0 || j<0 || grid[i][j]!='1')return;
    //没越界，没访问，值为1时
    grid[i][j]=-1;//置为-1，已访问
    dfs(grid,m,n,i-1,j);//上
    dfs(grid,m,n,i+1,j);//下
    dfs(grid,m,n,i,j-1);//左
    dfs(grid,m,n,i,j+1);//右
}
```

# 回溯

## 电话号码的字母组合

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母

- 建立数字和字符串的映射
- 从第0个数字下标开始dfs

```cpp
unordered_map<char,string>m{
    {'2', "abc"}, 
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"},
};
vector<string>res;
string ts;
vector<string> letterCombinations(string digits) {
    if(digits != "") dfs(digits,0);
    return res;
}
void dfs(string digits,int i){
    if(i>=digits.length()){
        res.push_back(ts);
        return;
    }
    for(int j=0;j<m[digits[i]].length();++j){
        ts+=m[digits[i]][j];
        dfs(digits,i+1);
        ts.pop_back();
    }
}
```

## 括号生成

数字 *n* 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 **有效的** 括号组合。

```cpp
vector<string> res;
vector<string> generateParenthesis(int n) {
    dfs("",n,n);//左右括号数为n
    return res;
}
void dfs(string ts,int L,int R){
    if(L==0 && R==0){
        res.push_back(ts);
        return;
    }
    if(L>0){//放左括号
        dfs(ts+'(',L-1,R);
    }
    if(R>L){//放右括号
        dfs(ts+')',L,R-1);
    }
}
```

- 每次放完左括号，再考虑右括号
- 保留n个左括号后，插入一个右括号配对，就紧接着放完剩余n-1个左括号，最后再放剩余的右括号

## 全排列

给定一个 **没有重复** 数字的序列，返回其所有可能的全排列

```cpp
vector<vector<int>>res;
vector<vector<int>> permute(vector<int>& nums) {
    int n=nums.size();
    vector<int>v;
    dfs(nums,v,n);
    return res;
}
void dfs(vector<int>& nums,vector<int>& v,int& n){
    if(v.size() == n){//找到一个排列，加入结果
        res.push_back(v);
        return;
    }
    for(int i=0;i<n;++i){
        //遍历原数组，find查找确定i尚未加入
        if(find(v.begin(),v.end(),nums[i]) == v.end()){
            v.push_back(nums[i]);//加入i元素
            dfs(nums,v,n);//递归
            v.pop_back();//回溯
        }
    }
}
```

## 子集

给定一组**不含重复元素**的整数数组 *nums*，返回该数组所有可能的子集（幂集）

```cpp
vector<vector<int>> res;
vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> v;
    dfs(nums,v,0);
    return res;
}
void dfs(vector<int>& nums,vector<int>& v,int size){
    res.push_back(v);
    for(int i=size;i<nums.size();++i){
        v.push_back(nums[i]);
        dfs(nums,v,i+1);
        v.pop_back();
    }
}
```

## 单词搜索

给定一个二维网格和一个单词，找出该单词是否存在于网格中。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。

同一个单元格内的字母不允许被重复使用

```cpp
bool exist(vector<vector<char>>& board, string word) {
    int m=board.size();
    int n=board[0].size();
    vector<vector<int>> visited(m,vector<int>(n,0));
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            if(board[i][j]==word[0]){
                if(dfs(board,m,n,i,j,word,0,visited))return true;
            }
        }
    }
    return false;
}
bool dfs(vector<vector<char>>& board, int m,int n,int i,int j,
         string& word,int k,vector<vector<int>>& visited){
    if(word[k]=='\0')return true;
    if(i<0 || i>=m || j<0 || j>=n || visited[i][j] || word[k]!=board[i][j]) return false;
    visited[i][j]=1;
    k++;
    bool res = dfs(board,m,n,i-1,j,word,k,visited) || 
        dfs(board,m,n,i+1,j,word,k,visited) || 
        dfs(board,m,n,i,j-1,word,k,visited) || 
        dfs(board,m,n,i,j+1,word,k,visited);
    if(res)return true;
    k--;
    visited[i][j]=0;
    return false;
}
```

# 排序和搜索

## 颜色分类

给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色

- 直接计数，再挨个放值
- O(n)解法：三指针
  - L指向0数组末尾，R指向2数组头部，c指向当前元素
  - c为2，则和R交换，R左移；c为0和L交换，c和L均右移；c为1则右移c

```cpp
void sortColors(vector<int>& nums) {
    int L=0,R=nums.size()-1,c=0;
    while(c<=R){
        if(nums[c]==0){
            swap(nums[L++],nums[c++]);
        }else if(nums[c]==2){
            swap(nums[c],nums[R--]);
        }else ++c;
    }
}
```

## 前 K 个高频元素

给定一个非空的整数数组，返回其中出现频率前 ***k*** 高的元素

- 第一遍遍历使用map计数
- 第二遍遍历map，使用pair存入优先队列，注意:warning:
  - 优先队列默认大顶堆，因此将计数取负值
  - pair默认使用first排序，因此优先队列存入时计数值为first
  - ```q.push(make_pair(-i.second,i.first));```
- 依次从队列中取k个元素

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    vector<int> res;
    unordered_map<int,int> m;
    priority_queue<pair<int,int>> q;
    for(int n:nums)m[n]++;
    for(auto i:m){
        q.push(make_pair(-i.second,i.first));
        if(q.size()>k)q.pop();
    }
    while(k--){
        res.push_back(q.top().second);
        q.pop();
    }
    return res;
}
```

## 数组中的第K个最大元素

在未排序的数组中找到第 **k** 个最大的元素

思路1：直接sort后取倒数第k个元素

思路2：快排/堆排，或者冒泡排序冒泡k次即可

```cpp
int findKthLargest(vector<int>& nums, int k) {
    int c=0;
    for(int i=0;i<nums.size();++i){
        for(int j=i+1;j<nums.size();++j){
            if(nums[j]>=nums[i])swap(nums[j],nums[i]);
        }
        if(++c==k)break;
    }
    return nums[k-1];
}
```

## 寻找峰值

峰值元素是指其值大于左右相邻值的元素。

给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。

数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞

思路1：线性搜索

思路2：二分查找，mid+1>mid收缩左侧，否则收缩右侧

```cpp
int findPeakElement(vector<int>& nums) {
    int L=0,R=nums.size()-1;
    while(L<R){
        int mid=(L+R)/2;
        if(nums[mid]<nums[mid+1]){
            L=mid+1;
        }else R=mid;
    }
    return L;
}
```

## 在排序数组中查找元素的第一个和最后一个位置

给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

你的算法时间复杂度必须是 O(log n) 级别。

如果数组中不存在目标值，返回 [-1, -1]。

思路1：直接线性搜索，时间复杂度O(n)

思路2：二分查找，参考[庸才顾子汐的题解](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/solution/da-jia-bu-yao-kan-labuladong-de-jie-fa-fei-chang-2/)

```cpp
vector<int> searchRange(vector<int>& nums, int target) {
    if(nums.size()==0)return {-1,-1};
    int L=0,R=nums.size()-1;
    while(L<=R){
        int mid = L+(R-L)/2;
        if(nums[mid]==target)R=mid-1;//向左收缩，找第一个位置
        else if(nums[mid]>target)R=mid-1;
        else if(nums[mid]<target)L=mid+1;
    }
    int left;
    if(L<nums.size()&&nums[L]==target){//找到第一个位置
        left=L;
        L=0;
        R=nums.size()-1;
    }
    else return {-1,-1};//没找到直接返回
    while(L<=R){
        int mid = L+(R-L)/2;
        if(nums[mid]==target)L=mid+1;//向右侧收缩，找最后一个位置
        else if(nums[mid]>target)R=mid-1;
        else if(nums[mid]<target)L=mid+1;
    }
    return {left,R};
}
```

## 合并区间

给出一个区间的集合，请合并所有重叠的区间

思路1：用栈模拟，同样需要排序，[代码在这里](https://leetcode-cn.com/submissions/detail/107598920/)

思路2：官方代码如下，[题解在这里](https://leetcode-cn.com/problems/merge-intervals/solution/he-bing-qu-jian-by-leetcode-solution/)

```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.size() == 0) {
        return {};
    }
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> merged;
    for (int i = 0; i < intervals.size(); ++i) {
        int L = intervals[i][0], R = intervals[i][1];
        if (!merged.size() || merged.back()[1] < L) {
            merged.push_back({L, R});//新的L大，直接添加到结果
        }
        else {//否则，设置前一组的R和新的R取较大者
            merged.back()[1] = max(merged.back()[1], R);
        }
    }
    return merged;
}
/*
作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/merge-intervals/solution/he-bing-qu-jian-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
```

## 搜索旋转排序数组

假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

你可以假设数组中不存在重复的元素。

你的算法时间复杂度必须是 O(log n) 级别

```cpp
int search(vector<int>& nums, int target) {
    int L=0,R=nums.size()-1;
    while(L<=R){
        int mid=L+(R-L)/2;
        if(nums[mid]==target)return mid;
        if(nums[mid]<nums[L]){//首先和L比较确定mid位于右侧升序数组
            if(nums[mid]<target && target<=nums[R]){//mid<target<R
                L=mid+1;
            }else R=mid-1;
        }else{//mid在左侧升序
            if(nums[mid]>target && target>=nums[L]){//mid>target>L
                R=mid-1;
            }else L=mid+1;
        }
    }
    return -1;
}
```

## 搜索二维矩阵 II

编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：

每行的元素从左到右升序排列
每列的元素从上到下升序排列

思路1：从左下角或右上角搜索，参考[小邓](https://leetcode-cn.com/problems/search-a-2d-matrix-ii/solution/sou-suo-er-wei-ju-zhen-ii-by-leetcode-2/157526)的解释

思路2：在思路一的基础上结合二分查找

```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if(matrix.size()==0)return false;
    int m=matrix.size(),n=matrix[0].size(),i=0,j=n-1;
    while(i<m && j>=0){
        if(matrix[i][j]==target)return true;
        if(matrix[i][j]<target)++i;
        else --j;
    }
    return false;
}
```

# 动态规划

## 跳跃游戏

给定一个非负整数数组，你最初位于数组的第一个位置

数组中的每个元素代表你在该位置可以跳跃的最大长度

判断你是否能够到达最后一个位置

思路1：动态规划，每个位置i是否到达=位置i-j能到达并且nums[i-j]>=j，j从i~0

思路2：参考[Ikaruga的题解](https://leetcode-cn.com/problems/jump-game/solution/55-by-ikaruga/)

```cpp
bool canJump(vector<int>& nums) {
    int can_reach = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (i > can_reach) return false;
        can_reach = max(can_reach, i + nums[i]);
    }
    return true;
}
```

## 不同路径

一个机器人位于一个 m x n 网格的左上角

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角

问总共有多少条不同的路径

思路1：组合，从左上到右下，向右n-1，向左m-1，一共m+n-2步，则从中选m-1步向左即可C（m+n-2,m-1）

思路2：动态规划，参考[BiYu2019的题解](https://leetcode-cn.com/problems/unique-paths/solution/xiao-xue-ti-java-by-biyu_leetcode/)

```cpp
int uniquePaths(int m, int n) {
    vector<int> res(n,1);
    for(int i=1;i<m;++i)
        for(int j=1;j<n;++j)
            res[j]+=res[j-1];
    return res[n-1];
}
```

## 零钱兑换

给定不同面额的无限个硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数

如果没有任何一种硬币组合能组成总金额，返回 -1

思路：动态规划，目标为i时，需要的最小硬币数=min(目标为i-num时的数量+1，dp[i])

```cpp
int coinChange(vector<int>& coins, int amount) {
    int n=coins.size();
    vector<int> dp(amount+1,amount+1);//注意初始化为amount+1，确保min
    dp[0]=0;
    for(int num:coins){
        for(int i=num;i<=amount;++i){
            dp[i]=min(dp[i],dp[i-num]+1);
        }
    }
    return dp[amount]>amount?-1:dp[amount];
}
```

## 最长上升子序列

给定一个无序的整数数组，找到其中最长上升子序列的长度

直接参考[newhar的思路](https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/yi-bu-yi-bu-tui-dao-chu-guan-fang-zui-you-jie-fa-x/)理解

```cpp
int lengthOfLIS(vector<int>& nums) {
    vector<int> res;
    for(auto i:nums){
        if(!res.size()||i>res.back())//比末尾大，直接加入
            res.push_back(i);
        else *lower_bound(res.begin(),res.end(),i)=i;
        //否则，二分找到当前元素i的合适位置（地址），*取值后将i赋值
    }
    return res.size();
}
```

# 设计问题

## 二叉树的序列化与反序列化

请设计一个算法来实现二叉树的序列化与反序列化

这里不限定你的序列 / 反序列化算法执行逻辑

只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构

```cpp
/*
作者：nuan-nuan-qing-feng-l
链接：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/solution/c-qing-xi-jian-ji-yi-dong-by-nuan-nuan-qing-feng-l/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
string serialize(TreeNode* root) {//层序遍历序列化
    queue<TreeNode*> q;
    q.push(root);
    string res;
    while(!q.empty()){
        auto p=q.front();
        q.pop();
        if(p!=NULL){
            res+=to_string(p->val);
            res+=',';
            q.push(p->left);
            q.push(p->right);
        }else res+="null,";
    }
    return res;
}
TreeNode* deserialize(string data) {
    auto vals = split(data);//存储每个节点值，层序遍历顺序
    queue<TreeNode*> q;
    if(vals[0]=="null")return NULL;//root为空
    q.push(new TreeNode(stoi(vals[0])));//根节点入队
    TreeNode *res=q.front();
    for(int i=1;i<vals.size();){
        if(vals[i]!="null"){//有左节点
            auto p=new TreeNode(stoi(vals[i]));
            q.push(p);
            q.front()->left=p;
        }
        ++i;
        if(vals[i]!="null"){//有右节点
            auto p=new TreeNode(stoi(vals[i]));
            q.push(p);
            q.front()->right=p;
        }
        ++i;
        q.pop();
    }
    return res;
}
vector<string> split(string &data){//按照逗号分割字符串
    int start=0;
    vector<string> res;
    while(1){
        auto end = data.find(',',start);
        if(end==string::npos)break;
        res.push_back(data.substr(start,end-start));
        start=end+1;
    }
    return move(res);
}
```

## 常数时间插入、删除和获取随机元素

设计一个支持在平均时间复杂度 O(1) 下，执行以下操作的数据结构。

    insert(val)：当元素 val 不存在时，向集合中插入该项。
    remove(val)：元素 val 存在时，从集合中移除该项。
    getRandom：随机返回现有集合中的一项。每个元素应该有相同的概率被返回。

思路：参考[D__wade的题解](https://leetcode-cn.com/problems/insert-delete-getrandom-o1/solution/fen-xiang-yi-ge-you-xiu-de-suan-fa-hashsethe-shu-z/)vector存数值，unordered_map存值和下标的映射

```cpp
private:
    vector<int> nums;
    unordered_map<int,int> m;
public:
    RandomizedSet() {
        srand(time(NULL));//确保随机性
    }
    bool insert(int val) {
        if(m.count(val))return false;//已经存在
        nums.push_back(val);//加入末尾
        m[val]=nums.size()-1;//添加映射
        return true;
    }
    bool remove(int val) {
        if(!m.count(val))return false;//不存在
        int last=nums[nums.size()-1];//保存last元素
        nums[m[val]]=last;//将last元素覆盖到val所在位置
        m[last]=m[val];//更新last元素的映射下标
        nums.pop_back();//移除last
        m.erase(val);//清除val元素的映射
        return true;
    }
    int getRandom() {
        return nums[rand()%nums.size()];
    }
```

# 数学

## 快乐数

编写一个算法来判断一个数 n 是不是快乐数。「快乐数」定义为：

对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和

然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1

如果 可以变为  1，那么这个数就是快乐数

如果 n 是快乐数就返回 True ；不是，则返回 False

思路1：直接暴力，控制循环次数判断

思路2：参考[甜姨的题解](https://leetcode-cn.com/problems/happy-number/solution/kuai-le-de-zhi-shi-dian-zeng-jia-liao-by-sweetiee/)双指针思想，快慢相等时出现循环，则不是快乐数

```cpp
int squareSum(int n){//计算数字n，每一位的平方和
    int sum=0;
    while(n>0){
        int bit=n%10;
        sum+=bit*bit;
        n/=10;
    }
    return sum;
}
bool isHappy(int n) {
    int slow=n,fast=squareSum(n);
    while(slow!=fast){
        slow=squareSum(slow);
        fast=squareSum(squareSum(fast));//fast比slow快算一步
    }
    return slow==1;
}
```

## 阶乘后的零

给定一个整数 *n*，返回 *n*! 结果尾数中零的数量，时间复杂度O(logn)

直接暴力算阶乘后再统计0的个数

数学思路：参考[windliang](https://leetcode-cn.com/problems/factorial-trailing-zeroes/solution/xiang-xi-tong-su-de-si-lu-fen-xi-by-windliang-3/)

```cpp
/*
作者：windliang
链接：https://leetcode-cn.com/problems/factorial-trailing-zeroes/solution/xiang-xi-tong-su-de-si-lu-fen-xi-by-windliang-3/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int trailingZeroes(int n) {
    int count = 0;
    while (n > 0) {
        count += n / 5;
        n = n / 5;
    }
    return count;
}
```

## Excel表列序号

给定一个Excel表格中的列名称，返回其相应的列序号

思路：类比二进制的计算，从低位到高位依次*26的对应次方即可

```cpp
int titleToNumber(string s) {
    int res=0,gap=0;
    for(int i=s.length()-1;i>=0;--i){
        res = res + (s[i]-'A'+1)*pow(26,gap);
        ++gap;//次方++
    }
    return res;
}
```

## Pow(x, n)

实现 [pow(*x*, *n*)](https://www.cplusplus.com/reference/valarray/pow/) ，即计算 x 的 n 次幂函数，参考https://leetcode-cn.com/problems/powx-n/comments/10689

```cpp
double myPow(double x, int n) {
    double res = 1.0;
    for(int i = n; i != 0; i /= 2){
        if(i % 2 != 0){
            res *= x;
        }
        x *= x;
    }
    return  n < 0 ? 1 / res : res;
}
```

## x 的平方根

实现 int sqrt(int x) 函数。

计算并返回 x 的平方根，其中 x 是非负整数。

由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。

思路：二分，L=0，R=x，每次对比mid*mid和x的大小即可

```cpp
int mySqrt(int x) {
    int L=0,R=x,ans=-1;
    while(L<=R){
        int mid = L+(R-L)/2;
        if((long)mid*mid<=x){//防止越界，转为long
            ans=mid;
            L=mid+1;
        }else R=mid-1;
    }
    return ans;
}
```

## 两数相除

给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 dividend 除以除数 divisor 得到的商。

代码直接参考[liujin](https://leetcode-cn.com/problems/divide-two-integers/solution/po-su-de-xiang-fa-mei-you-wei-yun-suan-mei-you-yi-/)

```cpp
/*
作者：liujin-4
链接：https://leetcode-cn.com/problems/divide-two-integers/solution/po-su-de-xiang-fa-mei-you-wei-yun-suan-mei-you-yi-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int divide(int dividend, int divisor) {
    if(dividend == 0) return 0;
    if(divisor == 1) return dividend;
    if(divisor == -1){
        if(dividend>INT_MIN) return -dividend;// 只要不是最小的那个整数，都是直接返回相反数就好啦
        return INT_MAX;// 是最小的那个，那就返回最大的整数啦
    }
    long a = dividend;
    long b = divisor;
    int sign = 1; 
    if((a>0&&b<0) || (a<0&&b>0)){
        sign = -1;
    }
    a = a>0?a:-a;
    b = b>0?b:-b;
    long res = div(a,b);
    if(sign>0)return res>INT_MAX?INT_MAX:res;
    return -res;
}
int div(long a, long b){  // 似乎精髓和难点就在于下面这几句
    if(a<b) return 0;
    long count = 1;
    long tb = b; // 在后面的代码中不更新b
    while((tb+tb)<=a){
        count = count + count; // 最小解翻倍
        tb = tb+tb; // 当前测试的值也翻倍
    }
    return count + div(a-tb,b);
}
```

## 分数到小数

给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以字符串形式返回小数。

如果小数部分为循环小数，则将循环的部分括在括号内

直接参考[algsCG](https://leetcode-cn.com/problems/fraction-to-recurring-decimal/solution/fen-shu-dao-xiao-shu-by-leetcode/157208)

```cpp
//小数部分如果余数重复出现两次就表示该小数是循环小数了
string fractionToDecimal(int numerator, int denominator) {
    if(denominator==0) return "";//边界条件，分母为0
    if(numerator==0) return "0";//边界条件，分子为0
    string result;

    //转换为longlong防止溢出
    long long num = static_cast<long long>(numerator);
    long long denom = static_cast<long long>(denominator);

    //处理正负号，一正一负取负号
    if((num>0)^(denom>0))result.push_back('-');

    //分子分母全部转换为正数
    num=llabs(num);denom=llabs(denom);

    //处理整数部分
    result.append(to_string(num/denom));

    //处理小数部分
    num%=denom;                         //获得余数
    if(num==0)return result;             //余数为0，表示整除了，直接返回结果
    result.push_back('.');              //余数不为0，添加小数点
    int index=result.size()-1;          //获得小数点的下标
    unordered_map<int,int> record;      //map用来记录出现重复数的下标，然后将'('插入到重复数前面就好了
    while(num&&record.count(num)==0){   //小数部分：余数不为0且余数还没有出现重复数字
        record[num]=++index;
        num*=10;                        //余数扩大10倍，然后求商，和草稿本上运算方法是一样的
        result+=to_string(num/denom);
        num%=denom;
    }
    if(record.count(num)==1){           //出现循环余数，我们直接在重复数字前面添加'(',字符串末尾添加')'
        result.insert(record[num],"(");
        result.push_back(')');
    }
    return result;
}
```

# 其他

## 两整数之和

**不使用**运算符 `+` 和 `-` ，计算两整数 `a` 、`b` 之和

思路：位运算模拟，参考[Allen](https://leetcode-cn.com/problems/sum-of-two-integers/comments/69218)

```cpp
int getSum(int a, int b) {
    while (b) {
        auto c = ((unsigned int)a & b) << 1; // 防止 AddressSanitizer 对有符号左移的溢出保护处理
        a = a ^ b;
        b = c;
    }
    return a;
}
```

## 逆波兰表达式求值

根据[ 逆波兰表示法](https://baike.baidu.com/item/逆波兰式/128437)，求表达式的值。

思路：用栈模拟，参考[代码随想录](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/solution/150-ni-bo-lan-biao-da-shi-qiu-zhi-zhan-de-jing-dia/)

```cpp
/*
作者：carlsun-2
链接：https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/solution/150-ni-bo-lan-biao-da-shi-qiu-zhi-zhan-de-jing-dia/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int evalRPN(vector<string>& tokens) {
    stack<int> st;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
            int num1 = st.top();
            st.pop();
            int num2 = st.top();
            st.pop();
            if (tokens[i] == "+") st.push(num2 + num1);
            if (tokens[i] == "-") st.push(num2 - num1);
            if (tokens[i] == "*") st.push(num2 * num1);
            if (tokens[i] == "/") st.push(num2 / num1);
        } else {
            st.push(stoi(tokens[i]));
        }
    }
    int result = st.top();
    st.pop(); // 把栈里最后一个元素弹出（其实不弹出也没事）
    return result;
}
```

## 多数元素

给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

思路1：map计数，但需要O(n)空间

思路2：一个变量计数，参考[YourBaymax](https://leetcode-cn.com/problems/majority-element/comments/418)

```cpp
int majorityElement(vector<int>& nums) {
    int count = 1;
    int res = nums[0];
    for(int i = 1;i<nums.size();i++)
    {
        if(count == 0)
        {
            res = nums[i];
            count = 1;
        }
        else
        {
            if(res == nums[i]) count++;
            else count--;
        }
    }
    return res;
}
```

## 任务调度器

给定一个用字符数组表示的 CPU 需要执行的任务列表。其中包含使用大写的 A - Z 字母表示的26 种不同种类的任务。任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。CPU 在任何一个单位时间内都可以执行一个任务，或者在待命状态。

然而，两个相同种类的任务之间必须有长度为 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。

你需要计算完成所有任务所需要的最短时间

直接参考[popopop](https://leetcode-cn.com/problems/task-scheduler/solution/tong-zi-by-popopop/)

```cpp
/*
作者：popopop
链接：https://leetcode-cn.com/problems/task-scheduler/solution/tong-zi-by-popopop/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int leastInterval(vector<char>& tasks, int n) {
    int len=tasks.size();
    vector<int> vec(26);
    for(char c:tasks) ++vec[c-'A'];
    sort(vec.begin(),vec.end(),[](int& x,int&y){return x>y;});
    int cnt=1;
    while(cnt<vec.size()&&vec[cnt]==vec[0]) cnt++;
    return max(len,cnt+(n+1)*(vec[0]-1) );
}
```
