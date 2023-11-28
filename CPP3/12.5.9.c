#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    int count;
    printf("Teh words number you enter:");
    scanf("%d",&count);
    printf("Put:");
    char **words=(char**)malloc(count*sizeof(char*));
    for(int i=0;i<count;i++){
        char st[50];
        scanf("%s",st);
        int len=strlen(st);
        char *str=(char*)malloc(len * sizeof(char));
        strcpy(str,st);
        words[i]=str;
    }
    for(int i=0;i<count;i++){
        printf("%s\n",words[i]);
        free(words[i]);
    }
    free(words);
    return 0;
}