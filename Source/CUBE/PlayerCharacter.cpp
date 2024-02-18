/*
* PlayerCharacter.cpp
* �v���C���[�L�����N�^�[�𐧌䂷��N���X
* Create by ������@�吹 on 2023/12/07
* �X�V�����E���e�FCamera�̓��͏����̍쐬		by ������@�吹  on 2023/12/14
*				�FPlayerMoveMent�̍쐬			by ���c�@�Y�u	 on 2023/12/15
*				�F�ړ���������					by ���c�@�Y�u	 on 2023/12/22
*				�F�ҋ@�������s					by ���c			 on 2024/01/29
*				�F�J������]�����̎d�l�ύX		by ������@		 on 2024/02/09
*				�FMoveInput�d�l�ύX				by ������@		 on 2024/02/09
*				�F�J�����̎d�l�ύX				by ������		 on 2024/02/14
*				�F�L�����N�^�[�̏�ԊǗ�����	by ������		 on 2024/02/16
*/



#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"				// �J��������
#include "GameFramework/SpringArmComponent.h"   // �X�v�����O�A�[��
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

	// �J�����̏�����
	InitializeCamera();

	// �J�����̎擾
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
	// PlayerController���擾����
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// ���͂�L���ɂ���
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
	// �X�v�����O�A�[���I�u�W�F�N�g�̐���
	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	pSpringArm->SetupAttachment(RootComponent);

	// �J�����̃I�u�W�F�N�g�𐶐�
	mp_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("pCamera"));
	mp_Camera->SetupAttachment(pSpringArm, USpringArmComponent::SocketName);

	// �J�����̃Z�b�g
	mp_CameraMng = NewObject<UCameraManager>();
	mp_CameraMng->SetCamera(mp_Camera, pSpringArm);

	// �J���������݂���Ȃ�
	if (mp_CameraMng->GetCamera() != NULL)
	{
		// �J�����̑��Ή�]��ݒ�
		mp_CameraMng->SetCameraRot(0.f, -90.f, 0.f);
		// �X�v�����O�A�[��
		mp_CameraMng->SetTargetArmLength(600.f);
		// �J�����̃R���W����
		mp_CameraMng->SetDoCollisionTest(false);
		// �J�����̒Ǐ]���O
		mp_CameraMng->SetEnableCameraLag(false);
	}
}

// �J�����̍X�V
void APlayerCharacter::UpdateCamera()
{
	// �{�^���������ꂽ��
	if (mp_bPressed)
	{
		// �J�����̍X�V
		if (CntNum < 90)
		{
			if (playerstate != PlayerCamera)
			{
				// �J�����̎擾
				AMainCamera* CameraObj = Cast<AMainCamera>(Camera);

				CameraObj->RotationCamera(MoveCamera_R, MoveCamera_L);
			}
			else
			{
				// �J�����̈ʒu�̎擾
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

// �J�����C���v�b�g�i��]�j
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

// �J�����C���v�b�g�i�����j
void APlayerCharacter::CameraDistanceInput(const FInputActionValue& Value)
{
	AMainCamera* CameraObj = Cast<AMainCamera>(Camera);

	float NewOffset;
	NewOffset = FMath::Clamp(Value.Get<float>(), -10.0f, 10.0f);

	if (pSpringArm != NULL)
	{
		// �X�v�����O�A�[���̒���
		if (playerstate == PlayerCamera)
		{
			pSpringArm->TargetArmLength -= NewOffset * 10;
			if (pSpringArm->TargetArmLength > MaxPlayerCamera) { pSpringArm->TargetArmLength = MaxPlayerCamera; }
			if (pSpringArm->TargetArmLength < MinPlayerCamera) { pSpringArm->TargetArmLength = MinPlayerCamera; }
		}
		else { CameraObj->ChangeDistance(NewOffset); }
	}
}

// �L�����̓���
void APlayerCharacter::MoveInput(const FInputActionValue& Value)
{
	//FVector NewLocation = GetActorLocation();		// ����
	//FVector2D NewLocation = Value.Get<FVector2D>();	// UE5�e���v���[�g��
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

	// ���_��]�̃L�[��������Ă��Ȃ�
	if (!mp_bPressed)
	{
		if (pSpringArm != NULL)
		{
			// ��q��鏈��
			// �g���Ȃ������ł��B
			if (playerstate == Climb)
			{
				//FVector vec = GetActorLocation();
				//vec.Z += 10.f;//NewLocation.X * 10.f;
				//SetActorLocation(vec);
				////AddMovementInput(GetActorUpVector(), NewLocation.X);
			}
			// �����猩���Ƃ�(X������ړ�)
			// SpringArm�����������ɁA���͂ɂ��ړ��ʂ�PawnMovementComponent�ɓn��
			// �ق�Ƃ͈�s�ɂ܂Ƃ߂���Ǝv���܂��B
			else
			{
				if (camerastate == Front)
				{
					//FVector vec = GetActorLocation();
					//vec += pSpringArm->GetRightVector() * NewLocation.X;
					AddMovementInput(ForwardDirection, NewLocation.X);
					// ���ꂾ�Əo����@�͂��H
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

// �J�����A�N�^�[�̎擾
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
