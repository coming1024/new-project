

#ifndef __HEROSHOME_SCENE_H__
#define __HEROSHOME_SCENE_H__


#include "cocos2d.h"

class HerosHome :public cocos2d::Scene
{//”¢–€—°‘ÒΩÁ√Ê
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HerosHome);

    void BackToHelloWorld(cocos2d::Ref* pSender);
};

#endif 


