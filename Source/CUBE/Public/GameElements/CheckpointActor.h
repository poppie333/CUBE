//-------------------------------------------------------
// ファイル名：CheckpointActor.h
// 概要　　　：チェックポイントのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/22 松丸 作成
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

	/** Checkpoint用のStaticMesh : Checkpoint */
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> Checkpoint;

	/** Checkpoint用のStaticMesh : Button */
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> Button;

	/** 接触判定用のCollision : Sphere */
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USphereComponent> Sphere;

	/** Respawn用のTransformを更新するSceneComponent **/
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USceneComponent> CheckTransform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
