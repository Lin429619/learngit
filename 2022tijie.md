> ① 本题解只作为西邮 `Linux `兴趣小组 2022纳新面试题目的有限参考。
② 为节省版面，本试题的程序源码省去了`#include `指令。
③ 本试题中的程序源码仅用于考察 C 语言基础，不应当作为 C 语言「代码风格」的范例。
④ 所有题目编译并运行于 `x86_64 GNU/Linux `环境。
***
## 0. 我的计算器坏了？！

* `2^10 = 1024`对应于十进制的4位，那么`2^10000`对应于十进制的多少位呢?
>采用取对数的方法，取底数为10的对数，结果加一就是对应十进制的位数
>lg[2]=0.301029.....
>lg[2^10]=(10lg[2]+1)=1024
>lg[2^10000]=(10000lg[2]+1)=3011

## 1. printf还能这么玩？

* 尝试着解释程序的输出。

```c
int main(void) {
    if ((3 + 2 < 2) > (3 + 2 > 2))
    //(3 + 2 < 2)返回值为0,(3 + 2 > 2)返回值为1,（0 > 1）返回0,所以不执行下面语句，执行else后面的语句
        printf("Welcome to Xiyou Linux Group\n");
    else
        printf("%d\n", printf("Xiyou Linux Group - 2%d", printf("")));
}//printf的返回值为括号内字符的长度，从里到外书写
```
最后输出`Xiyou Linux Group - 2022`
## 2. 你好你好你好呀！

* 程序的输出有点奇怪，请尝试解释一下程序的输出吧。
请谈谈对`sizeof()`及`strlen()`的理解吧。

```c
int main(void) {
    char p0[] = "Hello,Linux";
    char *p1 = "Hello,Linux";
    char p2[11] = "Hello,Linux";
    printf("p0 == p1: %d, strcmp(p0, p2): %d\n", p0 == p1, strcmp(p0, p2));
    //p0 == p1: 0, strcmp(p0, p2): -72
    printf("sizeof(p0): %zu, sizeof(p1): %zu, sizeof(*p2): %zu\n",
           sizeof(p0), sizeof(p1), sizeof(*p2));
           //sizeof(p0): 12=11+1('\0'), sizeof(p1): 8, sizeof(*p2): 1
    printf("strlen(p0): %zu, strlen(p1): %zu\n", strlen(p0), strlen(p1));
    //strlen(p0): 11, strlen(p1): 11都为括号内字符串的大小
}
```
>`sizeof`的返回值是括号内的字节数，==包括字符串末尾的‘/0’==，不对括号内表达式作运算；     
> `strlen `是一个用于计算 C 语言字符串的长度的函数。==它的作用是返回一个字符串的字符数量，不包括字符串结尾的空字符 ('\0')；==    
> `strcmp`是一个用于比较两个字符串大小的函数，按ASCLL码一个字符一个字符比较，直到遇到'\0'或者两个字符不相等为止。函数原型是`int strcmp(const char* str1,const char* str2)`==若str1大于str2则返回负数；若str1等于str2则返回零；若str1大于str2则返回正数。==

`p0`是数组名，代表该数组的首地址，`*p0`是一个指向字符串的指针，由于俩地址不同，、`p0 == p1`返回0；`p0`读到`’/0‘`时，`p2`读到一个随即数值，ASCLL码做加减结果为-72。
`sizeof(p1)`代表指针所指数组首位的地址大小，`sizeof（*p2）`是数组首位`H`的大小：为1。

## 3. 换个变量名不行吗？

* 请结合本题，分别谈谈你对C语言中「全局变量」和「局部变量」的「生命周期」理解。

```c
int a = 3;//全局变量
void test() {
    int a = 1;//在test函数中的局部变量
    a += 1;
    {
        int a = a + 1;
        printf("a = %d\n", a);//在此语句块内的局部变量
    }
    printf("a = %d\n", a);//输出的是test函数中的局部变量，在该函数执行结束之后栈上的内存会被自动释放
}
int main(void) {
    test();
    printf("a= %d\n", a);//输出的是全局变量，内存在整个程序运行完之后释放
}
```
```c
a = 1 ;a = 2 ;a= 3
```
>* 全局变量：
> ==在程序开始执行之前，全局变量就已经被创建==。通常在程序的顶部定义，在任何函数之外。它的存在范围涵盖整个程序，在程序启动时分配内存，在程序结束时释放占用的内存。因此，全局变量在整个程序执行期间都存在。
> * 局部变量：
>  局部变量在它们所属的代码块（函数、语句块等）被执行时创建。它们存在于函数的栈区中，也仅存在于定义它的区域内，运行完该区域后栈区的内存会被自动释放，局部变量消失。因此它的==生命周期仅存在于定义它的代码块==。

## 4. 内存对不齐

* `union`与`struct`各有什么特点呢，你了解他们的内存分配模式吗。

```c
//x86_64 GNU/Linux 环境下是8字节对齐
typedef union {
    long l;//4
    int i[5];//4*5=20
    char c;//1
} UNION;//20——>24
typedef struct {
    int like;//4——>8
    UNION coin;//24
    double collect;//8
} STRUCT;//8+24+8=40
int main(void) {
    printf("sizeof (UNION) = %zu\n", sizeof(UNION)); //sizeof (UNION) = 24
    printf("sizeof (STRUCT) = %zu\n", sizeof(STRUCT));//sizeof (STRUCT) = 40
}
```
>
>* `struct`结构体内的各个成员独立分配空间，并且是按照成员顺序分配，按照内存对齐的方式储存内容，用以提高访问速度。
>* `union`联合允许多个成员共享同一块内存空间，所有成员共享相同的起始地址，修改一个成员会影响其他成员的值。联合的大小等于它最大成员的大小。
>* `typedef` 关键字可以为已有数据类型创建新的别名，它的主要作用是增加代码的可读性和可维护性。

[这里是关于结构体字节对齐的详解](https://blog.csdn.net/x2528238270/article/details/120798606#:~:text=%E5%8F%91%E5%B8%83-,%E7%BB%93%E6%9E%84%E4%BD%93%E5%AD%97%E8%8A%82%E5%AF%B9%E9%BD%90%E8%AF%A6%E8%A7%A3%E3%80%90%E5%90%AB%E5%AE%9E%E4%BE%8B%E3%80%91,-%E8%AF%B7%E5%8F%AB%E6%88%91)

## 5. Bitwise

* 请使用纸笔推导出程序的输出结果。
请谈谈你对位运算的理解。

```c
int main(void) {
    unsigned char a = 4 | 7;//0000 0010 | 0000 0111->0000 0111(7)
    a <<= 3;//0000 0111<<3->0011 1000(56)
    unsigned char b = 5 & 7;//0000 0101 & 0000 0111->0000 0101(5)
    b >>= 3;//0000 0101>>3->0
    unsigned char c = 6 ^ 7;//0000 0110 ^ 0000 0111->0000 0001(1)
    c = ~c;//1111 1110(254)
    unsigned short d = (a ^ c) << 3;
    //0011 1000 ^ 1111 1110->1100 0110
    //d= 1100 0110<<3->0000 0110 0011 0000(1584)
    signed char e = -63;//1100 0001
    e <<= 2;//0000 0100(4)
    printf("a: %d, b: %d, c: %d, d: %d\n", a, b, c, (char)d);//char类型只保留后八位0011 0000（48）
    printf("e: %#x\n", e);//0x4
    //使用 %x 打印十六进制数
    //使用 %#x 打印带有 "0x" 前缀的十六进制数
}
```
>[位运算全面总结](https://blog.csdn.net/hzf0701/article/details/117359478#:~:text=%E5%8F%91%E5%B8%83-,%E4%BD%8D%E8%BF%90%E7%AE%97%E5%85%A8%E9%9D%A2%E6%80%BB%E7%BB%93%EF%BC%8C%E5%85%B3%E4%BA%8E%E4%BD%8D%E8%BF%90%E7%AE%97%E7%9C%8B%E8%BF%99%E7%AF%87%E5%B0%B1%E5%A4%9F%E4%BA%86,-unique_pursuit)

* 请说说下面数据类型的含义，谈谈`const`的作用。

>1. `char *const p`。指向字符的常量指针。它指向的内存地址不能被改变，但它指向的字符可以被改变可以通过 *p 来修改字符，但不能改变 p 指向的内存地址。
>2. `char const *p`。指向常量字符的指针。p 指向的字符是常量，不允许通过 *p 来修改字符的值，可以改变 p 指向的不同字符，不能修改字符。
>3. `const char *p`。与第二个相同，`const`都在`*`的前面。


## 7. 汉译英

* 请用变量`p`给出下面的定义:

>1. 含有10个指向`int`的指针的数组。`int * p[10]`
>2. 指向含有10个`int`数组的指针。`int (*p)[10]`
>3. 含有3个「指向函数的指针」的数组，被指向的函数有1个`int`参数并返回`int`。`int(*p[3])(int) `

## 8. 混乱中建立秩序

* 你对排序算法了解多少呢?  
请谈谈你所了解的排序算法的思想、稳定性、时间复杂度、空间复杂度。

**冒泡排序：**
```c
void BubbleSort(int arr[],int len)
{
    for(int i=0; i<len-1; i++)
    {
        for(int j=0; j<len-i-1; j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
```
**插入排序：**
```c
void InsertionSort(int arr[], int len)
{
    int j,key;
    for (int i=1; i<len; i++)
    {
        key = arr[i];
        j=i-1;
        while((j>=0) && (arr[j]>key))
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

```
>[经典的十种排序算法](https://blog.csdn.net/a695415974/article/details/123581071?app_version=6.1.9&csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22123581071%22%2C%22source%22%3A%222301_80123601%22%7D&utm_source=app#:~:text=%E5%8F%91%E5%B8%83-,%E7%BB%8F%E5%85%B8%E7%9A%84%E5%8D%81%E7%A7%8D%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95,-C%E8%AF%AD%E8%A8%80%E7%89%88)
## 9. 手脑并用

* 请实现ConvertAndMerge函数：  
拼接输入的两个字符串，并翻转拼接后得到的新字符串中所有字母的大小写。
提示:你需要为新字符串分配空间。

```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* convertAndMerge(char words[2][20]){
    int len=strlen(words[0])+strlen(words[1]);
    char *new=(char*)malloc(len+1);
    strcpy(new,words[0]);
    strcat(new,words[1]);
    for(int i=0;i<len;i++){
        if(new[i]>='A' && new[i]<='Z'){
            new[i]+=32;
        }
        else if(new[i]>='a' && new[i]<='z'){
            new[i]-=32;
        }
    }
    return new;
}
int main(void) {
    char words[2][20] = {"Welcome to Xiyou ", "Linux Group 2022"};
    printf("%s\n", words[0]);
    printf("%s\n", words[1]);
    char *str = convertAndMerge(words);
    printf("str = %s\n", str);
    free(str);
	return 0;
}
```

## 10. 给你我的指针，访问我的心声

* 程序的输出有点奇怪，请尝试解释一下程序的输出吧。

```c
int main(int argc, char **argv) {
    int arr[5][5];
    int a = 0;
    for (int i = 0; i < 5; i++) {
        int *temp = *(arr + i);//temp指向数组arr每行的第一个元素
        for (; temp < arr[5]; temp++) *temp = a++;
    }//arr[5]是arr这个二维数组后一位的数的地址,所以这个循环会将整个arr数组赋值
    //但由于每轮循环结束之后，temp都重新指向下一行的一个元素，导致上一轮循环的数值被覆盖
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d\t", arr[i][j]);
        }
    }
}
```
来张图解释
![上图解释](https://img-blog.csdnimg.cn/9cd4ff22082a46db9dc513c2d619a9e0.png)
输出结果：
```c
0       1       2       3       4
25      26      27      28      29
45      46      47      48      49
60      61      62      63      64
70      71      72      73      74
```

## 11. 奇怪的参数

* 你了解argc和argv吗？  
直接运行程序argc的值为什么是1？  
程序会出现死循环吗？

```c
#include <stdio.h>
int main(int argc, char **argv) {
    printf("argc = %d\n", argc);
    while (1) {
        argc++;//自增最后溢出变为0，不执行以下语句
        if (argc < 0) {
            printf("%s\n", (char *)argv[0]);
            break;
    }
}
```
```c
argc = 1
```
>* `argc(argument count)`是一个整数，统计程序运行时传给命令行参数的数量，它包括程序名称本身在内的所有参数的总数，至少为1（因为程序名称本身就是一个参数）
>* `argv`是一个指向字符串数组的指针，表示命令行参数的字符串

## 12. 奇怪的字符

* 程序的输出有点奇怪，请尝试解释一下程序的输出吧。

```c
int main(int argc, char **argv) {
    int data1[2][3] = {{0x636c6557, 0x20656d6f, 0x58206f74},
                       {0x756f7969, 0x6e694c20, 0x00000000}};     
    int data2[] = {0x47207875, 0x70756f72, 0x32303220, 0x00000a32};
    char *a = (char *)data1;
    char *b = (char *)data2;//将十六进制转换为字符
    char buf[1024];
    strcpy(buf, a);//将 data1 中的字符拷贝到 buf 中
    strcat(buf, b);//将 data2 中的字符连接到 data1的末尾
    printf("%s \n", buf);//Welcome to Xiyou Linux Group 2022
}
```

## 13. 小试宏刀

- 请谈谈你对`#define`的理解。
请尝试着解释程序的输出。

```c
#define SWAP(a, b, t) t = a; a = b; b = t
#define SQUARE(a) a *a
#define SWAPWHEN(a, b, t, cond) if (cond) SWAP(a, b, t)//如果cond！=0,调换三个数的值
int main() {
    int tmp;
    int x = 1;
    int y = 2;
    int z = 3;
    int w = 3;
    SWAP(x, y, tmp);//tmp=x,x=y,y=tmp
    printf("x = %d, y = %d, tmp = %d\n", x, y, tmp);//x = 2, y = 1, tmp = 1
    if (x>y) SWAP(x, y, tmp);
    //if(x>y) tmp=x;x=y;y=tmp 后两个语句不在大括号内，无论怎样都会运行
    printf("x = %d, y = %d, tmp = %d\n", x, y, tmp);//x = 1, y = 2, tmp = 2
    SWAPWHEN(x, y, tmp, SQUARE(1 + 2 + z++ + ++w) == 100);//1+2+3+4*1+2+4+5！=100，不执行tmp=x语句,执行后两句x=y;y=tmp
    printf("x = %d, y = %d\n", x, y, tmp);//x = 2, y = 2
    printf("z = %d, w = %d, tmp = %d\n", z, w, tmp);//z = 5, w = 5, tmp = 2
}
```
>`define`宏定义，在头文件之前声明，可以提高代码的简洁性，但是不会自动加括号（无论大括号小括号），要遵循运算的先后顺序，可能导致对代码的误解，以上就是一个典型例子。

## 14. GNU/Linux命令 (选做)

* 你知道以下命令的含义和用法吗：
- `ls`
- `rm`
- `whoami`
>1.`ls`是用于列出当前目录中的文件和子目录的命令,用于查看目录内容。
>2.`rm` 是用于删除文件或目录的命令，永久删除且无法恢复。简单地执行 rm 文件名可以删除文件。如果要删除目录及其内容，可以使用 -r 选项，如 rm -r 目录名。
>3.`whoami` 是用于显示当前登录用户的用户名的命令。

**结束啦！！！**
