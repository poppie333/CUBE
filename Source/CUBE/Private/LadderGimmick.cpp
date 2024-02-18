//-------------------------------------------------------
// ファイル名：LadderGimmick.cpp
// 概要　　　：GimmickBaseを継承した、梯子ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/22 松丸 作成
//-------------------------------------------------------

#include "LadderGimmick.h"
#include "CUBE/PlayerCharacter.h"
#include "Components/BoxComponent.h"

ALadderGimmick::ALadderGimmick()
{
	//Tickを起動
	PrimaryActorTick.bCanEverTick = true;

	// Boxのサイズを設定する
	Box->SetBoxExtent(FVector(50.0f, 50.0f, 10.0f));
}

//毎フレームの更新処理
void ALadderGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//プレイヤーに触れたら処理を開始するフラグを起動
void ALadderGimmick::GimmickON()
{
	//梯子
	LadderCol = true;
}
