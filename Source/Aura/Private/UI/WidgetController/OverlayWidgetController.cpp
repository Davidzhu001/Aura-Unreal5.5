// Copyright Druid Mechanics


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	
	if (const UAuraAttributeSet* AuraAttributesSet = CastChecked<UAuraAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(AuraAttributesSet->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAttributesSet->GetMaxHealth());

		OnManaChanged.Broadcast(AuraAttributesSet->GetMana());
		OnMaxManaChanged.Broadcast(AuraAttributesSet->GetMaxMana());
	}

	
}

void UOverlayWidgetController::BindCallbacksToDependences()
{
	Super::BindCallbacksToDependences();
	const UAuraAttributeSet* AuraAttributesSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributesSet->GetHealthAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data) 
	{
		OnHealthChanged.Broadcast(Data.NewValue);

	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributesSet->GetMaxHealthAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data) 
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);

	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributesSet->GetManaAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data) 
	{
		OnManaChanged.Broadcast(Data.NewValue);

	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributesSet->GetMaxManaAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data) 
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);

	});

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

				// return if not message tag
				if (!Tag.MatchesTag(MessageTag)) return;
			

				const	FUIWidgetRow* Row =	GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				if (!Row)
				{
					const FString Msg = FString::Printf(TEXT("标签数据没有设置 : %s"), *Tag.ToString());
					GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
				} else  {
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
				
			}
		}
	);

}