#pragma once
#define g_ObjectManager cObjectManager::GetInstance()

class cObject;

class cObjectManager
{
private:
	SINGLETONE(cObjectManager);
	vector<cObject*> m_vecObject;
public:
	vector<cObject*>& GetVecObject() { return m_vecObject; }
	void Render();
	void CreateObject(D3DXVECTOR3 tagetPos);
};
