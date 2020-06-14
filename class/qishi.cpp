#include "qishi.h"
qishi* qishi::create(SpriteFrameCache* cache, char* s)
{
    qishi* player = new qishi();
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    if (player && player->initWithSpriteFrame(cache->spriteFrameByName(s)))
    {
        player->setWalkFalse();
        player->_leftOrRight = 0;
        player->setCurrentLifeNum(10);
        player->setTotalLifeNum(10);
        player->setDeath(false);
        player->setDefence(2);
        //普攻
        player->setATK(2);
        auto equipmentCache = SpriteFrameCache::sharedSpriteFrameCache();
        equipmentCache->addSpriteFramesWithFile("weapon.plist");
        //子弹
        auto bulletCache = SpriteFrameCache::sharedSpriteFrameCache();
        bulletCache->addSpriteFramesWithFile("bullet.plist");
        auto bulletFrame = bulletCache->getSpriteFrameByName("ptgj.png");
        auto bullet = Bullet::create(2, bulletFrame);
        //近战攻击特效
        SpriteFrame* framejzxfw;
        Vector<SpriteFrame*> vector_frame_jzxfw;
        for (int i = 0; i < 4; i++)
        {
            framejzxfw = equipmentCache->getSpriteFrameByName(String::createWithFormat("jzxfw%d.png", i)->getCString());
            vector_frame_jzxfw.pushBack(framejzxfw);
        }
        //初始装备设置
        player->equipmentOne = equipment::create(2, 3, 1,0, equipmentCache, "gjz.png", bullet);
        player->equipmentTwo = equipment::create(3, 5, 0,0, equipmentCache, "jzxfw0.png", vector_frame_jzxfw,25,player->getContentSize().height);
        player->nowEquipment = player->equipmentOne;
        if (player->equipmentOne->getParent() == nullptr)
        {
            player->addChild(player->equipmentOne, 2);
        }
        if (player->equipmentTwo->getParent() == nullptr)
        {
            player->addChild(player->equipmentTwo, 2);
        }
        auto fadeout = FadeOut::create(0.01f);
        player->equipmentTwo->runAction(fadeout);
        //血条设置
        player->spriteBar = Sprite::create("bar.png");
        player->addChild(player->spriteBar);
        player->spriteBar->setPosition(player->getPosition().x+ player->getContentSize().width/2, player->getContentSize().height);
        player->spriteBlood = Sprite::create("blood.png");
        player->bloodProgress = ProgressTimer::create(player->spriteBlood);
        player->bloodProgress->setType(ProgressTimer::Type::BAR);
        player->bloodProgress->setPosition(player->getPosition().x + player->getContentSize().width / 2, player->getContentSize().height);
        player->bloodProgress->setMidpoint(Point(0, 0.5));
        player->bloodProgress->setBarChangeRate(Point(1, 0));
        player->addChild(player->bloodProgress);


        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}
bool qishi::heroMove(EventKeyboard::KeyCode keycode, Event* event)
{
    if (_isMoveing == false)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto cache = SpriteFrameCache::sharedSpriteFrameCache();
        cache->addSpriteFramesWithFile("oneHero.plist");
        //左移动作
        SpriteFrame* framel;
        Vector<SpriteFrame*> vector_framel;
        for (int i = 0; i < 4; i++)
        {
            framel = cache->getSpriteFrameByName(String::createWithFormat("one_l%d.png", i)->getCString());
            vector_framel.pushBack(framel);
        }
        auto leftmove_animation = Animation::createWithSpriteFrames(vector_framel);
        leftmove_animation->setDelayPerUnit(0.2f);
        leftmove_animation->setLoops(-1);
        auto leftmove_animate = Animate::create(leftmove_animation);
        //右移动作
        SpriteFrame* framer;
        Vector<SpriteFrame*> vector_framer;
        for (int i = 0; i < 4; i++)
        {
            framer = cache->getSpriteFrameByName(String::createWithFormat("one_r%d.png", i)->getCString());
            vector_framer.pushBack(framer);
        }
        auto rightmove_animation = Animation::createWithSpriteFrames(vector_framer);
        rightmove_animation->setDelayPerUnit(0.2f);
        rightmove_animation->setLoops(-1);
        auto rightmove_animate = Animate::create(rightmove_animation);

        if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_W)
        {
            float time1 = visibleSize.height - this->getPosition().y;
            auto moveto_up = MoveTo::create(time1 / 150, Vec2(this->getPosition().x, visibleSize.height));
            this->runAction(rightmove_animate);
            this->runAction(moveto_up->clone());
            _isMoveing = true;
        }
        if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW || keycode == EventKeyboard::KeyCode::KEY_S)
        {
            float time2 = this->getPosition().y - origin.y;
            auto moveto_down = MoveTo::create(time2 / 150, Vec2(this->getPosition().x, origin.y));
            this->runAction(rightmove_animate);
            this->runAction(moveto_down);
            _isMoveing = true;
        }
        if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_A)
        {
            float time3 = this->getPosition().x - origin.x;
            auto moveto_left = MoveTo::create(time3 / 150, Vec2(origin.x, this->getPosition().y));
            this->runAction(leftmove_animate);
            this->runAction(moveto_left);
            this->equipmentOne->setPosition(Vec2(this->getContentSize().width/6, this->getContentSize().height / 2));
            this->equipmentTwo->setPosition(Vec2(this->getContentSize().width/6, this->getContentSize().height / 2));
            this->equipmentOne->setFlipX(true);
            this->equipmentTwo->setFlipX(true);
            this->setLeftOrRight(1);
            _isMoveing = true;
        }
        if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keycode == EventKeyboard::KeyCode::KEY_D)
        {
            float time4 = visibleSize.width - this->getPosition().x;
            auto moveto_right = MoveTo::create(time4 / 150, Vec2(visibleSize.width, this->getPosition().y));
            this->runAction(rightmove_animate);
            this->runAction(moveto_right);
            this->equipmentTwo->setPosition(Vec2(this->getContentSize().width/1.25 , this->getContentSize().height / 2));
            this->equipmentOne->setPosition(Vec2(this->getContentSize().width/1.25 , this->getContentSize().height / 2));
            this->equipmentOne->setFlipX(false);
            this->equipmentTwo->setFlipX(false);
            this->setLeftOrRight(0);
            _isMoveing = true;
        }
        return true;
    }
}
bool qishi::heroStopMove(EventKeyboard::KeyCode keycode, Event* event)
{
    this->stopAllActions();
    _isMoveing = false;
    return true;
}
bool qishi::commonAttack(Touch* tTouch, Event* eEvent)
{
    //近战
    if (nowEquipment->getType() == 0)
    {
        //关键在于设置 在攻击
        this->setIsUsingWeapon(true);
        auto jz_animation = Animation::createWithSpriteFrames(this->nowEquipment->vector_frame);
        jz_animation->setDelayPerUnit(float(1)/float(nowEquipment->getSpeed()));
        jz_animation->setLoops(-1);
        auto animate = Animate::create(jz_animation);
        nowEquipment->runAction(animate);
    }
    //远程攻击
    if (nowEquipment->getType() == 1)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto touchLocation = tTouch->getLocationInView();
        touchLocation = Director::getInstance()->convertToGL(touchLocation);
        //确定射箭方向
        auto shootdir = touchLocation - this->getPosition();
        auto normalizeddir = ccpNormalize(shootdir);
        auto overshootdir = normalizeddir * 1000;
        auto offscreenpoint = this->getPosition() + overshootdir;
        float moveduration = 9 / this->nowEquipment->getSpeed();
        auto moveTo = MoveTo::create(moveduration, offscreenpoint);
        //箭的角度旋转
        float angleRadians = atanf((float)shootdir.y / (float)shootdir.x);
        float cocosAngle = CC_RADIANS_TO_DEGREES(angleRadians);
        cocosAngle = -cocosAngle;
        auto rotateTo = RotateTo::create(0.01f, cocosAngle);
        auto seq1 = Sequence::create(rotateTo->clone(), moveTo->clone(), NULL);
        auto timeDelay = MoveBy::create(0.25, Vec2(0, 0));
        auto seq2 = Sequence::create(timeDelay, rotateTo->clone(), moveTo->clone(), NULL);
        //一次一颗子弹
        if (nowEquipment->getIsContinue() == false)
        {
            auto bulletExample = this->nowEquipment->_bullet->clone();
            bulletExample->setPosition(this->getPosition().x, this->getPosition().y);
            _pt_bullets->addObject(bulletExample);

            this->getParent()->addChild(bulletExample, 3);

            bulletExample->runAction(seq1);
        }
        //一次多颗子弹
        else if (nowEquipment->getIsContinue() == true)
        {
            auto bulletExampleOne = this->nowEquipment->_bullet->clone();
            bulletExampleOne->setPosition(this->getPosition().x, this->getPosition().y);
            _pt_bullets->addObject(bulletExampleOne);

            auto bulletExampleTwo = this->nowEquipment->_bullet->clone();
            bulletExampleTwo->setPosition(this->getPosition().x, this->getPosition().y);
            _pt_bullets->addObject(bulletExampleTwo);

            this->getParent()->addChild(bulletExampleOne, 3);
            this->getParent()->addChild(bulletExampleTwo, 3);
            bulletExampleOne->runAction(seq1);
            bulletExampleTwo->runAction(seq2);
        }
    }
    return true;
}
bool qishi::stopcommonAttack(Touch* tTouch, Event* eEvent)
{
    if (this->getIsUsingWeapon() == true)
    {
        nowEquipment->stopAllActions();
        this->setIsUsingWeapon(false);
    }
    return true;
}
void qishi::setWalkFalse()
{
    _isMoveing = false;
}