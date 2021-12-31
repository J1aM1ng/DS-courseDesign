#include <bits/stdc++.h>
using namespace std;

struct TreeNode {//树节点
	TreeNode *parent;//父指针
	TreeNode *FirstChild;//第一个儿子指针
	TreeNode *brother;//兄弟指针
	bool isFile;//true表示文件，false表示目录
	char fileName[100];//用字符串存储树节点对应的文件或目录的名字
	int depth;//当前节点的深度
	int size;//当前节点的子文件数目
};
typedef  TreeNode *nowPosition;//当前位置
typedef  TreeNode *Tree;//树节点数组表示整个树
typedef  TreeNode *ptr;//指向树节点的指针

class catalogTree;
void findPath(catalogTree *a, nowPosition x);//根据位置寻找路径
void deletePtr(catalogTree *a, ptr t);//根据位置删除

class catalogTree {//目录树

public:
	TreeNode *root;//根节点
	ptr nowPtr;//树节点指针，指向树中我们当前访问位置的树节点

	catalogTree();//构造函数
	~catalogTree() {//析构函数
		deletePtr(this, root);//删除树的根节点及其n辈孩子节点
	};
	void mkdir(char *name, nowPosition t);//在对应nowPosition创建对应名字的目录
	void mkfile(char *name, nowPosition t);//在对应nowPosition创建对应名字的文件
	void ListDir();//列出当前目录下的文件
	void Delete(char *str);//删除某文件或目录（通过给出相对路径/绝对路径）
	void cd();//打印当前目录的绝对路径
	void cdPath(char *str);//跳转到指定路径
	void cdFather();//跳转到父路径
	void saveCatalog(char *filename);//将目录结构保存至文件
	void loadCatalog(char *filename);//将目录结构从文件载入
	void print(nowPosition D, int Depth, FILE *file);//向文件打印出目录结构
};



catalogTree::catalogTree()
{ //构造函数
	ptr tRoot = (TreeNode*)malloc(sizeof(TreeNode));//申请根节点空间
	tRoot->FirstChild = NULL;
	memset(tRoot->fileName, 0, sizeof(tRoot->fileName));
	tRoot->fileName[0] = '/';
	tRoot->isFile = false;
	tRoot->parent = NULL;
	tRoot->brother = NULL;
	tRoot->size = 0;
	root = tRoot;
	nowPtr = root;//当前路径为根目录（当前指针指向根节点）
};

void  catalogTree::print(nowPosition D, int Depth, FILE *file)//向文件打印出目录结构(save）
{
	ptr tmp;
	if (D != NULL) {
		for (int i = 0; i < Depth; i++) {
			fprintf(file, "\t");//通过制表符演示目录结构
		}
		if (D->isFile == true) {//是文件
			fprintf(file, "%s	.f\n", D->fileName);
		}
		else {//是目录
			fprintf(file, "%s	.d\n", D->fileName);
			for (tmp = D->FirstChild; tmp != NULL; tmp = tmp->brother)
			{
				print(tmp, Depth + 1, file);//递归打印
			}
		}		
	}
}


void catalogTree::saveCatalog(char *filename) {//将目录结构保存至文件
	FILE* file = fopen(filename, "w");//向文件中写入，即保存至文件
	if (file == NULL) {
		printf("    文件打开失败\n");
		return;
	}
	print(this->root, 0, file);//将目录结构存入文件
	fclose(file);
}



void  inputCata(catalogTree *T, nowPosition D, char *preDir, int preDepth, FILE *file)//将文件中内容载入（load）
{
	char buf[120];
	char type[3];
	char subBuf[100];
	memset(buf, 0, sizeof(buf));
	memset(type, 0, sizeof(type));
	memset(subBuf, 0, sizeof(subBuf));
	int i;
	int tmpNum = 0;
	fgets(buf, sizeof(buf), file);//一行一行载入数据
	if (strlen(buf) == 0) return;//如果读到文件末尾，结束
	strncpy(type, buf + strlen(buf) - 3, 2);//获取该行数据是文件还是目录
	for (i = 0; buf[i] == '\t'; i++) {//计算改行中有多少缩进，可以判断出哪一级的文件
		tmpNum++;
	}
	char * c = new char;
	if (i == 0) inputCata(T, D, c, 0, file);//如果没有缩进，则证明是第一行根路径

	else//不是根路径
	{
		strncpy(subBuf, buf + tmpNum, strlen(buf) - 4 - tmpNum);//获取该行中文件或目录的文件
		if (tmpNum > preDepth) {//如果该行中制表符缩进比上一行多，证明改行文件/目录为上一行目录的子文件
			T->cdPath(preDir);//改变当前指标为上一行目录
		}
		else if (tmpNum < preDepth) {//如果缩进小于上一行，每小一行，则当前指针做一次“回到上一路径”操作
			for (int j = tmpNum; j < preDepth; j++) {
				T->cdFather();
			}
		}
		//默认深度与上一行文件/目录属于同一深度

		if (strcmp(type, ".d") == 0) {//如果是目录
			T->mkdir(subBuf, T->nowPtr);
		}
		else {//如果是文件
			T->mkfile(subBuf, T->nowPtr);
		}
		inputCata(T, T->nowPtr, subBuf, tmpNum, file);//进入下一行，递归输入

	}
}


void catalogTree::loadCatalog(char *filename) {//递归搜索当前位置的路径
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("    文件打开失败，请检查文件名是否正确\n");
		return;
	}
	inputCata(this, nowPtr, "/", 0, file);//调用input方法进行载入
	fclose(file);
	cdPath("/");
}

//递归搜索当前位置的路径
void findPath(catalogTree *a, nowPosition x) {
	if (x == a->root) {
		printf("/");
		return;
	}
	else
	{
		findPath(a, x->parent);
		printf("%s/\n", x->fileName);
	}
}

void  catalogTree::cd()//输出当前项的绝对路径
{
	ptr x = nowPtr;
	findPath(this, x);
}

//根据给出的路径改变nowPtr，跳转到指定路径
void  catalogTree::cdPath(char *str)
{
	ptr tmp;
	if (str[0] == '/') {//如果第一个字符为'/',证明是绝对路径
		ptr t = root;
		const char *d = "/";
		char *p;
		p = strtok(str, d);//分隔字符串
		bool flag;//判断用户输入的路径或命令是否有错
		while (p)
		{
			flag = false;
			for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
				if (strcmp(tmp->fileName, p) == 0 && tmp->isFile == false) {
					t = tmp;//不断修改t的值，t不断趋近我们要cd的目录项
					flag = true;
					break;
				}
			}
			if (flag == false) {//如果为false，则用户输入的路径应该有错
				printf("    没有该命令\n");
				return;
			}
			p = strtok(NULL, d);
		}
		this->nowPtr = t;//
	}
	else {//相对路径

		const char *d = "/";
		char *p;
		ptr t = nowPtr;
		p = strtok(str, d);
		bool flag;//判断用户输入的路径或命令是否有错
		while (p)
		{
			flag = false;
			for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
				if (strcmp(tmp->fileName, p) == 0 && tmp->isFile == false) {
					t = tmp;//不断更新当前路径，从当前目录项向下，到达目的项
					flag = true;
					break;
				}
			}
			if (flag == false) {
				printf("    没有该命令\n");
				return;
			}
			p = strtok(NULL, d);
		}
		nowPtr = t;
	}

}

void  catalogTree::cdFather() {//cd.. 当前目录变为当前目录的父目录
	if (nowPtr == root) {
		printf("已到根路径！\n");
		return;
	}
	nowPtr = nowPtr->parent;
}

void  catalogTree::ListDir()//列出当前目录下所有文件，即当前目录项中所有文件或目录
{
	nowPosition t = nowPtr;
	ptr tmp;
	for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
		if (tmp->isFile) {
			printf("    %s.f\n", tmp->fileName);
		}
		else {
			printf("    %s.d\n", tmp->fileName);
		}
	}
}


void deletePtr(catalogTree *a, ptr t) {//删除某个文件或目录，删除指针t对应的节点及其所有孩子
	ptr tmp;
	if (t->isFile) {//如果要删除的是文件
		tmp = t->parent->FirstChild;
		if (tmp == t) {//如果删除的文件是父亲的第一个儿子，将父亲的儿子指针指向该文件的兄弟，然后释放
			t->parent->FirstChild = tmp->brother;
			free(t);
			return;
		}

		//否则，删除的文件不是父亲的第一个儿子，执行链表的一般删除操作，找到该节点的位置，让该节点的前驱的兄弟指针指向删除结点的下一个兄弟，然后释放
		for (tmp = t->parent->FirstChild; tmp != NULL; tmp = tmp->brother) {
			if (t == tmp->brother) {
				tmp->brother = t->brother;
				free(t);
				return;
			}
		}
	}
	else {//如果要删除的是目录
		if (t->FirstChild == NULL) {//如果该目录下没有孩子（文件或目录），则直接删除
			if (t == a->root) return;//若要删除的是根节点，不执行删除，直接返回

			if (t->parent->FirstChild == t) {//如果该目录位于父亲节点的第一个儿子，则将父亲的儿子指针置为空，然后释放
				t->parent->FirstChild = t->brother;
			}
			else
			{
				for (tmp = t->parent->FirstChild; tmp != NULL; tmp = tmp->brother) {//如果不是第一个儿子，则找到该节点的前驱，将前驱的兄弟指针指向该节点的兄弟，然后释放该节点
					if (tmp->brother == t) {
						tmp->brother = t->brother;
						break;
					}
				}
			}
			free(t);
		}
		else {//如果该目录下有孩子（文件或目录），则访问下一层，再判断其孩子如何删除（并进行删除），如此，进行递归删除
			while (t->FirstChild != NULL) {//还没递归到目录树的最底层
				for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {//访问下层链表，
					if (tmp->brother == NULL) {
						deletePtr(a, tmp);//递归删除，删除tmp节点及其n辈孩子节点
						break;
					}

				}
			}
			deletePtr(a, t);//最后删除它自己（在将其孩子孙子都删除后）
		}
	}
}

void catalogTree::Delete(char *str) {//删除

	//删除操作
	nowPosition t;
	bool flag = false;
	for (t = nowPtr->FirstChild; t != NULL; t = t->brother) {
		if (strcmp(t->fileName, str) == 0) {
			flag = true;
			break;
		}
	}
	if (flag == false) {
		printf("    没有该目录或文件\n");
		return;
	}
	deletePtr(this, t);

}

void catalogTree::mkdir(char *name, nowPosition t) {//创建文件夹

	ptr tmp;
	for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
		if (strcmp(tmp->fileName, name) == 0) {//&&tmp->isFile == false
			cout << "   不能产生相同名字的目录或文件,创建失败" << '\n';
			return;
		}
	}

	tmp = (ptr)malloc(sizeof(struct TreeNode));//创建树节点
	tmp->parent = t;
	tmp->FirstChild = NULL;
	tmp->isFile = false;//false表示该节点为目录
	tmp->size = 0;
	strcpy(tmp->fileName, name);
	tmp->brother = t->FirstChild;
	t->FirstChild = tmp;

}

void catalogTree::mkfile(char *name, nowPosition t) {//创建文件
	ptr tmp;

	for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
		if (strcmp(tmp->fileName, name) == 0) {//&& tmp->isFile == true
			cout << "   不能产生相同名字的文件,创建失败" << '\n';
			return;
		}
	}

	tmp = (ptr)malloc(sizeof(struct TreeNode));//创建树结点
	tmp->parent = t;
	tmp->FirstChild = NULL;
	tmp->isFile = true;
	tmp->size = 1;
	strcpy(tmp->fileName, name);
	tmp->brother = t->FirstChild;
	t->FirstChild = tmp;
	for (tmp = t; t != NULL; t = t->parent) {
		t->size++;
	}
}