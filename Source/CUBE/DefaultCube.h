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
	//このアクターのプロパティのデフォルト値を設定します
	ADefaultCube();

protected:
	//ゲームスタート時、または生成時に呼ばれる処理
	virtual void BeginPlay() override;

public:	
	//毎フレームの更新処理
	virtual void Tick(float DeltaTime) override;

};
