#if true

/*
	Program LevelEnv �ؿ�����
	File version alpha 0.4
	TC202006201042
	ERR=ETH (P.Q.)
*/

#include "LevelEnv.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

LevelEnv::LevelEnv()
{
	VisibleSize = Director::getInstance()->getVisibleSize();
	Origin = Director::getInstance()->getVisibleOrigin();
	Audio = "RH_SRYAudio/Astrodophin.mp3"; //sry�Ļ���
	AudioSwitch = "RH_SRYAudio/EMBER_GeometryDash_(WPerShi Remix).mp3"; //sry������
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

#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Audio, true);

	srand((unsigned int)time(NULL)); //��ʼ�����������

	auto title = Label::createWithTTF("Level Environment Preview", "fonts/Marker Felt.ttf", 24); //���⣬������
	if (title != nullptr)
	{
		title->setPosition(Vec2(Origin.x + VisibleSize.width / 2, Origin.y + VisibleSize.height - title->getContentSize().height));
		this->addChild(title, 1);
	}

	//				��ֱ��С
	//				|	ˮƽ��С
	//				|	|	��ڸ���
	//				|	|	|	���ڸ���
	//				|	|	|	|	�ϰ�����
	//				|	|	|	|	|	���Ӹ���
	//				|	|	|	|	|	|
	MGM::Cmap PtMap(36, 50);
	if (!PtMap.GenerateMap(1, 3, 200, 100)); //false��δ�ɹ����ɵ�ͼ
	Vec2 manchor = Vec2(100, VisibleSize.height - 100); //��ͼ���Ͻ�ê��
	double mscale = 0.25; //��ͼ����
	Node* BackGround = PtMap.MapInstantiate(-1); //��ͼ����
	BackGround->setPosition(manchor);
	BackGround->setScale(mscale);
	addChild(BackGround, -1);
	Node* Physic = PtMap.MapInstantiate(0); //��ͼ����
	Physic->setPosition(manchor);
	Physic->setScale(mscale);
	addChild(Physic, 0);
	Node* Foreground = PtMap.MapInstantiate(1); //��ͼǰ��
	Foreground->setPosition(manchor);
	Foreground->setScale(mscale);
	addChild(Foreground, 2);


	//�����zorder���ó�1


#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(AudioSwitch, true);

	//û�������������棬���ǿ�����
	initWithPhysics();
	/*
	//��ȫû��������������
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	*/

	return true;
}

/*
	Program LevelEnv �ؿ�����
	End
*/

#endif