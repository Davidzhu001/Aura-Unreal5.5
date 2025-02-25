// Wecheng & Alicia Copyright


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true; // 与服务器同步的
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext); //检查Pointer 是否存在

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);

	//设置鼠标
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//Input Mode 鼠标
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	// UE_Log

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Log, TEXT("Move function called"));


	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	/**
	UE_LOG(LogTemp, Log, TEXT("Control Rotation: %s"), *Rotation.ToString());
	UE_LOG(LogTemp, Log, TEXT("Forward Direction: %s"), *ForwardDirection.ToString());
	UE_LOG(LogTemp, Log, TEXT("Right Direction: %s"), *RightDirection.ToString());
	UE_LOG(LogTemp, Log, TEXT("Input Axis Vector: %s"), *InputAxisVector.ToString());
	**/
	
}
