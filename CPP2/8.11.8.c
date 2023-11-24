#include<stdio.h>
float number();

int main()
{
   char ch;
   float a,b;
   do{
        printf("Enter the operation of your choice:\n");
        printf("a.add         s.subtract\n");
        printf("m.multiply    d.divide\n");
        printf("q.quit\n");
        ch=getchar();
        switch(ch){
            while(getchar()!='\n') continue;
            case 'a':
                printf("Enter first number:");
                a=number();
                printf("Enter second number:");
                b=number();
                printf("%.2f + %.2f = %.2f\n",a,b,a+b);
                break;        
            case 's':
                printf("Enter first number:");
                a=number();
                printf("Enter second number:");
                b=number();
                printf("%.2f - %.2f = %.2f\n",a,b,a-b);
                break;
            case 'm':
                printf("Enter first number:");
                a=number();
                printf("Enter second number:");
                b=number();
                printf("%.2f * %.2f = %.2f\n",a,b,a*b);
                break;
            case 'd':
                printf("Enter first number:");
                a=number();
                printf("Enter second number:");
                b=number();
                while(b == 0){
                    printf("Enter a number other than 0:");
                    scanf("%f",&b);
                }
                printf("%.2f / %.2f = %.2f\n",a,b,a/b);
                break;
            case 'q':
                break;
            default:
                printf("Please enter a,s,m,d or q.\n");
                continue;
        }
        while(getchar()!='\n');
   }while(ch!='q');
   printf("Bye!\n");
   return 0;
}

float number(){
    float c;
    char ch;
    while((scanf("%f",&c))!=1){
        while((ch = getchar())!='\n'){
            putchar(ch);
        }
        printf(" is not an number.\n");
        printf("Please enter a number ,such as 2.5, -1.78E8, or 3: ");
    }
    return c;
}