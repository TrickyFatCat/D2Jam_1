// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "BaseUserWidget.h"

#include "Animation/WidgetAnimation.h"

void UBaseUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	switch (GetVisibility())
	{
	case ESlateVisibility::Visible:
	case ESlateVisibility::SelfHitTestInvisible:
	case ESlateVisibility::HitTestInvisible:
		DefaultVisibility = GetVisibility();
		break;
	}
}

void UBaseUserWidget::Show()
{
	const float StartTime = CalculateStartTime(HideAnimation, ShowAnimation);
	PlayAnimation(ShowAnimation, StartTime);
}

void UBaseUserWidget::Hide()
{
	const float StartTime = CalculateStartTime(ShowAnimation, HideAnimation);
	PlayAnimation(HideAnimation, StartTime);
}

void UBaseUserWidget::OnAnimationStarted_Implementation(const UWidgetAnimation* Animation)
{
	SetVisibility(DefaultVisibility);
}

void UBaseUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation == ShowAnimation)
	{
		SetVisibility(DefaultVisibility); // In case, of rapid change of the state.
		OnShowed.Broadcast();
	}
	else if (Animation == HideAnimation)
	{
		SetVisibility(ESlateVisibility::Hidden);
		OnHidden.Broadcast();
	}
}

float UBaseUserWidget::CalculateStartTime(const UWidgetAnimation* CurrentAnimation,
                                          const UWidgetAnimation* NewAnimation) const
{
	if (!CurrentAnimation || !NewAnimation)
	{
		return -1.f;
	}
	
	const float AnimationEndTime = CurrentAnimation->GetEndTime();
	const float TargetTime = ((AnimationEndTime - GetAnimationCurrentTime(CurrentAnimation)) / AnimationEndTime) * NewAnimation->GetEndTime();
	return TargetTime * static_cast<float>(IsAnimationPlaying(CurrentAnimation));
}
