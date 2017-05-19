#pragma once
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
class Player : public Sprite
{
public:
	Player();
	~Player();
	void updatePkWeiZhi();//�����Ƶ�λ��
	void  initPlayerPlace(Node *parent, int random); //��ʼ����ҽ�ɫλ��
	void showFront();
	void  setRolePlace(int index);
	int getRolePlaceHuase(int index); //����λ�û�ȡ��������
	void yiwei();
private:

	void yiweiEvent(Ref *pSender, Widget::TouchEventType type);
	Node *	m_parent;
	CC_SYNTHESIZE(GameScene*, m_gameMain, GameMain);
	CC_SYNTHESIZE(__Array*, m_arrPk, ArrPk);//����ӵ�е��˿���
	CC_SYNTHESIZE(Point, m_point, Pt);//��������ĳ�ʼλ��
	CC_SYNTHESIZE(bool, m_iPlayerClass, PlayerClass);//�������:0Ϊ��ң�1Ϊ����
	std::vector<PaiXing> m_vecPX;//��������
	CC_SYNTHESIZE(bool, m_isOutPk, IsOutPk);//����Ƿ����true:�� false:����
	CC_SYNTHESIZE(int, m_jiaoIndex, JiaoIndex);//��ɫ�ڵڼ�����
	CC_SYNTHESIZE(Button*, m_role, Role);//��ɫ����ͷ��
	CC_SYNTHESIZE(int, m_iBloodNum, BloodNum);//���Ѫֵ



};

//ˮ1��2ľ3ľ4��5��6��7ˮ8��9