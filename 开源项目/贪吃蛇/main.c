//#define _CRT_SECURE_NO_WARNINGS

#include "snake.h"

int main() {
	init(map, snake);//初始化地图
	while (1) {
		getKey();
		system("cls");
		Sleep(33);
		move(snake, direct);//让蛇开始移动
		if (!food[0] && !food[1]) {//食物已经被吃掉--重新生成食物
			makeFood(food);//生成食物坐标
		}
		makeMap(map, snake, food);
		showView(map);
		if (ifBump(head)) {
			printf("游戏结束，你的成绩为：%d", head);
			break;
		}
		getKey();
	}
	getchar();
	return 0;
}
