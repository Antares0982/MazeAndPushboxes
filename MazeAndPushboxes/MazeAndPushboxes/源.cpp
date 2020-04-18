#include<iostream>
#include<string>
#include<conio.h>
#include<vector>
#include<array>
using namespace std;
string* A = new string[30];//存储游戏地图
int* xx;
int* yy;//这两个数组用来存储推箱子的目标点坐标
int TargetNum = 0;//存储推箱子目标点一共有多少个
bool isMaze = true;//游戏模式是走迷宫则为true，推箱子则为false
vector<int> beforex;
vector<int> beforey;//这两个vector用于存储前十步的位置，用于回档
vector<string> beforemap;//存储前十步的地图，用于回档

bool isTargetPoint(int x, int y)//判断当前的位置是否被存储在目标点坐标里
{
	for (int i = 0; i < TargetNum; i++)
	{
		if (x == xx[i] && y == yy[i]) { return true; }
	}
	return false;
}
bool isWinMaze(int y)//如果迷宫走到底就算赢
{
	if (y == 0)return true;
	else return false;
}
bool isWinPushbox()//循环判断所有目标点是否已经被箱子占据
{
	for (int i = 0; i < TargetNum; i++)
	{
		if (A[yy[i]][xx[i]] != '@')return false;
	}
	return true;
}
void mapmemory(int length, int x, int y)//记忆当前的地图以及玩家坐标
{
	if (beforemap.size() >= 10 * length)//如果存储数目大于10个，则删除之前第10步的地图
	{
		for (int i = 0; i < beforemap.size() - length; i++)
		{
			beforemap[i] = beforemap[i + length];
		}
		for (int i = 0; i < length; i++) { beforemap.pop_back(); }
	}
	for (int i = 0; i < length; i++)//写入当前的地图
	{
		beforemap.push_back(A[i]);
	}
	if (beforex.size() >= 10)//同理，删除之前的坐标
	{
		for (int i = 0; i < 9; i++)
		{
			beforex[i] = beforex[i + 1];
			beforey[i] = beforey[i + 1];
		}
		beforex.pop_back();
		beforey.pop_back();
	}
	beforex.push_back(x);//写入新的坐标
	beforey.push_back(y);
}
void readmapmemory(int length, int& x, int& y) //读取之前的地图及坐标，也就是回档
{
	if (beforex.size() == 0)return;//没有存储数据则不能回档
	x = beforex[beforex.size() - 1];//读取上一个存档位置
	beforex.pop_back();//删除存档
	y = beforey[beforey.size() - 1];//同上
	beforey.pop_back();
	for (int i = length - 1; i >= 0; i--) //读取地图，并删除存档
	{
		A[i] = beforemap[beforemap.size() - 1];
		beforemap.pop_back();
	}
}
int* initializeMaze() //初始化迷宫，返回值：p[0]是地图长度，p[1]是玩家初始位置x轴，p[2]是y轴
{
	A[0] = "* ********";
	A[1] = "*     ****";
	A[2] = "*****  ***";
	A[3] = "*    *  **";
	A[4] = "****  * **";
	A[5] = "*   * *  *";
	A[6] = "* *   ** *";
	A[7] = "* *****  *";
	A[8] = "*       **";
	A[9] = "* ********";
	A[10] = " #        ";
	int* p = new int[3];
	p[0] = 11;
	p[1] = 1;
	p[2] = 10;
	return p;
}
int* initializePushBox1()//初始化推箱子地图，返回值：p[0]是地图长度，p[1]是玩家初始位置x轴，p[2]是y轴。同时还要初始化目标点个数和坐标
{
	A[0] = "**********";
	A[1] = "* *     **";
	A[2] = "*#@  **  *";
	A[3] = "* @ &    *";
	A[4] = "* @ *&   *";
	A[5] = "* * &* ***";
	A[6] = "*        *";
	A[7] = "**       *";
	A[8] = "*** * ****";
	A[9] = "**********";
	int* p = new int[3];
	p[0] = 10;
	p[1] = 1;
	p[2] = 2;
	xx = new int[3];
	yy = new int[3];
	xx[0] = 4, yy[0] = 3;
	xx[1] = 5, yy[1] = 4;
	xx[2] = 4, yy[2] = 5;
	TargetNum = 3;
	return p;
}
int* initializePushBox2()//同上
{
	A[0] = "*****      ****";
	A[1] = "*#  ********  *";
	A[2] = "** @       @  *";
	A[3] = " * * *  ****  *";
	A[4] = " *  @   ****@**";
	A[5] = " *@ ** * @ @ * ";
	A[6] = "** @   *     * ";
	A[7] = "*   *      * * ";
	A[8] = "*   *****@**** ";
	A[9] = "*****   *   *  ";
	A[10] ="    *&&&  @ *  ";
	A[11] ="    *&&& *  *  ";
	A[12] ="    *&&&&****  ";
	A[13] ="    ******     ";
	int* p = new int[3];
	p[0] = 14;
	p[1] = 1;
	p[2] = 1;
	xx = new int[10];
	yy = new int[10];
	xx[0] = 5, yy[0] = 10;
	xx[1] = 5, yy[1] = 11;
	xx[2] = 5, yy[2] = 12;
	xx[3] = 6, yy[3] = 10;
	xx[4] = 6, yy[4] = 11;
	xx[5] = 6, yy[5] = 12;
	xx[6] = 7, yy[6] = 10;
	xx[7] = 7, yy[7] = 11;
	xx[8] = 7, yy[8] = 12;
	xx[9] = 8, yy[9] = 12;
	TargetNum = 10;
	return p;
}
void refreshmap(int ylength)//刷新地图
{
	system("cls");//清除屏幕
	for (int i = 0; i < ylength; i++)//输出地图
	{
		cout << A[i] << endl;
	}
}
void gameStart()//开始游戏，代码的主体在这里
{
	int ylength = -1;//ylength是地图长度
	int x = -1, y = -1;//玩家坐标用x,y表示
	int* p;//p仅仅用于读取地图初始化的返回值
	p = new int[1];
	*p = 1;
tag1://游戏模式选择有问题会返回这里
	system("cls");
	cout << "choose game mode. Please input Maze or Pushbox." << endl;
	string input;
	cin >> input;
	system("cls");
	if (input.find("Maze") != string::npos || input.find("maze") != string::npos) //如果选择走迷宫
	{
		p = initializeMaze(); ylength = p[0]; x = p[1]; y = p[2]; 
	}
	else if (input.find("Pushbox") != string::npos || input.find("pushbox") != string::npos)//如果选择玩推箱子
	{
	tag2://地图选择有问题会返回这里
		system("cls");
		cout << "Choose map:\nMap 1\nMap 2" << endl;
		cin >> input;
		if (input.find("1") != string::npos) { delete[] p; p = initializePushBox1(); }//选择地图1
		else if (input.find("2") != string::npos) { delete[] p; p = initializePushBox2(); }//选择地图2
		//在这里加入更多的地图初始化操作
		else goto tag2;//不是上述地图之一，则返回上面并重新执行
		ylength = p[0]; x = p[1]; y = p[2];//读取初始化地图得到的地图长度及坐标，之后删除临时指针p
		system("cls");
		delete[] p;
	}
	else goto tag1;//不选择迷宫也不选择推箱子，重新选一遍
	cout << "Press z to revoke at most 10 moves. Press 0 to end the game while in the game! Now press any key to start.";
	char a;
	a = _getch();//按任意键开始，这里是为了显示上面cout的提示
	system("cls");//清屏，开始输出地图
	for (int i = 0; i < ylength; i++)
	{
		cout << A[i] << endl;
	}
	a=_getch();//读取按下的按键
	int xlength = A[0].length();
	while (true)//获胜就会从while循环中跳出
	{
		if (a == '0')  { goto end; }//输入0则游戏结束，直接关闭窗口
		if (y == ylength - 1 && (a == 'a' || a == 's' || a == 'd'))  { a = _getch(); continue; }//在边缘不允许继续往外操作，防止溢出
		if (y == 0 && (a == 'a' || a == 'w' || a == 'd')) { a = _getch(); continue; }
		if (x == 0 && (a == 'a' || a == 's' || a == 'w')) { a = _getch(); continue; }
		if (x == xlength - 1 && (a == 'd' || a == 's' || a == 'w')) { a = _getch(); continue; }
		if (a != 'a' && a != 'w' && a != 's' && a != 'd' && a != 'z') { a = _getch(); continue; }//如果不是wasd以及撤回的按键z则读取下一个操作并忽略
		if (a == 'w')//前进
		{
			//if (A[y - 1][x] == '*') { a = _getch(); continue; }//理论上来讲这句没有意义
			if (A[y - 1][x] == ' ' || A[y - 1][x] == '&')//前方空旷，可以走
			{
				mapmemory(ylength, x, y);//先对当前地图存档
				y--;//将坐标向上移动一格
				if (isTargetPoint(x, y + 1))  { A[y + 1][x] = '&'; }//如果玩家刚刚踩在目标点上，则需要将原位置变回目标点的标记
				else { A[y + 1][x] = ' '; }
				A[y][x] = '#';//更新玩家位置
				refreshmap(ylength);//输出当前更新后的地图
			}
			else if (A[y - 1][x] == '@')//如果前面是箱子
			{
				//if (A[y - 2][x] == '*') { a = _getch(); continue; }//理论上来讲这句没有意义
				if (A[y - 2][x] == ' ' || A[y - 2][x] == '&') //更前方空旷，可以推动
				{
					mapmemory(ylength, x, y);//存档
					y--;//坐标向上移动一格
					A[y - 1][x] = '@';//将箱子推过去
					A[y][x] = '#';//更新玩家位置
					if (isTargetPoint(x, y + 1)) { A[y + 1][x] = '&'; }//如果玩家刚刚踩在目标点上，则需要将原位置变回目标点的标记
					else { A[y + 1][x] = ' '; }
				}
				refreshmap(ylength);//输出当前更新后的地图
				if (isWinPushbox()) { break; }//判断推箱子有没有赢（只需要在推动箱子的时候判断，走着是不可能突然就赢了的）
			}
			
		}
		if (a == 's')//请参考a=='w'时的注释
		{
			if (A[y + 1][x] == '*') { a = _getch(); continue; }
			if (A[y + 1][x] == ' '|| A[y + 1][x] == '&')
			{
				mapmemory(ylength, x, y);
				y++;
				if (isTargetPoint(x, y - 1)) { A[y - 1][x] = '&'; }
				else { A[y - 1][x] = ' '; }
				A[y][x] = '#';
				refreshmap(ylength);
			}
			else if (A[y + 1][x] == '@')
			{
				if (A[y + 2][x] == '*') { a = _getch(); continue; }
				if (A[y + 2][x] == ' '|| A[y + 2][x] == '&')
				{
					mapmemory(ylength, x, y);
					y++;
					A[y + 1][x] = '@';
					A[y][x] = '#';
					if (isTargetPoint(x, y - 1)) { A[y - 1][x] = '&'; }
					else { A[y - 1][x] = ' '; }
				}
				refreshmap(ylength);
				if (isWinPushbox()) { break; }
			}
		}
		if (a == 'a')//请参考a=='w'时的注释
		{
			if (A[y][x - 1] == '*') { a = _getch(); continue; }
			if (A[y][x - 1] == ' ' || A[y][x - 1] == '&') 
			{
				mapmemory(ylength, x, y);
				x--;
				if (isTargetPoint(x + 1, y)) { A[y][x + 1] = '&'; }
				else { A[y][x + 1] = ' '; }
				A[y][x] = '#';
				refreshmap(ylength);
			}
			else if (A[y][x - 1] == '@')
			{
				if (A[y][x - 2] == '*') { a = _getch(); continue; }
				if (A[y][x - 2] == ' ' || A[y][x - 2] == '&')
				{
					mapmemory(ylength, x, y);
					x--;
					A[y][x - 1] = '@';
					A[y][x] = '#';
					if (isTargetPoint(x + 1, y)) { A[y][x + 1] = '&'; }
					else { A[y][x + 1] = ' '; }
				}
				refreshmap(ylength);
				if (isWinPushbox()) { break; }
			}
		}
		if (a == 'd')//请参考a=='w'时的注释
		{
			if (A[y][x + 1] == '*') { a = _getch(); continue; }
			if (A[y][x + 1] == ' ' || A[y][x + 1] == '&') 
			{
				mapmemory(ylength, x, y);
				x++;
				if (isTargetPoint(x - 1, y)) { A[y][x - 1] = '&'; }
				else { A[y][x - 1] = ' '; }
				A[y][x] = '#';
				refreshmap(ylength);
			}
			else if (A[y][x + 1] == '@')
			{
				if (A[y][x + 2] == '*') { a = _getch(); continue; }
				if (A[y][x + 2] == ' ' || A[y][x + 2] == '&') 
				{
					mapmemory(ylength, x, y);
					x++;
					A[y][x + 1] = '@';
					A[y][x] = '#';
					if (isTargetPoint(x - 1, y)) { A[y][x - 1] = '&'; }
					else { A[y][x - 1] = ' '; }
				}
				refreshmap(ylength);
				if (isWinPushbox()) { break; }
			}
		}
		if (a == 'z') //撤回到上一步
		{
			readmapmemory(ylength, x, y);//读取存储
			refreshmap(ylength);//刷新当前地图
		}
		if (isMaze && isWinMaze(y))break;//是迷宫且走出去了的情况下获胜
		a = _getch();
	}
	system("cls");//清屏并输出恭喜通关
	cout << "Congratulations! GAME OVER. Press Enter to exit." << endl;
	cin.get();
	cin.get();//防止闪退
end://如果游戏中输入0会直接退出游戏并自动关闭窗口
	return;
}
int main()
{
	gameStart();
}