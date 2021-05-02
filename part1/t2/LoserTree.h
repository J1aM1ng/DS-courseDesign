#pragma once
struct operateFile {//对文件执行操作（可以理解为内存中的一片空间）
	string frontPath;//前驱路径
	string fileName;//文件名称
	string completePath;//文件全路径
	int visitNum = 0;//访问次数
	int n = 0;//全部数据的数量
	int bufferSize;//缓冲区大小 每个分区（file n） 包含的数据数量
	int sequenceNumber = 0;//分区数/顺串数
};
struct ele {//顺串元素，即用于生成顺串的每个元素，缓冲区大小即为初始元素的数目，ele的数目
	int id;//id为顺串号
	int key;//key为元素值
	bool operator<=(ele& ss) {//建立排序规则：顺串号小的获胜，顺串号相同时元素小的获胜
		if (id != ss.id) {
			return id < ss.id;
		}
		else {
			return key < ss.key;
		}
	}
};

template <class T>
class LoserTree {//最小输者树的定义
public:
	int* Node;//树的节点，存放每次比赛的输者
	int* branch;//树的边，即晋级者（每次比赛的赢者）
	int playerNumber;//player数组的元素数量（即一棵输者树包含的选手数）
	T* player;//所有元素存放于player数组（最小输者树的所有的数据元素，即该树的所有参赛者）
	int LowExt;//最底层的外部节点数
	int offset;//除了最底层以外的节点数
	LoserTree(T* player = nullptr, int playerNumber = 0) {//初始化，构造函数
		Node = nullptr;
		branch = nullptr;
		Init(player, playerNumber);//存放参赛者的数组，数组里面元素数量
	}
	void Init(T* ele, int num);//初始化最小输者树
	int Win(int x, int y) {//在一场比赛（两个参赛者）中，返回胜利者在其输者树元素数组player中的下标
		return player[x] <= player[y] ? x : y;
	}
	int Lose(int x, int y) {//在一场比赛（两个参赛者）中，返回失败者在其输者树元素数组player中的下标
		return player[x] <= player[y] ? y : x;
	}
	void Compete(int p, int l, int r);//比较l和r，即左孩子和右孩子比赛（compete），输者存入父节点p中（tree[])，赢者晋级，存入branch[]
	void Rebuild(int p, T val);//胜者移出树后，胜者的后一个元素接替胜者原来的位置，并重构整个输者树（涉及新元素的比赛重比）
};