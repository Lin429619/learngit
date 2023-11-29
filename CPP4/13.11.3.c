#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#define SIZE 40

int main(int argc,char *argv[]){
    char filename[SIZE];
    char ch;
    FILE *fp;
    printf("Enter filename:");
    scanf("%39s",filename);
    if((fp=fopen(filename,"r+"))==NULL){
        fprintf(stderr,"Can't open file: %s\n",filename);
        exit(EXIT_FAILURE);
    }
    while((ch=getc(fp))!=EOF){
        fseek(fp,-1L,SEEK_CUR);
        putc(toupper(ch),fp);
        fseek(fp,0L,SEEK_CUR);
    }
    rewind(fp);
    while((ch=getc(fp))!=EOF){
        putchar(ch);
    }
    putchar('\n');
    if((fclose(fp))!=0){
        fprintf(stderr,"Can't close file.\n");
    }
    return 0;
}