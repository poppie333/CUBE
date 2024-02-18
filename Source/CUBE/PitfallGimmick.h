//-------------------------------------------------------
// ファイル名：PitfallGimmick.h
// 概要　　　：GimmickBaseを継承した、落とし穴ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：12/08
//　　　　　 ：12/15 更新
//   
//-------------------------------------------------------

//インクルードガード
#pragma once

//インクルード
#include "CoreMinimal.h"
#include "GimmickBase.h"
#include "PitfallGimmick.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API APitfallGimmick : public AGimmickBase
{
	GENERATED_BODY()
	
public:
	//コンストラクタ
	APitfallGimmick();

public:
	//毎フレームの更新処理
	virtual void Tick(float DeltaTime)override;

protected:
	void GimmickON() override;

private:

	//メンバー変数


};
