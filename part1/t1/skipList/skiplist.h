#pragma once
#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>
const int inf = 0x3f3f3f;
using namespace std;
template<class K,class E>
struct skipNode//节点
{
	typedef pair<const K, E> pairType;
	pairType element;//数据域，存储数对
	skipNode<K, E> **next;//指针数组(指针域），一个存有数对的节点的指针数组中指针数应≥自身级数， next[i]:i级链表指针
	skipNode(const pairType& thePair, int size) :element(thePair)
	{
		next = new skipNode<K, E>*[size];//size表示指针域中指针的个数，i级链表的size为i+1
	}
	~skipNode() { delete[]  next; }
};

template<class K,class E>
class skipList {//跳表类
protected:
	float cutOff;//用来确定层数
	int levels;//当前最大的非空链表
	int dSize;//字典的数对个数
	int maxLevel;//允许的最大链表层数
	K tailKey;//最大关键字
	skipNode<K, E>* headerNode;//头节点指针
	skipNode<K, E>* tailNode;//尾节点指针
	skipNode<K, E>** last;//last[i]表示i层最后节点：在插入和删除之前的搜索时所遇到的每级链表的最后一个数对指针都存储在数组last中
public://todo:析构函数
	skipList(K largeKey=100000, int maxPairs=10000, float p=0.5);//构造函数
	~skipList();//析构函数
	bool find(const K& theKey) const;//查找
	int level() const;//级的分配函数
	skipNode<K, E>*  search(const K& theKey) const;//搜索并把每一级链表搜索时所遇到的最后一个节点指针存储起来
	void insert(const pair<const K, E>& thePair);//插入
	void erase(const K& theKey);//删除指定关键字的元素
	pair<const K, E> eraseMax();//删除关键字最大的元素，并返回该元素
	pair<const K, E> eraseMin();//删除关键字最小的元素，并返回该元素
	bool empty() const { return dSize == 0; }//判断跳表是否为空
	int size() const { return dSize; }//跳表节点个数
	int allXor();//返回跳表中所有元素的异或
};


template<class K, class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float p)//构造函数
{//数对个数size最多为maxPairs,以maxPairs为“N”     0 < prob < 1（这里p默认为0.5，严格跳表）
	cutOff = p * RAND_MAX;//确定新节点被分配到哪级链表,用于level成员函数中
	maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / p)) - 1;//ceil向上取整，以m为底logn需要lnn/lnm
	levels = 0;//初始化级数，目前级数最大的链表为0级链表
	dSize = 0;//目前整个跳表（字典）的数对个数=0
	tailKey = largeKey;//所有关键字小于largeKey，尾节点关键字赋上largeKey

	//生成头节点、尾节点和数组last
	pair<K, E> tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);//头节点有maxLevel+1个指向尾节点的指针
	tailNode = new skipNode<K, E>(tailPair, 0);//尾节点不需要指针
	last = new skipNode<K, E> *[maxLevel + 1];//存有maxLevel+1个数对指针（指向每层搜索到的最后一个节点）

	//链表为空时，任意级链表中的头节点都指向尾节点（头节点指针域中每一级链表的指针都指向尾节点）
	for (int i = 0; i <= maxLevel; i++)headerNode->next[i] = tailNode;
}

template<class K, class E>
skipList<K, E>::~skipList()//析构函数
{
	skipNode<K, E>* nextNode;
	while (headerNode != tailNode)
	{
		nextNode = headerNode->next[0];//头删法：从headNode开始删除，直到把整个跳表删除
		delete headerNode;
		headerNode = nextNode;
	}
	delete tailNode;//删除尾节点，至此跳表的节点所占空间全部被释放
	delete[] last;//释放last数组的空间
}

template<class K, class E>//时间复杂度平均O(logn)，最坏Θ(n)
bool skipList<K, E>::find(const K& theKey) const//是否找到
{
	if (theKey >= tailKey)return false;//找不到
	skipNode<K, E>* beforeNode = headerNode;//beforeNode节点是关键字为theKey的节点之前最右边的位置
	for (int i = levels; i >= 0; i--)//从上级链表到下级链表，最终i变为0，搜到了0级链表
	{//(实际上无论被搜索的节点在几级链表，我们还是要搜到0级）
		while (beforeNode->next[i]->element.first < theKey)//跟踪i级链表指针，直到beforeNode变为theKey的节点之前最右边的位置
			beforeNode = beforeNode->next[i];//beforeNode变为该级链表中下一个位置
	}
	if (beforeNode->next[0]->element.first == theKey)
		return true;
	return false;//没有找到相应数对
}

template<class K, class E>
int skipList<K, E>::level() const//返回一个表示链表级数的随机数，该级数≤maxLevel
{
	int lev = 0;
	while (rand() <= cutOff)
		lev++;
	return (lev <= maxLevel)?lev:maxLevel;
}

template<class K, class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey) const
{//搜索关键字theKey,把每一级链表中要查看的最后一个节点存储在数组last中(其中搜索操作与find函数逻辑相同）
	//返回包含关键字theKey的节点
	//beforeNode节点是关键字为theKey的节点之前最右边的位置
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;//搜索过程中每级链表的最后一个节点的指针
	}
	return beforeNode->next[0];//若跳表中存在关键字为theKey的节点，则返回beforeNode的后继节点（关键字为theKey的节点）
}//若跳表中不存在关键字为theKey的节点，则依旧返回beforeNode的后继节点（关键字不为theKey）

template<class K, class E>
void skipList<K, E>::insert(const pair<const K, E>&  thePair)//时间复杂度与查找的复杂度相同，平均O(logn)，最坏Θ(n)
{//把数对thePair插入跳表（字典），覆盖其关键字相同的已存在的数对
	if (thePair.first >= tailKey)//关键字太大
	{
		return;
	}

	//查看关键字为theKey的数对是否已经存在
	skipNode<K, E>* theNode = search(thePair.first);
	if (theNode->element.first == thePair.first)
	{//若存在，则更新（覆盖）此数对的值
		theNode->element.second = thePair.second;
		return;
	}

	//若不存在，则确定新节点所在的级链表
	int theLevel = level();//新节点的级
	//使级theLevel为<=levels+1（避免级与当前最高级相差过大）
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}

	//在节点beforeNode之后插入新节点
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0; i <= theLevel; i++)
	{//将newNode插入0-i级链表
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}
	dSize++;//跳表节点数+1
	return;
}

template<class K, class E>
void skipList<K, E>::erase(const K& theKey)//时间复杂度与查找的复杂度相同，平均O(logn)，最坏Θ(n)
{//删除关键字等于theKey的数对
	if (theKey >= tailKey)//关键字太小
		return;

	//查看是否有匹配的数对
	skipNode<K, E>* theNode = search(theKey);
	if (theNode->element.first != theKey)//不存在匹配的数对
		return;

	//从跳表中删除节点
	for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
		last[i]->next[i] = theNode->next[i];

	//更新链表级
	while (levels > 0 && headerNode->next[levels] == tailNode)//该层只有头节点和尾节点
		levels--;

	delete theNode;
	dSize--;
	return;
}

template<class K, class E>
pair<const K, E> skipList<K, E>::eraseMax()//时间复杂度与查找的复杂度相同，平均O(logn)，最坏Θ(n)
{
	//跳表为空，退出
	if (headerNode->next[0] == tailNode)
	{
		pair<const K, E> tempPair(make_pair(-1, -1));
		return tempPair;
	}

	//定位要删除的关键字最大的节点的位置
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		if (beforeNode->next[i] == tailNode)
			continue;//此层没有节点，跳到下一层继续搜寻
		while (beforeNode->next[i]->next[i] != tailNode)//还没搜寻到
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;//该层搜索完毕，用last[i]存储搜寻过程中每层最后一个节点的指针
	}
	skipNode<K, E>* theNode = beforeNode->next[0];
	pair<const K, E> thePair = theNode->element;

	//删除节点(0-I级链表）
	for (int i = 0;i <= levels && last[i]->next[i] == theNode; i++)
		last[i]->next[i] = theNode->next[i];

	//更新链表级
	while (levels > 0 && headerNode->next[levels] == tailNode)//该层无数据节点，删除该层
		levels--;

	//释放关键字最小元素对应的节点空间
	delete theNode;

	//更新跳表节点个数
	dSize--;
	return thePair;
}

template<class K, class E>
pair<const K, E> skipList<K, E>::eraseMin()//O(1)复杂度
{
	//跳表为空，退出
	if (headerNode->next[0] == tailNode)
	{
		pair<const K, E> tempPair(make_pair(-1, -1));
		return tempPair;
	}

	//删除节点
	skipNode<K, E>* theNode = headerNode->next[0];
	pair<const K, E> thePair = theNode->element;
	for (int i = 0; i <= levels && headerNode->next[i] == theNode; i++)
		headerNode->next[i] = theNode->next[i];//在关键字最小的元素所在的每级链表均删除它

	//更新链表级
	while (levels > 0 && headerNode->next[levels] == tailNode)
		levels--;

	//释放节点空间（跳表中指针指向转移代表是逻辑上删除该节点，现在是从内存空间上释放该节点占用的内存空间）
	delete theNode;
	dSize--;//更新跳表节点个数
	return thePair;
}

template<class K, class E>
int skipList<K, E>::allXor()//O(N)复杂度
{
	int temp;
	skipNode<K, E>* theNode = headerNode->next[0];
	if (theNode == tailNode || theNode->next[0] == tailNode)//跳表为空or跳表只有一个元素
	{
		return inf;
	}
	temp = (theNode->element.first) ^ (theNode->next[0]->element.first);//现在至少跳表中有两个元素了
	theNode = theNode->next[0]->next[0];
	while (theNode != tailNode)
	{
		temp ^= theNode->element.first;
		theNode = theNode->next[0];
	}
	return temp;
}