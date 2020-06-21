#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.3
	TC202006192221
	ERR=ETH (P.Q.)
*/

#include "LevelEnv.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
static int level = 0;
LevelEnv::LevelEnv()
{

	VisibleSize = Director::getInstance()->getVisibleSize();
	Origin = Director::getInstance()->getVisibleOrigin();
	Audio = "RH_SRYAudio/Astrodophin.mp3"; //sry的滑稽
	AudioSwitch = "RH_SRYAudio/EMBER_GeometryDash_(WPerShi Remix).mp3"; //sry的力量
}

LevelEnv::~LevelEnv()
{
	//doing nothing
}

Scene* LevelEnv::createScene()
{
	return LevelEnv::create();
}

bool LevelEnv::init()
{
	if (!Scene::init()) return false;
	this->initDate();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	srand((unsigned int)time(NULL)); //初始化随机数种子

	auto title = Label::createWithTTF("Level Environment Preview", "fonts/Marker Felt.ttf", 24); //标题，测试用
	title->setPosition(Vec2(Origin.x + VisibleSize.width / 2, Origin.y + VisibleSize.height - title->getContentSize().height));
	title->enableGlow(Color4B::BLUE);
	this->addChild(title);

	auto closeItem = MenuItemImage::create( //按钮
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(LevelEnv::Trigger, this));
	float x = Origin.x + VisibleSize.width - closeItem->getContentSize().width / 2;
	float y = Origin.y + closeItem->getContentSize().height / 2;
	closeItem->setPosition(Vec2(x, y));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	//人物的zorder设置成1
#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Audio, true);
	Node* PtMap;
	PtMap = GenerateEnv(level); //第0关
	addChild(PtMap, 0);
	//PtMap->setVisible(false);
#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(AudioSwitch, true);


	initWithPhysics();
	this->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto _PauseLayer = PauseLayer::create();
	this->addChild(_PauseLayer, 1);

	//初始化英雄
	hero_qishi = qishi::create(heroCache, "one_r0.png");
	hero_qishi->setPosition(Vec2(200, visibleSize.height / 2));
	hero_qishi->setZOrder(1);
	auto playerPos = hero_qishi->getPosition();
	this->addChild(hero_qishi, 1);
	//初始化怪物1
	monster1 = Monster::create();
	monster1->InitMonsterImage("monster.png");
	//monster1->InitMonsterImage("monster.png", "xue_back.png", "xue_fore.png");
	monster1->setPosition(ccp(visibleSize.width / 2+100, visibleSize.height / 2));
	this->addChild(monster1, 1);
	monsterArray->addObject(monster1);///

	//初始化怪物2
	monster2 = Monster::create();
	monster2->InitMonsterImage("small.png");
	//monster1->InitMonsterImage("monster.png", "xue_back.png", "xue_fore.png");
	monster2->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(monster2, 1);
	monsterArray->addObject(monster2);///

	//初始化怪物子弹
	monsterBu1 = MonsterBullet::create();
	monsterBu1->InitMonsterBulletImage("MonsterBullet.png");
	monsterBu1->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(monsterBu1, 1);
	monsterArray->addObject(monsterBu1);///
	


	//auto MonsterBullet = SpriteFrameCache::sharedSpriteFrameCache();
	//MonsterBullet->addSpriteFramesWithFile("bullet.plist");
	//auto bulletFrame = bulletCache->getSpriteFrameByName("ptgj.png");
	//auto bulletExample = Bullet::create(2, bulletFrame);
	//bulletExample->setPosition(monster2->getPositionX(),monster2->getPositionY());
	//怪物开始监听
	Node* Physic = PtMap;
	monster1->StartListen(hero_qishi, Physic);
	monsterBu1->StartBulletListen(hero_qishi, Physic);

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
	chestOne->setPosition(visibleSize.width - 150, visibleSize.height / 2);
	this->addChild(chestOne, 2);




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
	this->schedule(schedule_selector(LevelEnv::upDataAddEnergy), 0.15);
	this->schedule(schedule_selector(LevelEnv::upDataOABC), 0.01);
	this->schedule(schedule_selector(LevelEnv::upDataMABC), 0.01);
	this->schedule(schedule_selector(LevelEnv::upDataMAPC), 0.5);
	this->schedule(schedule_selector(LevelEnv::upDataMAWC), 0.2);
	this->schedule(schedule_selector(LevelEnv::upDataDeath), 0.01);


	return true;
}
Node* LevelEnv::GenerateEnv(int level)
{
	unsigned int vtsize; //地图垂直大小
	unsigned int hrsize; //地图水平大小
	unsigned int stcont; //地图入口个数
	unsigned int edcont; //地图出口个数
	unsigned int obcont; //地图障碍个数
	unsigned int bxcont; //地图箱子个数
	double strang = 0.4; //地图入口范围
	double edrang = 0.8; //地图出口范围
	switch (level)
	{
	case 0:
		vtsize = 20;
		hrsize = 27;
		stcont = 1;
		edcont = 2;
		obcont = 20;
		bxcont = 10;
		break;
	case 1:
		vtsize = 22;
		hrsize = 29;
		stcont = 1;
		edcont = 2;
		obcont = 36;
		bxcont = 16;
		break;
	case 2:
		vtsize = 24;
		hrsize = 32;
		stcont = 1;
		edcont = 2;
		obcont = 44;
		bxcont = 25;
		break;
	case 3:
		vtsize = 26;
		hrsize = 35;
		stcont = 1;
		edcont = 2;
		obcont = 55;
		bxcont = 30;
		break;
	case 4:
		vtsize = 28;
		hrsize = 37;
		stcont = 1;
		edcont = 2;
		obcont = 60;
		bxcont = 40;
		break;

	default:
		vtsize = 20;
		hrsize = 27;
		stcont = 0;
		edcont = 0;
		obcont = 0;
		bxcont = 0;
		break;
	}
	//if (GlobalMap != nullptr) delete GlobalMap;
	GlobalMap = new MGM::Cmap(vtsize, hrsize);
	if (!GlobalMap->GenerateMap(stcont, edcont, obcont, bxcont, strang, edrang))
		throw "Failed map generation";
	Node* map = GlobalMap->MapInstantiate();
	//动态调整地图缩放
	double vtscale = VisibleSize.height / ((double)vtsize * 64); //!64使用
	double hrscale = VisibleSize.width / ((double)hrsize * 64); //!64使用
	double scale;
	if (vtscale < hrscale) scale = vtscale * 0.9;
	else scale = hrscale * 0.9;
	map->setScale(scale);
	//动态调整地图偏移
	double vtoffset = VisibleSize.height / 2 + ((double)vtsize * 64 / 2 * scale); //!64使用
	double hroffset = VisibleSize.width / 2 - ((double)hrsize * 64 / 2 * scale); //!64使用
	map->setPositionY(vtoffset - 16);
	map->setPositionX(hroffset - 100);
	return map;
}

void LevelEnv::Trigger(Ref* pSender)
{
	//Director::getInstance()->end();
	level++;
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, createScene(), Color3B(0, 127, 127)));

}
void LevelEnv::initDate()
{
	weaponArray = CCArray::create();
	CC_SAFE_RETAIN(weaponArray);
	propArray = CCArray::create();
	CC_SAFE_RETAIN(propArray);
	chestArray = CCArray::create();
	CC_SAFE_RETAIN(chestArray);
	monsterArray = CCArray::create();
	CC_SAFE_RETAIN(monsterArray);

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
//返回开始界面
void LevelEnv::BackToHerosHomeScene(cocos2d::Ref* pSender)
{
	Director::sharedDirector()->replaceScene(HerosHome::createScene());
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
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
//障碍物和子弹
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
void LevelEnv::upDataOABC(float)
{
	this->obstacleAndBulletCollison(GlobalMap->Arry_Boxx, hero_qishi->_pt_bullets);
	this->obstacleAndBulletCollison(GlobalMap->Arry_Bodr, hero_qishi->_pt_bullets);
	this->obstacleAndBulletCollison(GlobalMap->Arry_Obst, hero_qishi->_pt_bullets);
	//this->obstacleAndBulletCollison(PtMap.Arry_Exit, hero_qishi->_pt_bullets);
	//this->obstacleAndBulletCollison(PtMap.Arry_Star, hero_qishi->_pt_bullets);
}
//怪和子弹
void LevelEnv::monsterAndBulletCollision(CCArray* monsterArray1, CCArray* bulletArray1)
{
	//通过两层循环每一个怪和每一个远程子弹进行碰撞检测
	if (monsterArray1->count() > 0 && bulletArray1->count() > 0)
	{
		for (unsigned int i = 0; i < monsterArray1->count(); i++)
		{
			Sprite* monster = (Sprite*)monsterArray1->objectAtIndex(i);
			auto position1 = monster->convertToWorldSpace(Point::ZERO);
			auto rect1 = CCRectMake(position1.x, position1.y, 77, 100);
			for (unsigned int j = 0; j < bulletArray1->count(); j++)
			{
				Bullet* bullet = (Bullet*)bulletArray1->objectAtIndex(j);
				auto position2 = bullet->convertToWorldSpace(Point::ZERO);
				auto rect2 = CCRectMake(position2.x, position2.y, bullet->getContentSize().width, bullet->getContentSize().height);
				if (monster != NULL && this->isCollision(rect1, rect2) && bullet != NULL)
				{
					//怪物减血,因为我这个怪物没有血 就只是一个sprite所以没有减血


					monsterArray1->removeObjectAtIndex(i);
					monster->removeFromParentAndCleanup(true);
					monster1->HurtAnimation("monster_hurt", 2, monster1->MonsterDirecton);//受伤
					bulletArray1->removeObjectAtIndex(j);
					bullet->removeFromParentAndCleanup(true);
				}
			}
		}
	}
}
void LevelEnv::upDataMABC(float)
{
	this->monsterAndBulletCollision(monsterArray, hero_qishi->_pt_bullets);
}
//怪和近战武器
void LevelEnv::monsterAndWeaponCollision(CCArray* monsterArray1)
{
	if (monsterArray1->count() > 0)
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
			rectWeapon = CCRectMake(hero_qishi->getPosition().x - hero_qishi->getContentSize().width - hero_qishi->nowEquipment->getWidth(), hero_qishi->getPosition().y,
				hero_qishi->nowEquipment->getWidth(), hero_qishi->nowEquipment->getHight());
		}
		for (int i = 0; i < monsterArray1->count(); i++)
		{
			Sprite* monster = (Sprite*)monsterArray1->objectAtIndex(i);
			auto positionMonster = monster->convertToWorldSpace(Point::ZERO);
			auto rectMonster = CCRectMake(positionMonster.x, positionMonster.y, 77, 100);
			if (this->isCollision(rectWeapon, rectMonster))
			{

				//可以通过武器伤害加上人物伤害对怪物减血
				//monsterArray1->removeObjectAtIndex(i);
				//monster->removeFromParentAndCleanup(true);
				monster1->HurtAnimation("monster_hurt", 2, monster1->MonsterDirecton);//受伤
			}
		}
	}
}
void LevelEnv::upDataMAWC(float)
{
	if (hero_qishi->getIsUsingWeapon() == true)
	{
		this->monsterAndWeaponCollision(monsterArray);
	}
}
//怪和英雄
void LevelEnv::monsterAndPlayerCollision(CCArray* monsterArray1)
{
	if (monsterArray1->count() > 0)
	{
		//通过循环每一个怪都和英雄进行碰撞检测
		for (int i = 0; i < monsterArray1->count(); i++)
		{
			Sprite* monster = (Sprite*)monsterArray1->objectAtIndex(i);
			auto positionMonster = monster->convertToWorldSpace(Point::ZERO);
			auto rectMonster = CCRectMake(positionMonster.x, positionMonster.y, 77, 100);
			if (this->isCollision(CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width - 7, hero_qishi->getContentSize().height - 3), rectMonster))
			{
				//这里可以通过根据怪物的伤害来更改伤的血
				hero_qishi->takeDamage(1);
			}
		}
	}
}
void LevelEnv::upDataMAPC(float)
{
	this->monsterAndPlayerCollision(monsterArray);
}
//死亡
void LevelEnv::upDataDeath(float t)
{
	//英雄死亡的判断
	if (hero_qishi->getCurrentLifeNum() <= 0 && hero_qishi->getDeath() == false)
	{
		hero_qishi->setDeath(true);
		auto fadeout = FadeOut::create(0.01f);
		hero_qishi->runAction(fadeout);
		Director::sharedDirector()->replaceScene(HerosHome::createScene());
		//接下来英雄死亡之后的回调
	}
	//接下来还有怪物死亡的判断
}
/*
	Program LevelEnv 关卡场景
	End
*/

#endif
