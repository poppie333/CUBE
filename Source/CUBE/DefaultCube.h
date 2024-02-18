// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultCube.generated.h"

UCLASS()
class CUBE_API ADefaultCube : public AActor
{
	GENERATED_BODY()
	
public:	
	//���̃A�N�^�[�̃v���p�e�B�̃f�t�H���g�l��ݒ肵�܂�
	ADefaultCube();

protected:
	//�Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:	
	//���t���[���̍X�V����
	virtual void Tick(float DeltaTime) override;

};
