//-------------------------------------------------------
// �t�@�C�����FLadderGimmick.h
// �T�v�@�@�@�FGimmickBase���p�������A��q�M�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/22 ���� �쐬
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "CUBE/GimmickBase.h"
#include "LadderGimmick.generated.h"

class UBoxComponent;

UCLASS()
class CUBE_API ALadderGimmick : public AGimmickBase
{
	GENERATED_BODY()
	
public:
	//�R���X�g���N�^
	ALadderGimmick();

public:
	//���t���[���̍X�V����
	virtual void Tick(float DeltaTime)override;

protected:
	void GimmickON() override;

private:       
	//�����o�[�ϐ�


};
