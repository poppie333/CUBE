//-------------------------------------------------------
// �t�@�C�����FCeilingfallGimmick.h
// �T�v�@�@�@�FGimmickBase���p�������A�V�䗎���M�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F12/15
//           �F12/18 �X�V
//           �F12/20 �X�V
//�@�@�@�@�@  �F12/22 �X�V
//�@�@�@�@ �@ �F1/12 �X�V
//�@�@�@�@ �@ �F1/22 �X�V
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GimmickBase.h"
#include "CeilingfallGimmick.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API ACeilingfallGimmick : public AGimmickBase
{
	GENERATED_BODY()

public:
	//�R���X�g���N�^
	ACeilingfallGimmick();

public:
	//���t���[���̍X�V����
	virtual void Tick(float DeltaTime)override;

protected:
	//�M�~�b�N�ғ����̃J�E���g����
	void GimmickActivation();

	//GimmickBase����p�������擾�p�̊֐�
	void GimmickON() override;

private:

	//�����o�[�ϐ�

public:
	//�����J�n�̃t���O
	bool FallON;
	//�������x
	float velocity;
	//�J�E���g�̎w�莞��
	float GimmickCntActivation;
	//�������x�̒����p
	UPROPERTY(EditAnywhere, Category = "Gimmick")
	float AdjustVelocity = 1.0f;
	//�J�E���g�w�莞�Ԃ̒����p
	UPROPERTY(EditAnywhere, Category = "Gimmick")
	float AdjustCount = 1.0f;

private:
	//�J�n�ʒu�̔c���p
	FVector startLocation;
	//�M�~�b�N�ғ����̃J�E���g�p
	float GimmickCnt;

	//��x�����s�������p
	bool OnProgram;
};
