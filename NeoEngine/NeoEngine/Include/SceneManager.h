/********************************************************************
	created:	5:12:2013   9:22
	filename: 	SceneManager.h
	author:		maval
	
	purpose:	����������
*********************************************************************/
#ifndef SceneManager_h__
#define SceneManager_h__

#include "Prerequiestity.h"
#include "Light.h"

namespace Neo
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

	public:
		bool		Init();
		void		Update(float fDeltaTime);
		void		Render(Material* pMaterial = nullptr);
		void		RenderPipline(uint32 phaseFlag = eRenderPhase_All, Material* pMaterial = nullptr);

		void		ToggleScene();
		void		SetCamera(Camera* pCam) { m_camera = pCam; }
		Camera*		GetCamera()	{ return m_camera; }
		Scene*		GetCurScene() { return m_pCurScene; }
		void		ClearScene();

		// Create entity from loaded mesh
		Entity*		CreateEntity(eEntity type, const STRING& meshname);
		Mesh*		LoadMeshFromFile(const STRING& meshname, const STRING& filename);
		void		EnableDebugRT(eDebugRT type);
		void		SetShadowDepthBias(float fBias);
		float		GetShadowDepthBias() const;
		void		SetEnableAmbientCube(bool bEnable);
		void		SetCurRenderPhase(eRenderPhase e) { m_curRenderPhase = e; }
		eRenderPhase	GetCurRenderPhase() const { return m_curRenderPhase; }
		STRING&		GetHeroStateChangeStr() { return m_strHeroStateChange; }
		void		SetShadowMapSize(uint32 nSize);
		uint32		GetShadowMapSize() const;


		void		SetupSunLight(const VEC3& dir, const SColor& color);
		void		AddPointLight(const SPointLight& light);
		void		CreateSky();
		void		CreateTerrain();
		void		CreateWater(float waterHeight = 0.0f);
		ThirdPersonCharacter*		CreateHero(Scene* pScene, const VEC3& vCamPos);

		const SDirectionLight&		GetSunLight() const { return m_sunLight; }
		D3D11RenderTarget*			GetNormalRT() { return m_pRT_Normal; }
		D3D11RenderTarget*			GetAlbedoRT() { return m_pRT_Albedo; }
		D3D11RenderTarget*			GetSpecRT() { return m_pRT_Specular; }
		D3D11RenderTarget*			GetDepthRT() { return m_pRT_Depth; }
		SSAO*						GetSSAO()		{ return m_pSSAO; }
		Terrain*					GetTerrain()	{ return m_pTerrain; }
		Sky*						GetSky()		{ return m_pSky; }
		ThirdPersonCharacter*		GetHero()		{ return m_pHero; }
		ShadowMap*					GetShadowMap()	{ return m_pShadowMap; }
		AmbientCube*				GetAmbientCube() { return m_pAmbientCube; }
		const PointLightVector&		GetPointLights() const { return m_vecPointLights; }
		D3D11Texture*				GetEnvBRDFTexture() { return m_pTexEnvBRDF; }

		// Convenient mesh create function
		static Mesh*	CreatePlaneMesh(float w, float h, float fUvMultiplier = 1.0f);
		static Mesh*	CreateCubeMesh(const VEC3& minPt, const VEC3& maxPt);
		static Mesh*	CreateFrustumMesh(const VEC3& minBottom, const VEC3& maxBottom, const VEC3& minTop, const VEC3& maxTop);
		bool			LoadSponzaScene(Scene* pScene);

	private:
		void		_InitAllScene();
		void		_RenderGBuffer();
		void		_LinearizeDepth();
		void		_CompositionPass();
		void		_PointLightPass();
		void		_HDRFinalScenePass();

		std::vector<Scene*>		m_scenes;	
		Scene*					m_pCurScene;

		D3D11RenderSystem*		m_pRenderSystem;
		D3D11RenderTarget*		m_pRT_Normal;
		D3D11RenderTarget*		m_pRT_Albedo;
		D3D11RenderTarget*		m_pRT_Specular;
		D3D11RenderTarget*		m_pRT_Compose;
		D3D11RenderTarget*		m_pRT_Depth;

		uint32			m_nShadowMapSize;
		eRenderPhase	m_curRenderPhase;
		Camera*			m_camera;
		SDirectionLight	m_sunLight;				// Sun light
		AmbientCube*	m_pAmbientCube;
		PointLightVector	m_vecPointLights;	// Point lights in current scene
		Terrain*		m_pTerrain;
		Water*			m_pWater;
		Sky*			m_pSky;
		ShadowMap*		m_pShadowMap;
		SSAO*			m_pSSAO;
		TileBasedDeferredRenderer*	m_pTBDR;
		ThirdPersonCharacter*	m_pHero;
		D3D11Texture*	m_pTexEnvBRDF;
		Material*		m_pMtlCompose;
		Material*		m_pMtlLinearizeDepth;
		Material*		m_pMtlFinalScene;

		MeshLoader*		m_pMeshLoader;
		typedef std::unordered_map<STRING, Mesh*>			MeshContainer;
		typedef std::unordered_map<Mesh*, SkeletonAnim*>	SkeletonContainer;
		MeshContainer	m_meshes;
		SkeletonContainer m_skeletons;
		
		eDebugRT		m_debugRT;
		Mesh*			m_pDebugRTMesh;
		Material*		m_pDebugRTMaterial;
		STRING			m_strHeroStateChange;
	};
}

#endif // SceneManager_h__