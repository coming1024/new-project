

#ifndef __GAMESCENE_H__//主界面
#define __GAMESCENE_H__

#include "cocos2d.h"

//英雄创建
#include "qishi.h"
#include "Bullet.h"
#include "equipment.h"
#include "hero.h"
#include "Buff.h"
#include "Monster.h"///

class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    ~GameScene();


    //创建场景
    static cocos2d::Scene* createScene();
    virtual bool init();
    bool isRectCollision(CCRect rect1, CCRect rect2);///
    CREATE_FUNC(GameScene);

    //返回主界面
    void BackToHomeScene();
private:
    Monster* monster1;

};

#endif // __HELLOWORLD_SCENE_H__
