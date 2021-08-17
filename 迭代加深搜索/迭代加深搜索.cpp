#include <cstdio>
#include <cstring> 

bool Quick_Read(int &N) {
	N = 0;
	int op = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-')
			op = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		N = (N << 1) + (N << 3) + (c ^ 48);
		c = getchar();
	}
	N *= op;
	return N != 0;
}
void Quick_Write(int N) {
	if(N < 0) {
		putchar('-');
		N = -N;
	}
	if(N >= 10)
		Quick_Write(N / 10);
	putchar(N % 10 + 48);
}
const int MAXN = 1e5 + 5;
int ans[MAXN];
int limit;
bool flag;
int n;
void Id_Dfs(int nowdepth) {
	if(nowdepth > limit || flag)//达到层数不在恋战或找到答案，直接跳出
		return;
	if(ans[nowdepth] == n) {//满足题意
		flag = true;
		return;
	}
	for(int i = nowdepth; i >= 1; i--) {
		for(int j = nowdepth; j >= i; j--) {//两两搭配，且答案越大越容易找到解，故而到着找
			if(ans[i] + ans[j] <= n && ans[i] + ans[j] > ans[nowdepth]) {//满足题意1，2两点的搜索
				int now;//找到下一项
				ans[nowdepth + 1] = now = ans[i] + ans[j];	
				for(int k = nowdepth + 2; k <= limit; k++)
	//从nowdepth + 1这一项开始，后面最大时也就是now不停扩大2倍，若最大都达不到n，舍去不求
					now <<= 1;
				if(now < n)
					continue;
				Id_Dfs(nowdepth + 1);//搜索下一层
				if(flag)//找到答案
					return;
			}
		}
	}
}
void Work() {
	for(; !flag; limit++)//直到找到答案时停止搜索
		Id_Dfs(1);
	for(int i = 1; i < limit; i++) {//输出
		Quick_Write(ans[i]);
		putchar(' ');
	}
	putchar('\n');
}
void Init() {
	limit = 1;
	int test = 1;
	while(test < n) {//找到最小层数
		test <<= 1;
		limit++;
	}
	ans[1] = 1;
	flag = false;
}
int main() {
	while(Quick_Read(n)) {//多组输入输出，到0为止
		Init();
		Work();
	}
	return 0;
}
