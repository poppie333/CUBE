//-------------------------------------------------------
// ファイル名：GimmickBase.h
// 概要　　　：ギミックのベースクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：12/08  
//          ：12/15 更新
//　　　　　 ：12/22 更新
//　　　　 　：1/12 更新
//　　　　 　：1/22 更新
//　　　　 　：2/08 更新
//-------------------------------------------------------

//インクルードガード
#pragma once

//インクルード
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GimmickBase.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class CUBE_API AGimmickBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGimmickBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Hit EventをBindingする関数
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	/** BOXコリジョン取得用の関数 */
	virtual void GimmickON();

protected:
	//スタティックメッシュ
	UPROPERTY(VisibleAnywhere, Category = "Gimmick", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> GimmickMesh;

	//BOXコリジョン
	UPROPERTY(VisibleAnywhere, Category = "Gimmick", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> Box;

public:
	//ギミックを破棄するフラグ
	bool UNDestroy = false;
	//ギミックがプレイヤーをキルするフラグ
	bool PlayerKill = false;
	//ギミックを起動するフラグ
	bool BootGimmick = false;
	//ギミックが起動したかどうかの反応フラグ
	bool BootGimmickReaction = false;

	//メンバー変数
	bool LadderCol = false;

	//移動量
	float velocity = 70.0f;
	//ギミック稼働中のカウント用
	float GimmickCnt;
	//カウントの指定時間
	float GimmickCntActivation = 5.0f;

protected:
	//ギミック稼働中のカウント処理
	void GimmickActivation();

	AActor* AO;
	bool PA = false;
};
