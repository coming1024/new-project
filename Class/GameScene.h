

#ifndef __GAMESCENE_H__//������
#define __GAMESCENE_H__

#include "cocos2d.h"

//Ӣ�۴���
#include "qishi.h"
#include "Bullet.h"
#include "equipment.h"
#include "hero.h"
#include "Buff.h"

class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    ~GameScene();


    //��������
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

    //����������
    void BackToHomeScene();


};

#endif // __HELLOWORLD_SCENE_H__