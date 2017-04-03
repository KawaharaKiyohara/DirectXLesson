/*!
 * @brief	StructuredBuffer
 */

#include "tkEngine2/tkEnginePreCompile.h"
#include "tkEngine2/graphics/GPUBuffer/tkStructuredBuffer.h"
#include "tkEngine2/tkEngine.h"

namespace tkEngine2{
	CStructuredBuffer::CStructuredBuffer()
	{
	}
	CStructuredBuffer::~CStructuredBuffer()
	{
	}
	void CStructuredBuffer::Release()
	{
		if (m_structuredBuffer != nullptr) {
			m_structuredBuffer->Release();
			m_structuredBuffer = nullptr;
		}
	}
	bool CStructuredBuffer::Create(int numElement, int elementSize, const void* pInitData)
	{
		Release();
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		//UAVとSRVにバインド可能。
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
		desc.ByteWidth = numElement * elementSize;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = elementSize;
		HRESULT hr;
		if (pInitData) {
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = pInitData;
			hr = Engine().GetD3DDevice()->CreateBuffer(&desc, &InitData, &m_structuredBuffer);
		}
		else {
			hr = Engine().GetD3DDevice()->CreateBuffer(&desc, NULL, &m_structuredBuffer);
		}
		if (FAILED(hr)) {
			return false;
		}
		return true;
	}
}