# Project N 🎮  
언리얼 엔진 5 + C++ 기반 개인 프로젝트 **소울라이크**  
<br><br>

## 프로젝트 개요

| 항목 | 내용 |
|------|------|
| **장르** | 소울라이크 |
| **플랫폼** | Windows (PC) |
| **엔진 / 언어** | Unreal Engine&nbsp;5 · C++ |
| **개발 기간** | 2024-11-17 ~ 2024-12-23 |
| **팀 규모** | 개인 |
| **시연 영상** | [시연 영상](https://drive.google.com/file/d/16cSb3JgFYUaeaxbVX6jHcfQzHpt080LG/view?usp=sharing) |

<br><br>

## 주요 특징

| 특징 | 설명 |
|------|------|
| **콤보 전투** | **약 5-콤보 / 강 3-콤보 / 차지·대시** 공격을 유기적으로 연결 |
| **정밀 히트 판정** | `AnimNotifyState` + 라인트레이스로 **칼날 궤적 기반** 타격·피격 처리 |
| **스태미나** | 공격·회피 시 스태미나 소비, 고갈 시 행동 제한 |
| **스마트 AI** | **Behavior Tree + AI Perception** 기반 탐지·추적·패턴 공격 |
| **보스 게이트** | 특정 조건 충족 시 **보스 존** 개방 |

<br><br>

## 시스템 / 기술 스택


### C++ 아키텍처
![image01](https://github.com/user-attachments/assets/4ddaa156-c8ab-42d7-a040-285e4da44e65)

<br>

### Unreal Engine 5
- **언리얼 C++**
- **Enhanced Input** – 상태별 **Input Mapping Context** 동적 교체  

<br>

### AI
- `AIController` + Behavior Tree **서비스 / 태스크**  
- **거리 기반 확률**로 보스 패턴 6종 선택  

<br>

### 이벤트 브로드캐스트
- 델리게이트 래퍼 **`FChangeBehaviorStateWrapper`** 로 상태 변화 알림  

<br><br>

## 핵심 시스템 구현

### 전투 FSM

| State | 기능 |
|-------|------|
| **ASIdle**   | 대기 |
| **ASLight**  | 5-Hit 약공격 |
| **ASHeavy**  | 3-Hit 강공격 (ASLight 1-Hit 후 진입) |
| **ASCharge** | `InputAction.Trigger` **1 s Hold** → 차지 |
| **ASDash**   | 대시 중 좌클릭 |

<br>

- 공격&emsp;[관련 소스코드](https://github.com/kimkyungjae1112/Project_N/blob/main/Source/ProjectN/Component/PNBattleSystemComponent.cpp)
    - 플레이어 캐릭터의 공격은 UPNBattleSystemComponent 에서 구현 및 관리합니다.
    - 공격의 기본 설정
        1. 마우스 좌클릭으로 플레이어가 바인딩된 공격 함수를 실행합니다.
        
        ```cpp
        void APNCharacter::MouseLeftAttack()
        {
        	IsCharge = true;
        	
        	BattleSystemComp->Attack();
        }
        ```
        
        2. 공격 함수 실행
            
            현재 어떤 공격을 실행 중인지 enum class로 구분 중입니다.
            
            처음 좌클릭을 이용해 공격을 실행하면 Charge() 함수를 호출하게 됩니다.
            
            Charge() 함수는 Charge 모션을 취하는 애니메이션 몽타주를 실행하는 함수입니다.
            
        
        ```cpp
        UENUM()
        enum class EAttackState : uint8
        {
        	ASIdle,
        	ASLight,
        	ASHeavy,
        	ASCharge,
        	ASDash
        };
        
        void UPNBattleSystemComponent::Attack()
        {
        	switch (CurrentAttackState)
        	{
        	case EAttackState::ASIdle:
        		Charge();
        		break;
        	case EAttackState::ASLight:
        		if (!LightAttackTimer.IsValid())
        			HasNextLightAttack = false;
        		else
        			HasNextLightAttack = true;
        		break;
        	}
        }
        
        void UPNBattleSystemComponent::Charge()
        {
        	if (!Anim->Montage_IsPlaying(ChargeMontage))
        	{
        		Anim->Montage_Play(ChargeMontage);
        	}
        
        	FOnMontageEnded MontageEnd;
        	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndCharge);
        	Anim->Montage_SetEndDelegate(MontageEnd, ChargeMontage);
        }
        ```
        
        3. IsCharge의 값에 따라 공격 방식이 분기됩니다.
            
            이때 IsCharge라는 bool 형식의 값이 true로 바뀌고 일정 프레임 이상 true 상태라면 Charge 행동을 취하고, false 상태라면 약공격으로 전환됩니다.
            
            IsCharge는 플레이어가 좌클릭을 누르고 있으면 true, 좌클릭을 때면 false로 값이 바뀝니다.
            
        
        ```cpp
        void UAttackStartNotify::Notify(USkeletalMeshComponent* MeshComp, 
        UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
        {
        	Super::Notify(MeshComp, Animation, EventReference);
        	
        	APNCharacter* Player = Cast<APNCharacter>(MeshComp->GetOwner());
        	if (Player)
        	{
        		if (Player->GetIsCharge())
        		{
        			UPNBattleSystemComponent* BSComp = Cast<UPNBattleSystemComponent>
        								(Player->GetComponentByClass<UPNBattleSystemComponent>());
        			
        			BSComp->SuccessCharge();
        		}
        		else
        		{
        			UPNBattleSystemComponent* BSComp = Cast<UPNBattleSystemComponent>
        								(Player->GetComponentByClass<UPNBattleSystemComponent>());
        			
        			BSComp->FailCharge();
        		}
        
        		Player->SetAfterAttack(true);
        	}
        }
        ```
        ![image](https://github.com/user-attachments/assets/2c625d47-3057-46cb-a583-e039821b2b3a)



    <br>
    
    - 약공격 : 최대 콤보 5회
    - **코드 흐름**
        1. 약공격
            
            IsCharge가 false가 되면 FailCharge() 함수를 호출합니다.
            
            Charge 몽타주를 멈추고 LightAttack() 함수를 호출하여 약공격을 실행합니다.
            
            현재 공격의 상태는 Light로 바뀌며, 플레이어가 다음번 좌클릭을 클릭 시 현재 약공격 콤보 공격이 가능한지 검사 후 약공격을 계속할지, 중단할지 결정합니다.
            
        
        ```cpp
        void UPNBattleSystemComponent::FailCharge()
        {
        	CurrentAttackState = EAttackState::ASLight;
        
        	Anim->Montage_Stop(0.1f, ChargeMontage);
        	LightAttack();
        }
        
        void UPNBattleSystemComponent::LightAttack()
        {
        	CurrentLightAttackCombo = 1;
        	StatComp->ApplyEnergy(StatComp->UseLightAttackEnergy());
        	Anim->Montage_Play(AttackMontage);
        
        	FOnMontageEnded MontageEnd;
        	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndLightAttack);
        	Anim->Montage_SetEndDelegate(MontageEnd, AttackMontage);
        
        	LightAttackTimer.Invalidate();
        	SetTimerLightAttack();
        }
        ```
        
      <br>
      
    - 강공격 : 최대 콤보 3회
    - **코드 흐름**
        1. 마우스 우클릭으로 플레이어가 바인딩된 공격 함수를 실행합니다.
        
        ```cpp
        void APNCharacter::MouseRightAttack()
        {
        	BattleSystemComp->HeavyAttack();
        }
        ```
        
        1. 약공격의 콤보가 1일 때 강공격을 실행할 수 있습니다.
            
            처음 강공격을 실행하기 위해서 약공격의 콤보가 1일 때 진행될 수 있도록, 그 후 공격 상태를 Heavy(강공격)으로 바꿔 진행합니다.
            
            최대 3콤보까지 강공격을 진행할 수 있습니다.
            
        
        ```cpp
        void UPNBattleSystemComponent::HeavyAttack()
        {
        	if (CurrentLightAttackCombo == 1 || CurrentAttackState == EAttackState::ASHeavy)
        	{
        
        		CurrentAttackState = EAttackState::ASHeavy;
        
        		if (CurrentHeavyAttackCombo == 0)
        		{
        			BeginHeavyAttack();
        			return;
        		}
        
        		if (!HeavyAttackTimer.IsValid())
        			HasNextHeavyAttack = false;
        		else
        			HasNextHeavyAttack = true;
        	}
        }
        ```
        
      <br>

    - 차지 공격
        - Input Action의 Triggers 옵션을 이용해 구현
        - Hold 옵션으로 1초 이상 누르고 있을 시 공격 실행

      <br>
      
    - 대쉬 공격
        - 현재 플레이어 캐릭터 상태가 Dash 상태일 때 좌클릭 시 공격 실행

      <br><br>
      
* **히트 판정**  
  `USwordAttackHitNotifyState` 가 Montage Tick 마다  
  **소켓 ↔ 소켓 라인트레이스** 수행 → `TSet<AActor*>` 로 **중복 피격 제거**




