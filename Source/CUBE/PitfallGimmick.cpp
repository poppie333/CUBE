//-------------------------------------------------------
// ファイル名：PitfallGimmick.h
// 概要　　　：GimmickBaseを継承した、落とし穴ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：12/08  
//          ：12/15 完成
//-------------------------------------------------------

//インクルード
#include "PitfallGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

//コンストラクタ
APitfallGimmick::APitfallGimmick()
{
	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("PitfallGimmick"));

	// StaticMeshをStaticMeshComponentに設定する
	GimmickMesh->SetStaticMesh(Mesh);

	// Boxの位置を調整する
	Box->SetRelativeLocation(FVector(40.0f, -40.0f, 70.0f), false);
}

//毎フレームの更新処理
void APitfallGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//プレイヤーに触れたら自身を消す処理
void APitfallGimmick::GimmickON()
{
	//このギミックは破棄される
	UNDestroy = true;
}