#include"mfunc.h"
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
using namespace std;
void Menu() {
	cout << "\n\n\n\n\n\n\n";
	cout << "           ********************************************************\n";
	cout << '\n';
	cout << "                            ������������ˣ�ɣ�                        \n";
	cout << '\n';
	cout << "                       ��ѡ����Ϸ������\n";
	cout << '\n';
	cout << "                                1.��ʼ��Ϸ\n";
	cout << '\n';
	cout << "                                2.����\n";
	cout << '\n';
	cout << "                                3.������ô��붼���ģ�������\n";
	cout << '\n';
	cout << "           ======================================================\n";
}
//��ȡ��Ȧ��Ϣ 
void read456() {
	ifstream read;
	read.open("456.txt");
	if (!read) {
		cout << "�򿪳�Ȧ��Ϣ�ļ�ʧ��";
		exit(0);
	}
	char flag;
	read >> flag;
	if (flag == '#') {
		cout << "�޼�¼" << endl;
		return;
	}
	int times, outpigs, sellprice, bpig, lpig, wpig;
	while (read>>times) {
		if (read.eof()) break;
		read >> outpigs >> sellprice >> bpig >> lpig >> wpig;
		cout << "��" << times / 4 + 1 << "��";
		cout << "��" << (times % 4 + 1) << "��3�£�\n";
		cout << "��Ȧ������" << outpigs << "     ������棺" << sellprice << "   ������������" << bpig << "   С��������" << lpig << "   ��׻�������" << wpig << endl;
	}
	read.close();
}
//������ 
void save_789() {
	ofstream save;
	save.open("789.txt");
	if (!save) {
		cout << "�޷����ļ�������ȫ�ֱ���ʧ�ܣ�"; exit(0);
	}
	else {
		save << allpig << "   " << money << "   " << month << "   " << day << "   " << sellcount << endl;
		cout << "�˴���Ϸ����ɹ����˳���Ϸ�밴0��������Ϸ�밴1��" << endl;
		save.close();
	}
}
//����������ȥ����Ϣ 
void save_456(int outpignum, double sellprice, int bpig, int lpig, int wpig) {
	ifstream testin;
	testin.open("456.txt");
	char flag;
	testin >> flag;
	if (flag == '#') {
		testin.close();
		ofstream testout;
		testout.open("456.txt");
		testout << '$';
		testout.close();
	}
	else testin.close();
	ofstream save("456.txt", ios::app);
	save << sellcount << endl;
	save << outpignum << "   " << sellprice << "    " << bpig << "   " << lpig << "   " << wpig  << endl;
	save.close();
}
//�������������� 
void buypig(int bpig, int lpig, int wpig, PigFarm pjuan[]) {
	//С�ڻ��Ƿ���С��Ȧ �� 
	int average = allpig / 100 + 1;
	while (bpig--) {
		for (int i = 0; i < 100; i++) {
			if (pjuan[i].getisBlackPig() == 1 && pjuan[i].getcount() <=average) {
				pjuan[i].insert(1);
				break;
			}
			if (pjuan[i].gethead() == NULL) {
				pjuan[i].insert(1);
				pjuan[i].setisBlackPig(1);
				break;
			}
		}
	}
	//ƽ������	
	
	while (1) {
		for (int i = 0; i < 100; i++) {
			if (pjuan[i].getisBlackPig() == 0) {
				if (lpig > 0 && pjuan[i].getcount() <= average) {
					pjuan[i].insert(2);
					lpig--;
				}
				if (wpig > 0 && pjuan[i].getcount() <= average) {
					pjuan[i].insert(3);
					wpig--;
				}
			}
		}
		if (lpig == 0 && wpig == 0)break;
	}
}

void Menu_pigsty_byfile(PigFarm pjuan[]) {
	ifstream getinfo;
	getinfo.open("789.txt");  // 789�Ǳ�������� 
	getinfo >> allpig >> money >> month >> day >> sellcount;
	getinfo.close();
	ifstream read;    //123 
	read.open("123.txt");
	if (!read) {
		cout << "��ȡ���������ʧ�ܣ�";
		exit(0);
	}
	int t, cntnum;
	pig* p;
	read >> t;
	for (int i = 0; i < 100; i++) {
		read >> cntnum;  //��ȡÿ����Ȧ����  
		for (int j = 0; j < cntnum; j++) {
			p = new pig;
			p->number = j;     //ÿͷ���� 
			read >> p->species;   //����Ʒ�� 
			if (p->species == '$') {     //�������$���˳� 
				delete p;
				break;
			}
			else read >> p->weight >> p->growmonth >> p->growday;  //���� ���أ��·ݣ����� 
			pjuan[i].addpig(p);  //������ӵ����� 
		}
	}
	read.close();
}
//��ʼ����Ȧ 
void Menu_pigsty(PigFarm pjuan[]) {
	allpig = 500;
	money = 20000;
	month = 0;
	day = 0;
	sellcount = 0;
	ofstream f;
	f.open("123.txt");//��123�ļ� 
	f << 0; //���ļ�����д��0 ��д��ʱ����Ҫ����ļ�һ�����ڣ������ھ���Ŀ¼�����Զ�����һ�� 
	f.close(); //�ر��ļ� 
	f.open("456.txt"); //��456�ļ� 
	f << '#'; //д��# 
	f.close(); //�ر��ļ� 
	pig* p;
	srand((unsigned)time(NULL));
	int count = 500;       //�����ʼ����500ͷ�� 
	while (count--) {
		p = new pig;
		p->species = rand() % 3 + 1;  //�����ʼ��Ʒ�� 
		p->weight = double(rand() % 30 + 20);  //�����ʼ������ 
		p->growmonth = 0;
		p->growday = 0;
		//cout << "count = " << count << "species " << p->species << "weight " << p->weight << endl;
		int i = rand() % 99;
		//	cout<<"      "<<pjuan[i].getcount()<<endl;	
		//	for(int i=0;i<100;i++){
				//���һͷ����С�ڣ����� ���Ȧ�Ǻ�Ȧ���߿�Ȧ  ���� Ȧû���� 
		if (p->species == 1 && (pjuan[i].getisBlackPig() == 1 || pjuan[i].gethead() == NULL) && pjuan[i].getcount() < 10) {
			p->number = pjuan[i].getcount();
			pjuan[i].addpig(p);  //���������Ȧ 
			pjuan[i].setisBlackPig(1);  //������Ϊ��Ȧ 
			continue;
		}
		//������� С�ڣ��������Ȧȫ�ǻ���    ��û���� 
		else if (p->species != 1 && pjuan[i].getisBlackPig() == 0 && pjuan[i].getcount() < 10) {//<10???
			p->number = pjuan[i].getcount();
			pjuan[i].addpig(p);   // 
			continue;
		}
		else count++;
		delete p;
	}
	//for (int i = 0; i < 100; i++)
		//cout << "��" << i << "����Ȧ����" << pjuan[i].getcount() << endl;
}
//�ѳ�����������ļ����� 
void savefile(PigFarm pjuan[]) {
	ofstream savefile;
	savefile.open("123.txt");
	if (!savefile) {
		cout << "�򿪱����ļ�ʧ�ܣ�";
		exit(0);
	}
	savefile << 1 << endl;//���ļ�����д��1 
	for (int i = 0; i < 100; i++) {
		pjuan[i].save(savefile);
	}
	savefile.close();
}
//��ѯ������ѡ�� 
void check() {
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "            ======================================================\n";
	cout << "                                         ��ѯ                          \n";
	cout << '\n';
	cout << "                       ��ѡ�������\n";
	cout << '\n';
	cout << "                            1.��ѯ��ǰĳһ��Ȧ�������������\n";
	cout << "                            2.��ѯĳ��Ȧĳͷ���״̬��Ϣ\n";
	cout << "                            3.ͳ��ÿ��������������ء�����ʱ��ֲ�\n";
	cout << "                            4.��ѯ��5��������ۺ͹����¼\n";
	cout << "                            5.��ӡ��ǰ�����������Ϣ\n";
	cout << "                            6.����\n";
	cout << '\n';
	cout << "            ======================================================\n";
}
//��ʼ�� 
void Menu_initial() {
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "            ======================================================\n";
	cout << "                                          �ҵ���                        \n";
	cout << '\n';
	cout << "                       ��ѡ�������\n";
	cout << '\n';
	cout << "                                 1.��ѯ\n";
	cout << "                                 2.��Ȧ������\n";
	cout << "                                 3.������Ϸ\n";
	cout << "                                 4.������Ϸ\n";
	cout << "                    5.��һ��                      6.�¸���        \n";
	cout << '\n';
	cout << "               ��ǰ�������" << money << "    ��������" << allpig << "   ����ʱ��:"; if (month > 0)cout << month << "����"; if (day >= 0)cout << day << "��";
	cout << '\n';
	cout << "           ======================================================\n";
}
//���100����Ȧ������ 
int getallpig(PigFarm pjuan[]) {
	int allcount = 0;
	for (int i = 0; i < 100; i++) {
		allcount += pjuan[i].getcount();
	}
	return allcount;
}
//
void statistic(PigFarm pjuan[])
{
	int blackTot = 0; double Bget150 = 0; int Blt30 = 0; int Bm3_6 = 0; int Bm7_12 = 0;
	int sflowerTot = 0; double SFget150 = 0;  int SFlt30 = 0; int SFm3_6 = 0; int SFm7_12 = 0;
	int bflowerTot = 0;  double BFget150 = 0; int BFlt30 = 0; int BFm3_6 = 0; int BFm7_12 = 0;
	for (int i = 0; i < 100; i++)
	{
		pig* p = pjuan[i].gethead();
		while (p)
		{
			if (p->species == 1)
			{
				blackTot++;
				if (p->weight >= 150)	Bget150++;  //���ش���150 
				if (p->growday < 30)   Blt30++;    //����ʱ��С��1���� 
				if (p->growmonth >= 3 && p->growmonth < 7) Bm3_6++;  //����ʱ��3-6���� 
				if (p->growmonth >= 7) Bm7_12++;	  //����ʱ����ڰ��� 
			}
			else if (p->species == 2)
			{
				sflowerTot++;
				if (p->weight >= 150)	SFget150++;  //���ش���150 
				if (p->growday < 30)   SFlt30++;    //����ʱ��С��1���� 
				if (p->growmonth >= 3 && p->growmonth < 7) SFm3_6++;  //����ʱ��3-6���� 
				if (p->growmonth >= 7) SFm7_12++;	  //����ʱ����ڰ��� 

			}
			else if (p->species == 3)
			{
				bflowerTot++;
				if (p->weight >= 150)	BFget150++;  //���ش���150 
				if (p->growday < 30)   BFlt30++;    //����ʱ��С��1���� 
				if (p->growmonth >= 3 && p->growmonth < 7) BFm3_6++;  //����ʱ��3-6���� 
				if (p->growmonth >= 7) BFm7_12++;	  //����ʱ����ڰ��� 	

			}
			p = p->next;
		}
	}
	cout << "���������������ֳ������£�" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "    ������������" << blackTot + sflowerTot + bflowerTot << " ͷ" << endl;
	cout << "    ����" << endl;
	cout << "         ������    " << blackTot << " ͷ" << endl;
	cout << "         ���أ�    " << endl;
	cout << "                   " << "��150��:  " << blackTot - Bget150 << " ͷ" << endl;
	cout << "                   " << "��150� " << Bget150 << " ͷ" << endl;
	cout << "         ����ʱ��: " << endl;
	cout << "                   " << "��1���£� " << Blt30 << " ͷ" << endl;
	cout << "                   " << "3-6���£� " << Bm3_6 << " ͷ" << endl;
	cout << "                   " << "�ݰ��� :  " << Bm7_12 << " ͷ" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "    С����" << endl;
	cout << "         ������    " << sflowerTot << " ͷ" << endl;
	cout << "         ���أ�    " << endl;
	cout << "                   " << "��150��:  " << sflowerTot - SFget150 << " ͷ" << endl;
	cout << "                   " << "��150� " << SFget150 << " ͷ" << endl;
	cout << "         ����ʱ��: " << endl;
	cout << "                   " << "��1���£� " << SFlt30 << " ͷ" << endl;
	cout << "                   " << "3-6���£� " << SFm3_6 << " ͷ" << endl;
	cout << "                   " << "�ݰ��� :  " << SFm7_12 << " ͷ" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "    �󻨰���" << endl;
	cout << "         ������    " << bflowerTot << " ͷ" << endl;
	cout << "         ���أ�    " << endl;
	cout << "                   " << "��150��:  " << bflowerTot - BFget150 << " ͷ" << endl;
	cout << "                   " << "��150� " << BFget150 << " ͷ" << endl;
	cout << "         ����ʱ��: " << endl;
	cout << "                   " << "��1���£� " << BFlt30 << " ͷ" << endl;
	cout << "                   " << "3-6���£� " << BFm3_6 << " ͷ" << endl;
	cout << "                   " << "�ݰ��� :  " << BFm7_12 << " ͷ" << endl;
	cout << "---------------------------------------------------------" << endl;
}

