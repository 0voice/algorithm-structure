#include <stdio.h>

int main(){
	int n;  // 用户输入的整数
	int i;  // 循环标志

	printf("输入一个整数：");
	scanf("%d",&n);
	printf("%d=",n);

	// n>=2才执行下面的循环
	for(i=2; i<=n; i++){
		while(n!=i){
			if(n%i==0){
				printf("%d*",i);
				n=n/i;
			}else
				break;
		}
	}
	printf("%d\n",n);

	return 0;
}


//运行结果：

//输入一个整数：10000
//10000=2*2*2*2*5*5*5*5
