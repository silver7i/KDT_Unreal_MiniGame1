// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = GetCapsuleComponent();

	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCameraArm->SetupAttachment(mCapsule);

	mCameraArm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 80.f), FRotator(-25.f, 0.f, 0.f));
	mCameraArm->TargetArmLength = 500.f;
	mCameraArm->bUsePawnControlRotation = false;
	mCameraArm->bInheritYaw = false;
	mCameraArm->bInheritPitch = false;
	mCameraArm->bInheritRoll = false;

	mCameraArmRotation = mCameraArm->GetRelativeRotation();

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mCameraArm);

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Character 클래스의 SkeletalMeshComponent가 가지고 있는 AnimInstance 객체를 얻어온다.
	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	StartPoint = K2_GetActorLocation();
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

void APlayerCharacter::SetPlayerStartLocation()
{
	SetActorLocation(StartPoint);
}

