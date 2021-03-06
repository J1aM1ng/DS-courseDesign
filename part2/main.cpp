#include <bits/stdc++.h>
using namespace std;

const int noEdge = 1e6;//?????
int lineNum;//?????????
int cnt;//??????????????????????????????????????????????????????????
int *area;
double *price;//?????????????
int *speed;//???????????

double **distanceMap;//???????????????  ???????????
double **priceMap;;//??????????????  ???????????
double **timeMap;;//??????????????  ???????????

int *stationIndex;//??????????
string *nameIndex;//???????????
int *priceIndex;//???????
int *iPriceIndex;
int range;

double restrict(double a)
{
	double tmp = int(a * 100);
return tmp / 100;
}

double getDistance(double a, double b, double c, double d)
{
	return restrict(sqrt((a - c)*(a - c) + (b - d)*(b - d)));
}

class rChainNode
{
private:
	friend class busRoutine;
	friend class rChain;
public:
	string station;
	double px;
	double py;
	rChainNode *nxt;
	rChainNode *prior;
};

class rChain
{
private:
	friend class busRoutine;
	rChainNode *first;
public:
	rChain() :first(0) {};
	~rChain();
	bool isEmpty() { return first == 0; };
	int length() const;
	rChainNode *getFirst() { return first; };
	rChain &insert(const string& s, const double &x, const double &y);
	rChain &iInsert(rChainNode *rn);
	void output(ostream &out) const;
	string getStation() { return first->station; };
	rChain &reArrange(double &y);
	rChain &reCharge(rChain &r);
	rChain &dReJudge();
};

rChain::~rChain()
{
	rChainNode *nxt;
	while (this->first)
	{
		nxt = this->first->nxt;
		delete  this->first;
		this->first = nxt;
	}
}

int rChain::length() const
{
	rChainNode *current = this->first;
	int len = 0;
	while (current)
	{
		++len;
		current = current->nxt;
	}
	return len;
}

rChain &rChain::insert(const string &s, const double &x, const double &y)
{
	if (!this->first)
	{
		this->first = new rChainNode;
		this->first->station = s;
		this->first->px = x;
		this->first->py = y;
		this->first->nxt = 0;
		this->first->prior = 0;
	}
	else
	{
		rChainNode *p = first;
		while (p->nxt)
		{
			p = p->nxt;
		}
		rChainNode *r = new rChainNode;
		r->station = s;
		r->px = x;
		r->py = y;
		p->nxt = r;
		r->prior = p;
		r->nxt = 0;
	}
	return *this;
}

rChain &rChain::iInsert(rChainNode *rn)
{
	if (this->first)
	{
		rChainNode *tmp = rn;
		rChainNode *p = this->first;
		while (p->nxt)
		{
			p = p->nxt;
		}
		p->nxt = tmp;
		tmp->prior = p;
	}
	else
	{
		this->first = rn;
	}
	return *this;
}

rChain &rChain::reArrange(double &y)
{
	rChainNode *current = this->first;
	for (current; current->nxt; current = current->nxt)
	{
		rChainNode *tmp = current->nxt;
		current->px = getDistance(current->px, current->py, tmp->px, tmp->py);
		current->py = y;
		++y;
	}
	current->px = noEdge;
	current->py = y;
	++y;
	return *this;
}

rChain &rChain::reCharge(rChain &r)
{
	this->iInsert(r.getFirst());
	if (!this->first)
	{
		this->first = r.getFirst();
	}
	return *this;
}

rChain &rChain::dReJudge()
{
	range = this->length();
	rChainNode *current = this->first;
	for (int i = 0; i < range; i++)
	{
		if (i == 0)
		{
			current->py += 0;
			current = current->nxt;
		}
		else
		{
			rChainNode *tmp = this->first;
			int flag = 0;
			for (int j = 0; j < i; j++)
			{
				if (current->station == tmp->station)
				{
					current->py = tmp->py;
					flag++;
					cnt++;
					break;
				}
				tmp = tmp->nxt;
			}
			if (!flag)
			{
				current->py = cnt;
			}
			current = current->nxt;
		}
	}
	return *this;
}

void rChain::output(ostream &out) const
{
	rChainNode *current;
	for (current = this->first; current->nxt; current = current->nxt)
	{
		out << current->station << '(' << current->px << ',' << current->py << ')' << "->";
	}
	out << current->station << '(' << current->px << ',' << current->py << ')' << '\n';
}

ostream &operator<<(ostream &out, const rChain &x)
{
	x.output(out);
	return out;
}

class busRoutine
{
public:
	busRoutine();
	void setStage(int nm, int n);
	void setOthers(int s, int p);
	rChain& getStage() { return stage; };
	void allOutput();
	void lineOutput() { cout << this->stage; };
	int getPrice() { return this->price; };
	int getSpeed() { return this->speed; };
	int getNum() { return this->num; };
	int getName() { return this->name; };
private:
	int name;
	int num;
	int speed;
	int price;
	rChain stage;
};

busRoutine::busRoutine()
{
	num = 0;
	speed = 0;
	stage.first = 0;
}

void busRoutine::setStage(int nm, int n)
{
	this->name = nm;
	this->num = n;
	string s;
	double x, y;
	cout << "??????????????????????" << '\n';
	for (int j = 0; j < n; j++)
	{
		cin >> s >> x >> y;
		this->stage.insert(s, x, y);
	}
}

void busRoutine::setOthers(int s, int p)
{
	speed = s;
	price = p;
}

void busRoutine::allOutput()
{
	cout << "?????" << this->name << '\n';
	cout << this->stage;
	cout << "speed:" << this->speed << "km/h" << '\n';
	cout << "price:" << this->price << "RMB" << '\n';
}

busRoutine *br;//???????????
rChain wholeRoad;

void change(busRoutine *br, int n)
{
	double x = 1;
	for (int i = 0; i < n; i++)
	{
		(br[i].getStage()).reArrange(x);
	}
}

void getNumIndex()
{
	int all = wholeRoad.length();
	stationIndex = new int[all + 1];
	stationIndex[0] = 0;
	rChainNode *tmp = wholeRoad.getFirst();
	for (int i = 1; i <= all; i++)
	{
		stationIndex[i] = tmp->py;
		if (i != all)
		{
			tmp = tmp->nxt;
		}
	}
}

void stationIndexOutput()
{
	for (int i = 1; i <= range; i++)
	{
		cout << stationIndex[i] << " ";
	}
	cout << "\n\n";
}

void getNameIndex()
{
	range -= cnt;
	nameIndex = new string[range + 1];
	rChainNode *tmp = wholeRoad.getFirst();
	nameIndex[0] = " ";
	for (int i = 1; i <= wholeRoad.length(); i++)
	{
		nameIndex[stationIndex[i]] = tmp->station;
		if (i != wholeRoad.length())
		{
			tmp = tmp->nxt;
		}
	}
}

void nameIndexOutput()
{
	for (int i = 1; i <= range; i++)
	{
		cout << nameIndex[i] << " ";
	}
	cout << "\n\n";
}

bool searchNo(string a, int &b)
{
	for (int i = 1; i <= range; i++)
	{
		if (a == nameIndex[i])
		{
			b = i;
			return true;
		}
	}
	return false;
}

void getPriceIndex()
{
	priceIndex = new int[lineNum + 1];
	priceIndex[0] = 0;
	for (int i = 1; i <= lineNum; i++)
	{
		priceIndex[i] = br[i - 1].getPrice();
	}
}

void getIPriceIndex()
{
	iPriceIndex = new int[lineNum + 1];
	iPriceIndex[0] = 0;
	for (int i = 1; i <= lineNum; i++)
	{
		iPriceIndex[i] = priceIndex[i] * i*i;
	}
}

void priceIndexOutput()
{
	for (int i = 1; i <= lineNum; i++)
	{
		cout << priceIndex[i] << " ";
	}
	cout << "\n\n";
}

void iPriceIndexOutput()
{
	for (int i = 1; i <= lineNum; i++)
	{
		cout << iPriceIndex[i] << " ";
	}
	cout << "\n\n";
}

double searchPrice(double p)
{
	for (int i = 1; i <= lineNum; i++)
	{
		if (p == iPriceIndex[i])
		{
			double tmp = priceIndex[i];
			return tmp;
		}
	}
	return noEdge;
}

void getArea()
{
	int bound = 2 * (wholeRoad.length() - lineNum) + 1;
	area = new int[bound];
	int i = 1, ii = 1;
	int sign = 0;
	while (i <= bound - 1)
	{
		for (int j = 0; j < lineNum; j++)
		{
			for (int k = 1; k < br[j].getNum(); k++)
			{
				area[i] = 10 * stationIndex[ii + sign] + stationIndex[ii + 1 + sign];
				area[i + 1] = 10 * stationIndex[ii + sign + 1] + stationIndex[ii + sign];
				i += 2;
				ii++;
				if (k == br[j].getNum() - 1)
				{
					sign++;
				}
			}
		}
	}
}

void areaOutput()
{
	int bound = 2 * (wholeRoad.length() - lineNum) + 1;
	for (int i = 1; i < bound; i++)
	{
		cout << area[i] << " ";
	}
	cout << "\n\n";
}

int areaCheck(int a, int b)
{
	int bound = 2 * (wholeRoad.length() - lineNum) + 1;
	int tmp = 10 * a + b;
	int i = 1;
	for (i; i < bound; i++)
	{
		if (area[i] == tmp)
		{
			break;
		}
	}
	int *roadNumber=new int[lineNum + 1];
	roadNumber[0] = 0;
	for (int j = 1; j <= lineNum; j++)
	{
		roadNumber[j] = br[j - 1].getNum() + roadNumber[j - 1];
	}
	for (int j = 0; j < lineNum; j++)
	{
		if (i > 2 * (roadNumber[j] - j) && i <= 2 * (roadNumber[j + 1] - j - 1))
		{
			return j + 1;
		}
	}
}

void getDistanceMap()
{
	distanceMap = new double *[range + 1];
	for (int i = 0; i <= range; i++)
	{
		distanceMap[i] = new double[range + 1];
	}
	rChainNode *tmp = wholeRoad.getFirst();
	for (int i = 0; i <= range; i++)
	{
		for (int j = 0; j <= range; j++)
		{
			distanceMap[i][j] = noEdge;
		}
	}
	for (int i = 1; i <= wholeRoad.length() - 1; i++)
	{
		distanceMap[stationIndex[i]][stationIndex[i + 1]] = tmp->px;
		distanceMap[stationIndex[i + 1]][stationIndex[i]] = tmp->px;
		tmp = tmp->nxt;
	}
}

void dMapOutput()
{
	for (int i = 1; i <= range; i++)
	{
		for (int j = 1; j <= range; j++)
		{
			printf("%8.2f", distanceMap[i][j]);
		}
		cout << '\n';
	}
	cout << '\n';
}

void getTimeMap()
{
	timeMap = new double *[range + 1];
	for (int i = 0; i <= range; i++)
	{
		timeMap[i] = new double[range + 1];
	}
	for (int i = 0; i <= range; i++)
	{
		for (int j = 0; j <= range; j++)
		{
			timeMap[i][j] = distanceMap[i][j];
		}
	}
	int i = 1;
	while (i < wholeRoad.length())
	{
		for (int j = 0; j < lineNum; j++)
		{
			for (int k = 0; k < br[j].getNum(); k++)
			{
				if (k != br[j].getNum() - 1)
				{
					timeMap[stationIndex[i]][stationIndex[i + 1]] = 
						restrict(timeMap[stationIndex[i]][stationIndex[i + 1]] / br[j].getSpeed());
					timeMap[stationIndex[i + 1]][stationIndex[i]] = timeMap[stationIndex[i]][stationIndex[i + 1]];
					i++;
				
				}
				if (k == br[j].getNum() - 1)
				{
					i++;
				}
			}
		}
	}
}

void tMapOutput()
{
	for (int i = 1; i <= range; i++)
	{
		for (int j = 1; j <= range; j++)
		{
			printf("%8.2f", timeMap[i][j]);
		}
		cout << '\n';
	}
	cout << '\n';
}

void getPriceMap()
{
	priceMap = new double *[range + 1];
	for (int i = 0; i <= range; i++)
	{
		priceMap[i] = new double[range + 1];
	}
	for (int i = 0; i <= range; i++)
	{
		for (int j = 0; j <= range; j++)
		{
			priceMap[i][j] = distanceMap[i][j];
		}
	}
	int i = 1;
	while (i < wholeRoad.length())
	{
		for (int j = 0; j < lineNum; j++)
		{
			for (int k = 0; k < br[j].getNum(); k++)
			{
				if (k != br[j].getNum() - 1)
				{
					priceMap[stationIndex[i]][stationIndex[i + 1]] =
						br[j].getPrice()*br[j].getName()*br[j].getName();
					priceMap[stationIndex[i + 1]][stationIndex[i]] = priceMap[stationIndex[i]][stationIndex[i + 1]];
					i++;
				}
				if (k == br[j].getNum() - 1)
				{
					i++;
				}
			}
		}
	}
}

void pMapOutput()
{
	for (int i = 1; i <= range; i++)
	{
		for (int j = 1; j <= range; j++)
		{
			printf("%8.2f", priceMap[i][j]);
		}
		cout << '\n';
	}
	cout << '\n';
}

//dijkstra
//???????????1???
double *dis;
int *pre;
int line = 2 * (range - 1);

void init()
{
	dis = new double[range + 1];
	pre = new int[range + 1];
	for (int i = 1; i <= range; ++i)
	{
		dis[i] = noEdge;
	}
}

void dijkstra(int n, int v, double *dis, int *pre, double **c)
{
	bool *s=new bool[range + 1];
	for (int i = 1; i <= n; ++i)
	{
		dis[i] = c[v][i];
		s[i] = 0;
		if (dis[i] == noEdge)
		{
			pre[i] = 0;
		}
		else
		{
			pre[i] = v;
		}
	}
	dis[v] = 0;
	s[v] = 1;
	for (int i = 2; i <= n; ++i)
	{
		double tmp = noEdge;
		int u = v;
		for (int j = 1; j <= n; ++j)
		{
			if (!s[j] && dis[j] < tmp)
			{
				u = j;
				tmp = dis[j];
			}
		}
		s[u] = 1;
		for (int j = 1; j <= n; ++j)
		{
			if ((!s[j]) && c[u][j] < noEdge)
			{
				double newDis = dis[u] + c[u][j];
				if (newDis < dis[j])
				{
					dis[j] = newDis;
					pre[j] = u;
				}
			}
		}
	}
}

void reDijkstra(int n, int v, double *dis, int *pre, double **c)
{
	bool *s = new bool[range + 1];
	for (int i = 1; i <= n; ++i)
	{
		dis[i] = searchPrice(static_cast<int>(c[v][i]));
		s[i] = 0;
		if (dis[i] == noEdge)
		{
			pre[i] = 0;
		}
		else
		{
			pre[i] = v;
		}
	}
	dis[v] = 0;
	s[v] = 1;
	for (int i = 2; i <= n; ++i)
	{
		double tmp = noEdge;
		int u = v;
		for (int j = 1; j <= n; ++j)
		{
			if ((!s[j]) && dis[j] < tmp)
			{
				u = j;
				tmp = dis[j];
			}
		}
		s[u] = 1;
		for (int j = 1; j <= n; ++j)
		{
			if ((!s[j]) && c[u][j] < noEdge)
			{
				double newDis;
				if (c[u][pre[u]] != c[u][j])
				{
					newDis = dis[u] + searchPrice(c[u][j]);
				}
				else
				{
					newDis = dis[u];
				}
				if (newDis < dis[j])
				{
					dis[j] = newDis;
					pre[j] = u;
				}
			}
		}
	}
}

void searchPath(int *pre, int v, int u)
{
	int *q = new int[range + 1];
	int tot = 1;
	q[tot] = u;
	++tot;
	int tmp = pre[u];
	while (tmp != v)
	{
		q[tot] = tmp;
		tot++;
		tmp = pre[tmp];
	}
	q[tot] = v;
	for (int i = tot; i >= 1; --i)
	{
		if (i != 1)
		{
			cout << nameIndex[q[i]] << " -> ";
			cout << "(???????" << areaCheck(q[i], q[i - 1]) << ")";
		}
		else
		{
			cout << nameIndex[q[i]] << '\n';
		}
	}
}

void getDRoad(string s, string e)
{
	int startp, endp;
	if (searchNo(s, startp) && searchNo(e, endp))
	{
		init();
		dijkstra(range, startp, dis, pre, distanceMap);

		if (dis[endp] == noEdge)
		{
			cout << "?????????" << '\n';
		}
		else
		{
			cout << s << "??? " << e << " ??????????????" << dis[endp] << '\n';

			cout << s << "??? " << e << " ????????????";
			searchPath(pre, startp, endp);
		}
	}
	else
	{
		cout << "No Such Station!!!" << '\n';
	}
}

void getTRoad(string s, string e)
{
	int startp, endp;

	if (searchNo(s, startp) && searchNo(e, endp))
	{
		init();
		dijkstra(range, startp, dis, pre, timeMap);
		cout << s << "??? " << e << " ?????????" << dis[endp] << '\n';
		cout << s << "??? " << e << " ?????????????";
		searchPath(pre, startp, endp);
	}
	else
	{
		cout << "No Such Station!!!" << '\n';
	}
}

void getPRoad(string s, string e)
{
		int startp, endp;

		if (searchNo(s, startp) && searchNo(e, endp))
		{
			init();
			reDijkstra(range, startp, dis, pre, priceMap);
			cout << s << "??? " << e << " ???????????" << dis[endp] << '\n';
			cout << s << "??? " << e << " ?????????????";
			searchPath(pre, startp, endp);
		}
		else
		{
			cout << "No Such Station!!!" << '\n';
		}
}

void getShowStarted()//???????????????
{
	int n;//??i+1????????????
	cout << "????????????????" << '\n';
	cin >> lineNum;
	br = new busRoutine[lineNum];
	for (int i = 0; i < lineNum; i++)
	{
		cout << "???????" << i + 1 << "???????????????" << '\n';
		cin >> n;
		br[i].setStage(i + 1, n);
		cout<< "???????" << i + 1 << "??????????????????" << '\n';
		int s, p;
		cin >> s >> p;
		br[i].setOthers(s, p);
	}
	change(br, lineNum);

	for (int i = 0; i < lineNum; i++)//??????????
	{
		br[i].lineOutput();
	}

	for (int i = 0; i < lineNum; i++)
	{
		wholeRoad.reCharge(br[i].getStage());
	}
	cout << wholeRoad << '\n';

	wholeRoad.dReJudge();
	cout << wholeRoad << '\n';

	getNameIndex();
	stationIndexOutput();

	getPriceIndex();
	priceIndexOutput();

	getIPriceIndex();
	iPriceIndexOutput();

	getArea();
	areaOutput();

	getDistanceMap();
	dMapOutput();

	getTimeMap();
	tMapOutput();

	getPriceMap();
	pMapOutput();
}

int main()
{
	getShowStarted();
	int c;
	string flag = "Y";
	int gg = 0;
	while (1)//(flag == "Y" || flag == "y") && gg == 0
	{
		cout << "?????????????????????" << '\n';
		cout << "1.??????" << '\n';
		cout << "2.????????" << '\n';
		cout << "3.??????" << '\n';
		cin >> c;
		string s, e;
		switch (c)
		{
		case 1:
			cout << "????????????????????????" << '\n';
			cin >> s >> e;
			getDRoad(s, e);
			break;
		case 2:
			cout << "????????????????????????" << '\n';
			cin >> s >> e;
			getPRoad(s, e);
			break;
		case 3:
			cout << "????????????????????????" << '\n';
			cin >> s >> e;
			getTRoad(s, e);
			break;
		default:
			cout << "????????" << '\n';
			gg++;
			break;
		}
		if (!gg)
		{
			cout << "????????<Y/N>" << '\n';
			cin >> flag;
		}
	}
	return 0;
}
