#ifndef __SETTINGSCENE_H__
#define __SETTINGSCENE_H__

#include "cocos2d.h"

class SettingScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);
	void volumeControl(cocos2d::Ref* pSender);
	//void volumeDown(cocos2d::Ref* pSender);
	void backtoHelloWorld(cocos2d::Ref* pSender);
};

#endif // !__INFOSCENE_H__


