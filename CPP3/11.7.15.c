#include<stdio.h>
#include<ctype.h>
#define SIZE 100

char *s_gets(char *st,int n);
int myatoi(char *str);

int main()
{
    char *str[SIZE];
    while(s_gets(str,SIZE)!=NULL){
        printf("String %s change to number is %d\n",str,myatoi(str));
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

int myatoi(char *str){
    int len=strlen(str);
    int n=0;
    for(int i=0;i<len;i++){
        if(isdigit(str[i])==0)
            return 0;
        n=n*10 + (str[i]-'0');
    }
    return n;
}