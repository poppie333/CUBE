//-------------------------------------------------------
// ファイル名：KillVolume.h
// 概要　　　：プレイヤーをキルする空間のクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/15 松丸 作成
//          ：1/19 松丸 更新
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

	/** PlayerをKillするAreaを設定するBox Collision **/
	UPROPERTY(VisibleAnywhere, Category = KillVolume, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> KillVolume;

public:
	/** Box Collisionのサイズを設定する変数 **/
	UPROPERTY(EditAnywhere, Category = "Kill Volume")
		FVector BoxExtent = FVector(32.0f, 32.0f, 32.0f);

private:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
