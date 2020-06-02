#include "qishi.h"
qishi* qishi::create(SpriteFrameCache* cache, char* s)
{
    qishi* player = new qishi();
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    if (player && player->initWithSpriteFrame(cache->spriteFrameByName(s)))
    {
        //普攻
        player->_commonATK = 2;
        auto equipmentCache = SpriteFrameCache::sharedSpriteFrameCache();
        equipmentCache->addSpriteFramesWithFile("weapon.plist");
        auto bulletCache = SpriteFrameCache::sharedSpriteFrameCache();
        bulletCache->addSpriteFramesWithFile("bullet.plist");
        auto bulletFrame = bulletCache->getSpriteFrameByName("ptgj.png");
        //近战攻击特效
        SpriteFrame* framejzxfw;
        Vector<SpriteFrame*> vector_frame_jzxfw;
        for (int i = 1; i < 4; i++)
        {
            framejzxfw = equipmentCache->getSpriteFrameByName(String::createWithFormat("jzxfw%d.png", i)->getCString());
            vector_frame_jzxfw.pushBack(framejzxfw);
        }

        player->equipmentOne = equipment::create(2, 3, 1, equipmentCache, "gjz.png", bulletFrame);
        player->equipmentTwo = equipment::create(3, 3, 0, equipmentCache, "jzxfw0.png", vector_frame_jzxfw);

        player->nowEquipment = player->equipmentOne;

        player->addChild(player->equipmentOne, 2);
        player->addChild(player->equipmentTwo, 2);

        auto fadeout = FadeOut::create(0.01f);
        player->equipmentTwo->runAction(fadeout);

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
    //近战/未完善
    if (nowEquipment->_type == 0)
    {
        auto jz_animation = Animation::createWithSpriteFrames(this->nowEquipment->vector_frame);
        jz_animation->setDelayPerUnit(0.2f);
        jz_animation->setLoops(-1);
        auto animate = Animate::create(jz_animation);

        nowEquipment->runAction(animate);
        _isAttack = true;
    }
    //远程攻击
    if (nowEquipment->_type == 1)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point touchLocation = tTouch->getLocationInView();
        touchLocation = Director::getInstance()->convertToGL(touchLocation);
        numBullet++;
        auto bulletExample = Sprite::createWithSpriteFrame(this->nowEquipment->_bullet);
        auto OneBody = PhysicsBody::createBox(bulletExample->getContentSize());
        OneBody->applyImpulse(Vect(100, 500));//冲量
        OneBody->setContactTestBitmask(0x04);
        bulletExample->setPhysicsBody(OneBody);
        bulletExample->setPosition(this->getPosition().x,this->getPosition().y);

        _pt_bullets.push_back(bulletExample);

        this->getParent()->addChild(bulletExample, numBullet);
        //确定射箭方向
        Point shootdir = touchLocation - this->getPosition();
        Point normalizeddir = ccpNormalize(shootdir);
        Point overshootdir = normalizeddir * 1000;
        Point offscreenpoint = this->getPosition() + overshootdir;
        float moveduration = 9/this->nowEquipment->_speed;
        auto moveTo = MoveTo::create(moveduration, offscreenpoint);
        //箭的角度旋转
        float angleRadians = atanf((float)shootdir.y / (float)shootdir.x);
        float cocosAngle = CC_RADIANS_TO_DEGREES(angleRadians);
        cocosAngle = -cocosAngle;
        auto rotateTo = RotateTo::create(0.01f, cocosAngle);
        auto seq = Sequence::create(rotateTo, moveTo, NULL);
        bulletExample->runAction(seq);
    }
    return true;
}
bool qishi::stopcommonAttack(Touch* tTouch, Event* eEvent)
{
    if (_isAttack == true)
    {
        nowEquipment->stopAllActions();
    }
    return true;
}
bool qishi::take_buff(Buff* buff)
{
    return true;
}
bool qishi::clear_buff()
{
    return true;
}
void qishi::die()
{}
void qishi::take_damage()
{}
void qishi::die_animation()
{}
void qishi::setfalse()
{
    _isMoveing = false;
}