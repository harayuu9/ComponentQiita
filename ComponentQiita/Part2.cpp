//#include "Main.h"
//#include <list>
//#include <Windows.h>
//
//ScreenBuffer g_ScreenBuffer;
//char InputData::Buffer = 0;
//
//class Object
//{
//public:
//
//	int x, y;
//	virtual void Update() {}
//	virtual void Draw() {}
//};
//
////�I�u�W�F�N�g�̃��X�g���`
//std::list<Object*> g_ObjectList;
//
//class Enemy : public Object
//{
//public:
//	void Update() {}
//	void Draw()
//	{
//		g_ScreenBuffer.buffer2[x][y] = 'E';
//	}
//};
//
//class Bullet : public Object
//{
//public:
//	void Update()
//	{
//		x--;
//		//��ʊO�ɏ����Ă��玩��������
//		if (x < 0)
//		{
//			g_ObjectList.remove(this);
//			delete this;
//			return;
//		}
//
//		//ObjectList����Enemy���������ē����蔻����s���폜������B
//		auto buff = g_ObjectList;
//		for (auto obj : buff)
//		{
//			//obj��Enemy�̏ꍇ�L���X�g�o����B�Ⴄ�Ǝ��s����nullptr������
//			if (dynamic_cast<Enemy*>(obj) == nullptr)
//				continue;
//			if (obj->x == x && obj->y == y) {
//				g_ObjectList.remove(obj);
//				delete obj;
//			}
//		}
//	}
//	void Draw()
//	{
//		g_ScreenBuffer.buffer2[x][y] = 'b';
//	}
//};
//
//class Player : public Object
//{
//public:
//	Player()
//	{
//		x = 5; y = 8;
//	}
//	void Draw()
//	{
//		g_ScreenBuffer.buffer2[x][y] = 'p';
//	}
//
//	void Update()
//	{
//		//�ړ�
//		if (InputData::KeyCheck('d') && y < SCREE_NLENGTH - 1)
//			y++;
//		if (InputData::KeyCheck('a') && y > 0)
//			y--;
//		if (InputData::KeyCheck('s') && x < SCREE_NLENGTH - 1)
//			x++;
//		if (InputData::KeyCheck('w') && x > 0)
//			x--;
//
//		//������
//		if (InputData::KeyCheck(' '))
//		{
//			g_ObjectList.push_back(new Bullet());
//			g_ObjectList.back()->y = y;
//			g_ObjectList.back()->x = x - 1;
//		}
//	}
//};
//
//int main()
//{
//	//�ǉ�
//	g_ObjectList.push_back(new Player());
//	for (int i = 0; i < 10; i++)
//	{
//		g_ObjectList.push_back(new Enemy());
//		g_ObjectList.back()->x = 1;
//		g_ObjectList.back()->y = i;
//	}
//
//	while (!InputData::KeyCheck('p'))
//	{
//		//��ʂ̏�����
//		system("cls");
//		g_ScreenBuffer.Clear();
//		InputData::Update();
//
//		//���ۂ̏���
//		//Update����ObjectList���������ăC�e���[�V�����o�O��̂����
//		auto buff = g_ObjectList;
//		for (auto obj : buff)
//			obj->Update();
//
//		for (auto obj : g_ObjectList)
//			obj->Draw();
//
//		//Buffer�\��
//		printf("%s", g_ScreenBuffer.buffer);
//		Sleep(100);
//	}
//
//	//�ǉ�
//	for (auto obj : g_ObjectList)
//		delete obj;
//	g_ObjectList.clear();
//
//	return 0;
//}