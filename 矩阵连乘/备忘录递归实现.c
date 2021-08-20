
#include

using namespace std;
long MaxtrixChain1(int n);
long MaxtrixChain1(int i, int j);
int const MAX = 1000;
long subMatrixChain[MAX][MAX];
int bestK[MAX][MAX];
int dim[MAX];

int main()
{
    int i, n;

    while (cin >> n)

    {
        for (i = 0; i <= n; i++)
        {
            cin >> dim[i];
        }

        cout << MaxtrixChain1(n);

        memset(subMatrixChain,-1,sizeof(subMatrixChain));

        //cout << endl << subMatrixChain[5][1];

        cout << "case 2:" << MaxtrixChain1(1,n);

    }

    return 0;
}


long MaxtrixChain1(int n)
{
    int i,j,k,len;

    for (i = 1; i <= n; i++)
    {
        subMatrixChain[i][i] = 0;
    }

    for (len = 2; len <= n; len++)
    {
        for (i = 1; i <= n - len + 1; i++)
        {
            j = i + len - 1;

            subMatrixChain[i][j] = 100000000;

            for (k = i; k < j; k++)
            {
                long ans = subMatrixChain[i][k] + subMatrixChain[k+1][j] + dim[i-1] * dim[k] * dim[j];

                if (ans < subMatrixChain[i][j])
                {
                    subMatrixChain[i][j] = ans;
                    bestK[i][j] = k;
                }

            }

        }

    }

    return subMatrixChain[1][n];
}


long MaxtrixChain1(int i,int j)
{
    if (subMatrixChain[i][j] != -1)
    {
        return subMatrixChain[i][j];
    }

    if (i == j)
    {
        subMatrixChain[i][j] = 0;

        return 0;
    }

    long ans,max1 = 10000000;

    for (int k = i; k < j; k++)
    {
        ans = MaxtrixChain1(i,k)+ MaxtrixChain1(k+1,j)+ dim[i-1] * dim[k] * dim[j];

        if (ans < max1)
        {
            max1 = ans;

            bestK[i][j] = k;
        }

    }

    subMatrixChain[i][j] = max1;

    return max1;
}
