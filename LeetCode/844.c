#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int change(char* s){
    int fast = 0,slow = 0;
    int len = strlen(s);
    for(; fast<len; fast++){
        if(s[fast]=='#'){
            if(slow !=0 ) slow--;
        }
        else{
            s[slow++] = s[fast];
        }
    }
    return slow;
}

bool backspaceCompare(char* s, char* t) {
    int ls1 = change(s);
    int ls2 = change(t);
    if(ls1 != ls2) return false;
    else{
        if(strncmp(s,t,ls1)==0) return true;
        else return false;
    } 
}//双指针

/*栈解法
char *build(char *str){
    int len = strlen(str);
    int k = 0;
    char *ret = (char*)malloc(sizeof(char) * (len+1));
    for(int i=0; i<len; i++){
        if((str[i]) != '#')
            ret[k++] = str[i];
        else if(k>0)
            k--;
        }
    ret[k] = '\0';
    return ret;
}


bool backspaceCompare(char* s, char* t) {
    if(strcmp(build(s),build(t))==0)
        return true;
    else 
        return false;
}
*/

int main(){
    char s[100],t[100];
    scanf("%s %s",s,t);
    if(backspaceCompare(s,t))
        printf("true");
    else 
        printf("false");
    return 0;
}