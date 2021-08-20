//N queen's problem

#include<stdio.h>
#include <stdlib.h>

int x[20];
int c=0;
int place(int k, int i)
{
    for(int j=1; j<=k-1; j++)
    {
        if((x[j]==i)||(abs(x[j]-i)==abs(j-k)))
            return 0;
    }
    return 1;
}

void nqueens(int k, int n)
{
    for(int i=1; i<=n; ++i)
    {
        if(place(k,i))
        {
            x[k]=i;
            if(k==n)
            {
                c++;
                if(c==1){
                printf("Solution vector is:");
                for(int p=1;p<=n;p++)
                    printf("%d ",x[p]);
                printf("\n");
                }
            }
            else
                nqueens(k+1,n);
        }
    }
}

int main()
{
    int n;
    printf("Enter the value of n: ");
    scanf("%d",&n);

    nqueens(1,n);
    printf("The number of solutions are: %d\n",c);
    printf("\nFormat of output: Each number represents the column number of the queens\n");
    printf("The solutions are represented by an n-tuple(x1, x2, x3, ..., xn)\n");
    printf("Here xi is the column number on which ith queen Qi is placed\n\n");
}
