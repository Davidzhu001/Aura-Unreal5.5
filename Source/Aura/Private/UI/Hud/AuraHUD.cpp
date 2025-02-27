// Wecheng & Alicia Copyright


#include "UI/Hud/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayAuraWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"

UOverlayAuraWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetClass == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayAuraWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetController, TEXT("Overlay widget class uninitialized, please fill out BP_AuroHUD"));
	checkf(OverlayWidgetControllerClass == nullptr, TEXT("Overlay widget class uninitialized"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>( GetWorld(), OverlayWidgetClass );
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayAuraWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);

	
	Widget->AddToViewport();

	
}
