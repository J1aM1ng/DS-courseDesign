#pragma once
struct operateFile {//���ļ�ִ�в������������Ϊ�ڴ��е�һƬ�ռ䣩
	string frontPath;//ǰ��·��
	string fileName;//�ļ�����
	string completePath;//�ļ�ȫ·��
	int visitNum = 0;//���ʴ���
	int n = 0;//ȫ�����ݵ�����
	int bufferSize;//��������С ÿ��������file n�� ��������������
	int sequenceNumber = 0;//������/˳����
};
struct ele {//˳��Ԫ�أ�����������˳����ÿ��Ԫ�أ���������С��Ϊ��ʼԪ�ص���Ŀ��ele����Ŀ
	int id;//idΪ˳����
	int key;//keyΪԪ��ֵ
	bool operator<=(ele& ss) {//�����������˳����С�Ļ�ʤ��˳������ͬʱԪ��С�Ļ�ʤ
		if (id != ss.id) {
			return id < ss.id;
		}
		else {
			return key < ss.key;
		}
	}
};

template <class T>
class LoserTree {//��С�������Ķ���
public:
	int* Node;//���Ľڵ㣬���ÿ�α���������
	int* branch;//���ıߣ��������ߣ�ÿ�α�����Ӯ�ߣ�
	int playerNumber;//player�����Ԫ����������һ��������������ѡ������
	T* player;//����Ԫ�ش����player���飨��С�����������е�����Ԫ�أ������������в����ߣ�
	int LowExt;//��ײ���ⲿ�ڵ���
	int offset;//������ײ�����Ľڵ���
	LoserTree(T* player = nullptr, int playerNumber = 0) {//��ʼ�������캯��
		Node = nullptr;
		branch = nullptr;
		Init(player, playerNumber);//��Ų����ߵ����飬��������Ԫ������
	}
	void Init(T* ele, int num);//��ʼ����С������
	int Win(int x, int y) {//��һ�����������������ߣ��У�����ʤ��������������Ԫ������player�е��±�
		return player[x] <= player[y] ? x : y;
	}
	int Lose(int x, int y) {//��һ�����������������ߣ��У�����ʧ��������������Ԫ������player�е��±�
		return player[x] <= player[y] ? y : x;
	}
	void Compete(int p, int l, int r);//�Ƚ�l��r�������Ӻ��Һ��ӱ�����compete�������ߴ��븸�ڵ�p�У�tree[])��Ӯ�߽���������branch[]
	void Rebuild(int p, T val);//ʤ���Ƴ�����ʤ�ߵĺ�һ��Ԫ�ؽ���ʤ��ԭ����λ�ã����ع��������������漰��Ԫ�صı����رȣ�
};