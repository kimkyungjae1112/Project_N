// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PNCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Player/PNPlayerController.h"
#include "Component/PNBattleSystemComponent.h"
#include "Component/PNParkourComponent.h"

APNCharacter::APNCharacter()
{
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->TargetArmLength = 650.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	SwordMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sword"));
	SwordMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DARK_C_KNIGHT/MESHES/WEAPONS/SWORD/SK_DC_Knight_Sword.SK_DC_Knight_Sword'"));
	if (SwordMeshRef.Object)
	{
		SwordMeshComp->SetSkeletalMesh(SwordMeshRef.Object);
	}

	SheathMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sheath"));
	SheathMeshComp->SetupAttachment(GetMesh(), TEXT("thigh_lSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SheathMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ARPG_Samurai/Demo/Weapon/Mesh/scabbard.scabbard'"));
	if (SheathMeshRef.Object)
	{
		SheathMeshComp->SetSkeletalMesh(SheathMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Project_N/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
	if (MainMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MainMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_CompRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Project_N/Input/IMC/IMC_Player.IMC_Player'"));
	if (IMC_CompRef.Object)
	{
		IMC_Comp = IMC_CompRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Move.IA_Move'"));
	if (MoveActionRef.Object)
	{
		MoveAction = MoveActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Look.IA_Look'"));
	if (LookActionRef.Object)
	{
		LookAction = LookActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> MouseLeftAttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Attack.IA_Attack'"));
	if (MouseLeftAttackActionRef.Object)
	{
		MouseLeftAttackAction = MouseLeftAttackActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> MouseRightHeavyAttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Attack_Heavy.IA_Attack_Heavy'"));
	if (MouseRightHeavyAttackActionRef.Object)
	{
		MouseRightHeavyAttackAction = MouseRightHeavyAttackActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> MouseLeftChargeAttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Attack_Charge.IA_Attack_Charge'"));
	if (MouseLeftChargeAttackActionRef.Object)
	{
		MouseLeftChargeAttackAction = MouseLeftChargeAttackActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> RunAndWalkActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_RunAndWalk.IA_RunAndWalk'"));
	if (RunAndWalkActionRef.Object)
	{
		RunAndWalkAction = RunAndWalkActionRef.Object;
	}


	
	/* 사제 컴포넌트 */
	BSComp = CreateDefaultSubobject<UPNBattleSystemComponent>(TEXT("Battle System Component"));
	ParkourComp = CreateDefaultSubobject<UPNParkourComponent>(TEXT("Parkour Component"));


	CurrentBattleState = EBattleState::BSNonCombat;
}

void APNCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetMyController()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Comp, 0);
	}

}

void APNCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*FVector StartLoc = GetWeapon()->GetSocketLocation(TEXT("SwordBoneStart"));
	FVector EndLoc = GetWeapon()->GetSocketLocation(TEXT("SwordBoneEnd"));
	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 2.f);

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, true, this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_GameTraceChannel2, Params);
	if (bHit)
	{
		UE_LOG(LogTemp, Display, TEXT("닿음?"));
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 12.f, 32, FColor::Red, false, 3.f);
	}*/
}

void APNCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APNCharacter::Move);
	EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APNCharacter::Look);
	EnhancedInput->BindAction(MouseLeftAttackAction, ETriggerEvent::Started, this, &APNCharacter::MouseLeftAttack);
	EnhancedInput->BindAction(MouseLeftAttackAction, ETriggerEvent::Completed, this, &APNCharacter::MouseLeftAttackRelease);
	EnhancedInput->BindAction(MouseLeftChargeAttackAction, ETriggerEvent::Triggered, this, &APNCharacter::MouseLeftChargeAttack);
	EnhancedInput->BindAction(MouseRightHeavyAttackAction, ETriggerEvent::Started, this, &APNCharacter::MouseRightAttack);
	EnhancedInput->BindAction(RunAndWalkAction, ETriggerEvent::Triggered, this, &APNCharacter::Run);
	EnhancedInput->BindAction(RunAndWalkAction, ETriggerEvent::Completed, this, &APNCharacter::Walk);
}

APNPlayerController* APNCharacter::GetMyController()
{
	return CastChecked<APNPlayerController>(GetController());
}

void APNCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InputValue.X);
	AddMovementInput(RightDirection, InputValue.Y);
}

void APNCharacter::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerPitchInput(InputValue.X * 0.5f);
	AddControllerYawInput(-InputValue.Y * 0.5f);
}

void APNCharacter::MouseLeftAttack()
{
	IsCharge = true;
	
	BSComp->Attack();
}

void APNCharacter::MouseLeftAttackRelease()
{
	IsCharge = false;

	PressTime = 0.f;
}

void APNCharacter::MouseLeftChargeAttack()
{
	//PressTime * Damage 인자값 넘기기 고려
	BSComp->ChargeAttack();
}

void APNCharacter::MouseRightAttack()
{
	BSComp->HeavyAttack();
}

void APNCharacter::Run()
{
	ParkourComp->Run();
}

void APNCharacter::Walk()
{
	ParkourComp->Walk();
}


