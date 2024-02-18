//-------------------------------------------------------
// �t�@�C�����FGoalActor.cpp
// �T�v�@�@�@�F�S�[���A�N�^�[�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/15 �쐬
// 
//-------------------------------------------------------

#include "GoalActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CUBE/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalActor::AGoalActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent��ǉ����ARootComponent�ɐݒ肷��
	Goal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = Goal;

	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("S_Goal"));

	// StaticMesh��StaticMeshComponent�ɐݒ肷��
	Goal->SetStaticMesh(Mesh);

	// SphereCollision��ǉ�����
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	// Radius��ݒ肷��
	Sphere->SetSphereRadius(72.0f);

	// OnComponentBeginOverlap��Bind����
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnSphereBeginOverlap);
}

// Called when the game starts or when spawned
void AGoalActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//�X�t�B�A�R���W����
void AGoalActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ڐG����Actor���v���C���[�ɐG��Ă���Ƃ�
	if (const APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		//�f�o�b�O���O
		UE_LOG(LogTemp, Display, TEXT("Goal"));

		// �J�ڂ���Level��Load����
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, LoadLevel);
	}
}