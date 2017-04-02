/*!
 * @brief	StructuredBuffer
 */

#pragma once

namespace tkEngine2{
	/*!
	 * @brief	StructuredBuffer
	 */
	class CStructuredBuffer : Noncopyable{
	public:
		CStructuredBuffer();
		~CStructuredBuffer();
		/*!
		 * @brief	ID3D11Buffer*‚ğæ“¾B
		 */
		ID3D11Buffer*& GetBody() 
		{
			return m_structuredBuffer;
		}
	private:
		ID3D11Buffer*		m_structuredBuffer = nullptr;	//!<StructuredBuffer
	};
}