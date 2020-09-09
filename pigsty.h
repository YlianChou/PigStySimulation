#pragma once
#include<iostream>
using namespace std;
struct pig {
	int species;
	int growday;
	int growmonth;
	double weight;
	int number;
	pig* next;
};
//��Ȧ�� 
class PigFarm {
private:
	int cntnum;
	pig* head;
	int isblackspecies;
public:

	//		pigjuan();
	//		int setcnt(int i){
	//			return i;
	//		} 
	PigFarm();
	void print();  //��ӡ 
	void addpig(pig* p); //����� 
	void searchpig(int number); //����һ����Ȧ���ĳֻ�� 
	void sellpig();
	void insert(int species);
	double getprice();   //��ü۸�

	int getspecies(int i);
	int getgrowmonth(int i);
	int getgrowday(int i);

	double getweight(int i);

	void clearpigjuan();
	//   int getallpig(pigjuan pjuan[]);
	void setisBlackPig(int i);
	//��ȡС������ 
	int getspecies1();
	//��ȡС������ 
	int getspecies2();
	//��ȡ������ 
	int getspecies3();
	//��ȡ������ 
	int getcount();
	//�ж��Ƿ�ΪС�� 
	int getisBlackPig();
	void save(ofstream& savefile);
	//��ȡ��Ȧͷָ��               
	pig* gethead();
	//ˢ�µڶ������� 
	void next(int nexttime);
	//���Ҹø���Ȧĳ���ط���û���� 
	bool search(int number);
	//�����Ȧ���ˣ� 

};

