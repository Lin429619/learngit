//文件压缩程序，成原来的1/3
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 40

int main(int argc,char *argv[]){
    FILE *in,*out;
    int ch;
    char name[SIZE];
    int count=0;
    char temp[SIZE];
    printf("Enter filename:");
    scanf("%39s",temp);
    if((in=fopen(temp,"r"))==NULL){
        fprintf(stderr,"Can't open the file \"%s\"\n",temp);
        exit(EXIT_FAILURE);
    }
    strncpy(name,temp,SIZE-5);
    name[SIZE-5]='\0';
    strcat(name,".red");
    if((out=fopen(name,"w"))==NULL){
        fprintf(stderr,"Can't create output file.\n");
        exit(3);
    }
    while((ch=getc(in))!=EOF){
        if(count++ % 3 ==0){
            putc(ch,out);
        }
    }
    if(fclose(in)!=0 || fclose(out)!=0){ 
        fprintf(stderr,"Error in closing file.\n");
    }
    return 0;
}