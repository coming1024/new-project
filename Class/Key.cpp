#include "Key.h"
#include "SimpleAudioEngine.h"
#include"hero.h"
#include"qishi.h"

USING_NS_CC;
/*
Layer* Key::createLayer()
{
    auto layer = Layer::create();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return layer;
}
*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool Key::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    this->initDate();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto cache = SpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("oneHero.plist");
    //初始化英雄
    hero_qishi = qishi::create(cache, "one_r0.png");
    hero_qishi->setTag(6);
    hero_qishi->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    auto playerPos = hero_qishi->getPosition();
    hero_qishi->equipmentOne->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
    hero_qishi->equipmentTwo->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
    this->addChild(hero_qishi, 1);

    hero_qishi->_pt_bullets = CCArray::create();
    CC_SAFE_RETAIN(hero_qishi->_pt_bullets);

    auto bulletFrame = bulletCache->getSpriteFrameByName("ptzd.png");
    auto bullet = Bullet::create(3, bulletFrame);
    auto equipmentCFQ = equipment::create(2, 3, 1, 0, equipmentCache, "cfqz.png", bullet);
    equipmentCFQ->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(equipmentCFQ, 2);
    weaponArray->addObject(equipmentCFQ);

    SpriteFrame* framejzdfw;
    Vector<SpriteFrame*> vector_frame_jzdfw;
    for (int i = 0; i < 4; i++)
    {
        framejzdfw = equipmentCache->getSpriteFrameByName(String::createWithFormat("jzdfw%d.png", i)->getCString());
        vector_frame_jzdfw.pushBack(framejzdfw);
    }
    auto equipmentJZDFW = equipment::create(3, 3, 0, 0, equipmentCache, "jzdfw0.png", vector_frame_jzdfw, 35, hero_qishi->getContentSize().height+5);
    equipmentJZDFW->setPosition(visibleSize.width / 3, visibleSize.height / 2);
    this->addChild(equipmentJZDFW, 2);
    weaponArray->addObject(equipmentJZDFW);


    //设置行走
    //hero_qishi->setWalkFalse();
    //两种监听器
    auto keylistener = EventListenerKeyboard::create();
    keylistener->onKeyPressed = CC_CALLBACK_2(Key::onKeyPressed, this);
    keylistener->onKeyReleased = CC_CALLBACK_2(Key::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener,this);
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(Key::onTouchBegan, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(Key::onTouchMoved, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(Key::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

    this->schedule(schedule_selector(Key::addMonster), 1);
    this->schedule(schedule_selector(Key::upDataMABC), 0.05f);
    this->schedule(schedule_selector(Key::upDataMAPC), 0.5);
    this->schedule(schedule_selector(Key::upDataMAWC), 0.2);
    this->schedule(schedule_selector(Key::upDataDeath), 0.2);

    return true;
}

void Key::initDate()
{
    Monster = CCArray::create();
    CC_SAFE_RETAIN(Monster);
    weaponArray = CCArray::create();
    CC_SAFE_RETAIN(weaponArray);

    bulletCache = SpriteFrameCache::sharedSpriteFrameCache();
    bulletCache->addSpriteFramesWithFile("bullet.plist");
    equipmentCache = SpriteFrameCache::sharedSpriteFrameCache();
    equipmentCache->addSpriteFramesWithFile("weapon.plist");
}

void Key::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
    if (hero_qishi->getDeath()==false)
    {
        if (keycode == EventKeyboard::KeyCode::KEY_J)
        {
            hero_qishi->swithWeapon(keycode, event);
        }
        if (keycode == EventKeyboard::KeyCode::KEY_A || keycode == EventKeyboard::KeyCode::KEY_S
            || keycode == EventKeyboard::KeyCode::KEY_D || keycode == EventKeyboard::KeyCode::KEY_W
            || keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW
            || keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
        {
            hero_qishi->heroMove(keycode, event);
        }
        if (keycode == EventKeyboard::KeyCode::KEY_K)
        {
            this->playerAndWeaponCollision(weaponArray);
        }
    }
}

void Key::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (hero_qishi->getDeath() == false)
    {
        if (hero_qishi->_isMoveing == true)
        {
            hero_qishi->heroStopMove(keycode, event);
        }
    }
}

bool Key::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    if (hero_qishi->getDeath() == false)
    {
        hero_qishi->commonAttack(pTouch, pEvent);
        return true;
    }
    return false;
}
void Key::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    /*if (hero_qishi->getDeath() == false)
    {
        if (hero_qishi->nowEquipment->_isContinue)
        {
            hero_qishi->commonAttack(pTouch, pEvent);
        }
    }*/
}
void Key::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    if (hero_qishi->getDeath() == false)
    {
        hero_qishi->stopcommonAttack(pTouch, pEvent);
    }
}
bool Key::isCollision(CCRect rect1, CCRect rect2)
{
    float x1 = rect1.origin.x;
    float y1 = rect1.origin.y;
    float w1 = rect1.size.width;
    float h1 = rect1.size.height;
    float x2 = rect2.origin.x;
    float y2 = rect2.origin.y;
    float w2 = rect2.size.width;
    float h2 = rect2.size.height;
    if (x1 + w1 * 0.5 < x2 - w2 * 0.5)
    {
        return false;
    }
    else if (x1 - w1 * 0.5 > x2 + w2 * 0.5)
    {
        return false;
    }
    else if (y1 + h1 * 0.5 < y2 - h2 * 0.5)
    {
        return false;
    }
    else if (y1 - h1 * 0.5 > y2 + h2 * 0.5)
    {
        return false;
    }
    return true;
}
void Key::monsterAndPlayerCollision(CCArray* monsterArray)
{
    //通过循环每一个怪都和英雄进行碰撞检测
    for (int i = 0; i < monsterArray->count(); i++)
    {
        Sprite* monster = (Sprite*)monsterArray->objectAtIndex(i);
        if (this->isCollision(CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width-7, hero_qishi->getContentSize().height),
            CCRectMake(monster->getPosition().x, monster->getPosition().y, monster->getContentSize().width, monster->getContentSize().height)))
        {
            //这里可以通过根据怪物的伤害来更改伤的血
            hero_qishi->takeDamage(1);
        }
    }
}
void Key::monsterAndBulletCollision(CCArray* monsterArray, CCArray* bulletArray)
{
    //通过两层循环每一个怪和每一个远程子弹进行碰撞检测
    if (monsterArray->count() > 0 && bulletArray->count() > 0)
    {
        for (unsigned int i = 0; i < monsterArray->count(); i++)
        {
            Sprite* monster = (Sprite*)monsterArray->objectAtIndex(i);
            auto rect1 = CCRectMake(monster->getPosition().x, monster->getPosition().y, monster->getContentSize().width - 5, monster->getContentSize().height - 10);
            for (unsigned int j = 0; j < bulletArray->count(); j++)
            {
                Bullet* bullet = (Bullet*)bulletArray->objectAtIndex(j);
                auto rect2 = CCRectMake(bullet->getPosition().x, bullet->getPosition().y, bullet->getContentSize().width+5, bullet->getContentSize().height);
                if (monster != NULL && this->isCollision(rect1, rect2)&& bullet != NULL)
                {
                    //怪物减血,因为我这个怪物没有血 就只是一个sprite所以没有减血
                    monsterArray->removeObjectAtIndex(i);
                    monster->removeFromParentAndCleanup(true);
             
                    bulletArray->removeObjectAtIndex(j);
                    bullet->removeFromParentAndCleanup(true);
                }
            }
        }
    }
}
void Key::monsterAndWeaponCollision(CCArray* monsterArray)
{
    //设置一个武器的rect，因为要根据武器rect左右实时更新地方，所以逼不得已在这里实现，
    auto rectWeapon = CCRectMake(0, 0, 0, 0);
    if (hero_qishi->getLeftOrRight() == 0)
    {
        rectWeapon = CCRectMake(hero_qishi->getPosition().x + hero_qishi->getContentSize().width, hero_qishi->getPosition().y,
            hero_qishi->nowEquipment->getWidth(), hero_qishi->nowEquipment->getHight());
    }
    else if (hero_qishi->getLeftOrRight() == 1)
    {
        rectWeapon = CCRectMake(hero_qishi->getPosition().x - hero_qishi->getContentSize().width-hero_qishi->nowEquipment->getWidth(), hero_qishi->getPosition().y,
            hero_qishi->nowEquipment->getWidth(), hero_qishi->nowEquipment->getHight());
    }
    for (int i = 0; i < monsterArray->count(); i++)
    {
        Sprite* monster = (Sprite*)monsterArray->objectAtIndex(i);
        if (this->isCollision(rectWeapon,CCRectMake(monster->getPosition().x, monster->getPosition().y, monster->getContentSize().width, monster->getContentSize().height)))
        {
            //可以通过武器伤害加上人物伤害对怪物减血
            monsterArray->removeObjectAtIndex(i);
            monster->removeFromParentAndCleanup(true);
        }
    }
}
void Key::playerAndWeaponCollision(CCArray* weaponArray1)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto heroRect = CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width - 7, hero_qishi->getContentSize().height);
    for (int i = 0; i < weaponArray1->count(); i++)
    {
        equipment* weapon = (equipment*)weaponArray1->objectAtIndex(i);
        auto weaponRect = CCRectMake(weapon->getPosition().x, weapon->getPosition().y, hero_qishi->getContentSize().width + 5, hero_qishi->getContentSize().height + 3);
        if (this->isCollision(heroRect, weaponRect))
        {
            if (hero_qishi->nowEquipment == hero_qishi->equipmentOne)
            {
                //将被选的武器从资源除去
                weaponArray1->removeObjectAtIndex(i);
                weapon->removeFromParent();

                hero_qishi->equipmentOne->removeFromParent();
                equipment* equipTemp = hero_qishi->equipmentOne;
                weaponArray->addObject(equipTemp);
                equipTemp->setPosition(hero_qishi->getPosition().x, hero_qishi->getPosition().y);
                this->addChild(equipTemp,2);
                //被选武器加入英雄
                hero_qishi->equipmentOne = weapon;
                hero_qishi->nowEquipment = hero_qishi->equipmentOne;
                hero_qishi->addChild(hero_qishi->equipmentOne, 2);
                if (hero_qishi->getLeftOrRight() == true)
                {
                    hero_qishi->equipmentOne->setPosition(Vec2(hero_qishi->getContentSize().width / 6, hero_qishi->getContentSize().height / 2));
                }
                if (hero_qishi->getLeftOrRight() == false)
                {
                    hero_qishi->equipmentOne->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
                }
            }
            else if(hero_qishi->nowEquipment == hero_qishi->equipmentTwo)
            {
                weaponArray1->removeObjectAtIndex(i);
                weapon->removeFromParent();

                hero_qishi->equipmentTwo->removeFromParent();
                equipment* equipTemp = hero_qishi->equipmentTwo;
                weaponArray->addObject(equipTemp);
                equipTemp->setPosition(hero_qishi->getPosition().x, hero_qishi->getPosition().y);
                this->addChild(equipTemp, 2);

                hero_qishi->equipmentTwo = weapon;
                hero_qishi->nowEquipment = hero_qishi->equipmentTwo;
                hero_qishi->addChild(hero_qishi->equipmentTwo, 2);
                if (hero_qishi->getLeftOrRight() == 1)
                {
                    hero_qishi->equipmentTwo->setPosition(Vec2(hero_qishi->getContentSize().width / 6, hero_qishi->getContentSize().height / 2));
                }
                if (hero_qishi->getLeftOrRight() == 0)
                {
                    hero_qishi->equipmentTwo->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
                }
            }
        }
    }
}
void Key::upDataMABC(float t)
{
    this->monsterAndBulletCollision(Monster, hero_qishi->_pt_bullets);
}
void Key::upDataMAPC(float t)
{
    this->monsterAndPlayerCollision(Monster);
}
void Key::upDataMAWC(float t)
{
    if (hero_qishi->getIsUsingWeapon() == true)
    {
        this->monsterAndWeaponCollision(Monster);
    }
}
void Key::upDataDeath(float t)
{
    //英雄死亡的判断
    if (hero_qishi->getLifeNum() <= 0&&hero_qishi->getDeath()==false)
    {
        hero_qishi->setDeath(true);
        auto fadeout = FadeOut::create(0.01f);
        hero_qishi->runAction(fadeout);
        //接下来英雄死亡之后的回调

    }
    //接下来还有怪物死亡的判断
}

void Key::addMonster(float t)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* MonsterExample = Sprite::create("pig0.png");
    //tag
    MonsterExample->setTag(2);

    MonsterExample->setPosition(
        visibleSize.width + MonsterExample->getContentSize().width,
        MonsterExample->getContentSize().height / 2 + CCRANDOM_0_1() * (visibleSize.height - MonsterExample->getContentSize().height / 2)
    );
    Monster->addObject(MonsterExample);
    this->addChild(MonsterExample, 2);
    auto move = MoveTo::create(3, Vec2(-MonsterExample->getContentSize().width / 2, MonsterExample->getPosition().y));
    MonsterExample->runAction(move);
}
