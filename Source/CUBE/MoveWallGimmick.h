//-------------------------------------------------------
// �t�@�C�����FMoveWallGimmick.cpp
// �T�v�@�@�@�FGimmickBase���p�������A�ړ��ǃM�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/08�@�쐬
//�@�@�@�@ �@�F2/13 �X�V
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GimmickBase.h"
#include "MoveWallGimmick.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API AMoveWallGimmick : public AGimmickBase
{
	GENERATED_BODY()
	
public:
	//�R���X�g���N�^
	AMoveWallGimmick();

public:
	//���t���[���̍X�V����
	virtual void Tick(float DeltaTime)override;

protected:
	//�M�~�b�N�ғ����̃J�E���g����
	void GimmickActivation();

	//GimmickBase����p�������擾�p�̊֐�
	void GimmickON() override;

public:
	//�ړ��J�n�̃t���O
	bool MoveON;
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

	//�ړ����ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Move = false;
	//�g�k���ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Scale = false;

	//X�����ړ����邩�ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Xaxis = false;
	//Y�����ړ����邩�ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Yaxis = false;
	//Z�����ړ����邩�ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Zaxis = false;

	//X���̃v���X�}�C�i�X
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool XPlusMinus = false;
	//Y���̃v���X�}�C�i�X
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool YPlusMinus = false;
	//Z���̃v���X�}�C�i�X
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool ZPlusMinus = false;

	//�ғ���ɔj�󂷂邩�ۂ�
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool DestroyMoveWall = false;

private:
	//�J�n�ʒu�̔c���p
	FVector startLocation;
	//�M�~�b�N�ғ����̃J�E���g�p
	float GimmickCnt;
	//��x�����s�������p
	bool OnProgram;

};
