#include "stdafx.h"
#include "VertexData.h"

namespace Neo
{
	//------------------------------------------------------------------------------------
	VertexData::VertexData()
		: m_nVerts(0)
		, m_pVertData(nullptr)
		, m_pTangentData(nullptr)
		, m_pBoneWeights(nullptr)
	{

	}
	//------------------------------------------------------------------------------------
	VertexData::~VertexData()
	{
		SAFE_DELETE_ARRAY(m_pVertData);
		SAFE_DELETE_ARRAY(m_pTangentData);
		SAFE_DELETE_ARRAY(m_pBoneWeights);
	}
	//------------------------------------------------------------------------------------
	void VertexData::InitVertex(eVertexType type, const SVertex* pVert, uint32 nVert)
	{
		SAFE_DELETE_ARRAY(m_pVertData);

		m_vertType = type;
		m_nVerts = nVert;
		m_pVertData = new SVertex[nVert];

		memcpy(m_pVertData, pVert, sizeof(SVertex) * nVert);
	}
	//------------------------------------------------------------------------------------
	void VertexData::InitTangents(const STangentData* pVert, uint32 nVert)
	{
		_AST(nVert == m_nVerts);

		SAFE_DELETE_ARRAY(m_pTangentData);

		m_pTangentData = new STangentData[nVert];
		memcpy(m_pTangentData, pVert, sizeof(STangentData) * nVert);
	}
	//------------------------------------------------------------------------------------
	void VertexData::InitBoneWeights(const SVertexBoneWeight* pBoneWeights, uint32 nVert)
	{
		SAFE_DELETE_ARRAY(m_pBoneWeights);

		m_pBoneWeights = new SVertexBoneWeight[nVert];
		memcpy(m_pBoneWeights, pBoneWeights, sizeof(SVertexBoneWeight) * nVert);
	}

}