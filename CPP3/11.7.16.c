#include<stdio.h>
const int size=100;
void print(char *s);
void upper(char *s);
void lower(char *s);

int main(int argc,char *argv[])
{
    char c;
    if(argc==1) c='p';
    else c==argv[1][1];
    char text[size];
    fgets(text,size,stdin);
    switch(c){
        case 'p':
        case 'P':
            print(text);
            break;
        case 'u':
        case 'U':
            upper(text);
            break;
        case 'l':
        case 'L':
            lower(text);
            break;        
    }
    return 0;
}

void print(char *s){
    printf("%s",s);
}
void upper(char *s){
    while(*s != EOF && *s !='\0'){
        *s+=32;
        s++;
        putchar(*s);
    }
}
void lower(char *s){
    while(*s != EOF && *s !='\0'){
        *s-=32;
        s++;
        putchar(*s);
    }
}