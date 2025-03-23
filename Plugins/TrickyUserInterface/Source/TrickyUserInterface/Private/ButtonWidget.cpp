// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "ButtonWidget.h"
#include "Components/Button.h"

void UButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Button_Main->OnClicked.AddDynamic(this, &UButtonWidget::HandleButtonClick);
}

void UButtonWidget::HandleButtonClick()
{
	OnButtonClicked.Broadcast(this);
}
