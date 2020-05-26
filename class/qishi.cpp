#include "qishi.h"
qishi* qishi::create(SpriteFrameCache* cache, char* s)
{
    qishi* player = new qishi();
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    if (player && player->initWithSpriteFrame(cache->spriteFrameByName(s)))
    {
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
            auto moveto_up = MoveTo::create(time1 / 100, Vec2(this->getPosition().x, visibleSize.height));
            this->runAction(rightmove_animate);
            this->runAction(moveto_up);
        }
        if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW || keycode == EventKeyboard::KeyCode::KEY_S)
        {
            float time2 = this->getPosition().y - origin.y;
            auto moveto_down = MoveTo::create(time2 / 100, Vec2(this->getPosition().x, origin.y));
            this->runAction(rightmove_animate);
            this->runAction(moveto_down);
        }
        if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_A)
        {
            float time3 = this->getPosition().x - origin.x;
            auto moveto_left = MoveTo::create(time3 / 100, Vec2(origin.x, this->getPosition().y));
            this->runAction(leftmove_animate);
            this->runAction(moveto_left);
        }
        if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keycode == EventKeyboard::KeyCode::KEY_D)
        {
            float time4 = visibleSize.width - this->getPosition().x;
            auto moveto_right = MoveTo::create(time4 / 100, Vec2(visibleSize.width, this->getPosition().y));
            this->runAction(rightmove_animate);
            this->runAction(moveto_right);
        }
        _isMoveing = true;
        return true;
    }
}
bool qishi::heroStopMove(EventKeyboard::KeyCode keycode, Event* event)
{
    this->stopAllActions();
    _isMoveing = false;
    return true;
}