#include "MyPG.h"
#include "MyGameMain.h"
#include "sound.h"

namespace Ending
{
	int endPosW, endPosH;
	DG::Image::SP img, imgBG1, imgBG2, imgBG3;
	struct Chara
	{
		int x, y, w, h;
	};

	Chara backs[3];

	void Back_Initialize(Chara& c_, int x_, int y_);
	void Back_UpDate(Chara& c_);
	void Back_Draw1(Chara& c_);
	void Back_Draw2(Chara& c_);
	void Back_Draw3(Chara& c_);

	void Initialize()
	{
		img = DG::Image::Create("./data/image/over.png");
		imgBG1 = DG::Image::Create("./data/image/BG1.png");
		imgBG2 = DG::Image::Create("./data/image/BG2.png");
		imgBG3 = DG::Image::Create("./data/image/BG3.png");
		bgm::LoadFile("over", "./data/sound/over.mp3");
		bgm::Play("over");
		for (int b = 0; b < 3; b++)
		{
			Back_Initialize(backs[b], b * 1440, 0);
		}
		endPosW = 0;
		endPosH = 0;
	}

	void Finalize()
	{
		img.reset();
		imgBG1.reset();
		imgBG2.reset();
		imgBG3.reset();
		bgm::Del();
	}

	TaskFlag UpDate()
	{
		for (int b = 0; b < 3; b++)
		{
			Back_UpDate(backs[b]);
		}

		auto inp = ge->in1->GetState();
		endPosW += 9;
		endPosH += 5;
		if (endPosW > 720)
		{
			endPosW = 720;
		}
		if (endPosH > 400)
		{
			endPosH = 400;
		}
		TaskFlag rtv = TaskFlag::Ending;
		if (endPosW >= 720)
		{
			if (true == inp.ST.down)
			{
				rtv = TaskFlag::Title;
			}
		}
		return rtv;
	}

	void Render()
	{
		Back_Draw1(backs[0]);
		Back_Draw2(backs[1]);
		Back_Draw3(backs[2]);

		ML::Box2D draw(-endPosW / 2, -endPosH / 2, 0, 0);
		draw.Offset(360, 200);
		draw.w = endPosW;
		draw.h = endPosH;
		ML::Box2D src(0, 0, 1920, 1080);
		img->Draw(draw, src);
	}

	void Back_Initialize(Chara& c_, int x_, int y_)
	{
		c_.x = x_;
		c_.y = y_;
	}
	void Back_UpDate(Chara& c_)
	{
		c_.x -= 1;
		if (c_.x <= -1440)
		{
			c_.x = 2880;
		}
	}
	void Back_Draw1(Chara& c_)
	{
		ML::Box2D draw(0, 0, 1440, 400);
		ML::Box2D src(0, 0, 1440, 400);
		draw.Offset(c_.x, c_.y);
		imgBG1->Draw(draw, src);
	}
	void Back_Draw2(Chara& c_)
	{
		ML::Box2D draw(0, 0, 1440, 400);
		ML::Box2D src(0, 0, 1440, 400);
		draw.Offset(c_.x, c_.y);
		imgBG2->Draw(draw, src);
	}
	void Back_Draw3(Chara& c_)
	{
		ML::Box2D draw(0, 0, 1440, 400);
		ML::Box2D src(0, 0, 1440, 400);
		draw.Offset(c_.x, c_.y);
		imgBG3->Draw(draw, src);
	}
}