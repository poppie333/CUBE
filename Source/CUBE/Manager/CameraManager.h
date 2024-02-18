/*
* CameraManager.h
*
* Create by 日向野　大聖 on 2023/12/07
*/

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CameraManager.generated.h"


// クラスの前方宣言
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class UCameraManager : public UObject
{
	GENERATED_BODY()

public:
	// constructor
	UCameraManager();
	// destructor
	~UCameraManager();

	// カメラオブジェクトの取得
	UCameraComponent* GetCamera()const { return m_pCamera; }

	// スプリングアームの取得
	USpringArmComponent* GetSpringArm() const { return m_pSpringArm; }

	// カメラオブジェクトの設定
	void SetCamera(UCameraComponent* _pCamera, USpringArmComponent* _pSpringArm);

	// スプリングアームの長さを設定
	void SetTargetArmLength(float _length);

	// スプリングアームの長さを取得
	float GetTargetArmLength();

	// カメラの角度を設定
	void SetCameraRot(float _pitch, float _yaw, float _roll);

	// カメラのコリジョンテスト
	void SetDoCollisionTest(bool _bEnable);

	// カメラ追従ラグ
	void SetEnableCameraLag(bool _bEnable);

protected:

	// メンバ変数
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* m_pCamera;		 // カメラ

private:
	USpringArmComponent* m_pSpringArm;   // スプリングアーム
};
