#pragma once
#include "cocos2d.h"
#include <vector>
USING_NS_CC;

const int pkWidth = 71;//�ƵĿ�
const int pkHeight = 96;//�Ƶĸ�
const int pkJianJu = 100;//������֮��ļ��
const int PKCHUHEIGHT = 205;

//��ɫ
enum HuaSe	
{
	TU = 0,
	HUO,
	MU,
	SHUI,
	JIN,
	DAO,
	HuaSeBM = 6     //��ɫ����
};


//�ƺ�
enum PaiHao
{
	Yi = 0,Er,San,Si,Wu,Liu,Qi,Ba,Jiu,Shi,Dao,Yin,Yan,
	PaiHaoBM=2 //�ƺű���

};


enum CARD_TYPE
{
	SINGLE_CARD = 1,		//����-
	DOUBLE_CARD,			//����-
	THRID_CARD,             //��������
	ERROR_CARD				//���������
};


