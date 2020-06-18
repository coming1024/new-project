#ifndef __PAUSELAYER_H__
#define __PAUSELAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
class PauseLayer :public cocos2d::Layer
{
public:
	//游戏界面大小声明
	cocos2d::Size visibleSize;

	//横纵轴初始值大小声明
	cocos2d::Vec2 origin;

public:
	PauseLayer();
	~PauseLayer();

	//暂停场景初始化
	static cocos2d::Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(PauseLayer);


	//精灵声明
	Sprite* BackGround;
	MenuItemImage* PauseItem;
	Menu* menu;

	//继续游戏
	void BackToGame(cocos2d::Ref* pSender);

	//暂停键test
	void GotoPauseScene(cocos2d::Ref* pSender);

	//转到设置界面
	void GoToSettingScene(cocos2d::Ref* pSender);

	//返回主界面
	void BackToHerosHome(cocos2d::Ref* pSender);
};

#endif // !__PAUSESCENE_H__

