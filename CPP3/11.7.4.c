#include<stdio.h>
#include<ctype.h>
#define SIZE 100

char *get_words(char *out, int n);

int main(int argc,char *argv[]){
    char output[SIZE];
    get_words(output,SIZE);
    printf("The first word you put is: %s\n",output);
    return 0;
}

char *get_words(char *out,int n){
    char input[SIZE];
    char *in=input;
    int i = 0;
    puts("Enter a String:");
    fgets(input,SIZE,stdin);

    while(!isalpha(*in) && *in!='\0')
        in++;
    while(isalpha(*in) && *in!='\0' && i<n){
        *out++ = *in++;
        i++;
    }
    return out;
}
