#include <iostream>
#include <fstream>
#include "skiplist.h"
using namespace std;
int main()
{
	ifstream infile;
	infile.open("C:\\Users\\ASUS\\Desktop\\SkipListData\\non-duplicate\\input\\hhh.txt",ios::in);
	ofstream outfile;
	outfile.open("C:\\Users\\ASUS\\Desktop\\output.txt",ios::app|ios::out);
	if (infile.is_open() && outfile.is_open())
	{
		int N, M;//N������������N-1) & M����ʼ��������
		infile >> N >> M;
		skipList<int, int> sl;
		for (int i = 1; i <= M; i++)//��M��Ԫ�س�ʼ������M�β��������  key��valueֵͬ
		{
			int temp;
			infile >> temp;
			pair<const int, int> tempPair(make_pair(temp, temp));
			sl.insert(tempPair);
		}
		for (int i = 1; i < N; i++)//N-1������
		{
			int temp, num;
			infile >> temp;
			if (temp == 1 || temp == 2 || temp == 3)infile >> num;//����

			if (temp == 1)
			{
				bool tempJudge = sl.find(num);
				if (tempJudge)outfile << "YES" << '\n';
				else outfile << "NO" << '\n';
			}
			else if (temp == 2)
			{
				pair<const int, int> tempPair(make_pair(num, num));
				sl.insert(tempPair);
			}
			else if (temp == 3)
			{
				sl.erase(num);
			}
			else if (temp == 4)
			{
				pair<const int, int> tempPair = sl.eraseMin();
				if (tempPair.first != (-1))
					outfile << tempPair.first << '\n';
			}
			else if (temp == 5)
			{
				pair<const int, int> tempPair = sl.eraseMax();
				if (tempPair.first != (-1))
					outfile << tempPair.first << '\n';
			}
			else if (temp == 6)
			{
				int tempXor = sl.allXor();
				if (tempXor != inf)
					outfile << tempXor << '\n';
			}
		}
		infile.close();//�ر��ļ�
		outfile.close();
	}
	else
	{
		cerr << "fail to open file" << '\n';
		exit(0);
	}
	return 0;
}