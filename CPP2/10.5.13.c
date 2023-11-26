#include<stdio.h>
#define HANG 3
#define LIE 5

void input_arr(int hang,double arr[][LIE]);
double zu_average_arr(int lie,double *arr);
double average_arr(int hang,double arr[][LIE]);
double max_arr(int hang,double arr[][LIE]);
void print_arr(int hang,double arr[][LIE]);

int main()
{
    double arr[HANG][LIE];
    input_arr(HANG,arr);
    print_arr(HANG,arr);
    printf("\n");
    return 0;
}


void input_arr(int hang,double arr[][LIE]){
    printf("Please input 15 numbers,(3*5):\n");
    for(int i=0;i<hang;i++){
        for(int j=0;j<LIE;j++){
            scanf("%lf",&arr[i][j]);
        }
    }
}

double zu_average_arr(int lie,double arr[]){
    double sum=0;
    for(int i=0;i<lie;i++){
        sum+=arr[i];
    }
    return sum/lie;
}

double average_arr(int hang,double arr[][LIE]){
    double sum=0;
    for(int i=0;i<hang;i++){
        for(int j=0;j<LIE;j++){
            sum+=arr[i][j];
        }
    }
    return sum/(HANG*LIE);
}

double max_arr(int hang,double arr[][LIE]) {
    double max=arr[0][0];
    for(int i=0;i<hang;i++){
        for(int j=0;j<LIE;j++){
            if(max<arr[i][j])
                max=arr[i][j];
        }
    }
    return max;
}

void print_arr(int hang,double arr[][LIE]){
    printf("The array you input is:\n");
    for(int i=0;i<hang;i++){
        for(int j=0;j<LIE;j++){
            printf("%-5.2lf ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int j=0;j<hang;j++){
        printf("hang %d's average is %.2lf\n",j+1,zu_average_arr(LIE,arr[j]));
    }
    printf("average is %.2lf\n",average_arr(HANG,arr));
    printf("max number is %.2lf\n",max_arr(HANG,arr));
}
