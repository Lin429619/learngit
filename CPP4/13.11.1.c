#include<stdio.h>
#include<stdlib.h>
#define SIZE 50
int main(int argc,char *argv[])
{
    int ch;
    FILE *fp;
    unsigned long count=0;
    char filename[SIZE];
    printf("Enter filename:");
    scanf("%49s",filename);
    if((fp=fopen(filename,"r"))==NULL){
        printf("Can't open %s\n",filename);
        exit(EXIT_FAILURE);
    }
    while((ch=getc(fp))!=EOF){
        putc(ch,stdout);
        count++;
    }
    printf("\n");
    fclose(fp);
    printf("File %s has %lu characters\n",filename,count);
    return 0;
}