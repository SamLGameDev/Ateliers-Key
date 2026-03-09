// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "WidgetRichTextDecorator.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class DISPLAYCONTROLSSYSTEM_API UWidgetRichTextDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()

public:
	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	TMap<FName, TSubclassOf<UUserWidget>> WidgetMap;

	TSharedPtr<SWidget> CreateWidget(const FTextRunInfo& RunInfo) const;
};
