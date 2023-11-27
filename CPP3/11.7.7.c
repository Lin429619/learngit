#include<stdio.h>
#include<string.h>
#define SIZE 100

char* string_in(char *source,char *dest);

int main(int argc,char *argv[])
{
    char source_string[SIZE],dest[SIZE];
    printf("Enter a string as your source string(blank to quit):");
    fgets(source_string,SIZE,stdin);
    printf("Enter a dest string to find in source:");
    fgets(dest,SIZE,stdin);
    while(*source_string != '\n'){
        printf("Now the position of dest is: %p\n",string_in(source_string,dest));
        printf("Enter a string as your source string(blank to quit):");
        fgets(source_string,SIZE,stdin);
        printf("Enter a dest string to find in source:");
        fgets(dest,SIZE,stdin);
    }
    return 0;
}

char* string_in(char *source,char *dest){
    int cnt=0;
    int len=strlen(dest);
    while(*source!='\0' && cnt<len){
        if(*(source + cnt)==*(dest + cnt))
            cnt++;
        else{
            source++;
            cnt=0;
        }
    }
    if(cnt==len) return source;
    else return NULL;
} 
