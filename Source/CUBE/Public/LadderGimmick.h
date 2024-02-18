//-------------------------------------------------------
// ファイル名：LadderGimmick.h
// 概要　　　：GimmickBaseを継承した、梯子ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/22 松丸 作成
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "CUBE/GimmickBase.h"
#include "LadderGimmick.generated.h"

class UBoxComponent;

UCLASS()
class CUBE_API ALadderGimmick : public AGimmickBase
{
	GENERATED_BODY()
	
public:
	//コンストラクタ
	ALadderGimmick();

public:
	//毎フレームの更新処理
	virtual void Tick(float DeltaTime)override;

protected:
	void GimmickON() override;

private:       
	//メンバー変数


};
