> ① 本题解只作为西邮` Linux `兴趣小组 2023 纳新面试题目的有限参考。
② 为节省版面，本试题的程序源码省去了`#include `指令。
③ 本试题中的程序源码仅用于考察 C 语言基础，不应当作为 C 语言「代码风格」的范例。
④ 所有题目编译并运行于 `x86_64 GNU/Linux` 环境。
***
## 1. 大小和长度竟然不是一个意思

* `sizeof()`和`strlen()`有什么异同之处？
他们对于不同参数的结果有什么不同？请试举例子说明。

```c
int main(void) {
    char s[] = "I love Linux\0\0\0";//15+1（'\0'）
    int a = sizeof(s);
    int b = strlen(s);
    printf("%d %d\n", a, b);//a = 16;b = 12
}
```
>`sizeof`的返回值是括号内的字节数，==包括字符串的末尾的'\0'==，表示指定类型或变量占用的存储空间大小，不对括号内表达式作运算，可以返回数据类型的字节数，也可以计算数组大小，返回数组所占的总字节数。
`strlen `是一个用于计算 C 语言字符串的长度的函数。==它的作用是返回一个字符串的字符数量，不包括字符串结尾的空字符 ('\0')。== 

## 2. 箱子的大小和装入物品的顺序有关

* `test1`和`test2`都含有：1个`short`、1个`int`、1个`double`，那么`sizeof(t1)`和`sizeof(t2)`是否相等呢？这是为什么呢？

```c
struct test1 {
    int a;//4
    short b;//2->4
    double c;//8
};//4+4+8=16
struct test2 {
    short b;//2->4
    int a;//4
    double c;//8
};//4+4+8=16
//注意内存对齐！！!
int main(void) {
    struct test1 t1;
    struct test2 t2;
    printf("sizeof(t1): %d\n", sizeof(t1));
    printf("sizeof(t2): %d\n", sizeof(t2));
}
```


## 3. 哦，又是函数

* 想必在高数老师的教导下大家十分熟悉函数这个概念。那么你了解计算机程序设计中的函数吗？请编写一个`func`函数，用来输出二维数组`arr`中每个元素的值。

```c
void func(int arr[10][13]){
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 13; j++) {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}
int main(void) {
    int arr[10][13];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 13; j++) {
            arr[i][j] = rand();
        }
    }
    func(arr);
}
```

## 4.就不能换个变量名吗？

- 请结合下面的程序，简要谈谈`传值`和`传址`的区别。
简要谈谈你对C语言中变量的生命周期的认识。

```c
int ver = 123;//全局变量，生命周期贯穿整个程序，作用域是整个函数
void func1(int ver) {
    ver++;
    printf("ver = %d\n", ver);//ver = 1026
}//传值进入函数，离开函数后ver的值不发生改变
void func2(int *pr) {
    *pr = 1234;//通过指针修改该地址存放的变量
    printf("*pr = %d\n", *pr);//*pr = 1234
    pr = 5678;//直接将数值赋给地址会出现警告
    printf("ver = %d\n", ver);//ver = 123，func2函数中没有int型变量，所以调用全局变量
}//传入参数ver的地址给函数，通过指针可以访问该地址所存的值，也可以改变该地址所存放的值 
int main() {
    int a = 0;
    int ver = 1025;
    for (int a = 3; a < 4; a++) {
        static int a = 5;//静态局部变量，运行期间内存不释放，但作用域仅限于main函数中
        printf("a = %d\n", a);//a=5
        a = ver;
        func1(ver);
        int ver = 7;
        printf("ver = %d\n", ver);//ver=7
        func2(&ver);
    }
    printf("a = %d\tver = %d\n", a, ver);//a = 0;ver = 1025，在main函数中有定义它俩的值
}
```
输出结果为：
```c
a = 5
ver = 1026
ver = 7
*pr = 1234
ver = 123
a = 0   ver = 1025
```

## 5. 套娃真好玩！

* 请说明下面的程序是如何完成求和的？

```c
unsigned sum(unsigned n) { return n ? sum(n - 1) + n : 0; }
int main(void) { printf("%u\n", sum(100)); }
```
>`？`是一个条件运算符（也称三元运算符），本题中若`n`为真，则返回`sum(n-1)+n`的值；若`n`为假，则返回0。
>这是一个递归函数，通过反复调用自己来实现求和的目的，每次调用`n`的值都会减一然后加上原本的值，直到`n`的值减为0，返回0，最终结果就是求1一直加100的和（5050）。

## 6. 算不对的算术

```c
void func(void) {
    short a = -2;// 1111 1111 1111 1110，十六进制为0xfffe
    unsigned int b = 1;
    b += a;//b = -1，1111 1111 1111 1111 1111 1111 1111 1111,十六进制为0xffffffff
    int c = -1;
    unsigned short d = c * 256;//-256
    c <<= 4;//1111 1111 1111 1111 1111 1111 1111 0000
    int e = 2;//0000 0000 0000 0000 0000 0000 0000 0010
    e = ~e | 6;
    //1111 1111 1111 1111 1111 1111 1111 1101|0110->1111 1111 1111 1111 1111 1111 1111 1111,十六进制为0xffffffff
    d = (d & 0xff) + 0x2022;//首先-256被解释为一个正数是2^16-256=65280,0xff->1111 1111 ,做`&`运算后结果为零，最终输出0x2022
    printf("a=0x%hx\tb=0x%x\td=0x%hx\te=0x%x\n", a, b, d, e);//转换为十六进制输出,%hx表示输出short类型
    printf("c=Ox%hhx\t\n", (signed char)c);//%hhx表示输出short short 类型，c=1111 0000,十六进制0xf0
}
```
输出结果为：
```c
a=0xfffe        b=0xffffffff    d=0x2022        e=0xffffffff
c=Oxf0
```
>`unsigned int`表示无符号整数。无符号整数是一种整数类型，它只能表示非负整数值（包括0），没有符号位用来表示正负。故只能用来定义正数，若定义负数编译器会出现警告或错误。
>同理`signed char`表示有符号字符，可以表示正负数和零。
>[不同位宽整数扩展问题](https://blog.csdn.net/qq_17256689/article/details/129938851?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169917155816800188559818%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169917155816800188559818&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-129938851-null-null.142^v96^pc_search_result_base9&utm_term=0x%25hx&spm=1018.2226.3001.4187#:~:text=%E5%8F%91%E5%B8%83-,C%E5%AD%A6%E4%B9%A0%EF%BC%9A%E4%B8%8D%E5%90%8C%E4%BD%8D%E5%AE%BD%E6%95%B4%E6%95%B0%E6%89%A9%E5%B1%95%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90,-%E6%9D%A5%E7%9F%A5%E6%99%93)

## 7. 指针和数组的恩怨情仇

```c
int main(void) {
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int(*b)[3] = a;//指针b指向数组a的首地址
    ++b;//b指向&a[1][0]
    b[1][1] = 10;//a[2][1]=10,将7替换成10
    int *ptr = (int *)(&a + 1);//ptr指向arr数组的后一位，减一就指向arr数组的最后一位9
    printf("%d %d %d \n", a[2][1], **(a + 1), *(ptr - 1));//10 4 9 
}//**（a+1）等价于a[1][0]也就是4
```

## 8. 移形换位之术

* 下面有`a`、`b`、`c`三个变量和4个相似的函数。
你能说出使用这三个变量的值或地址作为参数分别调用这5个函数，在语法上是否正确吗？
 请找出下面的代码中的错误。
  `const int`和`int const`是否有区别？如果有区别，请谈谈他们的区别。
  `const int *`和`int const *`是否有区别？如果有区别，请谈谈他们的区别。

```c
int a = 1;
int const b = 2;
const int c = 3;//const int 和 int const没有区别，都表示int型的变量不能被修改
void funco(int n) {
    n += 1;
    n = a;
}
void func1(int *n) {
    *n += 1;
    n = &a;
}
void func2(const int *n) {
    *n += 1;//const int *n说明不能对*n进行赋值，此处错误
    n = &a;
}
void func3(int *const n) {
    *n += 1;
    n = &a;//int *const n说明指针指向的地址是固定的，不能被改变，此处错误
}
void func4(const int *const n) {//指针指向的地址和对*n赋的值都不能改变，以下两行都是错的
    *n += 1;
    n = &a;
}
```
>[有关const的运用和解释看这里～](https://blog.csdn.net/zhangheng837964767/article/details/33783511?app_version=6.1.9&csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%2233783511%22%2C%22source%22%3A%222301_80123601%22%7D&utm_source=app#:~:text=%E5%8F%91%E5%B8%83-,const%20int%20*a%E4%B8%8Eint%20*const%20a%EF%BC%8Cconst%20int%20*const%20a%E7%9A%84%E5%8C%BA%E5%88%AB,-wm_21000301)

## 9. 听说翻转字母大小写不影响英文的阅读？

* 请编写`convert`函数用来将作为参数的字符串中的大写字母转换为小写字母，将小写字母转换为大写字母。返回转换完成得到的新字符串。

```c
char *convert(const char *s)
{
    int len=strlen(s);
    char *Str=(char*)malloc(sizeof(int)*(len+1));

    for(int i=0;i<len;i++){
        if(s[i]>='A' && s[i]<='Z'){
                Str[i] = s[i]+32;
        }
        else if(s[i]>='a' && s[i]<='z'){
            Str[i] = s[i]-32;
        }
        else Str[i]=s[i];
    }
    return Str;
    free (Str);
}
int main(void) {
    char *str = "XiyouLinux Group 2022";
    char *temp = convert(str);
    puts(temp);
}
```

## 10. 交换礼物的方式

- 请判断下面的三种`Swap`的正误，分别分析他们的优缺点。
你知道这里的`do {...} while(0)`的作用吗？
你还有其他的方式实现`Swap`功能吗？//用指针，传入地址给函数

```c
//do{……}while(0)的作用是在宏定义中*实现局部作用域*
#define Swap1(a, b, t)   \
    do {                 \
        t = a;           \
        a = b;           \
        b = t;           \ 
    } while (0)//直接传入参数，方便快捷
#define Swap2(a, b)      \
    do {                 \
        int t = a;       \
        a = b;           \
        b = t;           \
    } while (0)//在函数内定义变量t，节省空间
void Swap3(int a, int b) {
    int t = a;
    a = b;
    b = t;
}//只是传值给函数，函数运行结束之后数据被销毁，没有达到交换数值的目的
```

## 11. 据说有个东西叫参数

* 你知道`argc`和`argv`的含义吗？请解释下面的程序。你能在不使用`argc`的前提下，完成对`argv`的遍历吗？

```c
int main(int argc, char *argv[]) {
    printf("argc = %d\n", argc);//argc=1
    for (int i = 0; i < argc; i++)
        printf("%s\n", argv[i]);
}
/*
int i=0;
while(argv[i]!=NULL){
	printf("%s\n", argv[i])；
	i++;
}
*/
```
>* `argc(argument count)`是一个整数，统计程序运行时传给命令行参数的数量，它包括程序名称本身在内的所有参数的总数，至少为1（因为程序名称本身就是一个参数）
>* `argv`是一个指向字符串数组的指针，表示命令行参数的字符串


## 12. 人去楼空

* 这段代码有是否存在错误？谈一谈静态变量与其他变量的异同。

```c
int *func1(void) {
    static int n = 0;//n是静态变量，内存不被释放，生命周期延长到程序运行结束
    n = 1;
    return &n;//返回n的地址
}
int *func2(void) {
    int *p = (int *)malloc(sizeof(int));//为int分配空间
    *p = 3;
    return p;//返回首地址
}
int *func3(void) {
    int n = 4;
    return &n;//这里错误，函数运行结束n会被释放，这里返回的是一个随即地址，并不是原先存放n的地址
}
int main(void) {
    *func1() = 4;
    *func2() = 5;
    *func3() = 6;
}
```
>局部变量用 `static `修饰后使它成为一个静态局部变量，改变了它的储存位置，==即从栈区进到全局区（静态区）==。静态局部变量与普通局部变量的不同之处在于，它们在程序的整个生命周期内都存在，并且只会初始化一次，从而延长了局部变量的生命周期。==值得注意的是，static修饰局部变量时只改变生命周期，不改变作用域==。static修饰全局变量时会使其作用域变小，只能在自己的源文件中使用，即使被`extern`关键字声明也不可以在其他源文件中使用，生命周期与程序运行时间相同。

## 13. 奇怪的输出

```c
int main(void) {
    int data[] = {0x636c6557, 0x20656d6f, 0x78206f74,
                  0x756f7969, 0x6e694c20, 0x67207875,
                  0x70756f72, 0x32303220, 0x00000a31};
    puts((const char*)data);//Welcome to xiyou Linux group 2021
}
```

## 14. 请谈谈对从「C语言文件到可执行文件」的过程的理解

>* 预处理：在编译之前，C预处理器将执行一些文本替换和宏展开等操作。这通常包括将头文件包含到源代码中，替换宏定义，以及条件编译等。（.c--->.i）
>* 编译：编译器将经过预处理的源文件转换为汇编代码。汇编代码是与计算机体系结构相关的低级代码，它描述了程序的操作和控制流。(.i--->.s)
>* 汇编：汇编器将汇编代码转换为机器代码或可重定位目标文件。这个目标文件包含了程序的二进制表示，但它还没有被链接到最终的可执行文件。(.s--->.o)
>* 链接：链接器将各种目标文件合并在一起，以创建一个完整的可执行文件。在这个过程中，符号引用被解析，生成可执行文件的符号表。最终，生成一个可执行文件，其中包含了完整的程序代码和数据。这个最终的可执行文件通常没有特定的扩展名，例如a.out或者你可以指定一个名称。
>* 可执行文件：最终输出的是一个可执行文件，它可以在计算机上运行。这个文件包括程序的二进制表示和必要的元数据，以便操作系统能够加载和执行它。
>* 运行程序



## 15. (选做) 堆和栈

* 你了解程序中的栈和堆吗？它们在使用上有什么区别呢？请简要说明。
>* 栈通常用于存储函数调用的局部变量、函数参数、返回地址等，遵循“先进后出”，出栈即被销毁。每次函数调用时，一个新的栈帧被压入栈，包含了函数的局部数据，同时栈的大小有限，适合用于临时储存小型数据。
>* 堆是通过动态分配和释放内存的，一般用于存储动态分配的数据，大小没有固定限制，可以自行定义。堆的生存期不受限制，分配的内存在被释放之前会一直存在，所以它可以用于存储持久数据，但也要注意及时释放堆中的内存，长期堆积内存会造成不良影响。
>* [堆与栈的区别](https://blog.csdn.net/abcd1476/article/details/123758621?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169911580216800211526929%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169911580216800211526929&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-123758621-null-null.142^v96^pc_search_result_base9&utm_term=%E5%A0%86%E5%92%8C%E6%A0%88%E7%9A%84%E5%8C%BA%E5%88%AB%E5%92%8C%E8%81%94%E7%B3%BB&spm=1018.2226.3001.4187#:~:text=%E5%8F%91%E5%B8%83-,%E5%A0%86%E3%80%81%E6%A0%88%E3%80%81%E9%98%9F%E5%88%97%E7%9A%84%E5%8C%BA%E5%88%AB%E5%92%8C%E8%81%94%E7%B3%BB,-He%20ZIJI)


## 16. (选做) 多文件

* 一个程序在不使用任何头文件的情况下，如何使用另一个文件中的函数。
>用关键字`extern`声明函数。
>`extern` 是一个用于声明变量或函数的关键字，它告诉编译器该变量或函数的定义存在于另一个源文件中或在当前源文件的后面部分。它用于在不同的源文件之间共享变量或函数的声明，以确保编译器知道它们的存在。`extern `关键字通常与头文件一起使用，以提供外部链接的声明。

## 17. (选做) `GNU/Linux`与文件

- 你知道如何在 `GNU/Linux`下如何使用命令行创建文件与文件夹吗？
- 你知道`GNU/Linux`下的命令ls 的每一列的含义吗？
- 你知道`GNU/Linux`下文件的访问时间、修改时间、创建时间如何查看吗？并简单说说他们的区别。

>[Linux创建文件的方法](https://blog.csdn.net/weixin_43233219/article/details/131659780?ops_request_misc=&request_id=&biz_id=102&utm_term=%E3%80%8CC%E4%BD%A0%E7%9F%A5%E9%81%93%E5%A6%82%E4%BD%95%E5%9C%A8%20%60GNU/Linux%60%E4%B8%8B%E5%A6%82%E4%BD%95%E4%BD%BF%E7%94%A8%E5%91%BD%E4%BB%A4%E8%A1%8C%E5%88%9B%E5%BB%BA&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-131659780.142^v96^pc_search_result_base9&spm=1018.2226.3001.4187#:~:text=%E5%8F%91%E5%B8%83-,Linux%20%E5%88%9B%E5%BB%BA%E6%96%87%E4%BB%B6%E7%9A%8412%E7%A7%8D%E6%96%B9%E6%B3%95%E6%80%BB%E7%BB%93,-Lotay_%E5%A4%A9%E5%A4%A9)
>[Linux命令-ls详解](https://blog.csdn.net/weixin_47307417/article/details/126331427?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169911683516800192213554%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169911683516800192213554&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-126331427-null-null.142^v96^pc_search_result_base9&utm_term=linux%20ls%E5%91%BD%E4%BB%A4%E8%AF%A6%E8%A7%A3&spm=1018.2226.3001.4187#:~:text=%E5%8F%91%E5%B8%83-,Linux%E5%91%BD%E4%BB%A4%2Dls%E8%AF%A6%E8%A7%A3,-%E9%94%A4%E5%93%A5123)
>使用 `stat `命令查看文件的访问、修改和更改时间，`stat+文件名`即可查看