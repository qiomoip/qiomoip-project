#include "BaseMesh.h"


CBaseMesh::CBaseMesh(void)
	: m_pGeometry(NULL)
{
}


CBaseMesh::~CBaseMesh(void)
{
}

void CBaseMesh::SetGeometry(CGeometry* pGeometry)
{
	m_pGeometry = pGeometry;
}