#if true

/*
	Program LevelEnv �ؿ�����(�ϲ�)
	File version alpha 0.51
	TC202006210106
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
	Audio = "RH_SRYAudio/Astrodophin.mp3"; //sry�Ļ���
	AudioSwitch = "RH_SRYAudio/EMBER_GeometryDash_(WPerShi Remix).mp3"; //sry������
	GlobalMap = nullptr;
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

	srand((unsigned int)time(NULL)); //��ʼ�����������

	auto title = Label::createWithTTF("Level Environment Preview", "fonts/Marker Felt.ttf", 24); //���⣬������
	title->setPosition(Vec2(Origin.x + VisibleSize.width / 2, Origin.y + VisibleSize.height - title->getContentSize().height));
	title->enableGlow(Color4B::BLUE);
	this->addChild(title);
	
	auto closeItem = MenuItemImage::create( //���԰�ť
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(LevelEnv::Trigger, this));
	float x = Origin.x + VisibleSize.width - closeItem->getContentSize().width / 2;
	float y = Origin.y + closeItem->getContentSize().height / 2;
	closeItem->setPosition(Vec2(x, y));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//��������
	initWithPhysics();
	this->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto _PauseLayer = PauseLayer::create();
	this->addChild(_PauseLayer, 1);

#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Audio, true);

	//��ͼ����
	Node* PtMap;
	PtMap = GenerateEnv(level); //��0��
	addChild(PtMap, 0);

#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(AudioSwitch, true);

	/***************************************
	������ԭ���ݣ��иĶ���       ��������������
	���������ʼ������ǰ�ˣ���������
	***************************************/

	/***************************************
	ע�⣬�����PtMap�Һ����ĳɷ�������ͼ�Ľڵ���
	Ҫ��ԭ��Cmap���PtMap�Ļ�������LevelEnv���
	public����GlobalMap���Ǹ������¼ӵģ�
	��������һ���ģ�
	�Ұ������õ�PtMap�ĵط��滻������ˣ�
	�滻ǰ�Ĵ���������·���
	***************************************/

	initDate(PtMap); //��������ĳ�ʼ��ȫ���ƶ���LevelEnvSupport��initDate()��
	
	return true;
}

Node* LevelEnv::GenerateEnv(int level)
{
	unsigned int vtsize; //��ͼ��ֱ��С
	unsigned int hrsize; //��ͼˮƽ��С
	unsigned int stcont; //��ͼ��ڸ���
	unsigned int edcont; //��ͼ���ڸ���
	unsigned int obcont; //��ͼ�ϰ�����
	unsigned int bxcont; //��ͼ���Ӹ���
	double strang = 0.4; //��ͼ��ڷ�Χ
	double edrang = 0.8; //��ͼ���ڷ�Χ
	switch (level)//������д�ؿ���������
	{
	case 0:
		vtsize = 20;
		hrsize = 27;
		stcont = 1;
		edcont = 5;
		obcont = 20;
		bxcont = 10;
		break;
	case 1:
		vtsize = 22;
		hrsize = 29;
		stcont = 1;
		edcont = 5;
		obcont = 36;
		bxcont = 16;
		break;
	case 2:
		vtsize = 24;
		hrsize = 32;
		stcont = 1;
		edcont = 4;
		obcont = 44;
		bxcont = 25;
		break;
	case 3:
		vtsize = 26;
		hrsize = 35;
		stcont = 1;
		edcont = 3;
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
	if (GlobalMap != nullptr) delete GlobalMap;
	GlobalMap = new MGM::Cmap(vtsize, hrsize);
	if (!GlobalMap->GenerateMap(stcont, edcont, obcont,bxcont,strang, edrang))
		throw "Failed map generation";
	Node* map = GlobalMap->MapInstantiate();
	//��̬������ͼ����
	double vtscale = VisibleSize.height / ((double)vtsize * 64); //!64ʹ��
	double hrscale = VisibleSize.width / ((double)hrsize * 64); //!64ʹ��
	double scale;
	if (vtscale < hrscale) scale = vtscale * 0.8;
	else scale = hrscale * 0.8;
	map->setScale(scale);
	//��̬������ͼƫ��
	double vtoffset = VisibleSize.height / 2 + ((double)vtsize * 64 / 2 * scale); //!64ʹ��
	double hroffset = VisibleSize.width / 2 - ((double)hrsize * 64 / 2 * scale); //!64ʹ��
	map->setPositionY(vtoffset-16);
	map->setPositionX(hroffset-32);
	return map;
}

void LevelEnv::Trigger(Ref* pSender) //��һ��
{
	//Director::getInstance()->end();
	level++;
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, createScene(), Color3B(0, 127, 127)));
	
}

/*
	Program LevelEnv �ؿ�����
	End
*/

#endif