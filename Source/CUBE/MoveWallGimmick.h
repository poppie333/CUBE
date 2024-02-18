//-------------------------------------------------------
// ファイル名：MoveWallGimmick.cpp
// 概要　　　：GimmickBaseを継承した、移動壁ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/08　作成
//　　　　 　：2/13 更新
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GimmickBase.h"
#include "MoveWallGimmick.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API AMoveWallGimmick : public AGimmickBase
{
	GENERATED_BODY()
	
public:
	//コンストラクタ
	AMoveWallGimmick();

public:
	//毎フレームの更新処理
	virtual void Tick(float DeltaTime)override;

protected:
	//ギミック稼働中のカウント処理
	void GimmickActivation();

	//GimmickBaseから継承した取得用の関数
	void GimmickON() override;

public:
	//移動開始のフラグ
	bool MoveON;
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

	//移動か否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Move = false;
	//拡縮か否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Scale = false;

	//X軸を移動するか否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Xaxis = false;
	//Y軸を移動するか否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Yaxis = false;
	//Z軸を移動するか否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool Zaxis = false;

	//X軸のプラスマイナス
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool XPlusMinus = false;
	//Y軸のプラスマイナス
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool YPlusMinus = false;
	//Z軸のプラスマイナス
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool ZPlusMinus = false;

	//稼働後に破壊するか否か
	UPROPERTY(EditAnywhere, Category = "Gimmick")
		bool DestroyMoveWall = false;

private:
	//開始位置の把握用
	FVector startLocation;
	//ギミック稼働中のカウント用
	float GimmickCnt;
	//一度だけ行う処理用
	bool OnProgram;

};
