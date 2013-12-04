/********************************************************************
	created:	2013/07/23
	created:	23:7:2013   9:33
	filename: 	RenderObject.h
	author:		maval
	
	purpose:	��Ⱦ����߲��װ
*********************************************************************/
#ifndef RenderObject_h__
#define RenderObject_h__

#include "Prerequiestity.h"
#include "MathDef.h"
#include "GeometryDef.h"
#include "AABB.h"

namespace Neo
{
	class RenderObject
	{
	public:
		RenderObject();
		~RenderObject();

	public:
		bool	CreateVertexBuffer(const Neo::SVertex* pVerts, int nVert, bool bStatic);
		bool	CreateIndexBuffer(const DWORD* pIdx, int nIdx, bool bStatic);
		void	OnFrameMove();
		void	Render();
		void	SetMaterial(Neo::Material* pMaterial);
		void	SetWorldMatrix(const MAT44& matWorld)	{ m_matWorld = matWorld; }
		const MAT44& GetWorldMatrix() const { return m_matWorld; }
		const MAT44& GetWorldITMatrix() const { return m_matWorldIT; }

	private:
		ID3D11Buffer*	m_pVertexBuf;
		ID3D11Buffer*	m_pIndexBuf;
		Neo::Material*	m_pMaterial;

		DWORD			m_nVertCnt;
		DWORD			m_nPrimCnt;
		MAT44			m_matWorld;
		MAT44			m_matWorldIT;		//����������ת��,���ڷ��߱任
		AABB			m_localAABB;		//���ذ�Χ��
		AABB			m_worldAABB;		//�����Χ��
	};

	typedef std::vector<RenderObject*>		RenderList;
}


#endif // RenderObject_h__