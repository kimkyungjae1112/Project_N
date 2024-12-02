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
#include "MotionWarpingComponent.h"

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

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_WalkRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Project_N/Input/IMC/IMC_Walk.IMC_Walk'"));
	if (IMC_WalkRef.Object)
	{
		IMC.Add(EBehaviorState::EWalk, IMC_WalkRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_RunRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Project_N/Input/IMC/IMC_Run.IMC_Run'"));
	if (IMC_RunRef.Object)
	{
		IMC.Add(EBehaviorState::ERun, IMC_RunRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_CrouchRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Project_N/Input/IMC/IMC_Crouch.IMC_Crouch'"));
	if (IMC_CrouchRef.Object)
	{
		IMC.Add(EBehaviorState::ECrouch, IMC_CrouchRef.Object);
	}
	ChangeBehaviorStateMap.Add(EBehaviorState::EWalk, FChangeBehaviorStateWarpper(FChangeBehaviorState::CreateUObject(this, &APNCharacter::SetBehaviorStateWalk)));
	ChangeBehaviorStateMap.Add(EBehaviorState::ERun, FChangeBehaviorStateWarpper(FChangeBehaviorState::CreateUObject(this, &APNCharacter::SetBehaviorStateRun)));
	ChangeBehaviorStateMap.Add(EBehaviorState::ECrouch, FChangeBehaviorStateWarpper(FChangeBehaviorState::CreateUObject(this, &APNCharacter::SetBehaviorStateCrouch)));


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
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Jump.IA_Jump'"));
	if (JumpActionRef.Object)
	{
		JumpAction = JumpActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> CrouchActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Crouch.IA_Crouch'"));
	if (CrouchActionRef.Object)
	{
		CrouchAction = CrouchActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> RollActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Roll.IA_Roll'"));
	if (RollActionRef.Object)
	{
		RollAction = RollActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> DashAttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_DashAttack.IA_DashAttack'"));
	if (DashAttackActionRef.Object)
	{
		DashAttackAction = DashAttackActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> AssassinationActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Project_N/Input/IA/IA_Assassination.IA_Assassination'"));
	if (AssassinationActionRef.Object)
	{
		AssassinationAction = AssassinationActionRef.Object;
	}
	
	/* 사제 컴포넌트 */
	BattleSystemComp = CreateDefaultSubobject<UPNBattleSystemComponent>(TEXT("Battle System Component"));
	ParkourComp = CreateDefaultSubobject<UPNParkourComponent>(TEXT("Parkour Component"));
	MotionWarpComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarp Component"));

	/* 델리게이트 */
	BattleSystemComp->InitBehaviorState.AddUObject(this, &APNCharacter::Walk);

	CurrentBehaviorState = EBehaviorState::EWalk;
}

void APNCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetBehaviorState(CurrentBehaviorState);
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
	EnhancedInput->BindAction(RunAndWalkAction, ETriggerEvent::Started, this, &APNCharacter::Run);
	EnhancedInput->BindAction(RunAndWalkAction, ETriggerEvent::Completed, this, &APNCharacter::Walk);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Started, this, &APNCharacter::OnCrouch);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APNCharacter::UnCrouch);
	EnhancedInput->BindAction(RollAction, ETriggerEvent::Started, this, &APNCharacter::Roll);
	EnhancedInput->BindAction(DashAttackAction, ETriggerEvent::Started, this, &APNCharacter::DashAttack);
	EnhancedInput->BindAction(AssassinationAction, ETriggerEvent::Started, this, &APNCharacter::Assassination);
}

APNPlayerController* APNCharacter::GetMyController()
{
	return CastChecked<APNPlayerController>(GetController());
}

void APNCharacter::SetBehaviorState(const EBehaviorState& BehaviorState)
{
	ChangeBehaviorStateMap[BehaviorState].ChangeBehaviorState.ExecuteIfBound();
}

void APNCharacter::SetBehaviorStateWalk()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetMyController()->GetLocalPlayer()))
	{
		UE_LOG(LogTemp, Display, TEXT("Walk"));
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(IMC[CurrentBehaviorState], 0);
		UE_LOG(LogTemp, Display, TEXT("IMC : %s"), *IMC[CurrentBehaviorState]->GetName());
	}
}

void APNCharacter::SetBehaviorStateRun()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetMyController()->GetLocalPlayer()))
	{
		UE_LOG(LogTemp, Display, TEXT("Run"));
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(IMC[CurrentBehaviorState], 0);
		UE_LOG(LogTemp, Display, TEXT("IMC : %s"), *IMC[CurrentBehaviorState]->GetName());
	}
}

void APNCharacter::SetBehaviorStateCrouch()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetMyController()->GetLocalPlayer()))
	{
		UE_LOG(LogTemp, Display, TEXT("Crouch"));
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(IMC[CurrentBehaviorState], 0);
		UE_LOG(LogTemp, Display, TEXT("IMC : %s"), *IMC[CurrentBehaviorState]->GetName());
	}
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
	
	BattleSystemComp->Attack();
}

void APNCharacter::MouseLeftAttackRelease()
{
	IsCharge = false;
}

void APNCharacter::MouseLeftChargeAttack()
{
	BattleSystemComp->ChargeAttack();
}

void APNCharacter::MouseRightAttack()
{
	BattleSystemComp->HeavyAttack();
}

void APNCharacter::Run()
{
	CurrentBehaviorState = EBehaviorState::ERun;
	SetBehaviorState(CurrentBehaviorState);
	ParkourComp->Run();
}

void APNCharacter::Walk()
{
	CurrentBehaviorState = EBehaviorState::EWalk;
	SetBehaviorState(CurrentBehaviorState);
	ParkourComp->Walk();
}

void APNCharacter::OnCrouch()
{
	CurrentBehaviorState = EBehaviorState::ECrouch;
	SetBehaviorState(CurrentBehaviorState);
	ParkourComp->Crouch();
}

void APNCharacter::UnCrouch()
{
	CurrentBehaviorState = EBehaviorState::EWalk;
	SetBehaviorState(CurrentBehaviorState);
	ParkourComp->UnCrouch();
}

void APNCharacter::Roll()
{
	ParkourComp->BeginRoll();
}

void APNCharacter::DashAttack()
{
	BattleSystemComp->BeginDashAttack();
}

void APNCharacter::Assassination()
{
	BattleSystemComp->BeginAssassinationAttack();
}


