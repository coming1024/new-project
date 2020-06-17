#ifndef __SETTINGSCENE_H__
#define __SETTINGSCENE_H__

#include "cocos2d.h"


//背景音乐音量
extern float BGMvolume;

//背景音乐是否播放
extern bool BGMisPlay;

class SettingScene :public cocos2d::Scene
{
public:
	//游戏界面大小声明
	cocos2d::Size VisibleSize;

	//横纵轴初始值大小声明
	cocos2d::Vec2 Origin;
public:
	SettingScene();
	~SettingScene();

	//场景初始化
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);
	
	//void BGMControl1(Ref* pSender, Control::EventType event);
	//音乐开关
	void BGMControl(cocos2d::Ref* pSender);

	//音量控制
	void VolumeControl(cocos2d::Ref* pSender);
	//返回上一个界面
	void BackToLastScene(cocos2d::Ref* pSender);
};

#endif // !__INFOSCENE_H__


