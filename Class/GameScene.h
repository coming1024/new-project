

#ifndef __GAMESCENE_H__//主界面
#define __GAMESCENE_H__

#include "ParentScene.h"
#include "cocos2d.h"

//英雄创建
#include "qishi.h"
#include "Bullet.h"
#include "equipment.h"
#include "hero.h"
#include "Buff.h"

class GameScene : public ParentScene
{
public:
    GameScene();
    ~GameScene();


    //创建场景
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

    //返回主界面
    void BackToHomeScene();


};

#endif // __HELLOWORLD_SCENE_H__
