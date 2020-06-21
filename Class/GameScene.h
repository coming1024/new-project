#ifndef __GAMESCENE_H__//Ö÷½çÃæ
#define __GAMESCENE_H__

#include "ParentScene.h"
#include "cocos2d.h"

//Ó¢ÐÛ´´½¨
#include "qishi.h"
#include "Bullet.h"
#include "equipment.h"
#include "hero.h"

class GameScene : public ParentScene
{
public:
    GameScene();
    ~GameScene();


    //´´½¨³¡¾°
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

    //·µ»ØÖ÷½çÃæ
    void BackToHomeScene();


};

#endif // __HELLOWORLD_SCENE_H__