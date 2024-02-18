//-------------------------------------------------------
// ファイル名：MovefloorGimmick.h
// 概要　　　：GimmickBaseを継承した、移動床ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：12/25 作成
//          ：1/15 更新
//　　　　 　：1/29 更新
//　　　　 　：2/08 更新
//　　　　 　：2/09 更新
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GimmickBase.h"
#include "MovefloorGimmick.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class CUBE_API AMovefloorGimmick : public AGimmickBase
{
	GENERATED_BODY()
	

public:
	//コンストラクタ
	AMovefloorGimmick();

public:
	//毎フレームの更新処理
	virtual void Tick(float DeltaTime)override;

protected:
	//ギミック稼働中のカウント処理
	void GimmickActivation();

	//GimmickBaseから継承した取得用の関数
	void GimmickON() override;

	//移動速度
	float velocity;
	//カウントの指定時間
	float GimmickCntActivation;
	//移動速度の調整用
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		float AdjustVelocity = 1.0f;
	//カウント指定時間の調整用
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		float AdjustCount = 1.0f;

	//X軸を移動するか否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Xaxis = false;
	//Y軸を移動するか否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Yaxis = false;
	//Z軸を移動するか否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Zaxis = false;

	//プレイヤーの接触で動くか否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool AutGimmick = false;

	//プレイヤーが接触してから自動で動くか否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool AutGimmickBoot = false;

private:
	//下降中のフラグ
	bool FloorDown;
	//移動速度の保存用
	float Save_velocity;
	//ギミック稼働中のカウント用
	float GimmickCnt;
	//一度だけ行う処理用
	bool OnProgram;

};
