//-------------------------------------------------------
// �t�@�C�����FGoalActor.cpp
// �T�v�@�@�@�F�S�[���A�N�^�[�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/15 �쐬
// 
//-------------------------------------------------------

//�C���N���[�h�K�[�h
#pragma once

//�C���N���[�h
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class CUBE_API AGoalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** Goal�p��StaticMesh : Goal */
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))TObjectPtr<UStaticMeshComponent> Goal;

	/** �ڐG����p��Collision : Sphere */
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))TObjectPtr<USphereComponent> Sphere;

private:
	UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	/** �J�ڂ���Level��Soft�Q�� */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GOAL")
		TSoftObjectPtr<UWorld> LoadLevel;

};
