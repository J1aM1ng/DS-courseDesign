#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
const int A = 1, B = 100000,NUM=1000,OPE=3000;//�˴�NUMΪ����NUM��1/10,OPE��Ȼ
//********��Ҫ����10��rand�ſ��Խ���ʵ��*************
using namespace std;
int main()
{
	srand((unsigned)time(NULL)*10);
	ofstream outfile_1,outfile_2;
	outfile_1.open("C:\\Users\\ASUS\\Desktop\\inputNum.txt", ios::app | ios::out);
	outfile_2.open("C:\\Users\\ASUS\\Desktop\\inputOpe.txt", ios::app | ios::out);
	for (int i = 1; i <= NUM; i++)//����NUM����������ڳ�ʼ������
	{
		outfile_1 << ((rand() % (B - A + 1)) + A)<<'\n';//ȡ��[A,B]�����������
	}
	int jud1 = OPE / 3,jud2=2*jud1;
	for (int i = 1; i <= OPE; i++)//����OPE���������У�**�����ɾ��������1��1(�������ɲ����ɾ������ռ�ܲ�������1/3��**
	{
		if (i <= jud1)//���ɲ������
		{
			int tempNum = 2;
			int temp = (rand() % (B - A + 1)) + A;//���������
			outfile_2 << tempNum << " " << temp << '\n';
		}
		else if (i > jud1&&i <= jud2)//����ɾ������
		{
			int tempNum = (rand() % (5 - 3 + 1)) + 3;//���������
			if (tempNum == 3)
			{
				int temp = (rand() % (B - A + 1)) + A;//���������
				outfile_2 << tempNum << " " << temp << '\n';
			}
			else if (tempNum == 4 || tempNum == 5)outfile_2 << tempNum<<'\n';
		}
		else//���ɲ���1��6
		{
			int tempNum;
			int tt = rand() % (1 - 0 + 1) + 0;
			if (tt <= 0.5)
			{
				tempNum = 1;
				int temp = (rand() % (B - A + 1)) + A;//���������
				outfile_2 << tempNum << " " << temp << '\n';
			}
			else
			{
				tempNum = 6;
				outfile_2 << tempNum << '\n';
			}
			
		}
	}
	outfile_1.close();
	outfile_2.close();
	return 0;
}