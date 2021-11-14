#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
const int A = 1, B = 100000,NUM=1000,OPE=3000;//此处NUM为所需NUM的1/10,OPE亦然
//********需要运行10次rand才可以进行实验*************
using namespace std;
int main()
{
	srand((unsigned)time(NULL)*10);
	ofstream outfile_1,outfile_2;
	outfile_1.open("C:\\Users\\ASUS\\Desktop\\inputNum.txt", ios::app | ios::out);
	outfile_2.open("C:\\Users\\ASUS\\Desktop\\inputOpe.txt", ios::app | ios::out);
	for (int i = 1; i <= NUM; i++)//生成NUM个随机数用于初始化跳表
	{
		outfile_1 << ((rand() % (B - A + 1)) + A)<<'\n';//取得[A,B]区间内随机数
	}
	int jud1 = OPE / 3,jud2=2*jud1;
	for (int i = 1; i <= OPE; i++)//生成OPE条操作序列，**插入和删除必须是1：1(首先生成插入和删除，各占总操作数的1/3）**
	{
		if (i <= jud1)//生成插入操作
		{
			int tempNum = 2;
			int temp = (rand() % (B - A + 1)) + A;//生成随机数
			outfile_2 << tempNum << " " << temp << '\n';
		}
		else if (i > jud1&&i <= jud2)//生成删除操作
		{
			int tempNum = (rand() % (5 - 3 + 1)) + 3;//生成随机数
			if (tempNum == 3)
			{
				int temp = (rand() % (B - A + 1)) + A;//生成随机数
				outfile_2 << tempNum << " " << temp << '\n';
			}
			else if (tempNum == 4 || tempNum == 5)outfile_2 << tempNum<<'\n';
		}
		else//生成操作1或6
		{
			int tempNum;
			int tt = rand() % (1 - 0 + 1) + 0;
			if (tt <= 0.5)
			{
				tempNum = 1;
				int temp = (rand() % (B - A + 1)) + A;//生成随机数
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