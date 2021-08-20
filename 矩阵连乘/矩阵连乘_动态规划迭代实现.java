/**

* 下面是矩阵连乘问题的动态规划算法

* 假设有6个矩阵：

* A1 A2A3 A4 A5A6

* 30*35 35*15 15*5 5*10 10*20 20*25 则matrixChain为

* {30, 35, 15, 5, 10, 20, 25} 结果为

* ((A1 * (A1 * A2)) * ((A4 * A5) * A6) )

*

* @author liuy

*/

public class MatrixMulitply {
    public static void main(String[] args) {
        int[] matrixChain = {30, 35, 15, 5, 10, 20, 25};

        matrixMultiply(matrixChain);

    }

    //矩阵连乘

    public static void matrixMultiply(int[] matrixChain) {
        int dimension = matrixChain.length;

        int[][] timeResult = new int[dimension][dimension];

        int[][] tagResult = new int[dimension][dimension];

        matrixMultiply(matrixChain, timeResult, tagResult);

        System.out.println("最优乘法次数：" + timeResult[1][dimension - 1]);

        System.out.println("划分规则为：");

        traceBack(tagResult, 1, dimension - 1);

    }

    //矩阵连乘

    public static void matrixMultiply(int[] matrixChain, int[][] timeResult, int[][] tagResult) {
        //timeResult 存放次数结果，矩阵的的行与列以1开始，tagResult 存放标记结果，矩阵的的行与列以1开始

        int n = matrixChain.length - 1;

        for(int i = 1; i <= n; i++)//初始化矩阵

            timeResult[i][i] = 0;

        for(int r = 2; r <= n; r++)//从列号的第二位开始

            for(int i = 1; i <= n - r + 1; i++ ) {//i为行号

                int j = i + r - 1;//j为列号

                timeResult[i][j] = timeResult[i + 1][j] + matrixChain[i - 1] * matrixChain[i] * matrixChain[j];

                tagResult[i][j] = i;

                for(int k = i + 1; k < j; k++) {//

                    int temp = timeResult[i][k] + timeResult[k + 1][j] + matrixChain[i - 1] * matrixChain[k] * matrixChain[j];

                    if(temp < timeResult[i][j]) {//寻找最小值

                        timeResult[i][j] = temp;

                        tagResult[i][j] = k;//记录划分标记

                    }

                }

            }

    }


    //按计算出断点矩阵tagResult指示的加括号方式

    public static void traceBack(int[][] tagResult, int i, int j) {
        if(i == j) return;

        traceBack(tagResult, i, tagResult[i][j]);

        traceBack(tagResult, tagResult[i][j] + 1, j);

        System.out.println("Multiply A(" + i + "," + tagResult[i][j] + ")and A(" + (tagResult[i][j] + 1) + "," + j + ")");

    }

}
