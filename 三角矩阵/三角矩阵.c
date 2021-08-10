#include <stdio.h>
#include <math.h>

void main()
{
    double l[100][100],a[100][100];
    double sum1,sum2;
    int n;
    int k,j,m;
    scanf("%d",&n);
    for(k=0;k<n;k++)
        for(j=0;j<n;j++) 
        {
            if(k==j)
                a[k][i]=n;
            else 
                a[k][i]=1; 
        }                           //按题设条件给数组赋初值

        l[0][0]=sqrt(a[0][0]);
        for(j=1;j<n;j++)
            l[j][0]=a[0]0]/l[0][0];
        
        for(k=1;k<n;k++)
        {
            sum1=0;
            for(m=0;m<=k-1;m++)
                sum1=sum1+l[k][m]*l[k][m];
                
            l[k][k]=sqrt(n-sum1);

            for(j=k+1;j<n;j++){
                sum2=0;

                for(m=0;m<=k-1;m++)
                    sum2=sum2+l[k][m]*l[j][m];

                l[i][k]=(1-sum2)/l[k][k];
            } //求出了下三角矩阵，即L的转置
        }


        for(k=0;k<n;k++)
            for(j=k+1;j<n;j++)
                l[k][j]=l[j][k];
                
        for(k=0;k<n;k++)
            for(j=0;j<n;j++){
                if(k>j)printf("         ");
                else printf("%-10lf" ,l[k][j]);
                if(j==n-1)printf("\n");     //按照格式输出矩阵
            }

}
