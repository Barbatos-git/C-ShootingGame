#include "MyPG.h"
#include "MyGameMain.h"
#include "sound.h"

namespace Game
{
	DG::Image::SP imgPlayer, imgShot, imgBomb, imgBomb4,
		imgEnemy1, imgEnemy2, imgEnemy3, imgLaser,
		imgBG1, imgBG2, imgBG3;
	int timeCnt, timer, istime, isfear, num, timeNum, psd;
	enum class State { Normal, Hit, Non };

	struct Chara
	{
		State state;
		int x, y, w, h;
		ML::Box2D hitBase;
		int moveCnt;
		int animCnt;
		int mode;
		int typeNum;
	};

	Chara player;
	Chara laser;
	Chara enemys[100];
	Chara shots[6];
	Chara shots2[6];
	Chara backs[3];
	Chara bombs[100];

	void Shot_Appear(int tn_, int x_, int y_);
	void Shot_Appear2(int tn_, int x_, int y_);
	void Laser_Appear(int x_, int y_);
	void Shot_Initialize(Chara& c_, int tn_, int x_, int y_);
	void Shot_UpDate(Chara& c_);
	void Shot_Draw(Chara& c_);
	void Shot_HitCheck_Std(Chara& c_);
	void Laser_HitCheck_Std(Chara& c_);

	void ShotA_Initialize(Chara& c_, int x_, int y_);
	void ShotA_UpDate(Chara& c_);
	void ShotA_Draw(Chara& c_);

	void ShotB_Initialize(Chara& c_, int x_, int y_);
	void ShotB_UpDate(Chara& c_);
	void ShotB_Draw(Chara& c_);

	void Laser_Initialize(Chara& c_, int x_, int y_);
	void Laser_UpDate(Chara& c_, Chara& p_);
	void Laser_Draw(Chara& c_);

	void Player_Initialize(Chara& c_, int x_, int y_);
	void Player_UpDate(Chara& c_);
	void Player_Draw(Chara& c_);

	void Enemy_Initialize(Chara& c_, int tn_, int x_, int y_);
	void Enemy_UpDate(Chara& c_);
	void Enemy_Draw(Chara& c_);
	void Enemy_HitCheckPlayers_Std(Chara& c_);
	void Enemy_Appear(int tn_, int x_, int y_);
	void Enemy_AppearTimer(Chara& c_);

	void EnemyA_Initialize(Chara& c_, int x_, int y_);
	void EnemyA_UpDate(Chara& c_);
	void EnemyA_Draw(Chara& c_);

	void EnemyB_Initialize(Chara& c_, int x_, int y_);
	void EnemyB_UpDate(Chara& c_);
	void EnemyB_Draw(Chara& c_);

	void EnemyC_Initialize(Chara& c_, int x_, int y_);
	void EnemyC_UpDate(Chara& c_);
	void EnemyC_Draw(Chara& c_);

	void Back_Initialize(Chara& c_, int x_, int y_);
	void Back_UpDate(Chara& c_);
	void Back_Draw1(Chara& c_);
	void Back_Draw2(Chara& c_);
	void Back_Draw3(Chara& c_);

	void Bomb_Initialize(Chara& c_, int tn_, int x_, int y_, int w_, int h_);
	void Bomb_UpDate(Chara& c_);
	void Bomb_Draw(Chara& c_);
	void Bomb_Appear(int x_, int y_, int w_, int h_);
	void Bomb_Appear2(int x_, int y_, int w_, int h_);

	void BombA_Initialize(Chara& c_, int x_, int y_, int w_, int h_);
	void BombA_UpDate(Chara& c_);
	void BombA_Draw(Chara& c_);

	void BombB_Initialize(Chara& c_, int x_, int y_, int w_, int h_);
	void BombB_UpDate(Chara& c_);
	void BombB_Draw(Chara& c_);

	void Initialize()
	{
		imgPlayer = DG::Image::Create("./data/image/player.png");
		imgShot = DG::Image::Create("./data/image/shot.png");
		imgEnemy1 = DG::Image::Create("./data/image/enemy1.png");
		imgEnemy2 = DG::Image::Create("./data/image/enemy2.png");
		imgEnemy3 = DG::Image::Create("./data/image/enemy3.png");
		imgBomb = DG::Image::Create("./data/image/bomb.png");
		imgBomb4 = DG::Image::Create("./data/image/bomb4.png");
		imgBG1 = DG::Image::Create("./data/image/BG1.png");
		imgBG2 = DG::Image::Create("./data/image/BG2.png");
		imgBG3 = DG::Image::Create("./data/image/BG3.png");
		imgLaser = DG::Image::Create("./data/image/laser.png");
		bgm::LoadFile("game", "./data/sound/game.mp3");
		bgm::Play("game");
		srand((unsigned int)time(NULL));
		for (int b = 0; b < 3; b++)
		{
			Back_Initialize(backs[b], b * 1440, 0);
		}

		Player_Initialize(player, 50, 400 / 2);

		Laser_Initialize(laser, 0, 0);

		for (int i = 0; i < 100; i++)
		{
			Enemy_Initialize(enemys[i], 0, 0, 0);
			Enemy_Initialize(enemys[i], 1, 0, 0);
			Enemy_Initialize(enemys[i], 2, 0, 0);
		}

		timeCnt = 0;
		num = 5;
		timeNum = 300;
		psd = 0;
		
		for (int s = 0; s < 6; s++)
		{
			Shot_Initialize(shots[s], 0, 0, 0);
			Shot_Initialize(shots2[s], 1, 0, 0);
		}

		for (int c = 0; c < 100; c++)
		{
			Bomb_Initialize(bombs[c], 0, 0, 0, 0, 0);
			Bomb_Initialize(bombs[c], 1, 0, 0, 0, 0);
		}
	}

	void Finalize()
	{
		imgPlayer.reset();
		imgShot.reset();
		imgEnemy1.reset();
		imgEnemy2.reset();
		imgEnemy3.reset();
		imgBG1.reset();
		imgBG2.reset();
		imgBG3.reset();
		imgBomb.reset();
		imgBomb4.reset();
		imgLaser.reset();
		bgm::Del();
	}

	TaskFlag UpDate()
	{
		timeCnt++;
		timeNum++;

		for (int b = 0; b < 3; b++)
		{
			Back_UpDate(backs[b]);
		}

		Player_UpDate(player);

		Laser_UpDate(laser, player);

		for (int s = 0; s < 6; s++)
		{
			Shot_UpDate(shots[s]);
			Shot_UpDate(shots2[s]);
		}

		for (int i = 0; i < 100; i++)
		{
			Enemy_UpDate(enemys[i]);
		}

		for (int i = 0; i < 100; i++)
		{
			Enemy_AppearTimer(enemys[i]);
		}

		for (int c = 0; c < 100; c++)
		{
			Bomb_UpDate(bombs[c]);
		}

		TaskFlag rtv = TaskFlag::Game;
		if (player.state == State::Non && timeCnt == timer + 100)
		{
			rtv = TaskFlag::Ending;
		}
		return rtv;
	}

	void Render()
	{
		Back_Draw1(backs[0]);
		Back_Draw2(backs[1]);
		Back_Draw3(backs[2]);

		Player_Draw(player);
		
		for (int i = 0; i < 100; i++)
		{
			Enemy_Draw(enemys[i]);
		}

		for (int s = 0; s < 6; s++)
		{
			Shot_Draw(shots[s]);
			Shot_Draw(shots2[s]);
		}

		Laser_Draw(laser);
		
		for (int c = 0; c < 100; c++)
		{
			Bomb_Draw(bombs[c]);
		}
	}

	void Shot_Appear(int tn_, int x_, int y_)
	{
		for (int s = 0; s < 6; s++)
		{
			if (shots[s].state == State::Non)
			{
				shots[s].state = State::Normal;
				shots[s].x = x_;
				shots[s].y = y_;
				shots[s].hitBase = ML::Box2D(-16, -16, 32, 32);
				shots[s].typeNum = tn_;
				break;
			}
		}
	}
	
	void Shot_Appear2(int tn_, int x_, int y_)
	{
		for (int s = 0; s < 6; s++)
		{
			if (shots2[s].state == State::Non)
			{
				shots2[s].state = State::Normal;
				shots2[s].x = x_;
				shots2[s].y = y_;
				shots2[s].hitBase = ML::Box2D(-8, -8, 16, 16);
				shots2[s].typeNum = tn_;
				break;
			}
		}
	}

	void Laser_Appear(int x_, int y_)
	{
		if (laser.state == State::Non)
		{
			laser.state = State::Normal;
			laser.x = x_;
			laser.y = y_;
			laser.hitBase = ML::Box2D(-x_/2, -64, x_, 128);
		}
	}

	void Player_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Normal;
		c_.x = x_;
		c_.y = y_;
		c_.hitBase = ML::Box2D(-32, -12, 64, 25);
	}
	void Player_UpDate(Chara& c_)
	{
		auto inp = ge->in1->GetState();
		if (c_.state != State::Hit)
		{
			if (c_.x >= 0 - c_.hitBase.x && c_.x <= 720 + c_.hitBase.x)
			{
				if (c_.y >= 0 - c_.hitBase.y && c_.y <= 400 + c_.hitBase.y)
				{
					if (inp.LStick.BL.on && c_.x > 2 - c_.hitBase.x) { c_.x -= 3; }
					if (inp.LStick.BR.on && c_.x < 718 + c_.hitBase.x) { c_.x += 3; }
					if (inp.LStick.BU.on && c_.y > 2 - c_.hitBase.y) { c_.y -= 3; }
					if (inp.LStick.BD.on && c_.y < 398 + c_.hitBase.y) { c_.y += 3; }
					if (inp.B1.down && c_.state == State::Normal)
					{
						isfear = 1;
						Shot_Appear(0, c_.x + 30, c_.y);
					}
					else if (inp.B2.down && c_.state == State::Normal)
					{
						isfear = 1;
						Shot_Appear2(1, c_.x + 32, c_.y + 12);
					}
					else { isfear = 0; }
					if (inp.L1.down && psd == 0){ psd++; }
					if (inp.R1.down && psd == 1){ psd++; }
					if (inp.ST.down && psd >= 2){ psd++; }
					if (inp.B3.on && psd >= 3 && c_.state == State::Normal)
					{
						Laser_Appear((720 - c_.x + 32) / 2 + c_.x + 32, c_.y);
					}
					else
					{
						laser.state = State::Non;
					}
				}
			}
		}
		else
		{
			if (timeCnt == timer + 5)
			{
				Bomb_Appear(c_.x - 16, c_.y, 32, 32);
			}
			if (timeCnt == timer + 20)
			{
				Bomb_Appear(c_.x + 16, c_.y, 32, 32);
			}
			if (timeCnt == timer + 40)
			{
				Bomb_Appear(c_.x - 16, c_.y - 16, 64, 64);
			}
			if (timeCnt == timer + 80)
			{
				player.state = State::Non;
			}
		}
	}
	void Player_Draw(Chara& c_)
	{
		if (c_.state != State::Non)
		{
			ML::Box2D draw(-32, -12, 64, 25);
			draw.Offset(c_.x, c_.y);
			ML::Box2D src(64 * isfear, 0, 64, 25);
			imgPlayer->Draw(draw, src);
		}
	}

	void Enemy_Initialize(Chara& c_, int tn_, int x_, int y_)
	{
		switch (tn_)
		{
		case 0:
			EnemyA_Initialize(c_, x_, y_);
			break;
		case 1:
			EnemyB_Initialize(c_, x_, y_);
			break;
		case 2:
			EnemyC_Initialize(c_, x_, y_);
			break;
		}
	}

	void EnemyA_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.x = x_;
		c_.y = y_;
		c_.moveCnt = 0;
		c_.hitBase = ML::Box2D(-32, -32, 64, 64);
		c_.animCnt = 0;
		c_.mode = 0;
		c_.typeNum = 0;
	}
	void EnemyA_UpDate(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			switch (c_.mode)
			{
			case 0:
				c_.x -= 2;
				c_.moveCnt++;
				if (c_.moveCnt > 100)
				{
					c_.mode = 1;
					c_.moveCnt = 0;
				}
				break;
			case 1:
				c_.x += 1;
				c_.y += 1;
				c_.moveCnt++;
				if (c_.moveCnt > 50)
				{
					c_.mode = 2;
					c_.moveCnt = 0;
				}
				break;
			case 2:
				c_.x -= 2;
				c_.moveCnt++;
				break;
			}
			if (c_.x + 64 < 0)
			{
				c_.state = State::Non;
			}
			c_.animCnt++;
			Enemy_HitCheckPlayers_Std(c_);
		}
	}
	void EnemyA_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-32, -32, 64, 64);
			draw.Offset(c_.x, c_.y);
			int animTable[] = { 0,1,2,3,2,1 };
			ML::Box2D src(animTable[(c_.animCnt / 5) % 6] * 40, 0, 40, 40);
			imgEnemy1->Draw(draw, src);
		}
	}

	void EnemyB_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.x = x_;
		c_.y = y_;
		c_.moveCnt = 0;
		c_.hitBase = ML::Box2D(-16, -16, 32, 32);
		c_.animCnt = 0;
		c_.mode = 0;
		c_.typeNum = 1;
	}
	void EnemyB_UpDate(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			switch (c_.mode)
			{
			case 0:
				c_.x -= 2;
				c_.moveCnt++;
				if (c_.moveCnt > 100)
				{
					c_.mode = 1;
					c_.moveCnt = 0;
				}
				break;
			case 1:
				c_.x -= 1;
				c_.y -= 1;
				c_.moveCnt++;
				if (c_.moveCnt > 50)
				{
					c_.mode = 2;
					c_.moveCnt = 0;
				}
				break;
			case 2:
				c_.x -= 2;
				c_.moveCnt++;
				break;
			}
			if (c_.x + 32 < 0)
			{
				c_.state = State::Non;
			}
			c_.animCnt++;
			Enemy_HitCheckPlayers_Std(c_);
		}
	}
	void EnemyB_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-16, -16, 32, 32);
			draw.Offset(c_.x, c_.y);
			int animTable[] = { 0,1,2,3,2,1 };
			ML::Box2D src(animTable[(c_.animCnt / 5) % 6] * 32, 0, 32, 32);
			imgEnemy2->Draw(draw, src);
		}
	}

	void EnemyC_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.x = x_;
		c_.y = y_;
		c_.moveCnt = 0;
		c_.hitBase = ML::Box2D(-20, -20, 40, 40);
		c_.animCnt = 0;
		c_.mode = 0;
		c_.typeNum = 2;
	}
	void EnemyC_UpDate(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			switch (c_.mode)
			{
			case 0:
				c_.x -= 2;
				c_.moveCnt++;
				if (c_.moveCnt > 100)
				{
					c_.mode = 1;
					c_.moveCnt = 0;
				}
				break;
			case 1:
				c_.x += 1;
				c_.moveCnt++;
				if (c_.moveCnt > 50)
				{
					c_.mode = 2;
					c_.moveCnt = 0;
				}
				break;
			case 2:
				c_.x -= 2;
				c_.moveCnt++;
				break;
			}
			if (c_.x + 40 < 0)
			{
				c_.state = State::Non;
			}
			c_.animCnt++;
			Enemy_HitCheckPlayers_Std(c_);
		}
	}
	void EnemyC_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-20, -20, 40, 40);
			draw.Offset(c_.x, c_.y);
			ML::Box2D src(0, 0, 40, 40);
			imgEnemy3->Draw(draw, src);
		}
	}

	void Enemy_UpDate(Chara& c_)
	{
		switch (c_.typeNum)
		{
		case 0:
			EnemyA_UpDate(c_);
			break;
		case 1:
			EnemyB_UpDate(c_);
			break;
		case 2:
			EnemyC_UpDate(c_);
			break;
		}
	}
	void Enemy_Draw(Chara& c_)
	{
		switch (c_.typeNum)
		{
		case 0:
			EnemyA_Draw(c_);
			break;
		case 1:
			EnemyB_Draw(c_);
			break;
		case 2:
			EnemyC_Draw(c_);
			break;
		}
	}
	void Enemy_HitCheckPlayers_Std(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D me = c_.hitBase.OffsetCopy(c_.x, c_.y);
			if (player.state == State::Normal)
			{
				ML::Box2D you = player.hitBase.OffsetCopy(player.x, player.y);
				if (you.Hit(me) == true)
				{
					player.state = State::Hit;
					timer = timeCnt;
				}
			}
		}
	}
	void Enemy_Appear(int tn_, int x_, int y_)
	{
		for (int c = 0; c < 100; c++)
		{
			if (enemys[c].state == State::Non)
			{
				Enemy_Initialize(enemys[c], tn_, x_, y_);
				enemys[c].state = State::Normal;
				break;
			}
		}
	}
	void Enemy_AppearTimer(Chara& c_)
	{
		if (num <= 100)
		{
			num += timeCnt / 300;
		}
		else
		{
			num = 100;
		}
		if (timeNum >= 300)
		{
			for (int i = 0; i < num; i++)
			{
				Enemy_Appear(rand() % 3, rand() % 360 + 720,
					rand() % (400 - 2 * c_.hitBase.h + 1) + c_.hitBase.h);
			}
			timeNum = 0;
		}
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

	void Bomb_Initialize(Chara& c_, int tn_, int x_, int y_, int w_, int h_)
	{
		switch (tn_)
		{
		case 0:
			BombA_Initialize(c_, x_, y_, w_, h_);
			break;
		case 1:
			BombB_Initialize(c_, x_, y_, w_, h_);
			break;
		}
	}
	
	void Bomb_UpDate(Chara& c_)
	{
		switch (c_.typeNum)
		{
		case 0:
			BombA_UpDate(c_);
			break;
		case 1:
			BombB_UpDate(c_);
			break;
		}
	}
	void Bomb_Draw(Chara& c_)
	{
		switch (c_.typeNum)
		{
		case 0:
			BombA_Draw(c_);
			break;
		case 1:
			BombB_Draw(c_);
			break;
		}
	}
	void Bomb_Appear(int x_, int y_, int w_, int h_)
	{
		for (int c = 0; c < 100; c++)
		{ 
			if (bombs[c].state == State::Non)
			{
				BombA_Initialize(bombs[c], x_, y_, w_, h_);
				bombs[c].state = State::Normal;
				break;
			}
		}
	}

	void Bomb_Appear2(int x_, int y_, int w_, int h_)
	{
		for (int c = 0; c < 100; c++)
		{
			if (bombs[c].state == State::Non)
			{
				BombB_Initialize(bombs[c], x_, y_, w_, h_);
				bombs[c].state = State::Normal;
				break;
			}
		}
	}

	void BombA_Initialize(Chara& c_, int x_, int y_, int w_, int h_)
	{
		c_.state = State::Non;
		c_.animCnt = 0;
		c_.typeNum = 0;
		c_.x = x_;
		c_.y = y_;
		c_.w = w_;
		c_.h = h_;
	}

	void BombA_UpDate(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			c_.animCnt++;
			if (c_.animCnt >= 40)
			{
				c_.state = State::Non;
			}
		}
	}

	void BombA_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-16, -16, c_.w, c_.h);
			draw.Offset(c_.x, c_.y);
			int animTable[] = { 0,1,2,3,4,5,6,7 };
			ML::Box2D src(animTable[(c_.animCnt / 5) % 8] * 32, 0, 32, 32);
			imgBomb->Draw(draw, src);
		}
	}

	void BombB_Initialize(Chara& c_, int x_, int y_, int w_, int h_)
	{
		c_.state = State::Non;
		c_.animCnt = 0;
		c_.typeNum = 1;
		c_.x = x_;
		c_.y = y_;
		c_.w = w_;
		c_.h = h_;
	}

	void BombB_UpDate(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			c_.animCnt++;
			if (c_.animCnt >= 40)
			{
				c_.state = State::Non;
			}
		}
	}

	void BombB_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-c_.w/2, -c_.h/2, c_.w, c_.h);
			draw.Offset(c_.x, c_.y);
			int animTable[] = { 0,1,2,3,4,5,6,7,8,9 };
			ML::Box2D src(animTable[(c_.animCnt / 5) % 10] * 120, 0, 120, 120);
			imgBomb4->Draw(draw, src);
		}
	}

	void Shot_Initialize(Chara& c_, int tn_, int x_, int y_)
	{
		switch (tn_)
		{
		case 0:
			ShotA_Initialize(c_, x_, y_);
			break;
		case 1:
			ShotB_Initialize(c_, x_, y_);
			break;
		}
	}
	void Shot_UpDate(Chara& c_)
	{
		switch (c_.typeNum)
		{
		case 0:
			ShotA_UpDate(c_);
			break;
		case 1:
			ShotB_UpDate(c_);
			break;
		}
	}
	void Shot_Draw(Chara& c_)
	{
		switch (c_.typeNum)
		{
		case 0:
			ShotA_Draw(c_);
			break;
		case 1:
			ShotB_Draw(c_);
			break;
		}
	}
	void Shot_HitCheck_Std(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D me = c_.hitBase.OffsetCopy(c_.x, c_.y);
			for (int e = 0; e < 100; e++)
			{
				if (enemys[e].state == State::Normal)
				{
					ML::Box2D you = enemys[e].hitBase.OffsetCopy(enemys[e].x, enemys[e].y);
					if (you.Hit(me) == true)
					{
						enemys[e].state = State::Non;
						c_.state = State::Hit;
						Bomb_Appear2(enemys[e].x, enemys[e].y, enemys[e].hitBase.w, enemys[e].hitBase.h);
					}
				}
			}
		}
	}

	void ShotA_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.typeNum = 0;
	}
	void ShotA_UpDate(Chara& c_)
	{
		if (c_.state != State::Non)
		{
			c_.x += 4;
			if (c_.x >= 720 + 16)
			{
				c_.state = State::Non;
			}
			Shot_HitCheck_Std(c_);
		}
	}
	void ShotA_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-16, -16, 32, 32);
			draw.Offset(c_.x, c_.y);
			ML::Box2D src(0, 96, 32, 32);
			imgShot->Draw(draw, src);
		}
	}

	void ShotB_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.typeNum = 1;
	}
	void ShotB_UpDate(Chara& c_)
	{
		if (c_.state != State::Non)
		{
			c_.x += 2;
			c_.y += 2;
			if (c_.x >= 720 + 8 || c_.y >= 400 + 8)
			{
				c_.state = State::Non;
			}
			Shot_HitCheck_Std(c_);
		}
	}
	void ShotB_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-8, -8, 16, 16);
			draw.Offset(c_.x, c_.y);
			ML::Box2D src(0, 32, 16, 16);
			imgShot->Draw(draw, src);
		}
	}
	void Laser_Initialize(Chara& c_, int x_, int y_)
	{
		c_.state = State::Non;
		c_.animCnt = 0;
	}
	void Laser_UpDate(Chara& c_, Chara& p_)
	{
		if (c_.state == State::Normal)
		{
			c_.x = (720 - p_.x + 32) / 2 + p_.x + 32;
			c_.y = p_.y;
			c_.hitBase.w = 720 - p_.x + 32;
			c_.animCnt++;
			if (c_.animCnt >= 20)
			{
				c_.animCnt = 0;
			}
			Laser_HitCheck_Std(c_);
		}
		if (p_.state != State::Normal)
		{
			c_.state = State::Non;
		}
	}
	void Laser_Draw(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D draw(-c_.hitBase.w / 2, -c_.hitBase.h / 2, c_.hitBase.w, c_.hitBase.h);
			draw.Offset(c_.x, c_.y);
			int animTable[] = { 0, 1, 2, 3 };
			ML::Box2D src(0, animTable[(c_.animCnt / 5) % 4] * 18, 38, 18);
			imgLaser->Draw(draw, src);
		}
	}
	void Laser_HitCheck_Std(Chara& c_)
	{
		if (c_.state == State::Normal)
		{
			ML::Box2D me = c_.hitBase.OffsetCopy(c_.x, c_.y);
			for (int e = 0; e < 100; e++)
			{
				if (enemys[e].state == State::Normal)
				{
					ML::Box2D you = enemys[e].hitBase.OffsetCopy(enemys[e].x, enemys[e].y);
					if (you.Hit(me) == true)
					{
						enemys[e].state = State::Non;
						Bomb_Appear2(enemys[e].x, enemys[e].y, enemys[e].hitBase.w, enemys[e].hitBase.h);
					}
				}
			}
		}
	}
}