#include<iostream>
#include<fstream>
#include"pigsty.h"
#include<time.h>
#include<iomanip>
using namespace std;
//����
PigFarm::PigFarm() {
	cntnum = 0;
	isblackspecies = 0;
	head = NULL;
}
//��ȡС������ 
int PigFarm::getspecies1() {
	int count = 0;
	for (int i = 0; i < cntnum; i++) {
		if (getspecies(i) == 1)
			count++;
	}
	return count;
}
//��ȡС������ 
int PigFarm::getspecies2() {
	int count = 0;
	for (int i = 0; i < cntnum; i++) {
		if (getspecies(i) == 2)
			count++;
	}
	return count;
}
//��ȡ������ 
int PigFarm::getspecies3() {
	int count = 0;
	for (int i = 0; i < cntnum; i++) {
		if (getspecies(i) == 3)
			count++;
	}
	return count;
}
//��ȡ����Ȧ�������� 
int PigFarm::getcount() {
	return cntnum;
}
//�ж��Ƿ�ΪС�� 
int PigFarm::getisBlackPig() {
	return isblackspecies;
}
//��ȡ��Ȧͷָ��               
pig* PigFarm::gethead() {
	return head;
}
//�����β�巨 
void PigFarm::addpig(pig* p) {
	cntnum++;
	p->next = NULL;
	if (head == NULL) {
		head = p;
	}
	else {
		pig* p1 = head;
		while (p1->next) {
			p1 = p1->next;
		}
		p1->next = p;
	}
}
//��ȡ��i�����Ʒ�� 
int PigFarm::getspecies(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		p = p->next;
	}
	return p->species;
}

//��ȡ��i�������� 
double PigFarm::getweight(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		p = p->next;
	}
	return p->weight;
}
//��ȡ��i����������·� 
int PigFarm::getgrowmonth(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		p = p->next;
	}
	return p->growmonth;
}
//��ȡ��i������������ 
int PigFarm::getgrowday(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		p = p->next;
	}
	return p->growday;
}

//��ȡ���ճ��ۡ���Ȧ 
double PigFarm::getprice() {
	double sellprice = 0;
	if (head == 0)
		return 0;
	int month, day, flag = 0;
	pig* p = head, * p1 = p;
	//����ѭ���ж�ÿͷ�� 
	while (p) {
		month = p->growmonth;
		day = p->growday;
		while (day >= 30) {
			day -= 30;
			month++;
		}
		//�·ݴ���12���������ش���75kg 
		if (month >= 12 || p->weight > 75) {
			if (cntnum == 1) {
				setisBlackPig(0);
				head = NULL;
				delete p;
				cntnum--;
				break;
			}
			//������ֻʣһͷ����Ҫ����������ͷ�ָ�룬Ҫ����ѭ��  
			// С�� 
			if (p->species == 1) {
				sellprice += 30 * p->weight;
			}
			//С�� 
			if (p->species == 2) {
				sellprice += 14 * p->weight;
			}
			//�� 
			if (p->species == 3) {
				sellprice += 12 * p->weight;
			}
			
			//�ҿվ��� 
			p1->next = p->next;
			delete p;
			p = p1->next;
			cntnum--;
			continue;
		}
		else if (flag == 0) {
			flag = 1;
			head = p;
		}
		p1 = p;
		p = p1->next;
	}
	return sellprice;  //��øø���Ȧ�����ܼ� 
}

//����������ļ� 
void PigFarm::save(ofstream& savefile) {

	if (head == NULL) {
		savefile << '$' << endl;
		return;
	}
	else {
		pig* p = head;
		int i = 0;
		savefile << cntnum << endl;//���ļ�д��ø���Ȧ���� ������ 
		while (p) {
			savefile << getspecies(i) << "   " << getweight(i) << "   " << getgrowmonth(i) << "   " << getgrowday(i) << endl;
			//�������ļ�д��Ʒ�֣����أ��·ݣ����� 
			i++;
			p = p->next;
		}
	}
}

//��ѯ�ø���Ȧ����Ϣ 
void PigFarm::print() {
	if (cntnum == 0) {
		cout << "    ���ԣ�����Ȧ " << endl;
		return;
	}
	if (isblackspecies == 1) {
		cout << "    ���ԣ�����Ȧ " <<"������ "<< cntnum<<" ͷ"<<endl;
	}
	else
		cout << "    ���ԣ�����Ȧ " << "������ " << cntnum << " ͷ"<< endl;
	pig* p = head;
	while (p) {
		int month = p->growmonth;
		int day = p->growday;
		while (day >= 30) {
			day -= 30;
			month++;
		}
		int i = p->number;
		cout <<"    "<< i << "����";
		if (p->species == 1)cout << "����     ";
		if (p->species == 2)cout << "С����   ";
		if (p->species == 3)cout << "��׻��� ";
		cout<<"����:"<<setw(5)<< p->weight << "Kg  ";
		cout << "����ʱ��:  " << month << "��" << day << "��" << endl;
		p = p->next;
	}
}
//ˢ�µڶ������� 
void PigFarm::next(int nexttime) {
	srand((unsigned)time(NULL));
	pig* p = head;
	while (p) {
		p->weight += (double)(rand() % 12) * nexttime / 10;//(ֱ��ȡ��1.2���а� 
		if (nexttime == 1)	p->growday++;
		else p->growmonth++;
		p = p->next;  //���� 
	}
}

//���Ҹø���Ȧĳ���ط���û���� 
bool PigFarm::search(int number) {
	pig* p = head;
	while (p) {
		if (p->number == number)
			return true;
		else
			p = p->next;
	}
	return false;
}

//��Ȧȫ�����
void PigFarm::clearpigjuan() {
	if (head == NULL) {
		return;
	}
	else {
		pig* p = head;
		pig* p1 = p;
		cntnum = 0;
		setisBlackPig(0);
		head = NULL;
		while (p) {
			p1 = p;
			p = p->next;
			delete p1;
		}
		delete p;
	}
}
//�������У�����Ʒ�ֲ������� 
void PigFarm::insert(int species) {
	pig* p = new pig;
	srand((unsigned)time(NULL));
	p->species = species;
	p->weight = double(rand() % 30 + 20);
	p->growmonth = 0;
	p->growday = 0;
	if (head == NULL) {
		p->number = 0;
		p->next = NULL;
		head = p;
		cntnum++;
		return;
	}
	if (head->number != 0) {
		p->number = 0;
		p->next = head;
		head = p;
		cntnum++;
		return;
	}
	else {
		pig* p1 = head, * p2 = p1;
		int k = 0;
		while (p1->number == k && p1->next) {
			k++;
			p2 = p1;
			p1 = p1->next;
		}
		if (p1->next == NULL) {
			p->number = cntnum;
			p->next = NULL;
			p1->next = p;
		}
		else {
			p->number = k;
			p2->next = p;
			p->next = p1;
		}
		cntnum++;
	}
}
void PigFarm::setisBlackPig(int i) {
	isblackspecies = i;
}
