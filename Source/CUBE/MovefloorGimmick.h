//-------------------------------------------------------
// �t�@�C�����FMovefloorGimmick.h
// �T�v�@�@�@�FGimmickBase���p�������A�ړ����M�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F12/25 �쐬
//          �F1/15 �X�V
//�@�@�@�@ �@�F1/29 �X�V
//�@�@�@�@ �@�F2/08 �X�V
//�@�@�@�@ �@�F2/09 �X�V
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GimmickBase.h"
#include "MovefloorGimmick.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class CUBE_API AMovefloorGimmick : public AGimmickBase
{
	GENERATED_BODY()
	

public:
	//�R���X�g���N�^
	AMovefloorGimmick();

public:
	//���t���[���̍X�V����
	virtual void Tick(float DeltaTime)override;

protected:
	//�M�~�b�N�ғ����̃J�E���g����
	void GimmickActivation();

	//GimmickBase����p�������擾�p�̊֐�
	void GimmickON() override;

	//�ړ����x
	float velocity;
	//�J�E���g�̎w�莞��
	float GimmickCntActivation;
	//�ړ����x�̒����p
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		float AdjustVelocity = 1.0f;
	//�J�E���g�w�莞�Ԃ̒����p
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		float AdjustCount = 1.0f;

	//X�����ړ����邩�ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Xaxis = false;
	//Y�����ړ����邩�ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Yaxis = false;
	//Z�����ړ����邩�ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Zaxis = false;

	//�v���C���[�̐ڐG�œ������ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool AutGimmick = false;

	//�v���C���[���ڐG���Ă��玩���œ������ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool AutGimmickBoot = false;

private:
	//���~���̃t���O
	bool FloorDown;
	//�ړ����x�̕ۑ��p
	float Save_velocity;
	//�M�~�b�N�ғ����̃J�E���g�p
	float GimmickCnt;
	//��x�����s�������p
	bool OnProgram;

};
