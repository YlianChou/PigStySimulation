#pragma once
#include"pigsty.h"
#include<iostream>
using namespace std;
extern double money;
extern int month;
extern int day;
extern int sellcount;
extern int allpig;

void Menu();//�˵��ĳ�ʼ��

void read456();//��ȡ��Ȧ��Ϣ 
void save_789();  //��������������������·� 

//����������ȥ����Ϣ 
void save_456(int outpignum, double sellprice, int bpig, int lpig, int wpig);
//�������������� 
void buypig(int bpig, int lpig, int wpig, PigFarm pjuan[]);
//�������У�����Ʒ�ֲ������� 
void Menu_pigsty_byfile(PigFarm pjuan[]);
//��ʼ����Ȧ 
void Menu_pigsty(PigFarm pjuan[]);
//�ѳ�����������ļ����� 
void savefile(PigFarm pjuan[]);
//��ѯ������ѡ�� 
void check();
//��ʼ�� 
void Menu_initial();
//���100����Ȧ������ 
int getallpig(PigFarm pjuan[]);
//�������
void statistic(PigFarm pjuan[]);

