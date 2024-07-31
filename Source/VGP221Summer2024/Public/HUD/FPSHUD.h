// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "GUI/Slate/SSettingWidget.h"
#include "GUI/FPSUserWidget.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class VGP221SUMMER2024_API AFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	// Slate
	TSharedPtr<class SSettingWidget> settingWidget;
	TSharedPtr<class SWidget> menuWidgetContainer;

	void ShowSettingMenu();
	void RemoveSettingMenu();

	// UMG
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UFPSUserWidget> gameMenuWidget;
	UFPSUserWidget* gameWidgetContainer;

	void ShowMenu(TSubclassOf<UFPSUserWidget> newGameMenu);

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
};
