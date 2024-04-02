// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCameraArm->SetupAttachment(GetCapsuleComponent());

	mCameraArm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 50.f), FRotator(-35.f, 0.f, 0.f));
	mCameraArm->TargetArmLength = 500.f;
	//mCameraArm->bUsePawnControlRotation = true;
	//mCameraArm->bInheritYaw = true;
	//mCameraArm->bInheritPitch = true;
	mCameraArmRotation = mCameraArm->GetRelativeRotation();

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mCameraArm);
	//mCamera->bUsePawnControlRotation = false;

	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	//bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Character 클래스의 SkeletalMeshComponent가 가지고 있는 AnimInstance 객체를 얻어온다.
	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::PlayJump()
{
	// CanJump() : 점프 가능 상태인지를 판단한다.
	if (CanJump())
	{
		Jump();
		// PlayerAnimInstance에서 점프 모션으로 변경하도록 하자
		mAnimInst->PlayJump();
	}
}

void APlayerCharacter::CameraArmControl(const FRotator& InputActionValue)
{
	mCameraArm->SetRelativeRotation(InputActionValue);

	mCameraArmRotation = mCameraArm->GetRelativeRotation();
}


//void APlayerCharacter::CameraControl(const FInputActionValue& InputActionValue)
//{
//	const FVector ActionValue = InputActionValue.Get<FVector>();
//	AddControllerYawInput(ActionValue.X);
//	AddControllerPitchInput(ActionValue.Y);
//}


