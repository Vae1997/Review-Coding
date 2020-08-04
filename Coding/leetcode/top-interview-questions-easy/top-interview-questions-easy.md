:link:https://leetcode-cn.com/explore/interview/card/top-interview-questions-easy/

# 数组

## 删除排序数组中的重复项

`排序`数组`原地`删除重复元素（ `O(1)` 空间），返回移除后数组长度

- 双指针，L定位一个元素，R遍历寻找不同的元素
- 找到后先将L+1，再将R元素赋值
- R到达末尾，L+1即为无重复数组长度

```cpp
int removeDuplicates(vector<int>& nums) {
    if(!nums.size())//空数组
        return 0;
    int L=0,R=1;//前后指针
    for (; R < nums.size(); ++R)//移动后指针
    {
        if(nums[L]!=nums[R])//直到找到不同元素
        {
            nums[++L]=nums[R];//先++L移动前指针，再赋值为后指针的值
        }
    }//遍历结束，L指向最后一个无重复的元素
    return L+1;//下标从0开始，最终数组长度L+1
}
```

## 买卖股票的最佳时机 II

数组第 *i* 个元素是股票第 *i* 天的价格，可多次买卖，求最大收益

- 在每次的上升时刻进行交易，将所得累加即可

```cpp
int maxProfit(vector<int>& prices) {
    int sum=0;
    for (int i = 1; i < prices.size(); ++i)
    {
        if(prices[i-1]<prices[i])//和前一天比较价格较高
        {
            sum+=prices[i]-prices[i-1];//前一天买，今天卖，累加收益
        }
    }//遍历结束，sum累计股票所有上升阶段的和，因此为最大收益
    return sum;
}
```

## 旋转数组

给定一个数组，将数组中的元素向右移动 *k* （非负数）个位置，思路：

- 暴力：数组元素挨个向右移动k次
- 额外数组：将i元素放置在新数组(i+k)%len位置，最后拷贝回原数组
- 三次反转：①反转0~len ②反转0~k ③反转k+1~len
- 环状替换：

```cpp
void rotate(vector<int>& nums, int k) {
    k%=nums.size();
    int count=0;//交换次数
    for(int i=0; count<nums.size(); ++i)//从0下标开始交换每个元素
    {
        int cur=i;//保存当前轮次起始下标
        int pre=nums[i];//保存起始元素
        do{
            int next=(cur+k)%nums.size();//将要放置位
            int tmp=nums[next];//保存next下标元素
            nums[next]=pre;//前一个元素覆盖next元素
            pre=tmp;//重置pre元素为next元素
            cur=next;//重置cur下标为next
            count++;//交换次数++
        }while(cur!=i);//cur==i则表示一轮结束，交换到了起点位置i，i++为起点继续，直到交换nums.size()次
    }
}
```

## 存在重复元素

判断一个整数数组是否存在重复元素，如任意一值出现至少两次返回true

- 直接存入set，已有则返回true

```cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> s;
    for(int i:nums)
    {
        if(s.count(i))//set中有i，则有重复
            return true;
        else
            s.insert(i);//否则插入
    }
    return false;
}
```

## 只出现一次的数字

找出一个整数数组中唯一只出现一次的某个元素，`其余元素均出现两次`，时间O(n)，空间O(1)

- 注意到，其余元素均出现两次，则异或为0
- 结合异或运算的交换律，从0挨个异或数组元素即可

```cpp
int singleNumber(vector<int>& nums) {
    int single=0;//0^i=i;i^i=0
    for(int i:nums)//整个遍历相当于计算：0^nums[0]^nums[1]···^nums[n-1]
    {              //                 =(a^a)^(b^b)^···^single
        single^=i; //                 =0^0^···^single
    }              //                 =single
    return single;
}
```

## 两个数组的交集 II

给定两个数组，编写一个函数来计算它们的交集。

- map存放一个数组元素及其次数
- 遍历另一个数组，并在map中查找对应元素
- 找到则为交集元素，计数-1；当计数为0，则将元素从map中移除

```cpp
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int,int> m;//key：nums1元素，value：次数
    for(int i:nums1)//将nums1存入map
    {
        if(m.count(i))//已有元素，计数++
            m[i]++;
        else
            m[i]=1;//新元素
    }
    vector<int> res;
    for(int i:nums2)//遍历nums2
    {
        if(m.count(i))//nums2中的i在nums1中出现
        {
            res.push_back(i);//存入结果
            m[i]--;//计数--
            if(!m[i])//计数为0
                m.erase(i);//移除数字i
        }
    }
    return res;
}
```

- 如果给定的数组已经排好序呢？你将如何优化你的算法？

  答：双指针，元素相等则同时移动指针并存入；否则移动元素较小的那个指针

- 如果 *nums1* 的大小比 *nums2* 小很多，哪种方法更优？

  答：将`元素较少的数组`存入map减少空间开销，遍历另一个数组

- 如果 *nums2* 的元素存储在磁盘上，磁盘内存是有限的，并且你不能一次加载所有的元素到内存中，你该怎么办？

  答：归并外排+双指针（内存有限，不能用哈希表）

## 加一

由整数数表示的非负整数，在该数的基础上加一，最高位数字存放在数组的首位， 数组中每个元素只存储**单个**数字

- 逆序遍历数字并进行累加，未发生进位则直接退出循环
- 否则将当前位置0，下一位继续+1；最高位+1时直接置1，数组末尾push一个0

```cpp
vector<int> plusOne(vector<int>& digits) {
    int i=digits.size()-1;
    for(; i>=0; --i)//从低位开始计算
    {
        digits[i]+=1;//加一
        if(digits[i]<10)//不需要进位，直接break
            break;
        else
            digits[i]=0;//进位，置0
    }
    if(i<0)//最高位发生进位
    {
        digits[0]=1;//最高位置1
        digits.push_back(0);//末尾+0
    }
    return digits;
}
```

## 移动零

将所有 `0` 移动到数组的末尾，同时`保持非零元素的相对顺序`，尽量少的操作次数，空间O(1)

- 注意：保存非零元素相对位置，因此不能选择首尾指针进行交换操作

1. 朴素想法：
   - 一次遍历记录0元素个数，同时将非零元素依次存放在额外数组O(n)
   - 额外数组后补0，再倒回原数组
2. 双指针+两次遍历：
   - R从0开始遍历，R非零则赋给L，L++。R到达末尾，第一次遍历结束
   - 记录此时L位置，此刻L之前所有非零元素已经按照相对位置排好
   - 第二次遍历从L开始直接赋值0，直到数组末尾
3. 双指针+一次遍历：
   - 双指针，L为首个0元素位置，R为L之后的首个非零元素位置
   - 交换L、R，即可保证非零元素相对位置

```cpp
void moveZeroes(vector<int>& nums) {
    int L=0,R;
    while(L<nums.size())
    {
        while(L<nums.size() && nums[L]!=0)
            ++L;//L记录0元素位置
        R=L+1;
        while(R<nums.size() && nums[R]==0)
            ++R;//R为L之后的非零元素
        if(L<nums.size() && R<nums.size())
            swap(nums[L++],nums[R++]);//交换L、R之后，分别++，进行下一次交换位置的判断
	}
}
```

```cpp
//简化上述写法
int L = 0;//记录需要覆盖的位置
for (int R = 0; R < nums.size(); ++R) {//内部第二个while，找非零位置
    if (nums[R] != 0) {//找到非零的交换目标
        if (R > L) {//交换位置在目标左侧，需要交换
            nums[L] = nums[R];//赋值到L
            nums[R] = 0;//R直接为0
        }//若R<=L，则不需要交换，L和R同时++即可
        L++;
    }
}
```

## 两数之和

给定一个整数数组 `nums` 和一个目标值 `target`，请你在该数组中找出和为目标值的那 **两个** 整数，并返回他们的数组下标

- 将元素i存入map之前，判断target-i是否已经存在
- 没有，则存入map；否则返回对应下标

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int,int> m;
    for(int i=0; i<nums.size(); ++i)
    {
        if(m.count(target-nums[i]))//map中已经存入target-i
            return {m[target-nums[i]],i};//target-i早于i存入，因此下标在前
        m[nums[i]]=i;//存入第i位元素
    }
    return {};
}
```

## 有效的数独(略)

判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可

```cpp
/*
作者：youlookdeliciousc
链接：https://leetcode-cn.com/problems/valid-sudoku/solution/cxiang-xi-ti-jie-ha-xi-biao-ji-jian-by-youlookdeli/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
bool isValidSudoku(vector<vector<char>>& board) {
    vector<unordered_map<int,int>> row(9), col(9), block(9);
    for(int i = 0; i < 9; ++ i){
        for(int j = 0; j < 9; ++ j){//遍历每个元素
            char cur = board[i][j];
            if(cur == '.')  continue;//略过空白
            int bindex =  (i / 3)* 3 + j / 3;//确定元素i，j所在的box位置
            if(row[i].count(cur) || col[j].count(cur) || block[bindex].count(cur))  
                return false;//第i行或第j列或第bindex个box中出现cur，则false
            row[i][cur] = 1;//设置i行的cur为1
            col[j][cur] = 1;//设置j列的cur为1
            block[bindex][cur] = 1;//设置第bindex个box的cur为1
        }
    }
    return true;
}
```

## 旋转图像(略)

给定一个 *n* × *n* 的二维矩阵表示一个图像，并将图像原地顺时针旋转 90 度

- 官方题解，先转置矩阵，再反转每行即可

```cpp
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    // 转置矩阵，即第i行变为第i列，即i行j列元素与j行i列元素交换
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        swap(matrix[i][j],matrix[j][i]);
      }
    }
    // 反转每一行
    for (int i = 0; i < n; i++) {
        reverse(matrix[i].begin(),matrix[i].end());
    }
}
```

# 字符串

## 反转字符串

原地将输入的字符串反转，O(1) 空间

- 双指针，首尾移动并进行元素交换即可

```cpp
void reverseString(vector<char>& s) {
    int L=0,R=s.size()-1;
    while(L<R)
    {
        if(s[L]!=s[R])
            swap(s[L],s[R]);
        ++L;
        --R;
    }
}
```

## 整数反转

给出一个 32 位的有符号整数$$[-2^{31},2^{31}-1]$$，你需要将这个整数中每位上的数字进行反转，反转后溢出为0

- 朴素想法：

```cpp
int reverse(int x) {
    string s=to_string(x);//先转为string
    ::reverse(s.begin(),s.end());//反转string
    long X=s[s.length()-1]=='-'?-stol(s):stol(s);//stol将string转long，注意负数
    if(X>2147483647 || X<-2147483648)//判断long是否超过int
        return 0;
    return X;
}
```

- 数学方法

```cpp
/*
作者：guanpengchn
链接：https://leetcode-cn.com/problems/reverse-integer/solution/hua-jie-suan-fa-7-zheng-shu-fan-zhuan-by-guanpengc/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int reverse(int x) {
    int ans = 0;
    while (x != 0) {//循环拆解x
        int pop = x % 10;//从低到高的每一位数字
        if (ans > INT_MAX / 10 || (ans == INT_MAX / 10 && pop > 7)) //大于最大
            return 0;
        if (ans < INT_MIN / 10 || (ans == INT_MIN / 10 && pop < -8)) //小于最小
            return 0;
        ans = ans * 10 + pop;//没有溢出，则进行累加
        x /= 10;//准备取下一位数字
    }
    return ans;
}
```

## 字符串中的第一个唯一字符

给定一个字符串，找到它的第一个不重复的字符，并返回它的索引。如果不存在，则返回 -1

```c++
int firstUniqChar(string s) {
    if(s=="")return -1;
    unordered_map<char,pair<int,int>> m;//pair分别对应char的下标和出现次数
    int index=0;
    for(char c:s)
    {
        if(m.count(c))//已经有char
            m[c].second++;//只增加次数
        else 
            m[c]=make_pair(index,1);//否则新建pair，当前index，次数1
        ++index;//下标++
    }
    index=INT_MAX;
    for(auto v:m)
    {//char次数为1，并且index最小的即为所求
        if(v.second.first<index && v.second.second==1)
            index=v.second.first;
    }
    return index==INT_MAX?-1:index;//index如果没有变，说明全部重复返回-1，否则返回index
}
```

可以直接指定长度为26的数组：

```cpp
/*
作者：zrita
链接：https://leetcode-cn.com/problems/first-unique-character-in-a-string/solution/c-gou-zao-ha-xi-shu-zu-jian-ji-yi-dong-90-z-by-zri/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int hash[26]={0};   
for(char n:s)
    hash[n-'a']++;//n-'a'，得到该字母在数组中对应的索引
for(int i=0;i<s.size();i++)
    if(hash[s[i]-'a']==1)//如果只出现了一次
        return i;
return -1;
```

## 有效的字母异位词

给定两个字符串 *s* 和 *t* ，编写一个函数来判断 *t* 是否是 *s* 的字母异位词。

```cpp
bool isAnagram(string s, string t) {
    if(s.length()!=t.length()) return false;//长度不一，false
    unordered_map<char,int> ms,mt;
    for(char c:s)//存放s
    {
        if(ms.count(c))
            ms[c]++;
        else ms[c]=1;
    }
    for(char c:t)//存放t，也可以使用ms，对应计数-1，出现小于0的计数则为false
    {
        if(mt.count(c))
            mt[c]++;
        else mt[c]=1;
    }
    for(char c:s)
    {
        if(ms[c]!=mt[c])//只要出现次数不一致，false
            return false;
    }
    return true;
}
```

## 验证回文字符串

给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

```cpp
bool isPalindrome(string s) {
    int L=0,R=s.length()-1;
    while(L<R)
    {
        while (L < R && !isalnum(s[L])) //isalnum包含字母和数字，直到L找到字母或数字
            ++L;
        while (L < R && !isalnum(s[R])) //R同理
            --R;
        if (tolower(s[L]) != tolower(s[R])) //字母统一tolower转小写，数字则返回对应ascii码
            return false;
        ++L;
        --R;
    }
    return true;
}
```

## 字符串转换整数 (atoi)

```cpp
int myAtoi(string str) {
    if(str.empty())return 0;//排除空串
    long number=0;//注意为long
    char sign=' ';//符号   
    int tag=0;//溢出标记
    for (int i = 0; i < str.length(); i++)
    {
        char c=str[i];
        if(c==' ' && tag==0 && sign==' ')continue;//空格忽略
        if((c=='+'||c=='-') && tag==0 && sign==' ')sign=c;//标记符号
        else if(c>='0' &&c <='9')//数字
        {
            number=number*10+(c-'0');//计算
            if(INT_MAX-number<0){tag=888;break;}//溢出标记
            tag=1;//标记数字               
        }else break;//其他字符直接return    
    }
    //溢出返回
    if(tag==888)return sign=='-'?INT_MIN:INT_MAX;
    //正常返回
    return sign=='-'?(-number):number;
}
```

## 实现 strStr()

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)

如果不存在，则返回 **-1**；当 `needle` 是空字符串时，返回0

```cpp
int strStr(string haystack, string needle) {
    if(needle=="" || haystack==needle)return 0;//空串或相等直接为0
    int n=needle.length();
    int m=haystack.length();
    for(int i=0; n<=m-i; ++i)//n比剩余串还长，直接跳出
    {
        if(haystack[i]==needle[0])//开始匹配
        {
            if(haystack.substr(i,n) == needle)//裁剪，如果相等直接返回
                return i;
        }
    }
    return -1;
}
```

## 外观数列

给定一个正整数 *n*（1 ≤ *n* ≤ 30），输出外观数列的第 *n* 项。

「外观数列」是一个整数序列，从数字 1 开始，序列中的每一项都是对前一项的描述。前五项如下：

```c++
1		//基准
11		//一个1
21		//两个1
1211	//一个2，一个1
111221	//一个1，一个2，两个1
```

```cpp
string countAndSay(int n) {
    string s="1";//基准
    string pre="";
    while(n>1)
    {
        pre=s;//保存前一行构造的字符串
        s="";//每次构造新的一行，s置空
        for(int i=0; i<pre.size(); ++i)//遍历前一行的字符串
        {
        	int count=1;//每个不同的字符，初始化计数1
            while(pre[i+1] == pre[i])//和下一位相等，注意当i为size-1时，i+1指向\0，因此不需担心越界
            {
                ++count;//计数+1
                ++i;//下标+1
            }//构造count个i位置的字符
            s+=to_string(count)+pre[i];
        }//当前行构造s完毕，n--，继续下一行
        --n;
    }
    return s;
}
```

## 最长公共前缀

查找字符串数组中的最长公共``前缀``，不存在返回 `""`，输入只包含小写字母 `a-z` 

```cpp
string longestCommonPrefix(vector<string>& strs) {
    int n=strs.size();
    if(n==0)return "";//空数组
    if(n==1)return strs[0];//只有一个元素
    vector<int> hash(26,-1);//记录字母出现次数，或只记录是否出现
    string s="";
    for(int i=0; i<strs[0].length(); ++i)//直接用第一个字符串遍历
    {
        hash[strs[0][i]-'a']=0;//将i位字符置0，表示已经出现
        for(string s:strs)//挨个拿字符串
            //i==s.length()表示有个字符串已经判断到末尾，再往下判断将发生下标溢出
            //hash[s[i]-'a']==-1表示s字符串的第i个字符之前没有出现
            if(i==s.length() || hash[s[i]-'a']==-1)
                return strs[0].substr(0,i);//直接将strs[0]截取到i即可
            //else hash[s[i]-'a']++; 不必++计数
        hash[strs[0][i]-'a']=-1;//注意i位字符判断完后，需重置为-1，避免之后再次出现时，发现为0而误以为i已经出现
    }//第一个字符串遍历完毕都没return，则直接返回strs[0]，表明该字符串即为最长公共前缀
    return strs[0];
}
```

另，可以直接排序strs，第一个长度最小，最后一个长度最大，则只需比较两者的前缀即可：

```cpp
/*
作者：you-yuan-de-cang-qiong
链接：https://leetcode-cn.com/problems/longest-common-prefix/solution/zi-dian-xu-zui-da-he-zui-xiao-zi-fu-chuan-de-gong-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
string longestCommonPrefix(vector<string>& strs) {
    if(strs.empty()) return "";
    const auto p = minmax_element(strs.begin(), strs.end());//p为pair类型，first为min，second为max
    for(int i = 0; i < p.first->size(); ++i)//遍历短的min，第i位不等则substr
        if(p.first->at(i) != p.second->at(i)) return p.first->substr(0, i);
    return *p.first;//遍历完，则直接返回min
}
```

# 链表

```cpp
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
```



## 删除链表中的节点

请编写一个函数，使其可以删除某个链表中给定的（非末尾）节点，你将只被给定要求被删除的节点

- 采用覆盖的方式进行删除，注意释放内存

```cpp
void deleteNode(ListNode* node) {//注意参数只有要删除的节点
    node->val=node->next->val;//直接用next节点值覆盖删除节点
    ListNode* deleteNode=node->next;//保存node->next作为删除节点，需释放内存
    node->next=deleteNode->next;//node节点指向deleteNode->next
    delete deleteNode;//防止内存泄漏
    //可以直接*node=*(node->next);
}
```

## 删除链表的倒数第N个节点

给定一个链表，一次遍历删除链表的倒数第 *n* 个节点，并且返回链表的头结点，n确保有效

- 双指针：R走到第n个节点，L、R再一起移动，R到末尾，L即为删除节点

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if(!head || !head->next)return nullptr;//空表或单个节点，删除均返回空
    ListNode* L=head;
    ListNode* R=L->next;
    ListNode* phead=new ListNode(-1);//哨兵节点
    phead->next=head;
    while(n-1)//R指向L->next，因此移动n-1步
    {
        R=R->next;
        --n;
    }
    //这里R为空，可以直接返回head->next，表明删除头节点
    while(R)
    {
        phead=L;//保存L之前的节点
        L=L->next;
        R=R->next;
    }
    phead->next=L->next;//删除L
    //L==head表示删除头节点，需返回phead->next
    return L==head?phead->next:head;
}
```

## 反转链表

迭代或递归地反转一个单链表

```cpp
ListNode* reverseList(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode* phead=reverseList(head->next);//递归
    head->next->next=head;//反转操作
    head->next=nullptr;
    return phead;
}
```

```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* phead=nullptr;
    ListNode* p=head;
    ListNode* tmp=phead;
    while(p)
    {
        tmp=p->next;//保存下一个节点
        p->next=phead;//当前节点的next指向pre
        phead=p;//pre节点后移
        p=tmp;//p后移
    }
    return phead;
}
```

## 合并两个有序链表

将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

- pre节点保存前一个节点，取l1和l2中较小值作为pre->next

```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* phead=new ListNode(-1);
    ListNode* pre=phead;//保存前一个节点
    while(l1 && l2)
    {
        if(l1->val <= l2->val)//l1小
        {
            pre->next=l1;//pre节点的next为l1
            l1=l1->next;//l1++
        }
        else//否则为l2
        {
            pre->next=l2;
            l2=l2->next;
        }
        pre=pre->next;//更新pre节点
    }
    pre->next=l1?l1:l2;//若一个链表没结束，则接到pre之后
    return phead->next;
}
```

## 回文链表

请判断一个链表是否为回文链表，时间O(n)，空间O(1)

- 快慢指针：快指针每次走两步，慢指针每次走一步并反转，快指针到达末尾后断开链表并进行比较即可

```cpp
bool isPalindrome(ListNode* head) {
    if(!head || !head->next)return true;//空表、单节点表也为回文，true
    ListNode* L=head;
    ListNode* R=head;
    ListNode* p=nullptr;
    ListNode* tmp=nullptr;
    while(R && R->next)//R到达末尾，开始比较
    {
        R=R->next->next;//R移动两步,R需要先移动，否则反转后无法到达next节点
        tmp=L->next;//保存下一个节点
        L->next=p;//反转
        p=L;//前置节点后移
        L=tmp;//L节点后移
    }
    //此时，若R非空，奇数节点，p指向左链表头部，L指向右链表头部，但为中间元素，需从L->next开始比较
    //否则，偶数节点，p指向左链表头部，L指向右链表头部，从L开始比较
    if(R) L=L->next;
    while(p && L)
    {
        if(p->val != L->val)//有一个不等，false
            return false;
        p=p->next;
        L=L->next;
    }
    return true;
}
```

## 环形链表

给定一个链表，判断链表中是否有环

- 快慢指针：快+2，慢+1，值相等，则有环

```cpp
bool hasCycle(ListNode *head) {
    if(!head || !head->next) return false;
    ListNode* L=head;
    ListNode* R=head->next;
    while(L && R && R->next)//确保R->next非空
    {
        if(L->val == R->val) //相等直接返回
            return true;
        L=L->next;//L+1
        R=R->next->next;//R+2
    }
    return false;
}
```

# 树

```cpp
//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
```

## 二叉树的最大深度

给定一个二叉树，找出其最大深度

```cpp
int maxDepth(TreeNode* root) {
    if(!root) return 0;
    //root非空，deep+1+左右子树的最大深度
    return 1+max(maxDepth(root->left),maxDepth(root->right));
}
```

```cpp
int maxDepth(TreeNode* root) {
    if(!root) return 0;
    pair<TreeNode*,int> r = make_pair(root,1);//保存每个节点及其深度
    queue<pair<TreeNode*,int>> q;
    q.push(r);
    int deep=1;
    while(!q.empty())
    {
        TreeNode* p=q.front().first;//获取队头
        deep=q.front().second;//更新deep
        q.pop();//弹出队头
        if(p->left)
            q.push(make_pair(p->left,deep+1));//加入左节点
        if(p->right)
            q.push(make_pair(p->right,deep+1));//加入右节点
    }
    return deep;
}
```

## 验证二叉搜索树

给定一个二叉树，判断其是否是一个有效的二叉搜索树

- 二叉搜索树中序遍历为增序

```cpp
long pre = LLONG_MIN;//测试用例包含INT_MIN，因此最初的值需要更小
bool isValidBST(TreeNode* root) {
    if(!root) return true;
    if(!isValidBST(root->left))//递归到最左节点
        return false;
    if(root->val <= pre)//中序遍历的当前节点大于pre值，则false
        return false;
    pre = root->val;//否则保存当前值
    return isValidBST(root->right);//递归右子树
}
```

```cpp
bool isValidBST(TreeNode* root) {
    stack<TreeNode*> s;
    long pre = LLONG_MIN;
    while(!s.empty() || root)
    {
        while(root)//迭代到最左节点
        {
            s.push(root);//依次入栈
            root=root->left;
        }
        root=s.top();
        s.pop();
        if(root->val <= pre) return false;//比之前节点值小，false
        pre=root->val;//更新pre值
        root=root->right;//
    }
    return true;
}
```

## 对称二叉树

给定一个二叉树，检查它是否是镜像对称的

:book:https://leetcode-cn.com/problems/symmetric-tree/solution/di-gui-die-dai-bi-xu-miao-dong-by-sweetiee/

```cpp
bool isSymmetric(TreeNode* left,TreeNode* right) {
    if(!left && !right) return true;//俩节点均递归到叶节点，说明对称，回溯
    //有一个非空，或俩节点值不相等，则不对称
    if(!left || !right || left->val != right->val) return false;
    //分别对比两侧的子节点和中间两个子节点
    return isSymmetric(left->left,right->right) && isSymmetric(left->right,right->left);
}
bool isSymmetric(TreeNode* root) {
    return isSymmetric(root,root);//传入两个节点，分别进行比对
}
```

```cpp
bool isSymmetric(TreeNode* root) {
    if(!root) return true;
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);//将root左右节点入队
    TreeNode* L;
    TreeNode* R;
    while(!q.empty())
    {
        L=q.front();q.pop();//每次取队列两个节点
        R=q.front();q.pop();
        if(!L && !R) continue;//空，也表示相等，直接下一轮，不需要入队
        if(!L || !R || L->val != R->val) return false;//有一个非空，或值不相等
        q.push(L->left);//左子树的左节点
        q.push(R->right);//右子树的右节点
        q.push(L->right);
        q.push(R->left);
    }
    return true;
}
```

## 二叉树的层序遍历

给你一个二叉树，请你返回其按 **层序遍历** 得到的节点值。 （即逐层地，从左到右访问所有节点）

- BFS使用队列进行迭代，注意内部循环通过q.size()确保区别每层节点
- DFS额外记录深度进行递归

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    if(!root)return {};
    vector<vector<int>> v;
    queue<TreeNode*> q;//队列，BFS入队
    q.push(root);
    while (!q.empty())
    {
        int count=q.size();//记录节点数，以便确定每层
        vector<int> vv;
        while (count--)//内部循环count次，将当前层的节点加入数组
        {
            TreeNode* n=q.front();
            vv.push_back(n->val);
            q.pop();
            if(n->left)q.push(n->left);
            if(n->right)q.push(n->right);
        }
        v.push_back(vv);
    }
    return v;
}
```

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    if(!root)return {};
    vector<vector<int>> res;
    dfs(root,res,0);//从0开始,根节点为第0层，对应结果数组下标为0
    return res;
}
void dfs(TreeNode* root,vector<vector<int>>& res,int deep)
{
    if(!root)return {};
    if(deep >= res.size())//当前递归深度大于结果数组的大小，说明需要构建新的一层
        res.push_back(vector<int>());
    res[deep].push_back(root->val);//res中的当前层下标添加root值
    dfs(root->left,res,deep+1);//递归左子树
    dfs(root->right,res,deep+1);//递归右子树
}
```

## 将有序数组转换为二叉搜索树

将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树

- 高度平衡，则每次选择中间元素作为根节点

```cpp
TreeNode* sortedArrayToBST(vector<int>& nums,int L,int R) {
    if(L<=R){
        int mid=L+(R-L)/2;
        TreeNode* root=new TreeNode(nums[mid]);//中间元素为根
        root->left=sortedArrayToBST(nums,L,mid-1);//递归左侧
        root->right=sortedArrayToBST(nums,mid+1,R);//递归右侧
        return root;
    }
    return nullptr;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return sortedArrayToBST(nums,0,nums.size()-1);
}
```

# 排序和搜索

## 合并两个有序数组

两个有序整数数组 ，将 *nums2* （n个元素）合并到 *nums1* （m个元素）中*，*使 *nums1* 有序，nums1长度>=m+n

- 合并nums1和nums2后排序
- 双指针从前往后，并借助额外空间存放合并结果
- 注意到nums1数组足够长，因此双指针``从后往前``，O(1)空间

```cpp
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    for(int i=nums1.size()-1;m-1>=0||n-1>=0;--i)//从后往前，m和n均为0时结束
    {
        if(m-1>=0 && n-1>=0 && nums1[m-1]>=nums2[n-1])//防止下标越界，之后数组1大于2
        {
            nums1[i]=nums1[m-1];//将大的值放在后面
            --m;//num1下标前移
        }
        else if(n-1>=0)//nums2值大
        {
            nums1[i]=nums2[n-1];
            --n;//nums2前移
        }
        else break;//n全部放入num1，结束
    }
    //如果nums1长度len大于m+n，nums1还需裁剪掉前面的len-m-n个元素
    //但是力扣没有测试用例，默认nums1长度为m+n，要避免这种情况初始值i=m+n-1
}
```

## 第一个错误版本

- 二分查找

```cpp
int firstBadVersion(int n) {
    int L=0,mid;
    while(L<n)
    {
        mid=L+(n-L)/2;
        if(isBadVersion(mid))//如果是错误的，则尝试继续往前找
        {
            n=mid;//不能-1，否则如果前面没有错的，就回不到当前这个错误的位置了
        }
        else
        {
            L=mid+1;//是对的，则L+1，往后走查找
        }
    }
    return n;
}
```

# 动态规划

## 爬楼梯

假设你正在爬楼梯。需要 *n* 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

```cpp
int climbStairs(int n) {
    if(n<4)return n; 
    int a=2,b=3,s;//斐波那契数列
    for(int i=4;i<=n;++i)
    {
        // s=a+b;
        // a=b;
        // b=s;
        b=a+b;//新的后一项为前两项和
        a=b-a;//新的前一项为新的后一项减去前一项
    }
    return b;//返回第n个数
}
```

## 买卖股票的最佳时机

数组第 *i* 个元素是股票第 *i* 天的价格，只进行一次买卖，求最大收益

```cpp
int maxProfit(vector<int>& prices) {
    if(prices.size() == 0) return 0;
    vector<int> dp(prices.size(),0);
    dp[0]=max(0,-prices[0]);//第一天，买则为-p[0]，不买收益0
    int MIN=prices[0];//记录历史最小，初始化为第一天
    for(int i=1;i<prices.size();++i)
    {
        MIN=min(MIN,prices[i]);//更新历史最小
        //第i天不卖，则收益同i-1天；卖，则当前价-历史最小价n[i]-MIN为最大收益；两者取最大
        dp[i]=max(dp[i-1],prices[i]-MIN);
    }
    return dp[prices.size()-1];
}
```

## 最大字序和

给定一个整数数组 `nums` ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。`O(n)`

```cpp
int maxSubArray(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    vector<int>dp(nums.size(),0);
    dp[0]=nums[0];//一个本身即为最大
    int MAX=dp[0];//保存最大和，初始化为第1个
    for(int i=1;i<nums.size();++i)
    {
        //第i为如果加，则为i-1+n[i]，加了后还比当前值小，则当前值为i位最大
        dp[i]=max(nums[i],dp[i-1]+nums[i]);
        MAX=max(MAX,dp[i]);//更新MAX，当前i位最大和历史最大比较取大的
    }
    return MAX;
}
```

## 打家劫舍

两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警，非负整数数组，不报警情况下最大金额

```cpp
int rob(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    if(nums.size() == 1) return nums[0];
    vector<int>dp(nums.size(),0);
    dp[0]=nums[0];//只有1家，最大金额即为nums[0]
    dp[1]=max(dp[0],nums[1]);//两家取大的
    for(int i=2;i<nums.size();++i)
    {
        dp[i]=max(dp[i-1],dp[i-2]+nums[i]);//i家不偷即为i-1，偷即为i-2+n[i]
    }
    return dp[nums.size()-1];
}
```

# 设计问题

## 打乱数组

打乱一个没有重复元素的数组（``洗牌算法``），保证n！种可能即可

 ```cpp
class Solution {
public:
    Solution(vector<int>& nums) {
        save = nums;
    }
    /** 重设数组到它的初始状态 */
    vector<int> reset() {
        return save;
    }
    /** 随机返回数组打乱后的结果,数组的任何排列返回的概率应该相同 */
    //参考：https://leetcode-cn.com/u/xiao-wei-6/
    vector<int> shuffle() {
        vector<int> v = save;
		for (int i = 1; i < v.size(); ++i)
		{
			int r = rand() % (i + 1);//随机选取一个交换位置
			if (r != i)
			{
				swap(v[r], v[i]);
			}
		}
		return v;
    }
private:
    vector<int> save;
};
 ```

## 最小栈

除了常规操作，实现``O(1)``时间内找到最小元素的栈

- 两个栈，一个正常存，另一个存放每次比较后的最小值，栈顶即为当前栈的最小值

```cpp
class MinStack {
public:
    void push(int x) {
        s1.push(x);//s1正常入栈
        if(s2.empty())//s2为空，也入栈
            s2.push(x);
        else if(x<=s2.top())//否则如果x比之前的还小，则入栈s2（等于也要入栈，因为不是同一个了）
            s2.push(x);
    }
    void pop() {
        s1.pop();//s1正常弹出
        if(s1.top()==s2.top())//如果弹出的栈顶为最小
            s2.pop();//最小值的栈顶也弹出
    }
    int top() {
        return s1.top();//s1正常栈顶
    }
    int getMin() {
        return s2.top();//最小值为s2的栈顶
    }
private:
    stack<int> s1,s2;
};
```

# 数学

## Fizz Buzz

写一个程序，输出从 1 到 n 数字的字符串表示

1. 如果 n 是3的倍数，输出“Fizz”；
2. 如果 n 是5的倍数，输出“Buzz”；
3. 如果 n 同时是3和5的倍数，输出 “FizzBuzz”

- 直接if判断也可以，但是当映射变多时，代码中的判断过多
- 采用map保存每个key对应的值，每次遍历map进行判断，参考[官方题解](https://leetcode-cn.com/problems/fizz-buzz/solution/fizz-buzz-by-leetcode/)

```cpp
vector<string> fizzBuzz(int n) {
    map<int,string> m = {//如果增加映射，只需修改map即可
        {3,"Fizz"},
        {5,"Buzz"}
    };
    vector<string> v(n);
    string s;
    for(int i=0;i<n;++i)
    {
        s="";//每一轮判断修改的字符串
        for(auto k:m)//遍历map
        {
            if((i+1)%k.first == 0)//可以整除key
                s+=k.second;//字符串增加对应的映射值
        }
        if(s == "")//表示均不可除
            s+=to_string(i+1);//保存原数字
        v[i]=s;
    }
    return v;
}
```

## 计数质数

统计所有小于非负整数 *n* 的质数的数量

- 传统解法，测试**1500000**会超时

```cpp
int countPrimes(int n) {
    if(n<3)return 0;
    if(n==3)return 1;
    if(n==4)return 2;
    int count=2;
    for(int i=5;i<n;++i)
    {
        bool isPrime = true;
        for(int j=2;j<=sqrt(i);++j)//判断到根号i为止
        {
            // cout<<"i:"<<i<<" j:"<<j<<endl;
            if(i%j == 0){
                // cout<<i<<"is not Prime!"<<endl;
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            ++count;
    }
    return count;
}
```

- 判断次数优化：从n，到n/2，到sqrt(n)进行判断，如上，但还是超时
- 考虑倍数，参考[这里](https://leetcode-cn.com/problems/count-primes/solution/ji-shu-zhi-shu-bao-li-fa-ji-you-hua-shai-fa-ji-you/)的题解

```cpp
/*作者：magicalchao
链接：https://leetcode-cn.com/problems/count-primes/solution/ji-shu-zhi-shu-bao-li-fa-ji-you-hua-shai-fa-ji-you/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int countPrimes(int n) {
    int count = 0;
    //初始默认所有数为质数
    vector<bool> signs(n, true);
    for (int i = 2; i < n; i++) {
        if (signs[i]) {
            count++;
            for (int j = i + i; j < n; j += i) {//将当前i的倍数置为false
                //排除不是质数的数
                signs[j] = false;
            }
        }
    }
    return count;
}
```

## 3的幂

给定一个整数，写一个函数来判断它是否是 3 的幂次方

- 普通思路：循环或递归，对传入的数字n进行判断

```cpp
 bool isPowerOfThree(int n) {
     if (n < 1) return false;
     while (n % 3 == 0) //n不能整除3直接跳出
         n /= 3;
     return n == 1;
 }
```

- 数学方法，参考[这里](https://leetcode-cn.com/problems/power-of-three/solution/huan-di-gong-shi-by-yzh/)，n为3的幂，则`log3(n)为整数`，换底公式log10(n) / log10(3)，注意``double型不能直接==比较``

```cpp
/*
作者：yzh
链接：https://leetcode-cn.com/problems/power-of-three/solution/huan-di-gong-shi-by-yzh/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
bool isPowerOfThree(int n) {
    if(n < 1)return false;
    double res = log10(n) / log10(3);
    return res - (int)res == 0?true:false;
}
```

## 罗马数字转整数
参考题解，[腐烂的橘子](https://leetcode-cn.com/problems/roman-to-integer/solution/qing-xi-tu-jie-python3-by-ml-zimingmeng/)

- 使用map存放键值对应关系，下一位比前一位大则在基础上减；否则加

```cpp
/*
作者：z1m
链接：https://leetcode-cn.com/problems/roman-to-integer/solution/qing-xi-tu-jie-python3-by-ml-zimingmeng/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int romanToInt(string s) {
    int result=0;
    map<char,int> luomab={
        {'I',1},
        {'V',5},
        {'X',10},
        {'L',50},
        {'C',100},
        {'D', 500},
        {'M', 1000}
    };//初始化哈希表
    for(int i=0;i<s.length();i++)
    {
        if(luomab[s[i]] < luomab[s[i+1]])
            result -= luomab[s[i]];
        else
        {
            result += luomab[s[i]];
        }
    }
    return result;
}
```

# 其他

## 位1的个数

编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’ 的个数（也被称为[汉明重量](https://baike.baidu.com/item/汉明重量)）

- 直接将n和1相&，为1计数；再右移n即可，直至n==0，:warning:需要注意负数情况
- 左移1，直到为0，n每次相&，为1计数（循环次数为n的位数）
- 将n和n-1相&，会消去n最右边的1，直到n为0（循环次数为1的个数）

```cpp
int hammingWeight(uint32_t n) {
    int count=0;
    while(n)
    {
        count++;
        n &= n-1;
    }
    return count;
}
```

## 汉明距离
两个整数之间的汉明距离指的是这两个数字对应二进制位不同的位置的数目

给出两个整数 x 和 y，计算它们之间的汉明距离

- 按位异或，为1则计数

```cpp
int hammingWeight(uint32_t n) {
    int count=0;
    while(n)
    {
        count++;
        n &= n-1;
    }
    return count;
}
int hammingDistance(int x, int y) {
    return hammingWeight(x ^ y);//直接对异或后的值统计1的个数
}
```

## 颠倒二进制位

颠倒给定的 32 位无符号整数的二进制位

- 常规思路：从右开始左移31位、30位....

```cpp
uint32_t reverseBits(uint32_t n) {
    uint32_t bit=31,res=0;
    while(n)
    {
        res += (n&1) << bit;//n&1确定最后一位，再<<到bit位置
        n >>= 1;//确定下一位
        --bit;//移动位数--
    }
    return res;
}
```

## 杨辉三角

给定一个非负整数 *numRows，*生成杨辉三角的前 *numRows* 行

- 常规思路：双层循环，外层控制行数，内层计算

```cpp
/*
作者：youlookdeliciousc
链接：https://leetcode-cn.com/problems/pascals-triangle/solution/cxiang-xi-ti-jie-by-youlookdeliciousc-4/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/ 
vector<vector<int>> generate(int numRows) {
     vector<vector<int>> ans(numRows);
     if(numRows == 0)    return ans; //若numRows为空，返回空数组
     for(int i = 0; i < numRows; ++ i ) //给数组一个个赋值
     {
         for(int j = 0; j <= i; ++ j)
         {
             if(j == 0 || j == i) //若是左右两边的边界，赋值为1
                 ans[i].push_back(1);
             else
                 ans[i].push_back(ans[i-1][j-1] + ans[i-1][j]); //否则赋值为该位置左上与右上的和
         }
     }
     return ans;
 }
```

- 参考[这里](https://leetcode-cn.com/problems/pascals-triangle-ii/solution/c-8xing-dai-ma-jian-ji-yi-dong-by-heroma-2/)，得到每一行填入数组

```cpp
/*
作者：heromapwrd
链接：https://leetcode-cn.com/problems/pascals-triangle-ii/solution/c-8xing-dai-ma-jian-ji-yi-dong-by-heroma-2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/ 
vector<int> getRow(int rowIndex) {
    vector<int> result;
    for(int i = 0; i <= rowIndex; ++i){
        result.push_back(1);//实际上是每行的最后一个1
        for(int j = i - 1; j > 0; --j){//相当于每行从后往前，最后两个数加，得到下一行的倒数第二个值
            result[j] += result[j - 1];
        }
    }
    return result;
}
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans(numRows);
    for(int i=0;i<numRows;++i)
        ans[i]=getRow(i);
    return ans;
}
```

## 有效的括号
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效

有效字符串需满足：

左括号必须用相同类型的右括号闭合
左括号必须以正确的顺序闭合
注意空字符串可被认为是有效字符串

- 使用栈模拟，使用map存放匹配规则

```cpp
bool isValid(string s) {
    if(s.empty()) return true;
    map<char,char> m = {//匹配规则
        {'(',')'},
        {'[',']'},
        {'{','}'}
    };
    stack<char> k;
    for(int i=0;i<s.length();++i)
    {
        if(!k.empty()){
            if(s[i] == m[k.top()])//匹配，弹出
                k.pop();
            else k.push(s[i]);
        }
        else if(s[i]==')' || s[i]==']' || s[i]=='}')//空栈压入右侧字符直接false
            return false;
        else k.push(s[i]);
    }
    return k.empty();//为空则全部匹配
}
```

## 缺失数字

给定一个包含 `0, 1, 2, ..., n` 中 *n* 个数的序列，找出 0 .. *n* 中没有出现在序列中的那个数

时间`O(n)`，空间`O(1)`

- 排序后查找不符合时间要求
- 哈希表直接查找不符合空间要求
- 高斯法：1~n的和为`n(n+1)/2`，再挨个减去数组元素，剩余的即为缺失

```cpp
int missingNumber(vector<int>& nums) {
    int sum=0;
    for(int i=1;i<=nums.size();++i)
    {
        sum+=i;//先算当前和
        sum-=nums[i-1];//顺便减去之前一个数
    }
    return sum;
}
```

- 异或：根据交换律，异或下标和元素，初始值为n，相同的异或为0

```cpp
int missingNumber(vector<int>& nums) {
    int res=nums.size();
    for(int i=0;i<nums.size();++i)
        res ^= i ^ nums[i];
    return res;
}
```

