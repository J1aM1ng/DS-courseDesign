#include<bits/stdc++.h>
#include"LoserTree.h"
using namespace std;
const int INF = 0x3f3f3f3f;
int totalPlayer[100000010], readPoint[100000010];//totalPlayer[]:总的数据元素(全部选手） 将i对应的输入流指针（文件“读”指针，指向当前文件读到的位置）储存到readPoint[]中
long i = 10000000L;
clock_t start, theEnd;//计时
double  timeInteval;
string output_name;//输出文件的名称
ofstream outfile;//输出最后结果到 output_name

ele s_player[100000010];//s_player[]:用于顺串归并的最小输者树（中的元素）

template <class T> 
void LoserTree<T>::Init(T* ele, int num) {//输入player数组（包含所有元素），元素数量（对树进行初始化）
	int n = num;
	player = ele;//使player与ele同指向，初始化输者树成员
	playerNumber = n;//初始化输者树成员数目playerNumber
	delete[] Node;
	delete[] branch;
	Node = new int[n + 1];//重新分配内存
	branch = new int[n + 1];//重新分配内存
	int tmp = 0;
	int s = 1;
	while (s * 2 <= n - 1) {//计算s（除最底层以外的节点数），由于最小输者树是完全二叉树，故除最底层以外均满
		s = s * 2;
	}
	
	LowExt = 2 * (n - s);
	offset = 2 * s - 1;
	for (int i = 2; i <= LowExt; i += 2) {//完成整个树的比赛
		int x = (i + offset) / 2;//父节点
		Compete(x, i - 1, i);//父节点，左孩子，右孩子，通过一次比赛将输者存入父节点
	}
	
	if (n % 2 == 1) {//n为奇数最后剩余一个点
		Compete(n / 2, branch[n - 1], LowExt + 1);
		tmp = LowExt + 3;
	}
	else {//n为偶数
		tmp = LowExt + 2;
	}
	for (int i = tmp; i <= n; i += 2) {
		Compete((i - LowExt + n - 1) / 2, i - 1, i);//比较从1开始，空出下标为0位置
	}
	Node[0] = branch[1];//tree[0]记录该最小输者树的最后胜者
}
template <class T> 
void LoserTree<T>::Compete(int p, int l, int r) {//父节点，左孩子，右孩子
	Node[p] = Lose(l, r);//该场比赛的败者存入内部节点数组Node[]
	branch[p] = Win(l, r);//该场比赛的胜者存入边数组branch[]
	while (p > 1 && p % 2 == 1) {//父节点为奇数 更新上一层
		Node[p / 2] = Lose(branch[p - 1], branch[p]);
		branch[p / 2] = Win(branch[p - 1], branch[p]);
		p /= 2;//更新当前层前面的节点
	}
}
template <class T> 
void LoserTree<T>::Rebuild(int p, T val) {//重构树,输入参赛者（原参赛者，即新参赛者要接替的原参赛者）的编号p、新的元素值val
	int n = this->playerNumber;
	if (p <= 0 || p > n) {//p必须在指定范围内[1,n]
		cerr << "输入错误" << '\n';
		return;
	}
	
	player[p] = val;
	int match_num, l, r;//match_num:需要重新比赛的场次
	if (p <= LowExt) {//选手在最底层
		match_num = (p + offset) / 2;//需要重新比赛的场次
		l = 2 * match_num - offset;//参与比赛的左孩子
		r = l + 1;//右孩子
	}
	else {//选手不在最底层
		match_num = (p - LowExt + playerNumber - 1) / 2;
		if (2 * match_num != playerNumber - 1) {//不在最底层且不与最底层第一个选手比赛
			l = 2 * match_num - playerNumber + 1 + LowExt;
			r = l + 1;
		}
		else {//不在最底层且与最底层第一个选手比赛
			l = branch[2 * match_num];
			r = p;
		}
	}
	if (p == Node[0]) {//如果这个选手是最终胜利者
		while (match_num >= 1) {
			int theloser = Node[match_num];//上一场比赛的失败者
			Node[match_num] = Lose(theloser, p);//更新这个失败者的下标
			branch[match_num] = Win(theloser, p);//更新晋级者下标
			p = branch[match_num];
			match_num /= 2;
		}
	}
	else {//如果这个选手不是最终胜利者，则更新失败者，晋级者
		Node[match_num] = Lose(l, r);
		branch[match_num] = Win(l, r);
		
		if (match_num == playerNumber - 1 && playerNumber % 2 == 1) {//最后一组比赛 参赛者数量为奇数
			match_num /= 2;//返回上一级
			Node[match_num] = Lose(branch[playerNumber - 1], LowExt + 1);
			branch[match_num] = Win(branch[playerNumber - 1], LowExt + 1);
			//更新失败者与晋级者
		}
		match_num /= 2;
		while (match_num >= 1) {
			Node[match_num] = Lose(branch[match_num * 2], branch[match_num * 2 + 1]);
			branch[match_num] = Win(branch[match_num * 2], branch[match_num * 2 + 1]);
			//更新失败者与晋级者
			match_num /= 2;//返回上一级 直到比赛完毕
		}
	}
	Node[0] = branch[1];//最终胜者
}
void Input(operateFile& oF) {//程序开始，从指定磁盘文件中向内存缓冲区读入所有元素
	cout << "请输入用作输入的磁盘文件名称：" << '\n';
	cin >> oF.fileName;
	oF.frontPath = "C:\\Users\\ASUS\\Desktop\\DS\\";
	oF.completePath = oF.frontPath + oF.fileName;
	cout << "您用作输入的磁盘文件路径为：";
	cout << oF.completePath << '\n';
	cout << "请输入内存缓冲区大小：" << '\n';
	cin >> oF.bufferSize;//缓冲区大小
	ifstream infile;
	infile.open(oF.completePath, ios::in);
	if (!infile) {//打开文件失败
		cerr << "打开文件失败" << '\n';
		exit(0);
	}
	infile >> oF.n;//n:磁盘文件中元素（数字）个数
	cout << '\n';
	start = clock();//程序开始，运行时钟
}
void primeString(operateFile& oF, ele* s_player)//通过最小输者树产生一些初始的顺串
{
	cout << "正在用所有数据元素通过最小输者树在内存缓冲区中排序生成顺串..." << '\n';
	ifstream infile;
	infile.open(oF.completePath, ios::in);
	int x;
	infile >> x;
	for (int i = 1; i <= oF.bufferSize; i++) {//基于给定的缓冲区大小
		infile >> s_player[i].key;//元素值
		s_player[i].id = 1;//顺串初始编号为1
		oF.visitNum++;//访问次数+1
	}
	LoserTree<ele> ss(s_player, oF.bufferSize);//建立最小输者树对象 (包含oF.m个ele对象)
	int num = 0;
	for (int i = 1; i <= oF.n; i++) {//从输入文件中取出元素，放入最小输者树
		if (!(infile >> num)) {//读入完毕后，将num置为最小值
			num = INT_MIN;
		}
		ele tw = s_player[ss.Node[0]];//将tw初始化为最小输者树的胜利者
		ele t;

		//顺串的生成规则
		t.key = num;//t的key初始化为num
		if (num >= tw.key) {//如果读入数值更大
			t.id = tw.id;//更新id为胜者id
		}
		else {//如果有更小的数值
			if (num == INT_MIN) {//如果读入结束
				num = INT_MAX;
			}
			else {//否则num存储下一个分区编号
				num = tw.id + 1;
			}
			t.id = num;//更新编号
		}
		ss.Rebuild(ss.Node[0], t);//更新胜者为读入的数值 重构输者树
		string fname = oF.frontPath + oF.fileName + "-file" + to_string(tw.id) + ".txt";//分区文件（即顺串）名称
		oF.sequenceNumber = max(oF.sequenceNumber, tw.id);
		ofstream tempout(fname, ios::app);//在该分区文件（即顺串）下添加数值
		tempout << tw.key << ' ';//将最终胜利者输出到分区文件（即顺串）下
		tempout.close();
		++oF.visitNum;//访问次数+1
	}
	infile.close();
	cout << "顺串生成完成，生成" << oF.sequenceNumber << "个文件（初始顺串）" << '\n';
	char c;
	c = 'n';
	if (c == 'y') {
		cout << "正在加载文件" << '\n';
		for (int i = 1; i <= oF.sequenceNumber; i++)
		{
			string fname = oF.frontPath + oF.fileName + "-file" + to_string(i) + ".txt";
			ifstream tempin(fname);
			cout << "file" << i << ".txt: " << '\n';
			while (tempin >> x) {
				cout << x << ' ';
			}
			cout << '\n';
			tempin.close();
		}
		cout << "输出完成" << '\n';
	}
}
void mergeString(operateFile& oF) {//合并所有分区文件（即通过最小输者树合并所有初始顺串，生成最终排序结果
	cout << "正在合并最终结果..." << '\n';
	output_name = oF.frontPath + "output.txt";
	outfile.open(output_name, ios::out);//打开最终结果要输出到的文件
	int x;
	if (oF.sequenceNumber == 1) {//如果只生成了一个顺串，直接将顺串输出到输出文件中
		string file = oF.frontPath + oF.fileName + "-file" + to_string(1) + ".txt";
		ifstream infile;
		infile.open(file, ios::in);
		while (infile >> x) {
			outfile << x << ' ';
			oF.visitNum += 2;
		}
		outfile.close();
		infile.close();
		exit(0);//退出程序
	}
	for (int i = 1; i <= oF.sequenceNumber; i++) {//生成了多个顺串
		string file = oF.frontPath + oF.fileName + "-file" + to_string(i) + ".txt";//分区文件名称
		ifstream infile;
		infile.open(file, ios::in);//打开各个分区文件
		infile >> totalPlayer[i];//每个顺串的头数据读入totalPlayer[]数组（实际上对应每次排序的最小输者树的player[]数组）中
								//用最小输者树对这些头数据比赛，赢者排好了，输入磁盘文件中，重构输者树
		readPoint[i] = infile.tellg();//将i对应的输入流指针（文件“读”指针，指向当前文件读到的位置）储存到readPoint[]中
		infile.close();
	}
	LoserTree<int> tr(totalPlayer, oF.sequenceNumber);//最小输者树（用于K路归并的最小输者树）
	for (int i = 1; i <= oF.n; i++) {
		int ii = tr.Node[0];//ii:该输者树的胜者
		int winner = totalPlayer[ii];
		outfile << winner << ' ';//胜利者数值输出到文件（每排好一个数就将其输出到磁盘文件中）
		++oF.visitNum;//访问次数+1
		string file = oF.frontPath + oF.fileName + "-file" + to_string(ii) + ".txt";
		ifstream infile(file);
		infile.clear();//重置输入流的指针
		infile.seekg(readPoint[ii] + (long long)1);//输入流指针移动到胜利者所在顺串的下一个元素
		int num;
		if (readPoint[ii] + 1 == 0) {//输入流位置到达文件最后，输入结束
			num = INT_MAX;//num改为不影响胜利者（元素值小的获胜，故设置为INF）的数
		}
		else {//输入还未结束，进行输入
			infile >> num;
			readPoint[ii] = infile.tellg();//更新ii对应输入流的指针
			if (readPoint[ii] + 1 == 0) {
				num = INT_MAX;
			}
		}
		++oF.visitNum;
		tr.Rebuild(ii, num);//用新元素num替代胜利者，重构最小输者树
		infile.close();
	}
	outfile.close();
	cout << "排序结果已输出到" << oF.frontPath << "output.txt" << "文件中" << '\n';
}
void End(operateFile& oF) {//该函数为“获取结果”函数，执行后统计排序时间，并在UI上进行显示的交互
	while (i--);
	theEnd = clock();//结束时钟
	timeInteval = (double)(theEnd - start) / CLOCKS_PER_SEC;//timeInteval：外排序执行时间
	cout << "程序运行时间为：" << timeInteval << "秒" << '\n';
	cout << '\n';
	cout << "磁盘访问次数为：" << oF.visitNum;
}
int main()
{
	ios::sync_with_stdio(false);
	operateFile oF;//声明磁盘文件对象，该对象用于对磁盘文件进行读/写操作
	Input(oF);//开始程序并计时
	primeString(oF, s_player);//通过最小输者树生成一些初始顺串
	mergeString(oF);//通过最小输者树合并这些顺串，每排好一个元素即将该元素输出到对应磁盘文件中，并用新元素替换该赢者，并重构最小输者树
	End(oF);//结束程序并结束计时
	return 0;
}