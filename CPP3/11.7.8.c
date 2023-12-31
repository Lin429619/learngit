#include<stdio.h>
#include<string.h>
#define SIZE 100

char* string_in(char *str,char *pt);
char* s_gets(char *st,int n);

int main()
{
    char str1[SIZE];
    char str2[SIZE];
    while(s_gets(str1,SIZE)!=NULL){
        if(s_gets(str2,SIZE)!=NULL){
            char *p=string_in(str1,str2);
            if(p!=NULL){
                printf("The position is %p",p);
            }else{
                printf("Not Found.");
            }
        }
    }
    return 0;
}

char *s_gets(char *st,int n){
    char *ret_val;
    char *find;
    ret_val=fgets(st,n,stdin);
    if(ret_val)
    {
        find=strchr(st,'\n'); 
        if(find) *find='\0';
        else{
            while(getchar()!='\n')
                continue;
        }
    }
    return ret_val;
}

char *string_in(char *str,char *pt){
    int i=0,j=0;
    int str_len=strlen(str),pt_len=strlen(pt);
    while(i<str_len && j<pt_len){
        if(str[i]==pt[j]){
            i++;
            j++;
        }
        else{
            i=i-j+1;
            j=0;
        }
    }
    return j==pt_len ? str+i-j : NULL;
}

