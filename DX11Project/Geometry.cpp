#include "Geometry.h"


CGeometry::CGeometry(void)
{
}


CGeometry::~CGeometry(void)
{
}

void CGeometry::SetPos(const XMFLOAT3& vPos)
{
	m_vPos = vPos;
}

void CGeometry::SetInputLayout(const INPUTLAYOUT_TYPE& eInput)
{
	m_eInputLayout = eInput;
}