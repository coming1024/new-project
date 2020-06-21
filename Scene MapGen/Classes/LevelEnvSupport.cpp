#if true

/*
	Program LevelEnvSupport 关卡场景(人物)
	File version alpha 0.51
	TC202006210106

*/

#include "LevelEnv.h"

/***************************************
以上是原来的函数（有改动）   以下是新增函数
***************************************/

void LevelEnv::initDate(Node* PtMap)
{
	weaponArray = CCArray::create();
	CC_SAFE_RETAIN(weaponArray);
	propArray = CCArray::create();
	CC_SAFE_RETAIN(propArray);
	chestArray = CCArray::create();
	CC_SAFE_RETAIN(chestArray);

	bulletCache = SpriteFrameCache::sharedSpriteFrameCache();
	bulletCache->addSpriteFramesWithFile("bullet.plist");
	propCache = SpriteFrameCache::sharedSpriteFrameCache();
	propCache->addSpriteFramesWithFile("prop.plist");
	equipmentCache = SpriteFrameCache::sharedSpriteFrameCache();
	equipmentCache->addSpriteFramesWithFile("weapon.plist");
	chestCache = SpriteFrameCache::sharedSpriteFrameCache();
	chestCache->addSpriteFramesWithFile("chest.plist");
	heroCache = SpriteFrameCache::sharedSpriteFrameCache();
	heroCache->addSpriteFramesWithFile("oneHero.plist");


	//初始化英雄
	hero_qishi = qishi::create(heroCache, "one_r0.png");
	hero_qishi->setPosition(Vec2(200, VisibleSize.height / 2));
	//hero_qishi->setPosition(((Sprite*)(GlobalMap->Arry_Star->getRandomObject()))->getPosition() + Vec2(32, 32)); //让英雄生成在随机一个起点 //!64使用
	//auto playerPos = hero_qishi->getPosition();
	//PtMap->addChild(hero_qishi, 0);//修改
	addChild(hero_qishi, 0);
	//设置装备位置
	hero_qishi->equipmentOne->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
	hero_qishi->equipmentTwo->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
	hero_qishi->_pt_bullets = CCArray::create();
	CC_SAFE_RETAIN(hero_qishi->_pt_bullets);
	auto qishiBody = PhysicsBody::createBox(hero_qishi->getContentSize());
	qishiBody->setRotationEnable(false);
	hero_qishi->setPhysicsBody(qishiBody);
	///////////////////////
	//将宝箱放入
	auto bulletFrame = bulletCache->getSpriteFrameByName("ptzd.png");
	auto bullet = Bullet::create(3, bulletFrame);
	auto equipmentCFQ = equipment::create(2, 3, 1, 1, equipmentCache, "cfqz.png", bullet);
	SpriteFrame* frameClose;
	SpriteFrame* frameOpen;
	Vector<SpriteFrame*> vector_frame_open;
	frameClose = chestCache->getSpriteFrameByName("chestClose.png");
	vector_frame_open.pushBack(frameClose);
	frameOpen = chestCache->getSpriteFrameByName("chestOpen.png");
	vector_frame_open.pushBack(frameOpen);
	auto chestOne = Chest::creat(chestCache, "chestClose.png", vector_frame_open, equipmentCFQ);
	auto chestBody = PhysicsBody::createBox(chestOne->getContentSize());
	chestBody->setDynamic(false);
	chestOne->setPhysicsBody(chestBody);
	chestArray->addObject(chestOne);
	chestOne->setPosition(VisibleSize.width - 150, VisibleSize.height / 2);
	//Sprite* ChestReplace = (Sprite*)(GlobalMap->Arry_Boxx->getRandomObject());
	//chestOne->setPosition(convertToWorldSpace(ChestReplace->getPosition()) + Vec2(30, 30)); //让宝箱生成在随机一个盒子 //!64使用
	//chestOne->setScale(1.5);
	//ChestReplace->getParent()->setVisible(false);
	//PtMap->addChild(chestOne, 0);//修改
	addChild(chestOne, 0);


		//两种监听器
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(LevelEnv::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(LevelEnv::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(LevelEnv::onTouchBegan, this);
	touchlistener->onTouchMoved = CC_CALLBACK_2(LevelEnv::onTouchMoved, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(LevelEnv::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

	this->schedule(schedule_selector(LevelEnv::upDataHeroNature), 0.05f);
	this->schedule(schedule_selector(LevelEnv::upDataAddEnergy), 0.1);
	this->schedule(schedule_selector(LevelEnv::upDataBABC), 0.01);
}

void LevelEnv::upDataHeroNature(float t)
{
	auto progress1 = (ProgressTimer*)hero_qishi->getBloodProgress();
	progress1->setPercentage((((float)hero_qishi->getCurrentLifeNum()) / (float)hero_qishi->getTotalLifeNum()) * 100);

	auto progress2 = (ProgressTimer*)hero_qishi->getEnergyProgress();
	progress2->setPercentage((((float)hero_qishi->getCurrentEnergy()) / (float)hero_qishi->getTotalEnergy()) * 100);

	auto progress3 = (ProgressTimer*)hero_qishi->getDefenceProgress();
	progress3->setPercentage((((float)hero_qishi->getCurrentDefence()) / (float)hero_qishi->getTotalDefence()) * 100);
}
void LevelEnv::upDataAddEnergy(float t)
{
	hero_qishi->addCurrentEnergy(1);
}

void LevelEnv::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	if (hero_qishi->getDeath() == false)
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
			this->playerAndPropCollison(propArray);
			this->playerAndChestCollison(chestArray);
		}
	}
}

void LevelEnv::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (hero_qishi->getDeath() == false)
	{
		if (hero_qishi->_isMoveing == true)
		{
			hero_qishi->heroStopMove(keycode, event);
		}
	}
}

bool LevelEnv::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if (hero_qishi->getDeath() == false)
	{
		hero_qishi->commonAttack(pTouch, pEvent);
		return true;
	}
	return false;
}
void LevelEnv::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	/*if (hero_qishi->getDeath() == false)
	{
		if (hero_qishi->nowEquipment->_isContinue)
		{
			hero_qishi->commonAttack(pTouch, pEvent);
		}
	}*/
}
void LevelEnv::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (hero_qishi->getDeath() == false)
	{
		hero_qishi->stopcommonAttack(pTouch, pEvent);
	}
}
bool LevelEnv::isCollision(CCRect rect1, CCRect rect2)
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
//人和武器
void LevelEnv::playerAndWeaponCollision(CCArray* weaponArray1)
{
	auto visibleSize = VisibleSize; //兼容
	auto heroRect = CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width + 30, hero_qishi->getContentSize().height - 3);
	for (int i = 0; i < weaponArray1->count(); i++)
	{
		equipment* weapon = (equipment*)weaponArray1->objectAtIndex(i);
		auto weaponRect = CCRectMake(weapon->getPosition().x, weapon->getPosition().y, hero_qishi->getContentSize().width, hero_qishi->getContentSize().height);
		if (this->isCollision(heroRect, weaponRect))
		{
			if (hero_qishi->nowEquipment == hero_qishi->equipmentOne)
			{
				//将被选的武器从资源除去
				weaponArray1->removeObjectAtIndex(i);
				weapon->removeFromParent();
				//将落下武器加入武器库
				hero_qishi->equipmentOne->removeFromParent();
				equipment* equipTemp = hero_qishi->equipmentOne;
				weaponArray->addObject(equipTemp);
				equipTemp->setPosition(hero_qishi->getPosition().x, hero_qishi->getPosition().y);
				this->addChild(equipTemp, 2);
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
			else if (hero_qishi->nowEquipment == hero_qishi->equipmentTwo)
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
//人和道具
void LevelEnv::playerAndPropCollison(CCArray* propArray1)
{
	auto visibleSize = VisibleSize; //兼容
	auto heroRect = CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width - 7, hero_qishi->getContentSize().height);
	for (int i = 0; i < propArray1->count(); i++)
	{
		Prop* prop = (Prop*)propArray1->objectAtIndex(i);
		auto propRect = CCRectMake(prop->getPosition().x, prop->getPosition().y, prop->getContentSize().width + 5, prop->getContentSize().height + 3);
		if (this->isCollision(heroRect, propRect))
		{
			//类型为1就是加血的
			if (prop->getType() == 1)
			{
				hero_qishi->addCurrentLifeNum(prop->getAddNum());
			}
			//类型为2就是加防御的
			if (prop->getType() == 2)
			{
				hero_qishi->addCurrentDefence(prop->getAddNum());
			}
			propArray1->removeObjectAtIndex(i);
			prop->removeFromParent();
		}
	}
}
//人和宝箱
void LevelEnv::playerAndChestCollison(CCArray* chestArray1)
{
	auto visibleSize = VisibleSize; //兼容
	auto heroRect = CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width - 7, hero_qishi->getContentSize().height);
	for (int i = 0; i < chestArray->count(); i++)
	{
		Chest* chest = (Chest*)chestArray1->objectAtIndex(i);
		auto chestRect = CCRectMake(chest->getPosition().x, chest->getPosition().y, chest->getContentSize().width + 50, chest->getContentSize().height);
		if (this->isCollision(heroRect, chestRect))
		{
			auto animationOpen = Animation::createWithSpriteFrames(chest->vector_frame);
			animationOpen->setDelayPerUnit(0.2f);
			animationOpen->setLoops(1);
			auto animateOpen = Animate::create(animationOpen);
			chest->runAction(animateOpen);
			equipment* equip = chest->getEquipment();
			weaponArray->addObject(equip);
			equip->setPosition(chest->getPosition().x, chest->getPosition().y);
			this->addChild(equip, 3);
			chestArray1->removeObjectAtIndex(i);
		}
	}
}

void LevelEnv::obstacleAndBulletCollison(CCArray* obstacleArray1, CCArray* bulletArray1)
{
	if (obstacleArray1->count() > 0 && bulletArray1->count() > 0)
	{
		for (unsigned int i = 0; i < obstacleArray1->count(); i++)
		{
			Sprite* obstacle = (Sprite*)obstacleArray1->objectAtIndex(i);
			obstacle->convertToWorldSpace(Point::ZERO);
			auto position1 = obstacle->convertToWorldSpace(Point::ZERO);
			auto rect1 = CCRectMake(position1.x + 50, position1.y + 50, obstacle->getContentSize().width, obstacle->getContentSize().height);
			for (unsigned int j = 0; j < bulletArray1->count(); j++)
			{
				Bullet* bullet = (Bullet*)bulletArray1->objectAtIndex(j);
				auto position2 = bullet->convertToWorldSpace(Point::ZERO);
				auto rect2 = CCRectMake(position2.x, position2.y, bullet->getContentSize().width, bullet->getContentSize().height);
				if (obstacle != NULL && this->isCollision(rect1, rect2) && bullet != NULL)
				{

					bulletArray1->removeObjectAtIndex(j);
					bullet->removeFromParentAndCleanup(true);
				}
			}
		}
	}
}

void LevelEnv::upDataBABC(float)
{

#if true ///这里我把PtMap换成GlobalMap了

	this->obstacleAndBulletCollison(GlobalMap->Arry_Boxx, hero_qishi->_pt_bullets);
	this->obstacleAndBulletCollison(GlobalMap->Arry_Bodr, hero_qishi->_pt_bullets);
	this->obstacleAndBulletCollison(GlobalMap->Arry_Obst, hero_qishi->_pt_bullets);
	//this->obstacleAndBulletCollison(GlobalMap->Arry_Exit, hero_qishi->_pt_bullets);
	//this->obstacleAndBulletCollison(GlobalMap->Arry_Star, hero_qishi->_pt_bullets);

#else ///这里是原来的代码，要用原来的代码的话把上面改成true即可

	this->obstacleAndBulletCollison(PtMap.Arry_Boxx, hero_qishi->_pt_bullets);
	this->obstacleAndBulletCollison(PtMap.Arry_Bodr, hero_qishi->_pt_bullets);
	this->obstacleAndBulletCollison(PtMap.Arry_Obst, hero_qishi->_pt_bullets);
	//this->obstacleAndBulletCollison(PtMap.Arry_Exit, hero_qishi->_pt_bullets);
	//this->obstacleAndBulletCollison(PtMap.Arry_Star, hero_qishi->_pt_bullets);

#endif

	static int counter = 0;
	if (GlobalMap->Arry_Exit->count() > 0)//判断切关
	{

		for (unsigned int i = 0; i < GlobalMap->Arry_Exit->count(); i++)
		{
			Sprite* exit = (Sprite*)GlobalMap->Arry_Exit->objectAtIndex(i);
			exit->convertToWorldSpace(Point::ZERO);
			auto position1 = exit->convertToWorldSpace(Point::ZERO);
			auto rect1 = CCRectMake(position1.x + 50, position1.y + 50, exit->getContentSize().width, exit->getContentSize().height);
			auto heroRect = CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width - 7, hero_qishi->getContentSize().height);
			if(isCollision(rect1, heroRect))
				{
				counter++;
				}
		}
		if (counter > 500)
		{
			Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, createScene(), Color3B(0, 127, 127)));
			counter = 0;
			return;
		}
	}

}
void LevelEnv::BackToHerosHomeScene(cocos2d::Ref* pSender)
{
	Director::sharedDirector()->replaceScene(HerosHome::createScene());
}

/*
	Program LevelEnvSupport 关卡场景(人物)
	End
*/

#endif