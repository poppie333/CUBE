//-------------------------------------------------------
// �t�@�C�����FCheckpointActor.h
// �T�v�@�@�@�F�`�F�b�N�|�C���g�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/22 ���� �쐬
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class CUBE_API ACheckpointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointActor();

private:
	UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Checkpoint�p��StaticMesh : Checkpoint */
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> Checkpoint;

	/** Checkpoint�p��StaticMesh : Button */
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> Button;

	/** �ڐG����p��Collision : Sphere */
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USphereComponent> Sphere;

	/** Respawn�p��Transform���X�V����SceneComponent **/
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USceneComponent> CheckTransform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
