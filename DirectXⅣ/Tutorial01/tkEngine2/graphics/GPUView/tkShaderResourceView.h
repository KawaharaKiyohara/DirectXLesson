/*!
 *@brief	ShaderResourceView
 */

#pragma once

namespace tkEngine2{
	class CStructuredBuffer;
	/*!
	 *@brief	ShaderResourceView
	 *@details
	 * テクスチャやストラクチャバッファなど、シェーダーで使用するリソースで使用するビュー。
	 */
	class CShaderResourceView : Noncopyable{
	public:
		CShaderResourceView();
		~CShaderResourceView();
		/*!
		 *@brief	StructuredBuffer用のSRVを作成。
		 *@param[in]	structuredBuffer	structuredBuffer
		 */
		bool Create(CStructuredBuffer& structuredBuffer);
		/*!
		 *@brief	明示的な開放。
		 *@details
		 * 明示的に開放する必要があるときに使用してください。
		 */
		void Release();
	private:
		ID3D11ShaderResourceView*		m_srv = nullptr;
	};
}