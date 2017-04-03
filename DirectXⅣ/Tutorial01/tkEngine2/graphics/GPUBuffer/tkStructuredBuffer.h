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
		* @brief	StructuredBuffer���쐬�B
		*@param[in]	numElement		�v�f���B
		*@param[in]	elementSize		�v�f����̃T�C�Y�B
		*@param[in]	pInitData		�����f�[�^�B
		*/
		bool Create(int numElement, int elementSize, const void* pInitData);
		/*!
		 * @brief	ID3D11Buffer*���擾�B
		 */
		ID3D11Buffer*& GetBody() 
		{
			return m_structuredBuffer;
		}
		/*!
		*@brief	�J���B
		*@details
		* ���̊֐��̓f�X�g���N�^������R�[������Ă��܂��B
		* �����I�ȃ^�C�~���O�ŊJ���������ꍇ�ɌĂяo���Ă��������B
		*/
		void Release();
	private:
		ID3D11Buffer*		m_structuredBuffer = nullptr;	//!<StructuredBuffer
	};
}