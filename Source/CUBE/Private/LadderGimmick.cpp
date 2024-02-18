//-------------------------------------------------------
// �t�@�C�����FLadderGimmick.cpp
// �T�v�@�@�@�FGimmickBase���p�������A��q�M�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/22 ���� �쐬
//-------------------------------------------------------

#include "LadderGimmick.h"
#include "CUBE/PlayerCharacter.h"
#include "Components/BoxComponent.h"

ALadderGimmick::ALadderGimmick()
{
	//Tick���N��
	PrimaryActorTick.bCanEverTick = true;

	// Box�̃T�C�Y��ݒ肷��
	Box->SetBoxExtent(FVector(50.0f, 50.0f, 10.0f));
}

//���t���[���̍X�V����
void ALadderGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//�v���C���[�ɐG�ꂽ�珈�����J�n����t���O���N��
void ALadderGimmick::GimmickON()
{
	//��q
	LadderCol = true;
}
