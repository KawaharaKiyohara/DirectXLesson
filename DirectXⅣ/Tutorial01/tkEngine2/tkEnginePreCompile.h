#pragma once

#pragma warning (disable  : 4201)

#include <windows.h>
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>
#include "tkEngine2/policy/tkNoncopyable.h"
#include "tkEngine2/policy/tkScopedResource.h"
#include "tkEngine2/debug/tkLog.h"
#include "tkEngine2/debug/tkAssert.h"
#include "tkEngine2/math/tkVector.h"
#include "tkEngine2/math/tkMatrix.h"
#include "graphics/tkRenderContext.h"

#include "gameObject/tkGameObjectManager.h"

#include "tkEngine2\graphics\tkShader.h"
#include "tkEngine2/graphics/GPUBuffer/tkVertexBuffer.h"
#include "tkEngine2/graphics/GPUBuffer/tkStructuredBuffer.h"
#include "tkEngine2/graphics/GPUView/tkShaderResourceView.h"
#include "tkEngine2/graphics/GPUView/tkUnorderedAccessView.h"
