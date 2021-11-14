#include <iostream>
#include <fstream>
#include "skiplist.h"
#include <ctime>
const int A = 1, B = 100000 ,NUM = 10000,OPE=30000,TEST=100000;//OPE:随机生成的操作数  NUM：随机生成的用来初始化跳表的元素个数
using namespace std;
int main()
{
	srand((unsigned)time(NULL));
	ifstream infile_1,infile_2;
	infile_1.open("C:\\Users\\ASUS\\Desktop\\inputNum.txt", ios::in);//随机数
	infile_1.open("C:\\Users\\ASUS\\Desktop\\inputOpe.txt", ios::in);//随机操作
	ofstream outfile;
	outfile.open("C:\\Users\\ASUS\\Desktop\\output.txt", ios::app | ios::out);
	skipList<int, int> sl;

	clock_t start_2 = clock();//初态：操作2
	for (int i = 1; i <= NUM; i++)//用NUM个元素初始化跳表（NUM次插入操作）  key和value同值
	{
		int temp;
		infile_1 >> temp;
		pair<const int, int> tempPair(make_pair(temp, temp));
		sl.insert(tempPair);
	}
	clock_t end_2 = clock();
	double t2 = (double)(1000 * (end_2 - start_2) / CLOCKS_PER_SEC)*10;

	clock_t start_1 = clock();//初态：操作1
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//随机生成
		bool tempJudge = sl.find(tn);
	}
	clock_t end_1 = clock();
	double t1 = (double)(1000 * (end_1 - start_1) / CLOCKS_PER_SEC);

	//clock_t start_2 = clock();//初态：操作2
	//for (int i = 1; i <= TEST; i++)
	//{
	//	int tn = (rand() % (B - A + 1)) + A;//随机生成
	//	pair<const int, int> tempPair(make_pair(tn, tn));
	//	sl.insert(tempPair);
	//}
	//clock_t end_2 = clock();
	//double t2 = (double)(1000 * (end_2 - start_2) / CLOCKS_PER_SEC);

	clock_t start_3 = clock();//初态：操作3
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//随机生成
		sl.erase(tn);
	}
	clock_t end_3 = clock();
	double t3 = (double)(1000 * (end_3 - start_3) / CLOCKS_PER_SEC);

	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//随机生成
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	clock_t start_4 = clock();//初态：操作4
	for (int i = 1; i <= TEST; i++)
	{
		pair<const int, int> tempPair = sl.eraseMin();
	}
	clock_t end_4 = clock();
	double t4 = (double)(1000 * (end_4 - start_4) / CLOCKS_PER_SEC);

	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//随机生成
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	clock_t start_5 = clock();//初态：操作5
	for (int i = 1; i <= TEST; i++)
	{
		pair<const int, int> tempPair = sl.eraseMax();
	}
	clock_t end_5 = clock();
	double t5 = (double)(1000 * (end_5 - start_5) / CLOCKS_PER_SEC);

	clock_t start_6 = clock();//初态：操作6
	for (int i = 1; i <= TEST; i++)
	{
		int tempXor = sl.allXor();
	}
	clock_t end_6 = clock();
	double t6 = (double)(1000 * (end_6 - start_6) / CLOCKS_PER_SEC);


	for (int i = 1; i < OPE; i++)//OPE个操作(大量操作)
	{
		int temp, num;
		infile_2 >> temp;
		if (temp == 1 || temp == 2 || temp == 3)infile_2 >> num;//输入

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

	start_1 = clock();//末态：操作1
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//随机生成
		bool tempJudge = sl.find(tn);
	}
	end_1 = clock();
	double tt1 = (double)(1000 * (end_1 - start_1) / CLOCKS_PER_SEC);

	start_2 = clock();//末态：操作2
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//随机生成
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	 end_2 = clock();
	double tt2 = (double)(1000 * (end_2 - start_2) / CLOCKS_PER_SEC);

	 start_3 = clock();//末态：操作3
	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//随机生成
		sl.erase(tn);
	}
	end_3 = clock();
	double tt3 = (double)(1000 * (end_3 - start_3) / CLOCKS_PER_SEC);

	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//随机生成
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	 start_4 = clock();//末态：操作4
	for (int i = 1; i <= TEST; i++)
	{
		pair<const int, int> tempPair = sl.eraseMin();
	}
	 end_4 = clock();
	double tt4 = (double)(1000 * (end_4 - start_4) / CLOCKS_PER_SEC);

	for (int i = 1; i <= TEST; i++)
	{
		int tn = (rand() % (B - A + 1)) + A;//随机生成
		pair<const int, int> tempPair(make_pair(tn, tn));
		sl.insert(tempPair);
	}
	 start_5 = clock();//末态：操作5
	for (int i = 1; i <= TEST; i++)
	{
		pair<const int, int> tempPair = sl.eraseMax();
	}
	 end_5 = clock();
	double tt5 = (double)(1000 * (end_5 - start_5) / CLOCKS_PER_SEC);

	 start_6 = clock();//末态：操作6
	for (int i = 1; i <= TEST; i++)
	{
		int tempXor = sl.allXor();
	}
	 end_6 = clock();
	double tt6 = (double)(1000 * (end_6 - start_6) / CLOCKS_PER_SEC);

	for (int i = 1; i <= 1; i++)
	{
		cout << "初态操作1时间为：" << t1 << "ms" << '\n';
		cout << "末态操作1时间为：" << tt1 << "ms" << '\n';

		cout << "初态操作2时间为：" << t2 << "ms" << '\n';
		cout << "末态操作2时间为：" << tt2 << "ms" << '\n';

		cout << "初态操作3时间为：" << t3 << "ms" << '\n';
		cout << "末态操作3时间为：" << tt3 << "ms" << '\n';

		cout << "初态操作4时间为：" << t4 << "ms" << '\n';
		cout << "末态操作4时间为：" << tt4 << "ms" << '\n';

		cout << "初态操作5时间为：" << t5 << "ms" << '\n';
		cout << "末态操作5时间为：" << tt5 << "ms" << '\n';

		cout << "初态操作6时间为：" << t6 << "ms" << '\n';
		cout << "末态操作6时间为：" << tt6 << "ms" << '\n';
	}

	infile_1.close();//关闭文件
	infile_2.close();
	outfile.close();
	return 0;
}
