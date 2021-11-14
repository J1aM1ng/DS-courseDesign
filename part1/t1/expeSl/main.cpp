#include <iostream>
#include <fstream>
#include "skiplist.h"
#include <ctime>
const int A = 1, B = 100000 ,NUM = 10000,OPE=30000,TEST=100000;//OPE:������ɵĲ�����  NUM��������ɵ�������ʼ�������Ԫ�ظ���
using namespace std;
int main()
{
	srand((unsigned)time(NULL));
	ifstream infile_1,infile_2;
	infile_1.open("C:\\Users\\ASUS\\Desktop\\inputNum.txt", ios::in);//�����
	infile_1.open("C:\\Users\\ASUS\\Desktop\\inputOpe.txt", ios::in);//�������
	ofstream outfile;
	outfile.open("C:\\Users\\ASUS\\Desktop\\output.txt", ios::app | ios::out);
	skipList<int, int> sl;

	clock_t start_2 = clock();//��̬������2
	for (int i = 1; i <= NUM; i++)//��NUM��Ԫ�س�ʼ������NUM�β��������  key��valueֵͬ
	{
		int temp;
		infile_1 >> temp;
		pair<const int, int> tempPair(make_pair(temp, temp));
		sl.insert(tempPair);
	}
	clock_t end_2 = clock();
	double t2 = (double)(1000 * (end_2 - start_2) / CLOCKS_PER_SEC)*10;

	clock_t start_1 = clock();//��̬������1
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//�������
		bool tempJudge = sl.find(tn);
	}
	clock_t end_1 = clock();
	double t1 = (double)(1000 * (end_1 - start_1) / CLOCKS_PER_SEC);

	//clock_t start_2 = clock();//��̬������2
	//for (int i = 1; i <= TEST; i++)
	//{
	//	int tn = (rand() % (B - A + 1)) + A;//�������
	//	pair<const int, int> tempPair(make_pair(tn, tn));
	//	sl.insert(tempPair);
	//}
	//clock_t end_2 = clock();
	//double t2 = (double)(1000 * (end_2 - start_2) / CLOCKS_PER_SEC);

	clock_t start_3 = clock();//��̬������3
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//�������
		sl.erase(tn);
	}
	clock_t end_3 = clock();
	double t3 = (double)(1000 * (end_3 - start_3) / CLOCKS_PER_SEC);

	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//�������
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	clock_t start_4 = clock();//��̬������4
	for (int i = 1; i <= TEST; i++)
	{
		pair<const int, int> tempPair = sl.eraseMin();
	}
	clock_t end_4 = clock();
	double t4 = (double)(1000 * (end_4 - start_4) / CLOCKS_PER_SEC);

	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//�������
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	clock_t start_5 = clock();//��̬������5
	for (int i = 1; i <= TEST; i++)
	{
		pair<const int, int> tempPair = sl.eraseMax();
	}
	clock_t end_5 = clock();
	double t5 = (double)(1000 * (end_5 - start_5) / CLOCKS_PER_SEC);

	clock_t start_6 = clock();//��̬������6
	for (int i = 1; i <= TEST; i++)
	{
		int tempXor = sl.allXor();
	}
	clock_t end_6 = clock();
	double t6 = (double)(1000 * (end_6 - start_6) / CLOCKS_PER_SEC);


	for (int i = 1; i < OPE; i++)//OPE������(��������)
	{
		int temp, num;
		infile_2 >> temp;
		if (temp == 1 || temp == 2 || temp == 3)infile_2 >> num;//����

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

	start_1 = clock();//ĩ̬������1
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//�������
		bool tempJudge = sl.find(tn);
	}
	end_1 = clock();
	double tt1 = (double)(1000 * (end_1 - start_1) / CLOCKS_PER_SEC);

	start_2 = clock();//ĩ̬������2
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//�������
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	 end_2 = clock();
	double tt2 = (double)(1000 * (end_2 - start_2) / CLOCKS_PER_SEC);

	 start_3 = clock();//ĩ̬������3
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//�������
		sl.erase(tn);
	}
	end_3 = clock();
	double tt3 = (double)(1000 * (end_3 - start_3) / CLOCKS_PER_SEC);

	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//�������
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	 start_4 = clock();//ĩ̬������4
	for (int i = 1; i <= TEST; i++)
	{
		pair<const int, int> tempPair = sl.eraseMin();
	}
	 end_4 = clock();
	double tt4 = (double)(1000 * (end_4 - start_4) / CLOCKS_PER_SEC);

	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//�������
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	 start_5 = clock();//ĩ̬������5
	for (int i = 1; i <= TEST; i++)
	{
		pair<const int, int> tempPair = sl.eraseMax();
	}
	 end_5 = clock();
	double tt5 = (double)(1000 * (end_5 - start_5) / CLOCKS_PER_SEC);

	 start_6 = clock();//ĩ̬������6
	for (int i = 1; i <= TEST; i++)
	{
		int tempXor = sl.allXor();
	}
	 end_6 = clock();
	double tt6 = (double)(1000 * (end_6 - start_6) / CLOCKS_PER_SEC);

	for (int i = 1; i <= 1; i++)
	{
		cout << "��̬����1ʱ��Ϊ��" << t1 << "ms" << '\n';
		cout << "ĩ̬����1ʱ��Ϊ��" << tt1 << "ms" << '\n';

		cout << "��̬����2ʱ��Ϊ��" << t2 << "ms" << '\n';
		cout << "ĩ̬����2ʱ��Ϊ��" << tt2 << "ms" << '\n';

		cout << "��̬����3ʱ��Ϊ��" << t3 << "ms" << '\n';
		cout << "ĩ̬����3ʱ��Ϊ��" << tt3 << "ms" << '\n';

		cout << "��̬����4ʱ��Ϊ��" << t4 << "ms" << '\n';
		cout << "ĩ̬����4ʱ��Ϊ��" << tt4 << "ms" << '\n';

		cout << "��̬����5ʱ��Ϊ��" << t5 << "ms" << '\n';
		cout << "ĩ̬����5ʱ��Ϊ��" << tt5 << "ms" << '\n';

		cout << "��̬����6ʱ��Ϊ��" << t6 << "ms" << '\n';
		cout << "ĩ̬����6ʱ��Ϊ��" << tt6 << "ms" << '\n';
	}

	infile_1.close();//�ر��ļ�
	infile_2.close();
	outfile.close();
	return 0;
}
