#ifndef __PAUSELAYER_H__
#define __PAUSELAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
class PauseLayer :public cocos2d::Layer
{
public:
	//��Ϸ�����С����
	cocos2d::Size visibleSize;

	//�������ʼֵ��С����
	cocos2d::Vec2 origin;

public:
	PauseLayer();
	~PauseLayer();

	//��ͣ������ʼ��
	static cocos2d::Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(PauseLayer);


	//��������
	Sprite* BackGround;
	MenuItemImage* PauseItem;
	Menu* menu;

	//������Ϸ
	void BackToGame(cocos2d::Ref* pSender);

	//��ͣ��test
	void GotoPauseScene(cocos2d::Ref* pSender);

	//ת�����ý���
	void GoToSettingScene(cocos2d::Ref* pSender);

	//����������
	void BackToHerosHome(cocos2d::Ref* pSender);
};

#endif // !__PAUSESCENE_H__

