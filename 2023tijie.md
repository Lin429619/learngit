@[TOC]
> ① 本题解只作为西邮` Linux `兴趣小组 2023 纳新面试题目的有限参考。
② 为节省版面，本试题的程序源码省去了`#include `指令。
③ 本试题中的程序源码仅用于考察 C 语言基础，不应当作为 C 语言「代码风格」的范例。
④ 所有题目编译并运行于 `x86_64 GNU/Linux` 环境。
***

## 0.鼠鼠我啊，要被祸害啦
将1000瓶水分别编号并转化为二进制，2的十次方是1024,所以十只老鼠就够用，每只鼠对应二进制中的一位(从右往左开始编号1～10)，喂水方式：0000000001为编号1的水，为给1号老鼠；0000000011为编号3的水，喂给1号和2号老鼠，如果只有1号老鼠死亡，则编号1的水有毒；若1号和2号老鼠都死亡，则编号3的水有毒。即将死亡老鼠对应编号从二进制转换为十进制，就可以找出有毒的水。

## 1.先预测一下～

```c
/*按照函数要求输入自己的姓名试试~*/
char *welcome(){
     return "XXX";
}
int main(void){
    char *a = welcome();
    printf("Hi,我相信 %s 可以面试成功\n",a);
    return 0;
}
```
```c
#include <stdio.h>

char *welcome() {
    static char name[] = "XXX"; 
    return name;
}

int main(void) {
    char *a = welcome();
    printf("Hi, 我相信 %s 可以面试成功!\n", a);
    return 0;
}
```
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *welcome() {
    char *name = (char *)malloc(sizeof(char) * (strlen("XXX") + 1));//分配内存
    strcpy(name, "XXX"); //复制name
    return name;
}

int main(void) {
    char *a = welcome();
    printf("Hi, 我相信 %s 可以面试成功!\n", a);
    free(a);
    return 0;
}
```
## 2.欢迎来到Linux兴趣小组

```c
int main(void)
{
    char *ptr0 = "Welcome to Xiyou Linux!";
    char ptr1[] = "Welcome yo Xiyou Linux!";
    if (*ptr0 == *ptr1)//运行中括号内容的条件是（*ptr0 == *ptr1）！=0,条件成立 原因：都指向字符串的第一个字符W，为1
    {
        printf("%d\n",printf("Hello, Linux Group - 2%d",printf("")));
    }
    int diff = ptr0 - ptr1;
    printf("Pointer Different: %d\n",diff);
    return 0;
}
```
输出结果是：`Hello, Linux Group - 2023 `。printf函数从最里层开始作运算，它的返回值为字符的长度，最里层内无内容，返回0，次里层内字符的长度为23,返回23，最后输出以上内容。
`diff`每次的结果都会不一样。原因：`ptr0`是指针，指向第一个字符的地址，`ptr1`是数组名，代表数组首项字符的地址，内存地址一般为`0x`开头的十六进制，输出时转化为十进制，由于函数是暂时写入栈内，每次分配内存的位置不一样，所以每次输出的结果都不一样。

## 3.一切都翻倍了吗

```c
int main(void)
{
    char arr[] = {'L','i','n','u','x','\0','!'},str[20];
    short num = 520;
    int num2 = 1314;
    printf("%zu\t%zu\t%zu\n",sizeof(*&arr),sizeof(arr+0),sizeof(num = num2 + 4));
    printf("%d\n",sprintf(str,"%0x%x", num) == num);
    printf("%zu\t%zu\n", strlen(&str[0] + 1),strlen(arr + 0));
}
```
 1、输出结果`7 8 2 0 4 5`；

> 解释前我们需要先了解下这些东西：
`sizeof`的返回值是括号内的字节数，==包括字符串末尾的'\0'==，表示指定类型或变量占用的存储空间大小，不对括号内表达式作运算。
`strlen `是一个用于计算 C 语言字符串的长度的函数。==它的作用是返回一个字符串的字符数量，不包括字符串结尾的空字符 ('\0')。==     
 `sprintf `用于将格式化的数据写入一个字符串，它的作用类似于 `printf`，但不是将结果打印出来，而是将格式化的文本写入一个字符数组或字符串。它的参数可以是各种类型，`sprintf `函数的返回值是一个整数，它表示写入到目标字符串中的字符的总数，不包括结尾的  ('\0')。==如果 `sprintf` 函数执行成功，它将返回写入的字符数，如果失败（就是写入的字符超过容量发生溢出），它将返回一个负数==。一般情况下，目标字符足够大，就可以成功返回一个整数。

2、原因分析：有了以上知识储备，问题就很好解决了。第一个输出的是`char`类型（一个字节）`arr`内的字节数，有七个`char`类型的字符，所以是7；第二个输出，0对指针没有影响，在64位环境下指针的固定大小是8（32位是4位）；所以是8；第三个输出2因为`num`是`short`类型，占两个字节；第四个输出==左边是将`num`（520） 转化为16进制写入`str`数组变成`0x208`，返回值为5不等于520，输出0；第五个输出的指针指向第二个字符，从第二位开始数，结果为4；第六个输出0依然对arr没有影响，`strlen`函数读到'\0'为止，所以是5。

## 4、奇怪的输出

> 操作符知识储备（二进制位运算符）
> `&`：对两个整数的二进制表示进行按位与操作，如果两个数的相应位都为 1，结果位也为 1；否则结果位为 0（同1异0）
> `^`：对两个整数的二进制表示进行按位异或操作，如果两个数的相应位不同，结果位为 1；如果相同，结果位为 0（同0异1）
>  `>>`：将一个整数的二进制表示向右移动指定的操作符，逻辑右移-->右边丢弃，左边补0 ； 算术右移-->右边丢弃，左边补原符号位
>  `<<`:与逻辑右移类似，将二进制向左移动，右边补0
>  ==注意：计算机中存储的是补码，所以是对补码进行以上操作==

```c
int main(void) {
    char a = 64 & 127;//结果是64
    char b = 64 ^ 127;//结果是63
    char c = -64 >> 6;//-1
    char ch = a + b - c;
    printf("a = %d b = %d c = %d\n", a, b, c);
    printf("ch = %d\n", ch);//64+63-(-1)=64.char能表示的整数范围是-128～127,128超出范围导致溢出，所以输出结果为-1【127—>011111111+1->10000000就是-1】
}
```
## 5、乍一看就不想看的函数

```c
/*这个 func()函数的功能是什么？是如何实现的？//实现两数相加（用二进制补码作运算才能看出其中的奥妙哦！）*/
int func(int a, int b) {
    if (!a) return b;//执行这句语句的条件翻译过来就是（a！=0），然后返回b的值
return func((a & b) << 1, a ^ b);//a^b实际就是做了不进位的加法，而(a & b) << 1负责达成进位目的，从而达到一个相加的效果，多进行几次运算就可以看出大致规律了
}//这是一个递归函数！
int main(void){
	int a = 4, b = 9, c = -7;
    printf("%d\n", func(a, func(b, c)));//结果就算a+b+c=6
}
```
## 6、自定义过滤

```c
/*请实现 filter()函数：过滤满足条件的数组元素。
提示：使用函数指针作为函数参数并且你需要为新数组分配空间。*/
typedef int (*Predicate)(int);
int *filter(int *array, int length, Predicate predicate,int *resultLength)
{
    int *result=(int*)malloc(length);  
    int cnt=0;
    for(int i=0;i<length;i++){
       if(predicate(array[i])){
        result[cnt]=array[i];
        cnt++;
       }
    }
    *resultLength=cnt;
    return result;
}
int isPositive(int num) { return num > 0; }
int main(void) {
    int array[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    int length = sizeof(array) / sizeof(array[0]);
    int resultLength;
    int *filteredNumbers = filter(array, length, isPositive,&resultLength);
    for (int i = 0; i < resultLength; i++) {
      printf("%d ", filteredNumbers[i]);
     }
    printf("\n");
    free(filteredNumbers);
    return 0;
}
```
## 7、静态
① 如何理解关键字 `static`？
中文意思是“静态的”，在c语言中主要是用来修饰变量和函数的。
② `static` 与变量结合后有什么作用？
局部变量用 `static `修饰后使它成为一个静态局部变量，改变了它的储存位置，==即从栈区进到全局区（静态区）==。静态局部变量与普通局部变量的不同之处在于，它们在程序的整个生命周期内都存在，并且只会初始化一次，从而延长了局部变量的生命周期。==值得注意的是，static修饰局部变量时只改变生命周期，不改变作用域==。static修饰全局变量时会使其作用域变小，只能在自己的源文件中使用，即使被`extern`关键字声明也不可以在其他源文件中使用，生命周期与程序运行时间相同。
③ `static `与函数结合后有什么作用？
函数被`static`修饰之后变成静态函数，与静态全局变量类似，只能在自己的源文件中使用，其他源文件无法访问它，==静态函数主要用于限制函数的可见性，以防止其他源文件意外使用或重写该函数==
④ static 与指针结合后有什么作用？
与指针结合后，它指示该指针变量在程序的整个生命周期内保持其地址不变。静态指针在函数内部声明时，不会在函数调用结束后销毁，而是保持其地址不变。
⑤` static` 如何影响内存分配？
被`static`修饰的对象，在编译时计算机会给它分配一块静态区内存，直到程序运行结束空间才会被释放。

## 8、救命！指针！
```c
/*数组指针是什么？指针数组是什么？函数指针呢？用自己的话说出来更好哦，下面数据类
型的含义都是什么呢？*/
   int (*p)[10];//数组指针，本质为指针，指针所指对象是一个int[10]型的数组
   const int* p[10];//指针数组，本质为数组，数组内存放的元素为int*型的指针
   int (*f1(int))(int*, int);
   //f1(int)表示f1是一个函数，它的参数是整数类型
   //int (*f1(int))(int*, int)表示f1函数返回一个指向函数的指针，
   //该函数的参数一个是整数指针，一个是整数，并返回有一个整数。可以把*f1(int)看成一个函数名
   //总的来说。f1接受一个整型参数并返回一个函数指针，该函数指针指向一个函数，它的参数一个是整数指针，一个是整数
```
>优先级：() >[ ] > * 

## 9、咋不循环了

```c
int main(int argc, char* argv[]) {
	printf("[%d]\n", argc);//此时argc=1，不往命令行传递任何额外参数则为1
	while (argc) //只要argc！=0,就会一直循环，但由于int表示整数的范围有限，一旦超出范围就会溢出导致argc变成0,循环停止
	{
	++argc;
	}
	int i = -1, j = argc, k = 1;//argc=1
	i++ && j++ || k++;
	//短路逻辑运算符，&&左侧为假则不执行右侧表达式，||左侧为真则不执行右侧表达式。i++的结果为0（假），不执行j++，k++后为2
	printf("i = %d, j = %d, k = %d\n", i, j, k);//0 1 2
	return EXIT_SUCCESS;
}
```
>* `argc(argument count)`是一个整数，统计程序运行时传给命令行参数的数量，它包括程序名称本身在内的所有参数的总数，至少为1（因为程序名称本身就是一个参数）
>* `argv`是一个指向字符串数组的指针，表示命令行参数的字符串
## 10.到底是不是TWO

```c
#define CAL(a) a * a * a//宏定义，定义CAL的返回值位为a的三次方
#define MAGIC_CAL(a, b) CAL(a) + CAL(b)//宏定义，定义MAGIC_CAL的返回值为a的三次方加b的三次方
int main(void) {
    int nums = 1;
	if(16 / CAL(2) == 2) {//注意此处的运算是16/2*2*2=32！=2,2*2*2没有加括号，不能优先做运算
	printf("I'm TWO(ﾉ>ω<)ﾉ\n");
	} else {
	int nums = MAGIC_CAL(++nums, 2);//此处nums为局部变量，不会影响主函数中nums的值
	}
	printf("%d\n", nums);//输出结果为1
}
```
## 11.克隆困境
运行出错，出现悬挂指针和内存泄露的问题。原代码只为一个name分配了空间，把s2直接赋给s1之后，s1.name 和s1.name指向相同的内存地址，在释放s1.name的内存之后，s2.name就变成了悬挂指针，原代码`free(s1.name);free(s2.name);`处就造成了重复释放。
并且原代码中每次调用 `initializeStudent` 时，将分配新的内存，但不会释放旧的内存，导致内存泄漏。
```c
/*试着运行一下程序，为什么会出现这样的结果？
直接将 s2 赋值给 s1 会出现哪些问题，应该如何解决？请写出相应代码。*/
struct Student {
	char *name;
	int age;
	};
void initializeStudent(struct Student *student, const char *name,
	int age) {
	student->name = (char *)malloc(strlen(name) + 1);//为name分配空间
	strcpy(student->name, name);//将传入函数的name字符串复制到 student->name 
	student->age = age;//将传入函数的age值赋给 student->age 成员变量
	}//这个函数的作用是完成对name age的初始化
//copyStudent函数是添加的代码
void copyStudent(struct Student *next, const struct Student *before) {
    next->name = (char *)malloc(strlen(before->name) + 1);//为第二个name分配空间
    strcpy(next->name, before->name);//将原来字符串 src->name 的内容复制到目标字符串 dest->name 所指向的内存中
    next->age = before->age;//同上，复制age
}
int main(void) {
	struct Student s1, s2;
	initializeStudent(&s1, "Tom", 18);
	initializeStudent(&s2, "Jerry", 28);
	//s1 = s2;这句改成：
	copyStudent(&s1, &s2);
	printf("s1 的姓名: %s 年龄: %d\n", s1.name, s1.age);
	printf("s2 的姓名: %s 年龄: %d\n", s2.name, s2.age);
	free(s1.name);
	free(s2.name);
	return 0;
}
```
>* **悬挂指针**是指一个指针持有一个无效的内存地址，==即指针指向的内存已经被释放或者不再有效==。当我们试图通过悬挂指针访问或操作该指针所指向的内存时，会导致未定义的行为。这可能包括访问无效的数据、崩溃或产生难以预测的结果。
>* **内存泄漏**是指在程序执行过程中，==动态分配的内存没有被正确释放或释放的机会丧失的情况==。当内存泄漏发生时，分配的内存将一直被占用，无法再被其他代码使用，从而造成内存资源的浪费。
## 12.你好，我是内存
```c
/*作为一名合格的 C-Coder，一定对内存很敏感吧~来尝试理解这个程序吧！*/
struct structure {
	int foo;
	union {
	int integer;
	char string[11];
	void *pointer;
	} node;
	short bar;
	long long baz;
	int array[7];
};
int main(void) {
	int arr[] = {0x590ff23c, 0x2fbc5a4d, 0x636c6557, 0x20656d6f,
	          //一个十六进制占4位（bit），所以0x590ff23c占8个位即4个字节
	          //输出的内容是从结构体中的string开始指的，直到遇到'\0'结束
	          //故跳过结构体中的前两个十六进制，从arr中的0x636c6557开始输出 
	          //0x57->W,0x65->e,0x6c->l,0x63->c以此类推          
				 0x58206f74, 0x20545055, 0x6577202c, 0x6d6f636c,
				 0x6f742065, 0x79695820, 0x4c20756f, 0x78756e69,
				 0x6f724720, 0x5b207075, 0x33323032, 0x7825005d,//0x5d->],0x00->\0,输出到此处就结束啦！
			   	 0x636c6557, 0x64fd6d1d};//用十六进制初始化，将十六进制转换为十进制再对照ASCLL码表
	printf("%s\n", ((struct structure *)arr)->node.string);//使用类型转换将 arr[]的地址解释为指向structure的指针，->用于访问结构体node中string的成员。
}//Welcome to XUPT , welcome to Xiyou Linux Group [2023]
```
>这里涉及到大小端的问题。
>首先要知道内存地址的分配都是从小大到大的（低地址->高地址）。然后是高低字节，在一个n进制的位中，最左边的位叫最高有效位，最右边的叫最低有效位。
>* 大端：==高字节存放在低地址，低字节存放在高地址==（这个符合我们人类从高到底的习惯）
> * 小端：==低字节存放在低地址，高字节存放在高地址==（这个更有利于计算机的存储和处理，效率更高，但具体是大端还是小端这取决于CPU的架构）
> * 其中网络协议制定了通讯字节序为大端。多个字节数据作为整体处理时需要考虑到字节序。

ASCLL码表在这里，出自[这里](https://blog.csdn.net/qq_53030983/article/details/121687624?app_version=6.2.2&csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22121687624%22%2C%22source%22%3A%222301_80123601%22%7D&utm_source=app#:~:text=%E5%8F%91%E5%B8%83-,%E5%AD%97%E6%AF%8D%E6%95%B0%E5%AD%97%2DASCII%E7%A0%81%E8%A1%A8%EF%BC%88%E6%9C%80%E8%AF%A6%E7%BB%86%EF%BC%8C%E6%9C%80%E7%9B%B4%E8%A7%82%EF%BC%89,-%E8%A3%85%E5%A4%87%E6%98%AF%E6%88%91)
![在这里插入图片描述](https://img-blog.csdnimg.cn/4c97be041eb74e38962b4117bf9a0664.png)

## 13.GNU/Liunx(选做)
注：嘿！你或许对 Linux 命令不是很熟悉，甚至你没听说过 Linux。但别担心，这是选做题，了解
Linux 是加分项，但不了解也不扣分哦！
你知道 cd 命令的用法与` / . ~` 这些符号的含义吗？
请问你还懂得哪些与 GNU/Linux 相关的知识呢~
 
 >* cd命令：cd 是 "change directory" 的缩写，用于在命令行界面中切换当前工作目录。使用 cd 命令后，可以指定要切换到的目标目录的路径。
 >cd  ：不带参数时，cd命令会将当前工作目录切换为当前用户的主目录（通常是/home/用户名）。
cd . ：表示当前工作目录，使用这个命令不会改变当前目录。
ch/     ：表示进入根目录，输入ls可以查看根目录的内容。

想要进一步了解就看这篇文章叭->[基础必备cd命令](https://blog.csdn.net/qq_51721904/article/details/120768474#:~:text=%E5%8F%91%E5%B8%83-,%E5%9F%BA%E7%A1%80%E5%BF%85%E5%A4%87cd%E5%91%BD%E4%BB%A4,-%E8%AF%A6%E7%BB%86%E4%BD%BF%E7%94%A8%E6%96%B9%E6%B3%95)
 
**完结撒花！！！**