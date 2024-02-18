//-------------------------------------------------------
// �t�@�C�����FKillVolume.h
// �T�v�@�@�@�F�v���C���[���L�������Ԃ̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/15 ���� �쐬
//          �F1/19 ���� �X�V
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillVolume.generated.h"

class UBoxComponent;

UCLASS()
class CUBE_API AKillVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillVolume();

protected:
	// ConstructionScript
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** Default Scene Root **/
	UPROPERTY(VisibleAnywhere, Category = KillVolume, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	/** Player��Kill����Area��ݒ肷��Box Collision **/
	UPROPERTY(VisibleAnywhere, Category = KillVolume, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> KillVolume;

public:
	/** Box Collision�̃T�C�Y��ݒ肷��ϐ� **/
	UPROPERTY(EditAnywhere, Category = "Kill Volume")
		FVector BoxExtent = FVector(32.0f, 32.0f, 32.0f);

private:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
