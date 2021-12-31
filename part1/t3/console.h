#include <bits/stdc++.h>
#include "catalogTree.h"
using namespace std;

void start()
{
	cout << "Microsoft Windows [版本 10.0.19042.928]\n";
	cout << "(c) Microsoft Corporation。保留所有权利。\n\n";
	cout << "菜单 虚拟文件目录系统\n";
	cout << "dir         列出当前目录下所有目录项\n";
	cout << "cd          查看当前路径\n";
	cout << "cd dir      当前目录变为str所表示路径的目录\n";
	cout << "cd ..       当前目录变为当前目录的父目录\n";
	cout << "mkdir str   在当前目录下创建一个名为str的子目录\n";
	cout << "mkfile str  在当前目录下创建一个名为str的文件\n";
	cout << "delete str  删除当前目录下名为str的目录或文件\n";
	cout << "save *.dat  保存虚拟目录到*.dat文件中\n";
	cout << "load *.dat  载入*.dat文件中的虚拟目录\n";
	cout << "size str    查看当前某子目录下的文件数\n";
	cout << "quit        退出\n";
}

void operate(CatalogTree T)
{
	char s[1000];
	char subs[1000];
	while (true) {
		T.cd();
		cout << "->";
		memset(s, 0, sizeof(s));
		memset(subs, 0, sizeof(subs));
		gets_s(s);
		if (strlen(s) > 3) {
			if (s[0] == 'c'&&s[1] == 'd') {//cd ..
				strncpy(subs, s + 3, strlen(s) - 3);
				if (strcmp(subs, "..") == 0) {
					T.cdPre();
				}
				else {//cd str
					T.cdStr(subs);
				}
			}
			else if (strlen(s) > 6 && s[0] == 'm'&&s[1] == 'k'&&s[2] == 'd'&&s[3] == 'i'&&s[4] == 'r') {//mkdir str
				strncpy(subs, s + 6, strlen(s) - 6);
				T.mkdir(subs, T.currentPosition);
			}
			else if (strlen(s) > 7 && s[0] == 'm'&&s[1] == 'k'&&s[2] == 'f'&&s[3] == 'i'&&s[4] == 'l'&&s[5] == 'e') {//mkfile str
				strncpy(subs, s + 7, strlen(s) - 7);
				T.mkfile(subs, T.currentPosition);
			}
			else if (strlen(s) > 7 && s[0] == 'd'&&s[1] == 'e'&&s[2] == 'l'&&s[3] == 'e'&&s[4] == 't'&&s[5] == 'e') {//delete str
				strncpy(subs, s + 7, strlen(s) - 7);
				T.Delete(subs);
			}
			else if (strlen(s) == 4 && strcmp(s, "quit") == 0) {//quit
				return ;
			}
			else if (strlen(s) == 4 && strcmp(s, "help") == 0) {//help
				cout << "Microsoft Windows [版本 10.0.19042.928]\n";
				cout << "(c) Microsoft Corporation。保留所有权利。\n\n";
				cout << "菜单 虚拟文件目录系统\n";
				cout << "dir         列出当前目录下所有目录项\n";
				cout << "cd          查看当前路径\n";
				cout << "cd dir      当前目录变为str所表示路径的目录\n";
				cout << "cd ..       当前目录变为当前目录的父目录\n";
				cout << "mkdir str   在当前目录下创建一个名为str的子目录\n";
				cout << "mkfile str  在当前目录下创建一个名为str的文件\n";
				cout << "delete str  删除当前目录下名为str的目录或文件\n";
				cout << "save *.dat  保存虚拟目录到*.dat文件中\n";
				cout << "load *.dat  载入*.dat文件中的虚拟目录\n";
				cout << "size str    查看当前某子目录下的文件数\n";
				cout << "quit        退出\n";
			}
			else if (strlen(s) > 5 && s[0] == 's'&&s[1] == 'a'&&s[2] == 'v'&&s[3] == 'e') {//save
				strncpy(subs, s + 5, strlen(s) - 5);
				char filePath[100] = "D:\\";
				strcat(filePath, subs);
				T.save(filePath);
				T.ListDirToFile(T.root, 0, stdout);
				cout<<"保存成功\n";
				//T.mkfile(subs, T.currentPosition);
			}
			else if (strlen(s) > 5 && s[0] == 'l'&&s[1] == 'o'&&s[2] == 'a'&&s[3] == 'd') {//load *.dat
				strncpy(subs, s + 5, strlen(s) - 5);
				char filePath[100] = "D:\\";
				strcat(filePath, subs);
				T.load(filePath);
				T.ListDirToFile(T.root, 0, stdout);
				cout << "载入成功\n";
			}
			else if (strlen(s) > 5 && s[0] == 's'&&s[1] == 'i'&&s[2] == 'z'&&s[3] == 'e') {//size str
				strncpy(subs, s + 5, strlen(s) - 5);

				T.size(subs);
			}
			else {
				cout << "    没有此命令\n";
			}
		}
		else {
			if (strlen(s) == 3) {
				if (strcmp(s, "dir") == 0) {//dir
					T.ListDir();
				}
				else {
					cout << "    没有此命令\n";
				}
			}
			else if (strlen(s) == 2) {//cd
				if (strcmp(s, "cd") == 0) {
					T.cd();
					cout << "\n";
				}
				else
					cout << "    没有此命令\n";
			}
			else if (strlen(s) == 1) {//p
				if (s[0] == 'p') {//打印目录结构
					T.ListDirToFile(T.root, 0, stdout);
				}
				else {
					cout << "    没有此命令\n";
				}
			}
			else {
				cout << "    没有此命令\n";
			}
		}
	}
}