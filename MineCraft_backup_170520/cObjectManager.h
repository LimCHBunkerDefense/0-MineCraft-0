#pragma once
#define g_ObjectManager cObjectManager::GetInstance()

class cObject;



class cObjectManager
{
private:
	SINGLETONE(cObjectManager);
	vector<cObject*> m_vecObject;
	vector<cObject*> m_nearPlayerObject;
public:
	vector<cObject*>& GetVecObject() { return m_vecObject; }
	vector<cObject*>& GetNearPlayerVecObject() { return m_nearPlayerObject; }
	void Render(D3DXVECTOR3 pos);
	void CreateObject(D3DXVECTOR3 tagetPos, OBJECT_NAME name);
	void UpdateVector(D3DXVECTOR3 pos);
	void ClearNearVec() { m_nearPlayerObject.clear(); }
	bool IsObjectHere(D3DXVECTOR3 tagetPos);
};
