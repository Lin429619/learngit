#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int search(char ch,FILE *fp);

int main(int argc,char *argv[])
{
    FILE *fp;
    int count=0;
    char ch,c;
    if(argc<2){
        fprintf(stderr,"Usage: %s filename",argv[0]);
        exit(EXIT_FAILURE);
    }    
    if(strlen(argv[1])!=0){
        fprintf(stderr,"Munst be one character!");
        exit(EXIT_FAILURE);
        }
    ch=argv[1][0];
    if(argc==2){
        fp=stdin;
        count=search(ch,fp);
        printf("%c appeared %d times",ch,count);
    }
    else {
        for(int i=2;i<argc;i++){
            if((fp=fopen(argv[i],"r"))==NULL){
                fprintf(stderr,"Can't open file: %s\n",argv[i]);
                continue;
            }
            printf("File:\n");
            while((c=getc(fp))!=EOF){
                putchar(c);
            }
            rewind(fp);
            count=search(ch,fp);
            printf("%c appeared %d times",ch,count);
            if(fclose(fp)!=0){
                fprintf(stderr,"Can't close file: %s",argv[i]);
            }
        }
    }
    return 0;
}

int search(char ch,FILE *fp){
    int find;
    int cnt=0;
    while((find=getc(fp))!=EOF){
        if(ch==find)
            cnt++;
    }
    return cnt;
}