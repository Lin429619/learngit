//(a)传地址
/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct user{
    char NUMS[20];
    struct {
        char fname[20];
        char mname[20];
        char lname[20];
    }; 
}user_list[5]={
    "302039823",{"Flossie","Mike","Dribble"}
};

void print_user_list(struct user list[],int num);

int main(){
    print_user_list(user_list,5);
    return 0;
}
void print_user_list(struct user list[],int num){
    for(int i=0; i<num; i++){
        if(strlen(list[i].NUMS)<9) break;
        printf("USER: %s, %s ",list[i].lname,list[i].fname);
        if(strlen(list[i].mname)>0)
            printf("%c.",list[i].mname[0]);
        printf(" -- %s\n",list[i].NUMS);
    }
}*/

//(b)结构的值
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct user{
    char NUMS[20];
    struct {
        char fname[20];
        char mname[20];
        char lname[20];
    }; 
}user_list[5]={
    "302039823",{"Flossie","Mike","Dribble"}
};

void print_user_list(struct user u);

int main(){
    print_user_list(user_list[0]);
    return 0;
}
void print_user_list(struct user u){
    if(strlen(u.NUMS)<9) return;
    printf("USER: %s, %s ",u.lname,u.fname);
    if(strlen(u.mname)>0)
        printf("%c.",u.mname[0]);
    printf(" -- %s\n",u.NUMS);
    return;
}

