#pragma once
#include "Global.h"
#include "vector"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#define DAOJISHI  3
class Poker;
class Player;
class Qipan;

//���� �����������
struct JiShu
{
	int pkZhi;//��ֵ
	int num; //������
	__Array* arr; //������

};
//�����������
struct PaiXing :public Ref
{
	CARD_TYPE type;
	std::vector<Poker*> vec;
};

class GameScene : public Layer
{
public:
	GameScene();
	~GameScene();
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	virtual void onEnter();
	virtual void onExit();
	void PlayerOutPaiXu(__Array* m_arrPlayerOut);
	bool Isdefend();
	bool Isdefend(bool bnpc);
	bool Isyiwei();
	void bianpai();
	bool Isjiepai(Poker *p1);
	bool IsHuixue();
	bool IsHuixue(Poker *pk);
	bool IsDefendPoker(Poker *pk, bool bnpc = false);
	bool IsAttackPoker(Poker *pk, bool bnpc = false);
	void ChoseJinmu(Poker *pk);
	void RefreshBloodNum(int iPlayer, int iBlood);
	Button* m_btnAttack; //����
	Button* m_btnQipai; //����
	Button * m_btnYiwei;//��λ	
	Button * m_btnJiepai;//����
	Button * m_btnHuixue;//��Ѫ
	__Array* m_npcattakcard;//���Թ��������
	__Array * m_playerattackcard;//��ҹ�������
	__Array * m_defendcar;
	int m_iOutCard;//�ֵ�˭���ƣ�����0�����1
private:
	void setWanfaVisible(Ref *pSender, Widget::TouchEventType type);

	void attacktouchEvent(Ref *pSender, Widget::TouchEventType type);
	void tioaguotouchEvent(Ref *pSender, Widget::TouchEventType type);
	void setgameEvent(Ref *pSender, Widget::TouchEventType type);
	void yiweiEvent(Ref *pSender, Widget::TouchEventType type);
	void jiepaiEvent(Ref *pSender, Widget::TouchEventType type);
	void huixueEvent(Ref *pSender, Widget::TouchEventType type);
	void QiPai(bool bchu, bool bhui = false, Poker *pJiedepai = NULL);
	void GiveUppai();
	void func(Node* pSender, void* pData);
	void update(float delta);
	void MovePk(Player* play, Poker* pk);
	bool xiPai();
	bool initBackGround();//���ر���
	bool initPlayer();//��ʼ�������Ϣ
	bool createPoker();
	bool loadPoker();

	void sendPk();
	void OutCard(float delta);//����
	void RobootAction();

	void feizi(bool bMine, const char *name, int icostblood = 0);
	void buPai(bool bnpc);
	void buPai(bool bnpc, Poker *pk); //��һ����
	void checkCard();
	Poker *m_pBianpk;

private:
	bool m_battk;//����ģʽ���Ƿ���ģʽ
	Text * m_time;
	Text * m_time2;
	int  m_iBianIndex;
	Node * m_pWanfa;
	ImageView * m_clock;
	ImageView * m_clock2;

    ImageView * m_player1;
    ImageView * m_player2;
    
    Text* m_TipTetx;
	float m_fTime;
	float m_fTime2;
	int m_iAddHp;
	Button *m_setBtn;
	Text *m_bloddNum1; //�ҷ�Ѫ��
	Text *m_bloddNum2; //����Ѫ��
	int m_iSendPk;//�ѷ����ڼ�����
	CC_SYNTHESIZE(Player*, m_player, player);//���
	CC_SYNTHESIZE(Player*, m_playerOut, PlayerOut);//��ҳ�����
	CC_SYNTHESIZE(__Array*, m_arrPlayerOut, ArrPlayerOut);//���ѡ��Ҫ������

	Player* m_npcOne;//����
	Player* m_npcOneOut;//���Գ�����

	__Array* m_arrGenPk;//Ҫ������

	bool m_isSend;
	int m_iState;//��ǰ״̬ 0������״̬  2������״̬ 3�����״̬
	Qipan *m_pBg;
	__Array* m_arrPokers;//���е���
	__Array* m_arrResulst;//��ȥ�������ʣ�����
	Size m_winSize;


};
