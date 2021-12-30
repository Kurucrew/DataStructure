#include "OcTree.h"
#include <Windows.h>
#pragma comment	(lib, "Winmm.lib")

void main()
{
	OcTree tree;
	tree.Init(100, 100, 100, 2);
	//정적 오브젝트
	for (int i = 0; i < 10; i++)
	{
		Object* obj = new Object();
		obj->SetPos((float)(rand() % 100), (float)(rand() % 100), (float)(rand() % 100));
		float hw = (float)(rand() % 4) + 1;
		float hh = (float)(rand() % 4) + 1;
		float hl = (float)(rand() % 4) + 1;
		Vector3D vec;
		vec.x = obj->m_Pos.x - hw;
		vec.y = obj->m_Pos.y - hh;
		vec.z = obj->m_Pos.z - hl;
		Box bx(vec, hw * 2.0f, hh * 2.0f, hl * 2.0f);
		obj->SetBox(bx);
		tree.Addobject(obj);
	}
	//동적 오브젝트 생성
	Object* DObj[10];
	for (int i = 0; i < 10; i++)
	{
		DObj[i] = new Object();
		DObj[i]->SetPos((float)(rand() % 100), (float)(rand() % 100), (float)(rand() % 100));
		float hw = (float)(rand() % 4) + 1;
		float hh = (float)(rand() % 4) + 1;
		float hl = (float)(rand() % 4) + 1;
		Vector3D vec;
		vec.x = DObj[i]->m_Pos.x - hw;
		vec.y = DObj[i]->m_Pos.y - hh;
		vec.z = DObj[i]->m_Pos.z - hl;
		Box bx(vec, hw * 2.0f, hh * 2.0f, hl * 2.0f);
		DObj[i]->SetBox(bx);
		tree.AddDobject(DObj[i]);
	}
	float fTime = 0.01f;
	DWORD PrevTime = timeGetTime();
	DWORD Time = 0;
	DWORD Timer = 0;
	static float RunTimer = 10.0f;
	//동적 오브젝트 이동
	while (RunTimer > 0)
	{
		tree.DelDobject(tree.m_Root);
		for (int i = 0; i < 10; i++)
		{
			Vector3D vec = DObj[i]->m_Pos;
			vec = vec + Vector3D(1, 0, 0) * (Timer / 1000.0f) * 10;
			DObj[i]->MoveObj(vec);
			tree.AddDobject(DObj[i]);
		}
		tree.PrintDObjList(tree.m_Root);
		cout << endl;
		Time = timeGetTime();
		Timer = Time - PrevTime;
		PrevTime = Time;
		RunTimer -= (Timer / 1000.0f);
		Sleep(1000);
	}
	tree.PrintList(tree.m_Root);
}