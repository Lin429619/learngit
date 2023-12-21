#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *head;

/*void InsertHead(int x){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = x;
    temp->next = head;
    head = temp;
}*/

//任意位置插入一个节点
void Insert(int x, int pos){//position
    struct Node *temp1 = (struct Node*)malloc(sizeof(struct Node));
    temp1->data = x;
    temp1->next = NULL;
    if(pos == 1){
        temp1->next = head;
        head = temp1;
        return;
    }
    struct Node *temp2 = head;
    for(int i = 0; i < pos - 2; i++){
        temp2 = temp2->next;
    }
    temp1->next = temp2->next;
    temp2->next = temp1;
}

//删除任意位置的节点
void Delete(int pos){
    struct Node *temp1 = head;
    if(pos == 1){
        head = temp1->next;
        free(temp1);
        return;
    }
    for(int i = 0; i < pos - 2; i++){
        temp1 = temp1->next;
    }
    struct Node *temp2 = temp1->next;
    temp1->next = temp2->next;
    free(temp2);
}

//通过遍历反转链表
struct Node *Reverse1(){
    struct Node *current,*prev,*next;
    current = head;
    prev = NULL;
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;    
    }
    head = prev;
    return head;
}

//通过递归反转链表
void *Reverse2(struct Node *p)
{
    if(p->next == NULL){
        head = p;
        return;
    }
    Reverse2(p->next);
    struct Node *q = p->next;
    q->next = p;
    p->next = NULL;
}

//递归反向输出链表
void ReversePrint(struct Node *p){
    if(p == NULL)
        return;
    ReversePrint(p->next);
    printf("%d ",p->data);
}

/*递归输出链表
void Print(struct Node *p){
    if(p == NULL)
        return;
    printf("%d ",p->data);
    Print(p->next);
}
*/

void Print(){
    struct Node *temp = head;
    while(temp != NULL){
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    head = NULL;
    return 0;
}