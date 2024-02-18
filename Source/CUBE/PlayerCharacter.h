/*
* PlayerCharacter.h
* プレイヤーキャラクターを制御するクラス
* Create by 日向野　大聖 on 2023/12/07
* 更新日時・内容：Cameraの入力処理の作成				by 日向野　大聖  on 2023/12/14
*						：PlayerMoveMentの作成			by 黒田　雄志	 on 2023/12/15
*						：移動処理完成					by 黒田　雄志	 on 2023/12/22
*						：待機処理試行					by 黒田			 on 2024/01/29
*						：カメラ回転処理の仕様変更		by 日向野　		 on 2024/02/09
*						：MoveInput仕様変更				by 日向野　		 on 2024/02/09
*						：カメラの仕様変更				by 日向野		 on 2024/02/14
*/

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Manager/CameraManager.h" // カメラマネージャー
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CUBE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		///** MappingContext */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	///** Camera Input Action */			// このクラスをLoadObjectし、EnhancedInputで関数とバインドする
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* RightCameraAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LeftCameraAction;

	// CameraDistance
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* CameraDistanceAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// カメラの初期化
	void InitializeCamera();

	// カメラを更新
	void UpdateCamera();

	// キャラクターを更新
	void UpdateCharacter();

	// カメラインプット
	void RightCameraInput();
	void LeftCameraInput();

	// コントローラーの入力による移動処理
	void MoveInput(const FInputActionValue& Value);

	// カメラ距離の入力処理
	void CameraDistanceInput(const FInputActionValue& Value);

	// カメラアクターの取得
	void GetCamera();

private:
	// メンバ変数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraManager* mp_CameraMng = nullptr;   // カメラマネージャー

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* mp_Camera = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* pSpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
		float MaxPlayerCamera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Reference, meta = (AllowPrivateAccess = "true"))
		float MinPlayerCamera;


	float mp_RotateNum;
	bool mp_bPressed;
	int CntNum;
	bool CameraMove;
	FVector2D m_characterMoveInput;
	float m_moveSpeed;					// 移動量
	float JumpPower;
	bool CanJump;
	// カメラの回転ステータス
	bool MoveCamera_R;
	bool MoveCamera_L;
	// カメラがどこにあるか
	enum CameraState {
		Front,
		Right,
		Back,
		Left
	};
	CameraState camerastate;

	AActor* Camera;

	// プレイヤーのステータス管理
	enum PlayerState {
		Idle,
		Climb,
		PlayerCamera,
	};
	PlayerState playerstate;

	AActor* Trigger;
	AActor* Ladder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
		bool OnLadder;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
		bool ChangePlayerCamera;
};
