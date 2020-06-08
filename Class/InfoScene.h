#ifndef __INFOSCENE_H__
#define __INFOSCENE_H__

#include "cocos2d.h"

class InfoScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(InfoScene);
	void backtoHelloWorld(cocos2d::Ref* pSender);
};

#endif // !__INFOSCENE_H__

