#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<cstdlib>
#include<ctime>
#include<graphics.h>
#define MAX_SIZE 4//每行格子数
#define GRID_WIDTH 100//格子宽度
#define INTERVAL 15//格子间隔
#define WIN_SIZE MAX_SIZE*GRID_WIDTH+5*INTERVAL
using namespace std;

enum  Color//枚举颜色
{
	zero = RGB(205, 193, 180),
	twoto1 = RGB(238, 228, 218),
	twoto2 = RGB(237, 224, 200),
	twoto3 = RGB(242, 177, 121),
	twoto4 = RGB(245, 149, 99),
	twoto5 = RGB(246, 124, 95),
	twoto6 = RGB(246, 94, 94),
	twoto7 = RGB(242, 164, 121),
	twoto8 = RGB(237, 204, 97),
	twoto9 = RGB(255, 42, 128),
	twoto10 = RGB(145, 0, 72),
	twoto11 = RGB(242, 17, 158),
	bk = RGB(187, 173, 160),
};
class GameDraw
{
public:
	//实现颜色与数据的链接
	Color arr[13] = { zero,twoto1,twoto2,twoto3,twoto4,twoto5,twoto6,twoto7,twoto8,twoto9,twoto10,twoto11,bk };
	int num[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
	POINT pos[MAX_SIZE][MAX_SIZE] = {};
	int map[MAX_SIZE][MAX_SIZE] = {};//数据存储
	int score = 0;
	char usrkey = 0;
	void GameInit()
	{
		srand(GetTickCount());
		//初始化数组
		for (int i = 0; i < MAX_SIZE; i++)
		{
			for (int j = 0; j < MAX_SIZE; j++)
			{
				map[i][j] = 0;
			}
		}
		//初始化每个格子的坐标，左上角
		for (int i = 0; i < MAX_SIZE; i++)
		{
			for (int j = 0; j < MAX_SIZE; j++)
			{
				pos[i][j].x = (j * GRID_WIDTH + (j + 1) * INTERVAL);
				pos[i][j].y = (i * GRID_WIDTH + (i + 1) * INTERVAL);
			}
		}
		CreateNumber();
		CreateNumber();
	}
	
	
	GameDraw()
	{
		//设置背景颜色
		setbkcolor(Color::bk);
		for (int i = 0; i < MAX_SIZE; i++)
		{
			for (int j = 0; j < MAX_SIZE; j++)
			{
				for (int k = 0; k < 12; k++)
				{
					if (map[i][j] == num[k])
					{
						DWORD tempcolor = arr[k];
						setfillcolor(tempcolor);
						solidrectangle(pos[i][j].x, pos[i][j].y, pos[i][j].x + GRID_WIDTH, pos[i][j].y + GRID_WIDTH);
						if (num[k] != 0)
						{
							char number[5] = " ";
							sprintf(number, "%d", num[k]);
							setbkmode(TRANSPARENT);
							settextcolor(RGB(119, 110, 101));
							settextstyle(45, 0, "黑体");
							int tempx = textwidth(number);
							tempx = (GRID_WIDTH - tempx) / 2;
							int tempy = textheight(number);
							tempy = (GRID_WIDTH - tempy) / 2;
							outtextxy(pos[i][j].x + tempx, pos[i][j].y + tempy, number);
						}
					}
				}
			}
		}
	}
	
	 //生成随机数2或4
	 int RandTwoFour()
	 {
		 if (rand() % 10 == 0)
		 {
			 return 4;
		 }
		 else
		 {
			 return 2;
		 }
	 }
	 bool CreateNumber()
	 {
		 int blank_count = 0;
		 for (int row = 0; row < MAX_SIZE; row++)
		 {
			 for (int col = 0; col < MAX_SIZE; col++)
			 {
				 if (map[row][col] == 0)
				 {
					 blank_count++;
				 }
			 }
		 }
		 if (blank_count == 0)
		 {
			 return false;
		 }

		 int index = rand() % blank_count;
		 int num = rand() % 2 ? 2 : 4;
		 int count = 0;
		 for (int row = 0; row < MAX_SIZE; row++)
		 {
			 for (int col = 0; col < MAX_SIZE; col++)
			 {
				 if (map[row][col] == 0)
				 {
					 if (count == index)
					 {
						 map[row][col] = num;
						 return true;
					 }
					 count++;
				 }
			 }
		 }
		 return false;
	 }
	 
	
};
class GameMove
{
	
public:
	GameDraw gamedraw;
	//移动方块合成数据
// 向上移动
	void MoveUp()
	{
		for (int i = 0; i < MAX_SIZE; i++) // 枚举列
		{
			int temp = 0; // 此列最上面
			for (int j = 1; j < MAX_SIZE; j++) // 枚举行
			{
				if (gamedraw.map[j][i] != 0) // 这个格子有数字
				{
					if (gamedraw.map[temp][i] == 0) // 最上面空着 -> 上去
					{
						gamedraw.map[temp][i] = gamedraw.map[j][i];
						gamedraw.map[j][i] = 0;
					}
					else if (gamedraw.map[temp][i] == gamedraw.map[j][i]) // 上面是同样数字 -> 合并
					{
						gamedraw.map[temp][i] += gamedraw.map[j][i];
						gamedraw.score += gamedraw.map[j][i];
						gamedraw.map[j][i] = 0;
						temp++;
					}
					else
					{
						gamedraw.map[temp + 1][i] = gamedraw.map[j][i]; // 上到前一个格子
						if (temp + 1 != j)
						{
							gamedraw.map[j][i] = 0;
						}
						temp++;
					}
				}
			}
		}
	}

	// 向下移动
	void MoveDown()
	{
		for (int i = 0; i < MAX_SIZE; i++) // 枚举列
		{
			int temp = MAX_SIZE - 1; // 此列最下面
			for (int j = MAX_SIZE - 2; j >= 0; j--) // 枚举行
			{
				if (gamedraw.map[j][i] != 0) // 这个格子有数字
				{
					if (gamedraw.map[temp][i] == 0) // 最下面空着 -> 下去
					{
						gamedraw.map[temp][i] = gamedraw.map[j][i];
						gamedraw.map[j][i] = 0;
					}
					else if (gamedraw.map[temp][i] == gamedraw.map[j][i]) // 下面是同样数字 -> 合并
					{
						gamedraw.map[temp][i] += gamedraw.map[j][i];
						gamedraw.score += gamedraw.map[j][i];
						gamedraw.map[j][i] = 0;
						temp--;
					}
					else
					{
						gamedraw.map[temp - 1][i] = gamedraw.map[j][i]; // 下到前一个格子
						if (temp - 1 != j)
						{
							gamedraw.map[j][i] = 0;
						}
						temp--;
					}
				}
			}
		}
	}

	// 向右移动
	void MoveRight()
	{
		for (int i = 0; i < MAX_SIZE; i++) // 枚举行
		{
			int temp = MAX_SIZE - 1; // 此行最右面
			for (int j = MAX_SIZE - 2; j >= 0; j--) // 枚举列
			{
				if (gamedraw.map[i][j] != 0) // 这个格子有数字
				{
					if (gamedraw.map[i][temp] == 0) // 最右面空着 -> 右去
					{
						gamedraw.map[i][temp] = gamedraw.map[i][j];
						gamedraw.map[i][j] = 0;
					}
					else if (gamedraw.map[i][temp] == gamedraw.map[i][j]) // 右面是同样数字 -> 合并
					{
						gamedraw.map[i][temp] += gamedraw.map[i][j];
						gamedraw.score += gamedraw.map[i][j];
						gamedraw.map[i][j] = 0;
						temp--;
					}
					else
					{
						gamedraw.map[i][temp - 1] = gamedraw.map[i][j]; // 到前一个格子
						if (temp - 1 != j)
						{
							gamedraw.map[i][j] = 0;
						}
						temp--;
					}
				}
			}
		}
	}

	// 向左移动
	void MoveLeft()
	{
		for (int i = 0; i < MAX_SIZE; i++) // 枚举行
		{
			int temp = 0; // 此行最左面
			for (int j = 1; j < MAX_SIZE; j++) // 枚举列
			{
				if (gamedraw.map[i][j] != 0) // 这个格子有数字
				{
					if (gamedraw.map[i][temp] == 0) // 最左面空着 -> 左去
					{
						gamedraw.map[i][temp] = gamedraw.map[i][j];
						gamedraw.map[i][j] = 0;
					}
					else if (gamedraw.map[i][temp] == gamedraw.map[i][j]) // 左面是同样数字 -> 合并
					{
						gamedraw.map[i][temp] += gamedraw.map[i][j];
						gamedraw.score += gamedraw.map[i][j];
						gamedraw.map[i][j] = 0;
						temp++;
					}
					else
					{
						gamedraw.map[i][temp + 1] = gamedraw.map[i][j]; // 到前一个格子
						if (temp + 1 != j)
						{
							gamedraw.map[i][j] = 0;
						}
						temp++;
					}
				}
			}
		}
	}
};
class GameJudgment
{
public:
	GameDraw gamedraw;
	//游戏是否结束
	bool IsGameOver()
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			for (int j = 0; j < MAX_SIZE; j++)
			{
				if (gamedraw.map[i][j] == 0)
				{
					return false;
				}
				if (i < MAX_SIZE - 1 && gamedraw.map[i][j] == gamedraw.map[i + 1][j])
				{
					return false;
				}
				if (j < MAX_SIZE - 1 && gamedraw.map[i][j] == gamedraw.map[i][j + 1])
				{
					return false;
				}
			}
		}
		return true;
	}
	// 用户键盘输入
	void KeyControl()
	{
		GameDraw gameDraw;
		GameMove gameMove;
		char input = _getch();
		switch (input)
		{
		case 72:
		case 'w':
		case 'W':
			cout << "up" << endl;
			gameMove.MoveUp();
			gameDraw.CreateNumber();
			break;
		case 80:
		case 's':
		case 'S':
			cout << "down" << endl;
			gameMove.MoveDown();
			gameDraw.CreateNumber();
			break;
		case 75:
		case 'a':
		case 'A':
			cout << "left" << endl;
			gameMove.MoveLeft();
			gameDraw.CreateNumber();
			break;
		case 77:
		case 'd':
		case 'D':
			cout << "right" << endl;
			gameMove.MoveRight();
			gameDraw.CreateNumber();
			break;
		case 'q':
		case 'Q':
			exit(0);
		}
	}
};





