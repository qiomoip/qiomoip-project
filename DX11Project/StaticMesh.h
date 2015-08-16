#pragma once
#include "basemesh.h"

class CGeometry;
class CTexture;

class CStaticMesh :
	public CBaseMesh
{

	//이건 스태틱 지오메트리의 인자값으로...
		//vector<tstring>	m_vecTextureName;

	//렌더러는 지오메트리 포인터를 갖고 있다
	//렌더러에서 지오메트리를 생성한다
	//지오메트리를 생성할 때 텍스처가 필요하다면 그 텍스처 이름을 지오메트리에 저장한다
	//저장된 텍스처 이름 리스트를 가져와 텍스처를 생성한다
	//텍스처 생성하는 부분을 렌더러에서...
	//이건 나중에 메쉬 만들 때 다시 할 것
	//만약에 11은 이렇게 안 하면 어쩌지 ㅇㅅㅇ............
private:
	CTexture*	m_pTexture;

public:
	void Init(const GEOMETRY_TYPE& eMesh, const LPCTSTR pFileName, tstring strTextureName);

	void Render(CShader* pShader, const TECH_TYPE& eTech, const INPUTLAYOUT_TYPE& eInputLayout, const UINT& uPass);

public:
	CStaticMesh(void);
	~CStaticMesh(void);
};

