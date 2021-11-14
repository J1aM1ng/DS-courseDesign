#include<bits/stdc++.h>
#include"LoserTree.h"
using namespace std;
const int INF = 0x3f3f3f3f;
int totalPlayer[100000010], readPoint[100000010];//totalPlayer[]:�ܵ�����Ԫ��(ȫ��ѡ�֣� ��i��Ӧ��������ָ�루�ļ�������ָ�룬ָ��ǰ�ļ�������λ�ã����浽readPoint[]��
long i = 10000000L;
clock_t start, theEnd;//��ʱ
double  timeInteval;
string output_name;//����ļ�������
ofstream outfile;//���������� output_name

ele s_player[100000010];//s_player[]:����˳���鲢����С���������е�Ԫ�أ�

template <class T> 
void LoserTree<T>::Init(T* ele, int num) {//����player���飨��������Ԫ�أ���Ԫ���������������г�ʼ����
	int n = num;
	player = ele;//ʹplayer��eleָͬ�򣬳�ʼ����������Ա
	playerNumber = n;//��ʼ����������Ա��ĿplayerNumber
	delete[] Node;
	delete[] branch;
	Node = new int[n + 1];//���·����ڴ�
	branch = new int[n + 1];//���·����ڴ�
	int tmp = 0;
	int s = 1;
	while (s * 2 <= n - 1) {//����s������ײ�����Ľڵ�������������С����������ȫ���������ʳ���ײ��������
		s = s * 2;
	}
	
	LowExt = 2 * (n - s);
	offset = 2 * s - 1;
	for (int i = 2; i <= LowExt; i += 2) {//����������ı���
		int x = (i + offset) / 2;//���ڵ�
		Compete(x, i - 1, i);//���ڵ㣬���ӣ��Һ��ӣ�ͨ��һ�α��������ߴ��븸�ڵ�
	}
	
	if (n % 2 == 1) {//nΪ�������ʣ��һ����
		Compete(n / 2, branch[n - 1], LowExt + 1);
		tmp = LowExt + 3;
	}
	else {//nΪż��
		tmp = LowExt + 2;
	}
	for (int i = tmp; i <= n; i += 2) {
		Compete((i - LowExt + n - 1) / 2, i - 1, i);//�Ƚϴ�1��ʼ���ճ��±�Ϊ0λ��
	}
	Node[0] = branch[1];//tree[0]��¼����С�����������ʤ��
}
template <class T> 
void LoserTree<T>::Compete(int p, int l, int r) {//���ڵ㣬���ӣ��Һ���
	Node[p] = Lose(l, r);//�ó������İ��ߴ����ڲ��ڵ�����Node[]
	branch[p] = Win(l, r);//�ó�������ʤ�ߴ��������branch[]
	while (p > 1 && p % 2 == 1) {//���ڵ�Ϊ���� ������һ��
		Node[p / 2] = Lose(branch[p - 1], branch[p]);
		branch[p / 2] = Win(branch[p - 1], branch[p]);
		p /= 2;//���µ�ǰ��ǰ��Ľڵ�
	}
}
template <class T> 
void LoserTree<T>::Rebuild(int p, T val) {//�ع���,��������ߣ�ԭ�����ߣ����²�����Ҫ�����ԭ�����ߣ��ı��p���µ�Ԫ��ֵval
	int n = this->playerNumber;
	if (p <= 0 || p > n) {//p������ָ����Χ��[1,n]
		cerr << "�������" << '\n';
		return;
	}
	
	player[p] = val;
	int match_num, l, r;//match_num:��Ҫ���±����ĳ���
	if (p <= LowExt) {//ѡ������ײ�
		match_num = (p + offset) / 2;//��Ҫ���±����ĳ���
		l = 2 * match_num - offset;//�������������
		r = l + 1;//�Һ���
	}
	else {//ѡ�ֲ�����ײ�
		match_num = (p - LowExt + playerNumber - 1) / 2;
		if (2 * match_num != playerNumber - 1) {//������ײ��Ҳ�����ײ��һ��ѡ�ֱ���
			l = 2 * match_num - playerNumber + 1 + LowExt;
			r = l + 1;
		}
		else {//������ײ�������ײ��һ��ѡ�ֱ���
			l = branch[2 * match_num];
			r = p;
		}
	}
	if (p == Node[0]) {//������ѡ��������ʤ����
		while (match_num >= 1) {
			int theloser = Node[match_num];//��һ��������ʧ����
			Node[match_num] = Lose(theloser, p);//�������ʧ���ߵ��±�
			branch[match_num] = Win(theloser, p);//���½������±�
			p = branch[match_num];
			match_num /= 2;
		}
	}
	else {//������ѡ�ֲ�������ʤ���ߣ������ʧ���ߣ�������
		Node[match_num] = Lose(l, r);
		branch[match_num] = Win(l, r);
		
		if (match_num == playerNumber - 1 && playerNumber % 2 == 1) {//���һ����� ����������Ϊ����
			match_num /= 2;//������һ��
			Node[match_num] = Lose(branch[playerNumber - 1], LowExt + 1);
			branch[match_num] = Win(branch[playerNumber - 1], LowExt + 1);
			//����ʧ�����������
		}
		match_num /= 2;
		while (match_num >= 1) {
			Node[match_num] = Lose(branch[match_num * 2], branch[match_num * 2 + 1]);
			branch[match_num] = Win(branch[match_num * 2], branch[match_num * 2 + 1]);
			//����ʧ�����������
			match_num /= 2;//������һ�� ֱ���������
		}
	}
	Node[0] = branch[1];//����ʤ��
}
void Input(operateFile& oF) {//����ʼ����ָ�������ļ������ڴ滺������������Ԫ��
	cout << "��������������Ĵ����ļ����ƣ�" << '\n';
	cin >> oF.fileName;
	oF.frontPath = "C:\\Users\\ASUS\\Desktop\\DS\\";
	oF.completePath = oF.frontPath + oF.fileName;
	cout << "����������Ĵ����ļ�·��Ϊ��";
	cout << oF.completePath << '\n';
	cout << "�������ڴ滺������С��" << '\n';
	cin >> oF.bufferSize;//��������С
	ifstream infile;
	infile.open(oF.completePath, ios::in);
	if (!infile) {//���ļ�ʧ��
		cerr << "���ļ�ʧ��" << '\n';
		exit(0);
	}
	infile >> oF.n;//n:�����ļ���Ԫ�أ����֣�����
	cout << '\n';
	start = clock();//����ʼ������ʱ��
}
void primeString(operateFile& oF, ele* s_player)//ͨ����С����������һЩ��ʼ��˳��
{
	cout << "��������������Ԫ��ͨ����С���������ڴ滺��������������˳��..." << '\n';
	ifstream infile;
	infile.open(oF.completePath, ios::in);
	int x;
	infile >> x;
	for (int i = 1; i <= oF.bufferSize; i++) {//���ڸ����Ļ�������С
		infile >> s_player[i].key;//Ԫ��ֵ
		s_player[i].id = 1;//˳����ʼ���Ϊ1
		oF.visitNum++;//���ʴ���+1
	}
	LoserTree<ele> ss(s_player, oF.bufferSize);//������С���������� (����oF.m��ele����)
	int num = 0;
	for (int i = 1; i <= oF.n; i++) {//�������ļ���ȡ��Ԫ�أ�������С������
		if (!(infile >> num)) {//������Ϻ󣬽�num��Ϊ��Сֵ
			num = INT_MIN;
		}
		ele tw = s_player[ss.Node[0]];//��tw��ʼ��Ϊ��С��������ʤ����
		ele t;

		//˳�������ɹ���
		t.key = num;//t��key��ʼ��Ϊnum
		if (num >= tw.key) {//���������ֵ����
			t.id = tw.id;//����idΪʤ��id
		}
		else {//����и�С����ֵ
			if (num == INT_MIN) {//����������
				num = INT_MAX;
			}
			else {//����num�洢��һ���������
				num = tw.id + 1;
			}
			t.id = num;//���±��
		}
		ss.Rebuild(ss.Node[0], t);//����ʤ��Ϊ�������ֵ �ع�������
		string fname = oF.frontPath + oF.fileName + "-file" + to_string(tw.id) + ".txt";//�����ļ�����˳��������
		oF.sequenceNumber = max(oF.sequenceNumber, tw.id);
		ofstream tempout(fname, ios::app);//�ڸ÷����ļ�����˳�����������ֵ
		tempout << tw.key << ' ';//������ʤ��������������ļ�����˳������
		tempout.close();
		++oF.visitNum;//���ʴ���+1
	}
	infile.close();
	cout << "˳��������ɣ�����" << oF.sequenceNumber << "���ļ�����ʼ˳����" << '\n';
	char c;
	c = 'n';
	if (c == 'y') {
		cout << "���ڼ����ļ�" << '\n';
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
		cout << "������" << '\n';
	}
}
void mergeString(operateFile& oF) {//�ϲ����з����ļ�����ͨ����С�������ϲ����г�ʼ˳������������������
	cout << "���ںϲ����ս��..." << '\n';
	output_name = oF.frontPath + "output.txt";
	outfile.open(output_name, ios::out);//�����ս��Ҫ��������ļ�
	int x;
	if (oF.sequenceNumber == 1) {//���ֻ������һ��˳����ֱ�ӽ�˳�����������ļ���
		string file = oF.frontPath + oF.fileName + "-file" + to_string(1) + ".txt";
		ifstream infile;
		infile.open(file, ios::in);
		while (infile >> x) {
			outfile << x << ' ';
			oF.visitNum += 2;
		}
		outfile.close();
		infile.close();
		exit(0);//�˳�����
	}
	for (int i = 1; i <= oF.sequenceNumber; i++) {//�����˶��˳��
		string file = oF.frontPath + oF.fileName + "-file" + to_string(i) + ".txt";//�����ļ�����
		ifstream infile;
		infile.open(file, ios::in);//�򿪸��������ļ�
		infile >> totalPlayer[i];//ÿ��˳����ͷ���ݶ���totalPlayer[]���飨ʵ���϶�Ӧÿ���������С��������player[]���飩��
								//����С����������Щͷ���ݱ�����Ӯ���ź��ˣ���������ļ��У��ع�������
		readPoint[i] = infile.tellg();//��i��Ӧ��������ָ�루�ļ�������ָ�룬ָ��ǰ�ļ�������λ�ã����浽readPoint[]��
		infile.close();
	}
	LoserTree<int> tr(totalPlayer, oF.sequenceNumber);//��С������������K·�鲢����С��������
	for (int i = 1; i <= oF.n; i++) {
		int ii = tr.Node[0];//ii:����������ʤ��
		int winner = totalPlayer[ii];
		outfile << winner << ' ';//ʤ������ֵ������ļ���ÿ�ź�һ�����ͽ�������������ļ��У�
		++oF.visitNum;//���ʴ���+1
		string file = oF.frontPath + oF.fileName + "-file" + to_string(ii) + ".txt";
		ifstream infile(file);
		infile.clear();//������������ָ��
		infile.seekg(readPoint[ii] + (long long)1);//������ָ���ƶ���ʤ��������˳������һ��Ԫ��
		int num;
		if (readPoint[ii] + 1 == 0) {//������λ�õ����ļ�����������
			num = INT_MAX;//num��Ϊ��Ӱ��ʤ���ߣ�Ԫ��ֵС�Ļ�ʤ��������ΪINF������
		}
		else {//���뻹δ��������������
			infile >> num;
			readPoint[ii] = infile.tellg();//����ii��Ӧ��������ָ��
			if (readPoint[ii] + 1 == 0) {
				num = INT_MAX;
			}
		}
		++oF.visitNum;
		tr.Rebuild(ii, num);//����Ԫ��num���ʤ���ߣ��ع���С������
		infile.close();
	}
	outfile.close();
	cout << "�������������" << oF.frontPath << "output.txt" << "�ļ���" << '\n';
}
void End(operateFile& oF) {//�ú���Ϊ����ȡ�����������ִ�к�ͳ������ʱ�䣬����UI�Ͻ�����ʾ�Ľ���
	while (i--);
	theEnd = clock();//����ʱ��
	timeInteval = (double)(theEnd - start) / CLOCKS_PER_SEC;//timeInteval��������ִ��ʱ��
	cout << "��������ʱ��Ϊ��" << timeInteval << "��" << '\n';
	cout << '\n';
	cout << "���̷��ʴ���Ϊ��" << oF.visitNum;
}
int main()
{
	ios::sync_with_stdio(false);
	operateFile oF;//���������ļ����󣬸ö������ڶԴ����ļ����ж�/д����
	Input(oF);//��ʼ���򲢼�ʱ
	primeString(oF, s_player);//ͨ����С����������һЩ��ʼ˳��
	mergeString(oF);//ͨ����С�������ϲ���Щ˳����ÿ�ź�һ��Ԫ�ؼ�����Ԫ���������Ӧ�����ļ��У�������Ԫ���滻��Ӯ�ߣ����ع���С������
	End(oF);//�������򲢽�����ʱ
	return 0;
}