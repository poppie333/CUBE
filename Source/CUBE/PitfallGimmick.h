//-------------------------------------------------------
// �t�@�C�����FPitfallGimmick.h
// �T�v�@�@�@�FGimmickBase���p�������A���Ƃ����M�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F12/08
//�@�@�@�@�@ �F12/15 �X�V
//   
//-------------------------------------------------------

//�C���N���[�h�K�[�h
#pragma once

//�C���N���[�h
#include "CoreMinimal.h"
#include "GimmickBase.h"
#include "PitfallGimmick.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API APitfallGimmick : public AGimmickBase
{
	GENERATED_BODY()
	
public:
	//�R���X�g���N�^
	APitfallGimmick();

public:
	//���t���[���̍X�V����
	virtual void Tick(float DeltaTime)override;

protected:
	void GimmickON() override;

private:

	//�����o�[�ϐ�


};
