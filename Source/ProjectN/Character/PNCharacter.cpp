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

APNCharacter::APNCharacter()
{
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
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
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ARPG_Samurai/Demo/Weapon/Mesh/katana.katana'"));
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
	static ConstructorHelpers::FObjectFinder<UInputAction> MouseRightActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Attack.IA_Attack'"));
	if (MouseRightActionRef.Object)
	{
		MouseRightAction = MouseRightActionRef.Object;
	}


	/* 사제 컴포넌트 */
	BSComp = CreateDefaultSubobject<UPNBattleSystemComponent>(TEXT("Battle System"));

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

void APNCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APNCharacter::Move);
	EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APNCharacter::Look);
	EnhancedInput->BindAction(MouseLeftAttackAction, ETriggerEvent::Started, this, &APNCharacter::MouseLeftAttack);
	EnhancedInput->BindAction(MouseLeftAttackAction, ETriggerEvent::Completed, this, &APNCharacter::MouseLeftAttackRelease);
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
	UE_LOG(LogTemp, Display, TEXT("클릭!"));
	IsCharge = true;
	BSComp->Charge();

	if (CurrentBattleState == EBattleState::BSCombat)
	{
		BSComp->Attack();
	}
}

void APNCharacter::MouseLeftAttackRelease()
{
	UE_LOG(LogTemp, Display, TEXT("땜!"));
	IsCharge = false;
}

void APNCharacter::MouseRightAttack()
{
	BSComp->HeavyAttack();
}
