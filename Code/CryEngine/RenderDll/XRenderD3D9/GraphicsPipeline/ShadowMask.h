// Copyright 2001-2016 Crytek GmbH. All rights reserved.

#pragma once

#include "Common/GraphicsPipelineStage.h"
#include "Common/FullscreenPass.h"
#include "StandardGraphicsPipeline.h"

namespace ShadowMaskInternal
{
	class CSunShadows;
	class CLocalLightShadows;
}

class CShadowMaskStage : public CGraphicsPipelineStage
{
	friend class ShadowMaskInternal::CSunShadows;
	friend class ShadowMaskInternal::CLocalLightShadows;

public:
	CShadowMaskStage();

	void Init();
	void Prepare(CRenderView* pRenderView) final;
	void Execute();

private:
	std::unique_ptr<ShadowMaskInternal::CSunShadows>        m_pSunShadows;
	std::unique_ptr<ShadowMaskInternal::CLocalLightShadows> m_pLocalLightShadows;

	std::vector<CPrimitiveRenderPass>                       m_maskGenPasses;
	CPrimitiveRenderPass                                    m_debugCascadesPass;

	CTexture*                                               m_pShadowMaskRT;
	CConstantBufferPtr                                      m_pPerViewConstantBuffer;
	float                                                   m_filterKernel[8][4];

	CStandardGraphicsPipeline::SViewInfo                    m_viewInfo[2];
	int                                                     m_viewInfoCount;

	int                                                     m_samplerComparison;
	int                                                     m_samplerPointClamp;
	int                                                     m_samplerPointWrap;
	int                                                     m_samplerBilinearWrap;
	int                                                     m_samplerTrilinearBorder;

	int                                                     m_sunShadowPrimitives;
	int                                                     m_localLightPrimitives;
};