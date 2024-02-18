//-------------------------------------------------------
// ファイル名：CeilingfallGimmick.h
// 概要　　　：GimmickBaseを継承した、天井落下ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：12/15
//           ：12/18 更新
//           ：12/20 更新
//　　　　　  ：12/22 更新
//　　　　 　 ：1/12 更新
//　　　　 　 ：1/22 更新
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GimmickBase.h"
#include "CeilingfallGimmick.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API ACeilingfallGimmick : public AGimmickBase
{
	GENERATED_BODY()

public:
	//コンストラクタ
	ACeilingfallGimmick();

public:
	//毎フレームの更新処理
	virtual void Tick(float DeltaTime)override;

protected:
	//ギミック稼働中のカウント処理
	void GimmickActivation();

	//GimmickBaseから継承した取得用の関数
	void GimmickON() override;

private:

	//メンバー変数

public:
	//落下開始のフラグ
	bool FallON;
	//落下速度
	float velocity;
	//カウントの指定時間
	float GimmickCntActivation;
	//落下速度の調整用
	UPROPERTY(EditAnywhere, Category = "Gimmick")
	float AdjustVelocity = 1.0f;
	//カウント指定時間の調整用
	UPROPERTY(EditAnywhere, Category = "Gimmick")
	float AdjustCount = 1.0f;

private:
	//開始位置の把握用
	FVector startLocation;
	//ギミック稼働中のカウント用
	float GimmickCnt;

	//一度だけ行う処理用
	bool OnProgram;
};
