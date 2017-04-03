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
		* @brief	StructuredBufferを作成。
		*@param[in]	numElement		要素数。
		*@param[in]	elementSize		要素一個分のサイズ。
		*@param[in]	pInitData		初期データ。
		*/
		bool Create(int numElement, int elementSize, const void* pInitData);
		/*!
		 * @brief	ID3D11Buffer*を取得。
		 */
		ID3D11Buffer*& GetBody() 
		{
			return m_structuredBuffer;
		}
		/*!
		*@brief	開放。
		*@details
		* この関数はデストラクタからもコールされています。
		* 明示的なタイミングで開放したい場合に呼び出してください。
		*/
		void Release();
	private:
		ID3D11Buffer*		m_structuredBuffer = nullptr;	//!<StructuredBuffer
	};
}