/*
* GameStage.h
* �X�e�[�W�𐧌䂷��N���X
* Create by ������@�吹 on 2023/01/05
* �X�V�����E���e�F�X�e�[�W�̉�]���� by ������@�吹 on 2023/01/05
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStage.generated.h"

UCLASS()
class CUBE_API AGameStage : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameStage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartRot(bool _rotOn);

private:
	void RotateStage();

private:
	bool StartRotation;
	int CntNum;

	enum StageStatus
	{
		Side,
		Front
	};
	StageStatus stagestatus;

};
