#include "Main.h"
#include <list>
#include <Windows.h>

ScreenBuffer g_ScreenBuffer;
char InputData::Buffer = 0;

class Object;
class Player;

class Component
{
protected:
public:
	Component() {}
	virtual ~Component() {}
	Object *Parent;
	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}
};

class Object
{
public:
	Object() {}
	~Object() {
		for (auto com : ComponentList)
			delete com;
	}

	std::list<Component*> ComponentList;
	void Update()
	{
		auto buff = ComponentList;
		for (auto com : buff)
			com->Update();
	}
	void Draw()
	{
		for (auto com : ComponentList)
			com->Draw();
	}

	//�I�u�W�F�N�g�������Ă���R���|�[�l���g���擾
	template<class T>
	T* GetComponent()
	{
		for (auto com : ComponentList) {
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
				return buff;
		}
		return nullptr;
	}

	//�I�u�W�F�N�g�������Ă���R���|�[�l���g��ǉ�
	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->Parent = this;
		ComponentList.push_back(buff);
		buff->Start();
		return buff;
	}
};

//�I�u�W�F�N�g�̃��X�g���`
std::list<Object*> g_ObjectList;

//�ꏊ�������R���|�[�l���g
class Position : public Component
{
public:
	int x, y;
};

//�G�R���|�[�l���g
class Enemy : public Component
{
	Position* pos = nullptr;
public:
	void Draw()
	{
		if (pos == nullptr)
			pos = Parent->GetComponent<Position>();
		g_ScreenBuffer.buffer2[pos->x][pos->y] = 'E';
	}
};

//�e�R���|�[�l���g
class Bullet : public Component
{
	Position* pos = nullptr;
public:
	void Update()
	{
		if (pos == nullptr)
			pos = Parent->GetComponent<Position>();
		pos->x--;
		//��ʊO�ɏ����Ă��玩��������
		if (pos->x < 0)
		{
			Parent->ComponentList.remove(this);
			delete this;
			return;
		}

		//ObjectList����Enemy���������ē����蔻����s���폜������B
		auto buff = g_ObjectList;
		for (auto obj : buff)
		{
			//�S�̂���Enemy��T��
			Enemy* enemy = obj->GetComponent<Enemy>();
			if (enemy == nullptr)
				continue;
			if (obj->GetComponent<Position>()->x == pos->x && obj->GetComponent<Position>()->y == pos->y) {
				//�I�u�W�F�N�g���폜���Ȃ�
				//g_ObjectList.remove(obj);
				//delete obj;

				//�G�R���|�[�l���g���폜
				obj->ComponentList.remove(enemy);
				delete enemy;

				//�v���C���[�R���|�[�l���g�ǉ�
				obj->AddComponent<Player>();
			}
		}
	}
	void Draw()
	{
		if (pos == nullptr)
			pos = Parent->GetComponent<Position>();
		g_ScreenBuffer.buffer2[pos->x][pos->y] = 'b';
	}
};

class Player : public Component
{
	Position* pos = nullptr;
public:
	void Start()
	{
		if (pos == nullptr)
			pos = Parent->GetComponent<Position>();
	}
	void Draw()
	{
		if (pos == nullptr)
			pos = Parent->GetComponent<Position>();
		g_ScreenBuffer.buffer2[pos->x][pos->y] = 'p';
	}

	void Update()
	{
		if (pos == nullptr)
			pos = Parent->GetComponent<Position>();
		//�ړ�
		if (InputData::KeyCheck('d') && pos->y < SCREE_NLENGTH - 1)
			pos->y++;
		if (InputData::KeyCheck('a') && pos->y > 0)
			pos->y--;
		if (InputData::KeyCheck('s') && pos->x < SCREE_NLENGTH - 1)
			pos->x++;
		if (InputData::KeyCheck('w') && pos->x > 0)
			pos->x--;

		//������
		if (InputData::KeyCheck(' '))
		{
			Object* obj = new Object;
			Position* posb = obj->AddComponent<Position>();
			obj->AddComponent<Bullet>();
			posb->y = pos->y;
			posb->x = pos->x - 1;
			g_ObjectList.push_back(obj);
		}
	}
};

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//�ǉ�
	Object* obj = new Object;
	Position* pos = obj->AddComponent<Position>();
	pos->x = 5; pos->y = 8;
	obj->AddComponent<Player>();
	g_ObjectList.push_back(obj);

	for (int i = 0; i < 10; i++)
	{
		obj = new Object;
		pos = obj->AddComponent<Position>();
		pos->x = 1;
		pos->y = i;
		obj->AddComponent<Enemy>();
		g_ObjectList.push_back(obj);
	}

	while (!InputData::KeyCheck('p'))
	{
		//��ʂ̏�����
		system("cls");
		g_ScreenBuffer.Clear();
		InputData::Update();

		//���ۂ̏���
		//Update����ObjectList���������ăC�e���[�V�����o�O��̂����
		auto buff = g_ObjectList;
		for (auto obj : buff)
			obj->Update();

		for (auto obj : g_ObjectList)
			obj->Draw();

		//Buffer�\��
		printf("%s", g_ScreenBuffer.buffer);
		Sleep(100);
	}

	//�ǉ�
	for (auto obj : g_ObjectList)
		delete obj;
	g_ObjectList.clear();

	return 0;
}