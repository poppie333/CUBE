/*
* PlayerCharacter.cpp
* プレイヤーキャラクターを制御するクラス
* Create by 日向野　大聖 on 2023/12/07
* 更新日時・内容：Cameraの入力処理の作成		by 日向野　大聖  on 2023/12/14
*				：PlayerMoveMentの作成			by 黒田　雄志	 on 2023/12/15
*				：移動処理完成					by 黒田　雄志	 on 2023/12/22
*				：待機処理試行					by 黒田			 on 2024/01/29
*				：カメラ回転処理の仕様変更		by 日向野　		 on 2024/02/09
*				：MoveInput仕様変更				by 日向野　		 on 2024/02/09
*				：カメラの仕様変更				by 日向野		 on 2024/02/14
*				：キャラクターの状態管理処理	by 日向野		 on 2024/02/16
*/



#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"				// カメラ制御
#include "GameFramework/SpringArmComponent.h"   // スプリングアーム
#include "kismet/kismetSystemLibrary.h"
#include "kismet/GamePlayStatics.h"
#include "DrawDebugHelpers.h"
#include "MainCamera.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(MyCategory, Warning, All);

// Sets default values
APlayerCharacter::APlayerCharacter()
	: mp_RotateNum(0.f)
	, mp_bPressed(false)
	, CntNum(0)
	, CameraMove(true)
	, m_characterMoveInput(FVector2D::ZeroVector)
	, m_moveSpeed(10.f)
	, JumpPower(500.f)
	, CanJump(true)
	, MoveCamera_R(false)
	, MoveCamera_L(false)
	, camerastate(Right)
	, Camera(NULL)
	, playerstate(Idle)
	, OnLadder(false)
	, CollisionPlayer(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RightCameraAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Input/InputAction/IA_CameraRot_R"), NULL, LOAD_None, NULL);
	LeftCameraAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Input/InputAction/IA_CameraRot_L"), NULL, LOAD_None, NULL);

	CameraDistanceAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Input/InputAction/IA_CameraDis"), NULL, LOAD_None, NULL);

	MoveAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Input/InputAction/IA_CharacterMove"), NULL, LOAD_None, NULL);

	DefaultMappingContext = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/Input/InputMapping"), NULL, LOAD_None, NULL);

	JumpAction = LoadObject<UInputAction>(NULL, TEXT("/Game/Input/InputAction/IA_CharacterJump"), NULL, LOAD_None, NULL);


	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// カメラの初期化
	InitializeCamera();

	// カメラの取得
	GetCamera();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SetActorRotation(FRotator(0, 0, 0));

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCamera();
	UpdateCharacter();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// PlayerControllerを取得する
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// 入力を有効にする
	EnableInput(controller);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		// CameraRotChange
		EnhancedInputComponent->BindAction(RightCameraAction, ETriggerEvent::Started, this, &APlayerCharacter::RightCameraInput);
		EnhancedInputComponent->BindAction(LeftCameraAction, ETriggerEvent::Started, this, &APlayerCharacter::LeftCameraInput);
		// CameraDisChange
		EnhancedInputComponent->BindAction(CameraDistanceAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CameraDistanceInput);
		// CharacterMovement
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveInput);
		// JumpAction
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

void APlayerCharacter::InitializeCamera()
{
	// スプリングアームオブジェクトの生成
	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	pSpringArm->SetupAttachment(RootComponent);

	// カメラのオブジェクトを生成
	mp_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("pCamera"));
	mp_Camera->SetupAttachment(pSpringArm, USpringArmComponent::SocketName);

	// カメラのセット
	mp_CameraMng = NewObject<UCameraManager>();
	mp_CameraMng->SetCamera(mp_Camera, pSpringArm);

	// カメラが存在するなら
	if (mp_CameraMng->GetCamera() != NULL)
	{
		// カメラの相対回転を設定
		mp_CameraMng->SetCameraRot(0.f, -90.f, 0.f);
		// スプリングアーム
		mp_CameraMng->SetTargetArmLength(600.f);
		// カメラのコリジョン
		mp_CameraMng->SetDoCollisionTest(false);
		// カメラの追従ラグ
		mp_CameraMng->SetEnableCameraLag(false);
	}
}

// カメラの更新
void APlayerCharacter::UpdateCamera()
{
	// ボタンが押されたら
	if (mp_bPressed)
	{
		// カメラの更新
		if (CntNum < 90)
		{
			if (playerstate != PlayerCamera)
			{
				// カメラの取得
				AMainCamera* CameraObj = Cast<AMainCamera>(Camera);

				CameraObj->RotationCamera(MoveCamera_R, MoveCamera_L);
			}
			else
			{
				// カメラの位置の取得
				FRotator rotation = pSpringArm->GetRelativeRotation();

				if (MoveCamera_R == true)
				{
					rotation.Yaw -= 5.f;
				}
				else if (MoveCamera_L == true)
				{
					rotation.Yaw += 5.f;
				}

				pSpringArm->SetRelativeRotation(FRotator(0.f, rotation.Yaw, 0.f));
			}
			CntNum += 5;
		}
		else
		{
			mp_bPressed = false;
			CameraMove = true;
			MoveCamera_L = false;
			MoveCamera_R = false;
			CntNum = 0;
		}
	}
}

void APlayerCharacter::UpdateCharacter()
{
	//this->OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnActorOverlapBegin);
	//this->OnActorEndOverlap.AddDynamic(this, &APlayerCharacter::OnActorOverlapEnd);

	if (OnLadder) { playerstate = Climb; }
	else if (ChangePlayerCamera) { playerstate = PlayerCamera; }
	else if (CollisionPlayer) { playerstate = FollowCamera; }
	else { playerstate = Idle; }

	AMainCamera* CameraObj = NULL;
	if (playerstate == FollowCamera)
	{
		if (CameraObj == NULL)
		{
			CameraObj = Cast<AMainCamera>(Camera);

			CameraObj->OnFollowPlayer(true);
		}
		else { return; }
	}
	else
	{
		if (CameraObj != NULL) {
			CameraObj->OnFollowPlayer(false);
		}
	}
}

// カメラインプット（回転）
void APlayerCharacter::RightCameraInput()
{
	if (!MoveCamera_L && !MoveCamera_R) {
		mp_bPressed = true;
		MoveCamera_R = true;
		if (camerastate == Right) { camerastate = Front; }
		else if (camerastate == Back) { camerastate = Right; }
		else if (camerastate == Left) { camerastate = Back; }
		else { camerastate = Left; }
	}
}
void APlayerCharacter::LeftCameraInput()
{
	if (!MoveCamera_L && !MoveCamera_R) {
		mp_bPressed = true;
		MoveCamera_L = true;
		if (camerastate == Right) { camerastate = Back; }
		else if (camerastate == Back) { camerastate = Left; }
		else if (camerastate == Left) { camerastate = Front; }
		else { camerastate = Right; }
	}
}

// カメラインプット（距離）
void APlayerCharacter::CameraDistanceInput(const FInputActionValue& Value)
{
	AMainCamera* CameraObj = Cast<AMainCamera>(Camera);

	float NewOffset;
	NewOffset = FMath::Clamp(Value.Get<float>(), -10.0f, 10.0f);

	if (pSpringArm != NULL)
	{
		// スプリングアームの調節
		if (playerstate == PlayerCamera)
		{
			pSpringArm->TargetArmLength -= NewOffset * 10;
			if (pSpringArm->TargetArmLength > MaxPlayerCamera) { pSpringArm->TargetArmLength = MaxPlayerCamera; }
			if (pSpringArm->TargetArmLength < MinPlayerCamera) { pSpringArm->TargetArmLength = MinPlayerCamera; }
		}
		else { CameraObj->ChangeDistance(NewOffset); }
	}
}

// キャラの動き
void APlayerCharacter::MoveInput(const FInputActionValue& Value)
{
	//FVector NewLocation = GetActorLocation();		// 俺の
	//FVector2D NewLocation = Value.Get<FVector2D>();	// UE5テンプレートの
	FVector NewLocation;
	NewLocation.X = FMath::Clamp(Value.Get<float>(), -1.0f, 1.0f);

	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// UKismetSystemLibrary::PrintString(GEngine->GetWorld(), this->GetActorRotation().ToString(), true, true, FLinearColor(0.0f, 0.66f, 1.0f, 1.0f), 2.0f);

	// get forward vector
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	FVector RightDirection = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);   //FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 視点回転のキーが押されていない
	if (!mp_bPressed)
	{
		if (pSpringArm != NULL)
		{
			// 梯子上る処理
			// 使えなかったです。
			if (playerstate == Climb)
			{
				//FVector vec = GetActorLocation();
				//vec.Z += 10.f;//NewLocation.X * 10.f;
				//SetActorLocation(vec);
				////AddMovementInput(GetActorUpVector(), NewLocation.X);
			}
			// 横から見たとき(X軸上を移動)
			// SpringArmが向く方向に、入力による移動量をPawnMovementComponentに渡す
			// ほんとは一行にまとめられると思います。
			else
			{
				if (camerastate == Front)
				{
					//FVector vec = GetActorLocation();
					//vec += pSpringArm->GetRightVector() * NewLocation.X;
					AddMovementInput(ForwardDirection, NewLocation.X);
					// これだと出来る　はぁ？
					//SetActorLocation(vec);
				}
				else if (camerastate == Left)
				{
					AddMovementInput(RightDirection, -NewLocation.X);
				}
				else if (camerastate == Back)
				{
					AddMovementInput(ForwardDirection, -NewLocation.X);
				}
				else if (camerastate == Right)
				{
					AddMovementInput(RightDirection, NewLocation.X);
				}
			}
		}
	}
}

// カメラアクターの取得
void APlayerCharacter::GetCamera()
{
	if (Camera == NULL)
	{
		TSubclassOf<AActor> findClass;
		findClass = AActor::StaticClass();
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), findClass, actors);

		if (actors.Num() > 0)
		{
			for (int idx = 0; idx < actors.Num(); idx++)
			{
				AActor* pActor = Cast<AActor>(actors[idx]);

				if (pActor->ActorHasTag("Camera"))
				{
					Camera = pActor;
					break;
				}
			}
		}
	}
}
