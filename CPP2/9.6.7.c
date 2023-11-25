#include<stdio.h>
int position(char ch);
void print();

int main()
{
    print();
    return 0;
}

void print(){
    char ch;
    while((ch=getchar())!=EOF){
        if(ch=='\n') continue;
        int num;
        num=position(ch);
        if(num!=-1) 
            printf("%c's position is %d\n",ch,num);
        else printf("%c isn't a zimu\n",ch);
    }
}

int position(char ch){
    if(ch>='a' && ch<='z')
        return ch-'a'+1;
     if(ch>='A' && ch<='Z')
        return ch-'A'+1;
    return -1;
}