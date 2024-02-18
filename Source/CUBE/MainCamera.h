// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manager/CameraManager.h" // カメラマネージャー
#include "MainCamera.generated.h"

UCLASS()
class CUBE_API AMainCamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMainCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// 初期化処理
	void InitializeCamera();

	void Initialize();

	// ステージの取得
	void GetStage();

	// プレイヤーの取得
	void GetPlayer();

	// 毎フレームのカメラの更新
	void UpdateCamera();

public:
	// カメラ回転の処理
	void RotationCamera(bool _right, bool _left);

	// カメラの距離変更
	void ChangeDistance(float _offset);

	// プレイヤーの高さに合わせるか
	void OnFollowPlayer(bool _follow);

	// メンバ変数
private:
	// アクター
	AActor* Stage;
	AActor* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraManager* mp_CameraMng = nullptr;   // カメラマネージャー

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* mp_Camera = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* pSpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float MaxArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float MinArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float ChangeLocationNum;

	bool FollowPlayer;
};
