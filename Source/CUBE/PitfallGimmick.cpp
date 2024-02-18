//-------------------------------------------------------
// �t�@�C�����FPitfallGimmick.h
// �T�v�@�@�@�FGimmickBase���p�������A���Ƃ����M�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F12/08  
//          �F12/15 ����
//-------------------------------------------------------

//�C���N���[�h
#include "PitfallGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

//�R���X�g���N�^
APitfallGimmick::APitfallGimmick()
{
	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("PitfallGimmick"));

	// StaticMesh��StaticMeshComponent�ɐݒ肷��
	GimmickMesh->SetStaticMesh(Mesh);

	// Box�̈ʒu�𒲐�����
	Box->SetRelativeLocation(FVector(40.0f, -40.0f, 70.0f), false);
}

//���t���[���̍X�V����
void APitfallGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//�v���C���[�ɐG�ꂽ�玩�g����������
void APitfallGimmick::GimmickON()
{
	//���̃M�~�b�N�͔j�������
	UNDestroy = true;
}