#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Player : public Object
{
public:
	Player();
	~Player();
	void updatePkWeiZhi();//�����Ƶ�λ��
	
private:

	CC_SYNTHESIZE(__Array*,m_arrPk,ArrPk);//����ӵ�е��˿���
	CC_SYNTHESIZE(Point,m_point,Point);//��������ĳ�ʼλ��
	CC_SYNTHESIZE(bool,m_bMine,PlayerClass);//�������:0Ϊ��ң�1Ϊ����

	CC_SYNTHESIZE(bool,m_isOutPk,IsOutPk);//����Ƿ����true:�� false:����
};

