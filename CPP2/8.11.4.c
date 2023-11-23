#include<stdio.h>
#include<ctype.h>
int main()
{
    int words=0;
    int letter=0;
    char ch;
    while((ch=getchar())!=EOF){
        if((ch>='A' && ch<='Z') || (ch>='a' && ch<='z')){
            letter++;
        }
        if(ispunct(ch)!=0 || ch==' '){
            words++;
        }
    }
    printf("平均每个单词的字母数为：%.2f\n",letter/words*1.0);
    return 0;
}