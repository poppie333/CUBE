//-------------------------------------------------------
// ファイル名：GoalActor.cpp
// 概要　　　：ゴールアクターのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/15 作成
// 
//-------------------------------------------------------

//インクルードガード
#pragma once

//インクルード
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
	/** Goal用のStaticMesh : Goal */
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))TObjectPtr<UStaticMeshComponent> Goal;

	/** 接触判定用のCollision : Sphere */
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))TObjectPtr<USphereComponent> Sphere;

private:
	UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	/** 遷移するLevelのSoft参照 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GOAL")
		TSoftObjectPtr<UWorld> LoadLevel;

};
