/*!
 *@brief	ShaderResourceView
 */

#pragma once

namespace tkEngine2{
	class CStructuredBuffer;
	/*!
	 *@brief	ShaderResourceView
	 *@details
	 * �e�N�X�`����X�g���N�`���o�b�t�@�ȂǁA�V�F�[�_�[�Ŏg�p���郊�\�[�X�Ŏg�p����r���[�B
	 */
	class CShaderResourceView : Noncopyable{
	public:
		CShaderResourceView();
		~CShaderResourceView();
		/*!
		 *@brief	StructuredBuffer�p��SRV���쐬�B
		 *@param[in]	structuredBuffer	structuredBuffer
		 */
		bool Create(CStructuredBuffer& structuredBuffer);
		/*!
		 *@brief	�����I�ȊJ���B
		 *@details
		 * �����I�ɊJ������K�v������Ƃ��Ɏg�p���Ă��������B
		 */
		void Release();
	private:
		ID3D11ShaderResourceView*		m_srv = nullptr;
	};
}