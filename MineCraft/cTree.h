
#include "cObject.h"
class cTree :
	public cObject
{
	vector<cTree*> m_vecTree;
public:
	cTree();
	cTree(D3DXVECTOR3 pos);
	~cTree();
	void Setup();
	virtual void Render();
	void SetWood();
	void SetLeaf();
};
