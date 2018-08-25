#include "SceneStart.h"
#include "ui/CocosGUI.h"
using namespace ui;

#define SPACE_Z (5)
#define PLANET_Z (10)
#define STATION_Z (15)
#define TITLE_Z (20)
//
#define METEORB_Z (6)
#define METEORF_Z (16)

#define STAR_P ("UI/star0.png")
#define STAR_N ("UI/star")

#define PLANET_P ("UI/planet.png")
#define STATION_P ("UI/station.png")
#define TITLE_P ("UI/title.png")

//���ǵ�plist·��
#define METEOR_P ("Particle/meteor.plist")
#define METEORT_P ("Particle/meteor.png")

Scene * SceneStart::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneStart::create();
	scene->addChild(layer);
	return scene;
}

bool SceneStart::init()
{
	if (!Layer::init()) {
		return false;
	}

	//��ʼ�����������
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		srand((unsigned int)(now.tv_sec * 1000 + now.tv_usec / 1000));
	}

	//��ʼ��UI
	initUI();
	//��ʼ�����
	initTouch();
	//��ʼ����ʱ��
	{
		timer_star = 0;
		time_star1 = 1.0f;
		timer_star = 0;
		time_star1 = 2.0f;
		timer_star2 = 0;
		time_star2 = 3.0f;
		timer_meteor = 0;
		time_meteor = 10.0f;
		timer_meteor1 = 0;
		time_meteor1 = 20.0f;
	}

	//������������
	//ShowStar(Vec2(100,50));
	
	//��������������Ч
	ShowMeteor();
	ShowMeteor();
	

	//��update����
	this->schedule(schedule_selector(SceneStart::update));
}

void SceneStart::initUI()
{
	//��ʾ����
	{
		Vec2 pos_title = Vec2(800, 550);

		Sprite* title = Sprite::create(TITLE_P);
		title->setPosition(pos_title);
		//������ӵ�clip�ڵ�����
		//this->addChild(title, TITLE_Z);

		//�������������Ч
		Size size_clip =title->getContentSize();
		Sprite* spark = Sprite::create("UI/spark.png");
		spark->setPosition(-size_clip.width, 0);
		ClippingNode* clip = ClippingNode::create();
		clip->setPosition(title->getPosition());
		this->addChild(clip, TITLE_Z );
		clip->setAlphaThreshold(0.05f);
		clip->setContentSize(size_clip);
		clip->setStencil(title);
		clip->addChild(title, 1);
		clip->addChild(spark, 2);
		
		auto moveto = MoveTo::create(2.0f, Vec2(size_clip.width, 0));
		auto moveback = MoveTo::create(2.0f, Vec2(-size_clip.width, 0));
		spark->runAction(RepeatForever::create(Sequence::create(moveto, moveback, nullptr, nullptr)));
	}
	//��ʾ����
	{
		Button* planet = Button::create(PLANET_P, PLANET_P, PLANET_P);
		planet->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				//log("click planet!");
				OpenPlanet();
			}
		});
		planet->setPosition(Vec2(300, 400));
		this->addChild(planet, PLANET_Z);
		//Ϊ����������Ŷ���
		auto scaleup = ScaleTo::create(0.8f, 1.01f);
		auto scaledown = ScaleTo::create(0.8f, 1.0f);
		auto seq = Sequence::create(scaleup, scaledown,nullptr,nullptr);
		auto repeat = RepeatForever::create(seq);
		planet->runAction(repeat);
	}
	//��ʾ�ռ�վ
	{
		Button* station = Button::create(STATION_P, STATION_P, STATION_P);
		station->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				//log("click station!");
				OpenStation();
			}
		});
		station->setPosition(Vec2(800, 300));
		this->addChild(station, STATION_Z);
		//Ϊ�ռ�վ�����������
		auto moveup = MoveBy::create(0.5f, Vec2(0, 5));
		auto movedown = MoveBy::create(0.5f, Vec2(0, -5));
		auto seq = Sequence::create(moveup, movedown,nullptr,nullptr);
		auto repeat = RepeatForever::create(seq);
		station->runAction(repeat);
	}

}

void SceneStart::initTouch()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		//���/������ʼʱ
		return true;
	};
	listener->onTouchMoved = [](Touch* touch, Event* event) {
		//���/�������ƶ�ʱ
		return true;
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event) {
		//���/��������ʱ
		Point pos = touch->getLocationInView();
		Point point = Director::getInstance()->convertToGL(pos);
		//log("pos%f,%f", pos.x, pos.y);
		//log("point%f,%f", point.x, point.y);
		ReturnToSpace();
		return true;
	};
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void SceneStart::update(float dt)
{
	//���ݼ�ʱ���������������
	{
		CreateStarByRandom(dt);
		CreateStarByRandom1(dt);
		CreateStarByRandom2(dt);;
	}
	//���ݼ�ʱ���������������
	{
		CreateMeteorByRandom(dt);
		CreateMeteorByRandom1(dt);
	}
	//���ٱ��ֶ����������б������
	{
		//��ִ�м�ʱ��
		for (int i = 0; i < vec_todestroy.size(); i++) {
			vec_todestroy.at(i)->updateLife(dt);
		}
		//Ȼ��ִ������
		for (int i = 0; i < vec_todestroy.size(); i++) {
			if (!vec_todestroy.at(i)->GetActive()) {
				Entity* temp = vec_todestroy.at(i);
				vec_todestroy.erase(vec_todestroy.begin() + i);
				temp->removeFromParent();
			}
		}
		//log("size of vec_todestroy is %d", vec_todestroy.size());
	}
}

void SceneStart::ShowStar(Vec2 pos)
{
	Entity* star = Entity::create(new Pos(0, 0));
	star->setPosition(pos);

	//�������ֵ
	float scale = rand_0_1() + 1.0f;

	star->setScale(scale);
	star->BindSprite(STAR_P);

	//��������ٶ�
	float time = (rand_0_1() + 1.0f) / 20.0f;

	star->BindAnimation(STAR_N, 6, time, Size(10,10));
	star->SetAnimationPlay(true, true);
	this->addChild(star, SPACE_Z);
	//�ֶ�����Entity
	vec_todestroy.pushBack(star);
	star->Destroy(3.0f);
}

void SceneStart::ShowMeteor()
{
	auto meteor = ParticleSystemQuad::create(METEOR_P);
	meteor->setTextureWithRect(Director::getInstance()->getTextureCache()->addImage(METEORT_P), Rect(0, 0, 10, 10));
	meteor->setBlendAdditive(true);
	meteor->setAutoRemoveOnFinish(true);
	meteor->setPosition(Vec2(1280+640*rand_0_1(),720+360*rand_0_1()));

	//��ʼ�����������(������)
	/*{
		struct timeval now;
		gettimeofday(&now, NULL);
		srand((unsigned int)(now.tv_sec * 1000 + now.tv_usec / 1000));
	}*/

	//���ͼ��
	float rz = rand_0_1();
	if (rz < 0.5f) {
		this->addChild(meteor, METEORF_Z);
	}
	else {
		this->addChild(meteor, METEORB_Z);
	}

	//�������ֵ�����ҵ���
	

	//�����������
	float time_life =3*( 1.0f+rand_0_1() * 9);
	meteor->setDuration(time_life);


	//�����С,���������ڳ�����
	meteor->setScale(0.003f*time_life);

	//�����ת������0��90��֮��
	Size size = Director::getInstance()->getVisibleSize();
	float x = -size.width*2-rand_0_1()*500.0f;
	float y = -size.height*2-rand_0_1()*500.0f;
	float rotation = MATH_RAD_TO_DEG(atan(x/y));
	//log("x: %f,y: %f,rotation: %f",x,y, rotation);
	meteor->setRotation(rotation);
	Vec2 dir = Vec2(x,y);

	
	auto moveby = MoveBy::create(10.0f+time_life/3, dir);
	meteor->runAction(moveby);

}

void SceneStart::CreateStarByRandom(float dt)
{
	timer_star += dt;
	if (timer_star > time_star) {
		timer_star = 0;
		time_star = 1.5f + rand_0_1();
		int num = (int)(2.5f + rand_0_1()*3);
		for (int i = 0; i < num; i++) {
			float posx = Director::getInstance()->getVisibleSize().width*rand_0_1();
			float posy = Director::getInstance()->getVisibleSize().height*rand_0_1();
			ShowStar(Vec2(posx, posy));
			//log("create star!");
		}
	}
}

void SceneStart::CreateStarByRandom1(float dt)
{
	timer_star1 += dt;
	if (timer_star1 > time_star1) {
		timer_star1 = 0;
		time_star1 = 2.5f + rand_0_1();
		int num = (int)(1.5f + rand_0_1());
		for (int i = 0; i < num; i++) {
			float posx = Director::getInstance()->getVisibleSize().width*rand_0_1();
			float posy = Director::getInstance()->getVisibleSize().height*rand_0_1();
			ShowStar(Vec2(posx, posy));
			//log("create star1!");
		}
	}
}

void SceneStart::CreateStarByRandom2(float dt)
{
	timer_star2 += dt;
	if (timer_star2 > time_star2) {
		timer_star2 = 0;
		time_star2 = 3.5f + rand_0_1() * 2;
		int num = (int)(1.5f + rand_0_1());
		for (int i = 0; i < num; i++) {
			float posx = Director::getInstance()->getVisibleSize().width*rand_0_1();
			float posy = Director::getInstance()->getVisibleSize().height*rand_0_1();
			ShowStar(Vec2(posx, posy));
			//log("create star1!");
		}
	}
}

void SceneStart::CreateMeteorByRandom(float dt)
{
	timer_meteor += dt;
	if (timer_meteor > time_meteor) {
		timer_meteor = 0;
		time_meteor = 10.0f + rand_0_1()*5.0f;
		ShowMeteor();
	}
}

void SceneStart::CreateMeteorByRandom1(float dt)
{
	timer_meteor1 += dt;
	if (timer_meteor1 > time_meteor1) {
		timer_meteor1 = 0;
		time_meteor1 = 20.0f + rand_0_1()*10.0f;
		ShowMeteor();
	}
}

void SceneStart::OpenPlanet()
{
	auto scaleto = ScaleTo::create(0.8f, 1.5f);
	auto moveto = MoveTo::create(0.8f, Vec2(600, -58));
	auto spawn = Spawn::create(scaleto, moveto, nullptr, nullptr);
	this->runAction(spawn);
}

void SceneStart::OpenStation()
{
	auto scaleto = ScaleTo::create(0.8f, 1.5f);
	auto moveto = MoveTo::create(0.8f, Vec2(-550, -20));
	auto spawn = Spawn::create(scaleto, moveto, nullptr, nullptr);
	this->runAction(spawn);
}

void SceneStart::ReturnToSpace()
{
	log("return!");
	auto scaleto = ScaleTo::create(0.8f, 1.0f);
	auto moveto = MoveTo::create(0.8f, Vec2(0, 0));
	auto spawn = Spawn::create(scaleto, moveto, nullptr, nullptr);
	this->runAction(spawn);
}


