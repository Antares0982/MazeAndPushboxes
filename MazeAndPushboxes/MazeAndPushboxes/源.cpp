#include<iostream>
#include<string>
#include<conio.h>
#include<vector>
#include<array>
using namespace std;
string* A = new string[30];//�洢��Ϸ��ͼ
int* xx;
int* yy;//���������������洢�����ӵ�Ŀ�������
int TargetNum = 0;//�洢������Ŀ���һ���ж��ٸ�
bool isMaze = true;//��Ϸģʽ�����Թ���Ϊtrue����������Ϊfalse
vector<int> beforex;
vector<int> beforey;//������vector���ڴ洢ǰʮ����λ�ã����ڻص�
vector<string> beforemap;//�洢ǰʮ���ĵ�ͼ�����ڻص�

bool isTargetPoint(int x, int y)//�жϵ�ǰ��λ���Ƿ񱻴洢��Ŀ���������
{
	for (int i = 0; i < TargetNum; i++)
	{
		if (x == xx[i] && y == yy[i]) { return true; }
	}
	return false;
}
bool isWinMaze(int y)//����Թ��ߵ��׾���Ӯ
{
	if (y == 0)return true;
	else return false;
}
bool isWinPushbox()//ѭ���ж�����Ŀ����Ƿ��Ѿ�������ռ��
{
	for (int i = 0; i < TargetNum; i++)
	{
		if (A[yy[i]][xx[i]] != '@')return false;
	}
	return true;
}
void mapmemory(int length, int x, int y)//���䵱ǰ�ĵ�ͼ�Լ��������
{
	if (beforemap.size() >= 10 * length)//����洢��Ŀ����10������ɾ��֮ǰ��10���ĵ�ͼ
	{
		for (int i = 0; i < beforemap.size() - length; i++)
		{
			beforemap[i] = beforemap[i + length];
		}
		for (int i = 0; i < length; i++) { beforemap.pop_back(); }
	}
	for (int i = 0; i < length; i++)//д�뵱ǰ�ĵ�ͼ
	{
		beforemap.push_back(A[i]);
	}
	if (beforex.size() >= 10)//ͬ��ɾ��֮ǰ������
	{
		for (int i = 0; i < 9; i++)
		{
			beforex[i] = beforex[i + 1];
			beforey[i] = beforey[i + 1];
		}
		beforex.pop_back();
		beforey.pop_back();
	}
	beforex.push_back(x);//д���µ�����
	beforey.push_back(y);
}
void readmapmemory(int length, int& x, int& y) //��ȡ֮ǰ�ĵ�ͼ�����꣬Ҳ���ǻص�
{
	if (beforex.size() == 0)return;//û�д洢�������ܻص�
	x = beforex[beforex.size() - 1];//��ȡ��һ���浵λ��
	beforex.pop_back();//ɾ���浵
	y = beforey[beforey.size() - 1];//ͬ��
	beforey.pop_back();
	for (int i = length - 1; i >= 0; i--) //��ȡ��ͼ����ɾ���浵
	{
		A[i] = beforemap[beforemap.size() - 1];
		beforemap.pop_back();
	}
}
int* initializeMaze() //��ʼ���Թ�������ֵ��p[0]�ǵ�ͼ���ȣ�p[1]����ҳ�ʼλ��x�ᣬp[2]��y��
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
int* initializePushBox1()//��ʼ�������ӵ�ͼ������ֵ��p[0]�ǵ�ͼ���ȣ�p[1]����ҳ�ʼλ��x�ᣬp[2]��y�ᡣͬʱ��Ҫ��ʼ��Ŀ������������
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
int* initializePushBox2()//ͬ��
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
void refreshmap(int ylength)//ˢ�µ�ͼ
{
	system("cls");//�����Ļ
	for (int i = 0; i < ylength; i++)//�����ͼ
	{
		cout << A[i] << endl;
	}
}
void gameStart()//��ʼ��Ϸ�����������������
{
	int ylength = -1;//ylength�ǵ�ͼ����
	int x = -1, y = -1;//���������x,y��ʾ
	int* p;//p�������ڶ�ȡ��ͼ��ʼ���ķ���ֵ
	p = new int[1];
	*p = 1;
tag1://��Ϸģʽѡ��������᷵������
	system("cls");
	cout << "choose game mode. Please input Maze or Pushbox." << endl;
	string input;
	cin >> input;
	system("cls");
	if (input.find("Maze") != string::npos || input.find("maze") != string::npos) //���ѡ�����Թ�
	{
		p = initializeMaze(); ylength = p[0]; x = p[1]; y = p[2]; 
	}
	else if (input.find("Pushbox") != string::npos || input.find("pushbox") != string::npos)//���ѡ����������
	{
	tag2://��ͼѡ��������᷵������
		system("cls");
		cout << "Choose map:\nMap 1\nMap 2" << endl;
		cin >> input;
		if (input.find("1") != string::npos) { delete[] p; p = initializePushBox1(); }//ѡ���ͼ1
		else if (input.find("2") != string::npos) { delete[] p; p = initializePushBox2(); }//ѡ���ͼ2
		//������������ĵ�ͼ��ʼ������
		else goto tag2;//����������ͼ֮һ���򷵻����沢����ִ��
		ylength = p[0]; x = p[1]; y = p[2];//��ȡ��ʼ����ͼ�õ��ĵ�ͼ���ȼ����֮꣬��ɾ����ʱָ��p
		system("cls");
		delete[] p;
	}
	else goto tag1;//��ѡ���Թ�Ҳ��ѡ�������ӣ�����ѡһ��
	cout << "Press z to revoke at most 10 moves. Press 0 to end the game while in the game! Now press any key to start.";
	char a;
	a = _getch();//���������ʼ��������Ϊ����ʾ����cout����ʾ
	system("cls");//��������ʼ�����ͼ
	for (int i = 0; i < ylength; i++)
	{
		cout << A[i] << endl;
	}
	a=_getch();//��ȡ���µİ���
	int xlength = A[0].length();
	while (true)//��ʤ�ͻ��whileѭ��������
	{
		if (a == '0')  { goto end; }//����0����Ϸ������ֱ�ӹرմ���
		if (y == ylength - 1 && (a == 'a' || a == 's' || a == 'd'))  { a = _getch(); continue; }//�ڱ�Ե��������������������ֹ���
		if (y == 0 && (a == 'a' || a == 'w' || a == 'd')) { a = _getch(); continue; }
		if (x == 0 && (a == 'a' || a == 's' || a == 'w')) { a = _getch(); continue; }
		if (x == xlength - 1 && (a == 'd' || a == 's' || a == 'w')) { a = _getch(); continue; }
		if (a != 'a' && a != 'w' && a != 's' && a != 'd' && a != 'z') { a = _getch(); continue; }//�������wasd�Լ����صİ���z���ȡ��һ������������
		if (a == 'w')//ǰ��
		{
			//if (A[y - 1][x] == '*') { a = _getch(); continue; }//�������������û������
			if (A[y - 1][x] == ' ' || A[y - 1][x] == '&')//ǰ���տ���������
			{
				mapmemory(ylength, x, y);//�ȶԵ�ǰ��ͼ�浵
				y--;//�����������ƶ�һ��
				if (isTargetPoint(x, y + 1))  { A[y + 1][x] = '&'; }//�����Ҹող���Ŀ����ϣ�����Ҫ��ԭλ�ñ��Ŀ���ı��
				else { A[y + 1][x] = ' '; }
				A[y][x] = '#';//�������λ��
				refreshmap(ylength);//�����ǰ���º�ĵ�ͼ
			}
			else if (A[y - 1][x] == '@')//���ǰ��������
			{
				//if (A[y - 2][x] == '*') { a = _getch(); continue; }//�������������û������
				if (A[y - 2][x] == ' ' || A[y - 2][x] == '&') //��ǰ���տ��������ƶ�
				{
					mapmemory(ylength, x, y);//�浵
					y--;//���������ƶ�һ��
					A[y - 1][x] = '@';//�������ƹ�ȥ
					A[y][x] = '#';//�������λ��
					if (isTargetPoint(x, y + 1)) { A[y + 1][x] = '&'; }//�����Ҹող���Ŀ����ϣ�����Ҫ��ԭλ�ñ��Ŀ���ı��
					else { A[y + 1][x] = ' '; }
				}
				refreshmap(ylength);//�����ǰ���º�ĵ�ͼ
				if (isWinPushbox()) { break; }//�ж���������û��Ӯ��ֻ��Ҫ���ƶ����ӵ�ʱ���жϣ������ǲ�����ͻȻ��Ӯ�˵ģ�
			}
			
		}
		if (a == 's')//��ο�a=='w'ʱ��ע��
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
		if (a == 'a')//��ο�a=='w'ʱ��ע��
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
		if (a == 'd')//��ο�a=='w'ʱ��ע��
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
		if (a == 'z') //���ص���һ��
		{
			readmapmemory(ylength, x, y);//��ȡ�洢
			refreshmap(ylength);//ˢ�µ�ǰ��ͼ
		}
		if (isMaze && isWinMaze(y))break;//���Թ����߳�ȥ�˵�����»�ʤ
		a = _getch();
	}
	system("cls");//�����������ϲͨ��
	cout << "Congratulations! GAME OVER. Press Enter to exit." << endl;
	cin.get();
	cin.get();//��ֹ����
end://�����Ϸ������0��ֱ���˳���Ϸ���Զ��رմ���
	return;
}
int main()
{
	gameStart();
}