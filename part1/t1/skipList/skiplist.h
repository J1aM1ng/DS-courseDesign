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
struct skipNode//�ڵ�
{
	typedef pair<const K, E> pairType;
	pairType element;//�����򣬴洢����
	skipNode<K, E> **next;//ָ������(ָ���򣩣�һ���������ԵĽڵ��ָ��������ָ����Ӧ���������� next[i]:i������ָ��
	skipNode(const pairType& thePair, int size) :element(thePair)
	{
		next = new skipNode<K, E>*[size];//size��ʾָ������ָ��ĸ�����i�������sizeΪi+1
	}
	~skipNode() { delete[]  next; }
};

template<class K,class E>
class skipList {//������
protected:
	float cutOff;//����ȷ������
	int levels;//��ǰ���ķǿ�����
	int dSize;//�ֵ�����Ը���
	int maxLevel;//���������������
	K tailKey;//���ؼ���
	skipNode<K, E>* headerNode;//ͷ�ڵ�ָ��
	skipNode<K, E>* tailNode;//β�ڵ�ָ��
	skipNode<K, E>** last;//last[i]��ʾi�����ڵ㣺�ڲ����ɾ��֮ǰ������ʱ��������ÿ����������һ������ָ�붼�洢������last��
public://todo:��������
	skipList(K largeKey=100000, int maxPairs=10000, float p=0.5);//���캯��
	~skipList();//��������
	bool find(const K& theKey) const;//����
	int level() const;//���ķ��亯��
	skipNode<K, E>*  search(const K& theKey) const;//��������ÿһ����������ʱ�����������һ���ڵ�ָ��洢����
	void insert(const pair<const K, E>& thePair);//����
	void erase(const K& theKey);//ɾ��ָ���ؼ��ֵ�Ԫ��
	pair<const K, E> eraseMax();//ɾ���ؼ�������Ԫ�أ������ظ�Ԫ��
	pair<const K, E> eraseMin();//ɾ���ؼ�����С��Ԫ�أ������ظ�Ԫ��
	bool empty() const { return dSize == 0; }//�ж������Ƿ�Ϊ��
	int size() const { return dSize; }//����ڵ����
	int allXor();//��������������Ԫ�ص����
};


template<class K, class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float p)//���캯��
{//���Ը���size���ΪmaxPairs,��maxPairsΪ��N��     0 < prob < 1������pĬ��Ϊ0.5���ϸ�����
	cutOff = p * RAND_MAX;//ȷ���½ڵ㱻���䵽�ļ�����,����level��Ա������
	maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / p)) - 1;//ceil����ȡ������mΪ��logn��Ҫlnn/lnm
	levels = 0;//��ʼ��������Ŀǰ������������Ϊ0������
	dSize = 0;//Ŀǰ���������ֵ䣩�����Ը���=0
	tailKey = largeKey;//���йؼ���С��largeKey��β�ڵ�ؼ��ָ���largeKey

	//����ͷ�ڵ㡢β�ڵ������last
	pair<K, E> tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);//ͷ�ڵ���maxLevel+1��ָ��β�ڵ��ָ��
	tailNode = new skipNode<K, E>(tailPair, 0);//β�ڵ㲻��Ҫָ��
	last = new skipNode<K, E> *[maxLevel + 1];//����maxLevel+1������ָ�루ָ��ÿ�������������һ���ڵ㣩

	//����Ϊ��ʱ�����⼶�����е�ͷ�ڵ㶼ָ��β�ڵ㣨ͷ�ڵ�ָ������ÿһ�������ָ�붼ָ��β�ڵ㣩
	for (int i = 0; i <= maxLevel; i++)headerNode->next[i] = tailNode;
}

template<class K, class E>
skipList<K, E>::~skipList()//��������
{
	skipNode<K, E>* nextNode;
	while (headerNode != tailNode)
	{
		nextNode = headerNode->next[0];//ͷɾ������headNode��ʼɾ����ֱ������������ɾ��
		delete headerNode;
		headerNode = nextNode;
	}
	delete tailNode;//ɾ��β�ڵ㣬��������Ľڵ���ռ�ռ�ȫ�����ͷ�
	delete[] last;//�ͷ�last����Ŀռ�
}

template<class K, class E>//ʱ�临�Ӷ�ƽ��O(logn)�����(n)
bool skipList<K, E>::find(const K& theKey) const//�Ƿ��ҵ�
{
	if (theKey >= tailKey)return false;//�Ҳ���
	skipNode<K, E>* beforeNode = headerNode;//beforeNode�ڵ��ǹؼ���ΪtheKey�Ľڵ�֮ǰ���ұߵ�λ��
	for (int i = levels; i >= 0; i--)//���ϼ������¼���������i��Ϊ0���ѵ���0������
	{//(ʵ�������۱������Ľڵ��ڼ����������ǻ���Ҫ�ѵ�0����
		while (beforeNode->next[i]->element.first < theKey)//����i������ָ�룬ֱ��beforeNode��ΪtheKey�Ľڵ�֮ǰ���ұߵ�λ��
			beforeNode = beforeNode->next[i];//beforeNode��Ϊ�ü���������һ��λ��
	}
	if (beforeNode->next[0]->element.first == theKey)
		return true;
	return false;//û���ҵ���Ӧ����
}

template<class K, class E>
int skipList<K, E>::level() const//����һ����ʾ����������������ü�����maxLevel
{
	int lev = 0;
	while (rand() <= cutOff)
		lev++;
	return (lev <= maxLevel)?lev:maxLevel;
}

template<class K, class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey) const
{//�����ؼ���theKey,��ÿһ��������Ҫ�鿴�����һ���ڵ�洢������last��(��������������find�����߼���ͬ��
	//���ذ����ؼ���theKey�Ľڵ�
	//beforeNode�ڵ��ǹؼ���ΪtheKey�Ľڵ�֮ǰ���ұߵ�λ��
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;//����������ÿ����������һ���ڵ��ָ��
	}
	return beforeNode->next[0];//�������д��ڹؼ���ΪtheKey�Ľڵ㣬�򷵻�beforeNode�ĺ�̽ڵ㣨�ؼ���ΪtheKey�Ľڵ㣩
}//�������в����ڹؼ���ΪtheKey�Ľڵ㣬�����ɷ���beforeNode�ĺ�̽ڵ㣨�ؼ��ֲ�ΪtheKey��

template<class K, class E>
void skipList<K, E>::insert(const pair<const K, E>&  thePair)//ʱ�临�Ӷ�����ҵĸ��Ӷ���ͬ��ƽ��O(logn)�����(n)
{//������thePair���������ֵ䣩��������ؼ�����ͬ���Ѵ��ڵ�����
	if (thePair.first >= tailKey)//�ؼ���̫��
	{
		return;
	}

	//�鿴�ؼ���ΪtheKey�������Ƿ��Ѿ�����
	skipNode<K, E>* theNode = search(thePair.first);
	if (theNode->element.first == thePair.first)
	{//�����ڣ�����£����ǣ������Ե�ֵ
		theNode->element.second = thePair.second;
		return;
	}

	//�������ڣ���ȷ���½ڵ����ڵļ�����
	int theLevel = level();//�½ڵ�ļ�
	//ʹ��theLevelΪ<=levels+1�����⼶�뵱ǰ��߼�������
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}

	//�ڽڵ�beforeNode֮������½ڵ�
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0; i <= theLevel; i++)
	{//��newNode����0-i������
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}
	dSize++;//����ڵ���+1
	return;
}

template<class K, class E>
void skipList<K, E>::erase(const K& theKey)//ʱ�临�Ӷ�����ҵĸ��Ӷ���ͬ��ƽ��O(logn)�����(n)
{//ɾ���ؼ��ֵ���theKey������
	if (theKey >= tailKey)//�ؼ���̫С
		return;

	//�鿴�Ƿ���ƥ�������
	skipNode<K, E>* theNode = search(theKey);
	if (theNode->element.first != theKey)//������ƥ�������
		return;

	//��������ɾ���ڵ�
	for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
		last[i]->next[i] = theNode->next[i];

	//��������
	while (levels > 0 && headerNode->next[levels] == tailNode)//�ò�ֻ��ͷ�ڵ��β�ڵ�
		levels--;

	delete theNode;
	dSize--;
	return;
}

template<class K, class E>
pair<const K, E> skipList<K, E>::eraseMax()//ʱ�临�Ӷ�����ҵĸ��Ӷ���ͬ��ƽ��O(logn)�����(n)
{
	//����Ϊ�գ��˳�
	if (headerNode->next[0] == tailNode)
	{
		pair<const K, E> tempPair(make_pair(-1, -1));
		return tempPair;
	}

	//��λҪɾ���Ĺؼ������Ľڵ��λ��
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		if (beforeNode->next[i] == tailNode)
			continue;//�˲�û�нڵ㣬������һ�������Ѱ
		while (beforeNode->next[i]->next[i] != tailNode)//��û��Ѱ��
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;//�ò�������ϣ���last[i]�洢��Ѱ������ÿ�����һ���ڵ��ָ��
	}
	skipNode<K, E>* theNode = beforeNode->next[0];
	pair<const K, E> thePair = theNode->element;

	//ɾ���ڵ�(0-I������
	for (int i = 0;i <= levels && last[i]->next[i] == theNode; i++)
		last[i]->next[i] = theNode->next[i];

	//��������
	while (levels > 0 && headerNode->next[levels] == tailNode)//�ò������ݽڵ㣬ɾ���ò�
		levels--;

	//�ͷŹؼ�����СԪ�ض�Ӧ�Ľڵ�ռ�
	delete theNode;

	//��������ڵ����
	dSize--;
	return thePair;
}

template<class K, class E>
pair<const K, E> skipList<K, E>::eraseMin()//O(1)���Ӷ�
{
	//����Ϊ�գ��˳�
	if (headerNode->next[0] == tailNode)
	{
		pair<const K, E> tempPair(make_pair(-1, -1));
		return tempPair;
	}

	//ɾ���ڵ�
	skipNode<K, E>* theNode = headerNode->next[0];
	pair<const K, E> thePair = theNode->element;
	for (int i = 0; i <= levels && headerNode->next[i] == theNode; i++)
		headerNode->next[i] = theNode->next[i];//�ڹؼ�����С��Ԫ�����ڵ�ÿ�������ɾ����

	//��������
	while (levels > 0 && headerNode->next[levels] == tailNode)
		levels--;

	//�ͷŽڵ�ռ䣨������ָ��ָ��ת�ƴ������߼���ɾ���ýڵ㣬�����Ǵ��ڴ�ռ����ͷŸýڵ�ռ�õ��ڴ�ռ䣩
	delete theNode;
	dSize--;//��������ڵ����
	return thePair;
}

template<class K, class E>
int skipList<K, E>::allXor()//O(N)���Ӷ�
{
	int temp;
	skipNode<K, E>* theNode = headerNode->next[0];
	if (theNode == tailNode || theNode->next[0] == tailNode)//����Ϊ��or����ֻ��һ��Ԫ��
	{
		return inf;
	}
	temp = (theNode->element.first) ^ (theNode->next[0]->element.first);//��������������������Ԫ����
	theNode = theNode->next[0]->next[0];
	while (theNode != tailNode)
	{
		temp ^= theNode->element.first;
		theNode = theNode->next[0];
	}
	return temp;
}