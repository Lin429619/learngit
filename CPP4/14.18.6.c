#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int id;
    char fname[20];
    char lname[20];
    int start;
    int hit;
    int base;
    int RBI;
    float lu; 
}PLAYER;

PLAYER list[19]={};

void read_data(PLAYER list[],FILE*fp);
void set_data(PLAYER list[]);
void print_data(PLAYER list[]);

int main()
{
    FILE *fp;
    if((fp=fopen("data.txt","r"))==NULL){
        fprintf(stderr,"Can't open data.txt file.\n");
        exit(EXIT_FAILURE);
    }
    read_data(list,fp);
    set_data(list);
    print_data(list);
    fclose(fp);
    return 0;
}

void read_data(PLAYER list[],FILE*fp){
    int id;
    char fname[20];
    char lname[20];
    int start;
    int hit;
    int base;
    int RBI;
    float lu;
    int count=1;
    while(1){
        count=fscanf(fp,"%d %s %s %d %d %d %d",&id,fname,
        lname,&start,&hit,&base,&RBI);
        if(count<7) break;
        strcpy(list[id].fname,fname);
        strcpy(list[id].lname,lname);
        list[id].id = id;
        list[id].start += start;
        list[id].hit += hit;
        list[id].base += base;
        list[id].RBI += RBI;
    }
}

void set_data(PLAYER list[]){
    for(int i=0;i<19;i++){
        list[i].lu =(float)list[i].hit/(float)list[i].start; 
    }
}

void print_data(PLAYER list[]){
    for(int i=0;i<19;i++){
        printf("%d %8s %-8s %3d %3d %3d %3d %3.2f",list[i].id,list[i].fname,
        list[i].lname,list[i].start,list[i].hit,list[i].base,
        list[i].RBI,list[i].lu);
        printf("\n");
    }
}