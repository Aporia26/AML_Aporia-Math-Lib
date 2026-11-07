#include <stdio.h>
#include <math.h>

    int main(){

      int a, b, c;
      
        printf("Enter three coefficients in order a,b,c: \n");
        printf("(To have a quadratic eqn as, ax^2 + bx + c)\n");

       scanf( "%d %d %d", &a, &b, &c);
       printf("Your quadratic is: %dx^2 ",a);
      
      if(b>0){
         printf("+ %dx" ,b);
       }
       else{
         printf("%dx ",b);
       }
       if(c>0){
         printf("+ %d\n",c);
       }
       else{
         printf("%d\n",c);
       }
     
           

      int D = b*b - 4*a*c;        

      if(a != 0){  

        if(D>0){
            float root1 = (- b + sqrt(b*b - 4*a*c))/(2*a);
            float root2 = (- b - sqrt(b*b - 4*a*c))/(2*a);
           printf("The Roots are real \n");
           printf("The roots are: \n");
           printf("%f and %f", root1, root2);
            }
        else if (D<0){
            printf("The Roots are Imaginary!");
         }
        else if(D == 0){
         float root2 = (- b )/(2*a);
           printf("The Roots are Equal\n");
           printf("The roots are: \n");
           printf("%f", root2);
        } 
        }
       
     else{
             printf("Quadratic dosen't exists!!");
       }

        return 0;
    }


      // fflush(stdin);  Clears any leftover input keys
      // getchar();      Forces the terminal to wait until you press Enter