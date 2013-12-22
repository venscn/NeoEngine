#include "stdafx.h"
#include "Font.h"
#include "D3D11Texture.h"
#include "D3D11RenderSystem.h"
#include "RenderObject.h"
#include "Material.h"


namespace Neo
{
	static const VEC2	GLYGH_SIZE		=	VEC2(15.0f / SCREEN_WIDTH, 42.0f / SCREEN_HEIGHT);
	static const float	GLYGH_UV_SIZEX	=	0.010526315f;
	//-------------------------------------------------------------------------------
	Font::Font()
	:m_pMesh(nullptr)
	,m_pMaterial(nullptr)
	,m_pRenderSystem(g_env.pRenderSystem)
	{
		_InitMaterial();
	}
	//-------------------------------------------------------------------------------
	Font::~Font()
	{
		SAFE_DELETE(m_pMesh);
		SAFE_RELEASE(m_pMaterial);
	}
	//-------------------------------------------------------------------------------
	void Font::DrawText( const STRING& text, const IPOINT& pos, const SColor& color )
	{
		_InitMesh(text, pos, color);

		// Enable alpha blend
		D3D11_BLEND_DESC& blendDesc = m_pRenderSystem->GetBlendStateDesc();
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		m_pRenderSystem->SetBlendStateDesc(blendDesc);

		m_pMesh->Render();

		// Reset render state
		blendDesc.RenderTarget[0].BlendEnable = FALSE;
		m_pRenderSystem->SetBlendStateDesc(blendDesc);
	}
	//------------------------------------------------------------------------------------
	void Font::_InitMesh( const STRING& text, const IPOINT& pos, const SColor& color )
	{
		// Screen pos --> NDC pos
		VEC2 startPos(pos.x/(float)SCREEN_WIDTH, pos.y/(float)SCREEN_HEIGHT);

		startPos.x = startPos.x * 2.0f - 1.0f;
		startPos.y = 1.0f - startPos.y * 2.0f;

		// Init text mesh
		const SColor dxColor = color.GetAsDx();
		const uint32 nChar = text.length();
		SVertex* pVert = new SVertex[nChar * 2 * 3];	// Each character has two triangles, each triangle has three vertices.

		for (uint32 iChar=0,iVert=0; iChar<nChar; ++iChar)
		{
			const char ch = text[iChar];
			assert(ch >= 32 && ch <= 126 && "Not support this character..");

			float left	= startPos.x;
			float top	= startPos.y;
			float right	= left + GLYGH_SIZE.x;
			float bottom= top - GLYGH_SIZE.y;

			float uvLeft	= (ch - 32) * GLYGH_UV_SIZEX;
			float uvRight	= uvLeft + GLYGH_UV_SIZEX;
			float uvTop		= 0.0f;
			float uvBottom	= 1.0f;

			// First tri
			pVert[iVert].pos.Set(left, top, 0);
			pVert[iVert].uv.Set(uvLeft, uvTop);
			pVert[iVert].color = dxColor;

			++iVert;

			pVert[iVert].pos.Set(right, top, 0);
			pVert[iVert].uv.Set(uvRight, uvTop);
			pVert[iVert].color = dxColor;

			++iVert;

			pVert[iVert].pos.Set(left, bottom, 0);
			pVert[iVert].uv.Set(uvLeft, uvBottom);
			pVert[iVert].color = dxColor;

			++iVert;

			// Second tri
			pVert[iVert].pos.Set(right, top, 0);
			pVert[iVert].uv.Set(uvRight, uvTop);
			pVert[iVert].color = dxColor;

			++iVert;

			pVert[iVert].pos.Set(right, bottom, 0);
			pVert[iVert].uv.Set(uvRight, uvBottom);
			pVert[iVert].color = dxColor;

			++iVert;

			pVert[iVert].pos.Set(left, bottom, 0);
			pVert[iVert].uv.Set(uvLeft, uvBottom);
			pVert[iVert].color = dxColor;

			++iVert;

			startPos.x += GLYGH_SIZE.x;
		}

		// Is old buffer big enough?
		const uint32 nBufSize = sizeof(SVertex) * nChar;
		const uint32 nOldSize = sizeof(SVertex) * m_pMesh->GetVertCount();

		if (/*nOldSize < nBufSize*/true)	// Not enough
		{
			m_pMesh->CreateVertexBuffer(pVert, nChar*2*3, false);
		}
		else	// Enough
		{

		}

		delete []pVert;
	}
	//------------------------------------------------------------------------------------
	void Font::_InitMaterial()
	{
		m_pMaterial = new Material;
		m_pMaterial->SetTexture(0, new D3D11Texture(GetResPath("Font.dds")));
		m_pMaterial->InitShader(GetResPath("Font.hlsl"), GetResPath("Font.hlsl"), false);

		m_pMesh = new RenderObject;
		m_pMesh->SetMaterial(m_pMaterial);
	}
}




