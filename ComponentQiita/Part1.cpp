//#include "Main.h"
//#include <list>
//#include <Windows.h>
//
//ScreenBuffer g_ScreenBuffer;
//char InputData::Buffer = 0;
//
//class Enemy
//{
//public:
//	static std::list<Enemy*> List;
//	int x, y;
//
//	Enemy()
//	{
//		List.push_back(this);
//	}
//	void Update() {}
//	void Draw()
//	{
//		g_ScreenBuffer.buffer2[x][y] = 'E';
//	}
//};
//std::list<Enemy*> Enemy::List;
//
//class Bullet
//{
//public:
//	int x, y;
//	void Update()
//	{
//		x--;
//		auto buff = Enemy::List;
//		for (auto e : buff)
//		{
//			if (e->x == x && e->y == y)
//				Enemy::List.remove(e);
//		}
//	}
//	void Draw()
//	{
//		g_ScreenBuffer.buffer2[x][y] = 'b';
//	}
//};
//
//class Player
//{
//	int x, y;
//	//球のリスト
//	std::list<Bullet*> BulletList;
//public:
//
//	Player()
//	{
//		x = 5; y = 8;
//	}
//
//	void Draw()
//	{
//		g_ScreenBuffer.buffer2[x][y] = 'p';
//
//		//球の描画を呼ぶ
//		for (auto b : BulletList)
//			b->Draw();
//	}
//
//	void Update()
//	{
//		//移動
//		if (InputData::KeyCheck('d') && y < SCREE_NLENGTH - 1)
//			y++;
//		if (InputData::KeyCheck('a') && y > 0)
//			y--;
//		if (InputData::KeyCheck('s') && x < SCREE_NLENGTH - 1)
//			x++;
//		if (InputData::KeyCheck('w') && x > 0)
//			x--;
//
//		//球のupdateを呼ぶ
//		for (auto b : BulletList)
//			b->Update();
//
//		//球発射
//		if (InputData::KeyCheck(' '))
//		{
//			BulletList.push_back(new Bullet());
//			BulletList.back()->y = y;
//			BulletList.back()->x = x - 1;
//		}
//
//		//画面から消えた球を消す
//		//イテレーション回してるリストの中身変えるとおかしくなるので
//		std::list<Bullet*> buff = BulletList;
//		for (auto b : buff)
//		{
//			if (b->x < 0)
//				BulletList.remove(b);
//		}
//	}
//};
//
//
//
//int main()
//{
//	Player player;
//	Enemy enemy[10];
//	for (int i = 0; i < 10; i++)
//	{
//		enemy[i].x = 1;
//		enemy[i].y = i;
//	}
//
//	while (!InputData::KeyCheck('p'))
//	{
//		//画面の初期化
//		system("cls");
//		g_ScreenBuffer.Clear();
//		InputData::Update();
//
//		//実際の処理
//		{
//			player.Update();
//			for (auto e : Enemy::List)
//				e->Update();
//			player.Draw();
//			for (auto e : Enemy::List)
//				e->Draw();
//		}
//
//		//Buffer表示
//		printf("%s", g_ScreenBuffer.buffer);
//		Sleep(100);
//	}
//	return 0;
//}