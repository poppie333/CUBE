/*
* PlayerCharacter.h
* �v���C���[�L�����N�^�[�𐧌䂷��N���X
* Create by ������@�吹 on 2023/12/07
* �X�V�����E���e�FCamera�̓��͏����̍쐬				by ������@�吹  on 2023/12/14
*						�FPlayerMoveMent�̍쐬			by ���c�@�Y�u	 on 2023/12/15
*						�F�ړ���������					by ���c�@�Y�u	 on 2023/12/22
*						�F�ҋ@�������s					by ���c			 on 2024/01/29
*						�F�J������]�����̎d�l�ύX		by ������@		 on 2024/02/09
*						�FMoveInput�d�l�ύX				by ������@		 on 2024/02/09
*						�F�J�����̎d�l�ύX				by ������		 on 2024/02/14
*/

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Manager/CameraManager.h" // �J�����}�l�[�W���[
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CUBE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		///** MappingContext */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	///** Camera Input Action */			// ���̃N���X��LoadObject���AEnhancedInput�Ŋ֐��ƃo�C���h����
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
	// �J�����̏�����
	void InitializeCamera();

	// �J�������X�V
	void UpdateCamera();

	// �L�����N�^�[���X�V
	void UpdateCharacter();

	// �J�����C���v�b�g
	void RightCameraInput();
	void LeftCameraInput();

	// �R���g���[���[�̓��͂ɂ��ړ�����
	void MoveInput(const FInputActionValue& Value);

	// �J���������̓��͏���
	void CameraDistanceInput(const FInputActionValue& Value);

	// �J�����A�N�^�[�̎擾
	void GetCamera();

private:
	// �����o�ϐ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraManager* mp_CameraMng = nullptr;   // �J�����}�l�[�W���[

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
	float m_moveSpeed;					// �ړ���
	float JumpPower;
	bool CanJump;
	// �J�����̉�]�X�e�[�^�X
	bool MoveCamera_R;
	bool MoveCamera_L;
	// �J�������ǂ��ɂ��邩
	enum CameraState {
		Front,
		Right,
		Back,
		Left
	};
	CameraState camerastate;

	AActor* Camera;

	// �v���C���[�̃X�e�[�^�X�Ǘ�
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
