#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 20
char * s_gets(char * st,int n);
struct book{
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
    int delete_flag;
};

int main()
{
    char delete;
    struct book library[MAXBKS];
    int count=0;
    int index,filecount;
    FILE * pbooks;
    int size = sizeof(struct book);

    if((pbooks=fopen("book.dat","r+b"))==NULL){
        fputs("Can't open the file.",stderr);
        exit(1);
    }
    rewind(pbooks);

    while(count<MAXBKS & fread(&library[count],size,1,pbooks)==1){
        if(count==0)
            puts("Current contents of book.dat:");
        printf("%s by %s: $%.2f\n",library[count].title,
        library[count].author,library[count].value);
        count++;    
    }

    filecount=count;
    if(count==MAXBKS){
        fputs("Can't open the file.",stderr);
        exit(2);
    }

    printf("Do you want to modety library?(Y/N):");
    scanf("%c",&delete);
    if( delete == 'Y'){
        for(int i=0;i<count;i++){
            printf("%s by %s: $%.2f\n",library[count].title,
            library[count].author,library[count].value);
            while(getchar()!='\n') continue;
            puts("Do you want to delete this book(Y/N)?");
            scanf("%c",&delete);
            if(delete=='Y') library[count].delete_flag=1;
        }
    }


    puts("Please add new book titles.");
    puts("Please [enter] at the start of a line to stop.");
    while(count<index && s_gets(library[count].title,MAXTITL) != NULL 
    && library[count].title[0] != '\0' && library[count].delete_flag != 1){
        puts("Now enter the autor.");
        s_gets(library[count].author,MAXAUTL);
        puts("Noe enter the value.");
        scanf("%f",&library[count].value);
        library[count].delete_flag=0;
        while(getchar() != '\n') continue;
        if(count < index)
            puts("Enter the next title.");
    } 

    rewind(pbooks);
    if(count>0){
        puts("Here is the list of your book:");
        for(index = 0; index < count; index++){
            if(library[count].delete_flag != 1){
               printf("%s by %s: $%.2f\n",library[count].title,
                library[count].author,library[count].value); 
            }
            fwrite(&library[filecount],size,count-filecount,pbooks);
        }
    }
    else
        puts("No books?Too bad!\n");
    puts("Bye!\n");
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