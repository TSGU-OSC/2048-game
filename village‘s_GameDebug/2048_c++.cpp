#include"2048.hpp"
int main()
{
	GameDraw gamedraw;
	GameJudgment gamejudgment;
	initgraph(WIN_SIZE,WIN_SIZE,SHOWCONSOLE);//创建窗口
	gamedraw.GameInit();
	while (1)
	{
		BeginBatchDraw();
		GameDraw();
		EndBatchDraw();
		gamejudgment.IsGameOver();
		gamejudgment.KeyControl();
	}
	closegraph();
	system("pause");
	return 0;
}