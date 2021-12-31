#include <bits/stdc++.h>
#include "catalogTree.h"
using namespace std;

void start()
{
	cout << "Microsoft Windows [�汾 10.0.19042.928]\n";
	cout << "(c) Microsoft Corporation����������Ȩ����\n\n";
	cout << "�˵� �����ļ�Ŀ¼ϵͳ\n";
	cout << "dir         �г���ǰĿ¼������Ŀ¼��\n";
	cout << "cd          �鿴��ǰ·��\n";
	cout << "cd dir      ��ǰĿ¼��Ϊstr����ʾ·����Ŀ¼\n";
	cout << "cd ..       ��ǰĿ¼��Ϊ��ǰĿ¼�ĸ�Ŀ¼\n";
	cout << "mkdir str   �ڵ�ǰĿ¼�´���һ����Ϊstr����Ŀ¼\n";
	cout << "mkfile str  �ڵ�ǰĿ¼�´���һ����Ϊstr���ļ�\n";
	cout << "delete str  ɾ����ǰĿ¼����Ϊstr��Ŀ¼���ļ�\n";
	cout << "save *.dat  ��������Ŀ¼��*.dat�ļ���\n";
	cout << "load *.dat  ����*.dat�ļ��е�����Ŀ¼\n";
	cout << "size str    �鿴��ǰĳ��Ŀ¼�µ��ļ���\n";
	cout << "quit        �˳�\n";
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
				cout << "Microsoft Windows [�汾 10.0.19042.928]\n";
				cout << "(c) Microsoft Corporation����������Ȩ����\n\n";
				cout << "�˵� �����ļ�Ŀ¼ϵͳ\n";
				cout << "dir         �г���ǰĿ¼������Ŀ¼��\n";
				cout << "cd          �鿴��ǰ·��\n";
				cout << "cd dir      ��ǰĿ¼��Ϊstr����ʾ·����Ŀ¼\n";
				cout << "cd ..       ��ǰĿ¼��Ϊ��ǰĿ¼�ĸ�Ŀ¼\n";
				cout << "mkdir str   �ڵ�ǰĿ¼�´���һ����Ϊstr����Ŀ¼\n";
				cout << "mkfile str  �ڵ�ǰĿ¼�´���һ����Ϊstr���ļ�\n";
				cout << "delete str  ɾ����ǰĿ¼����Ϊstr��Ŀ¼���ļ�\n";
				cout << "save *.dat  ��������Ŀ¼��*.dat�ļ���\n";
				cout << "load *.dat  ����*.dat�ļ��е�����Ŀ¼\n";
				cout << "size str    �鿴��ǰĳ��Ŀ¼�µ��ļ���\n";
				cout << "quit        �˳�\n";
			}
			else if (strlen(s) > 5 && s[0] == 's'&&s[1] == 'a'&&s[2] == 'v'&&s[3] == 'e') {//save
				strncpy(subs, s + 5, strlen(s) - 5);
				char filePath[100] = "D:\\";
				strcat(filePath, subs);
				T.save(filePath);
				T.ListDirToFile(T.root, 0, stdout);
				cout<<"����ɹ�\n";
				//T.mkfile(subs, T.currentPosition);
			}
			else if (strlen(s) > 5 && s[0] == 'l'&&s[1] == 'o'&&s[2] == 'a'&&s[3] == 'd') {//load *.dat
				strncpy(subs, s + 5, strlen(s) - 5);
				char filePath[100] = "D:\\";
				strcat(filePath, subs);
				T.load(filePath);
				T.ListDirToFile(T.root, 0, stdout);
				cout << "����ɹ�\n";
			}
			else if (strlen(s) > 5 && s[0] == 's'&&s[1] == 'i'&&s[2] == 'z'&&s[3] == 'e') {//size str
				strncpy(subs, s + 5, strlen(s) - 5);

				T.size(subs);
			}
			else {
				cout << "    û�д�����\n";
			}
		}
		else {
			if (strlen(s) == 3) {
				if (strcmp(s, "dir") == 0) {//dir
					T.ListDir();
				}
				else {
					cout << "    û�д�����\n";
				}
			}
			else if (strlen(s) == 2) {//cd
				if (strcmp(s, "cd") == 0) {
					T.cd();
					cout << "\n";
				}
				else
					cout << "    û�д�����\n";
			}
			else if (strlen(s) == 1) {//p
				if (s[0] == 'p') {//��ӡĿ¼�ṹ
					T.ListDirToFile(T.root, 0, stdout);
				}
				else {
					cout << "    û�д�����\n";
				}
			}
			else {
				cout << "    û�д�����\n";
			}
		}
	}
}