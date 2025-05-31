// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FSubtitle.h"
#include "SubtitleWidget.generated.h"
/**
 * 
 */
UCLASS()
class SUBTITLES_API USubtitleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetSubtitleData(UDataTable* Table);

	UFUNCTION()
	void SetRowName(FName Name);

	UFUNCTION()
	void OnSubtitleDelayComplete(const FSubtitle& row);
	
	UFUNCTION()
	void IterateRow(const FSubtitle& row);

	void ResetIndex()
	{
		SubtitleIndex = 0;
	}
	FTimerHandle SubtitleDelayHandle;


protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ShowSubtitle(const FSubtitle& Subtitle);

	UPROPERTY()
	int SubtitleIndex = 1;
	
	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* SubtitleText;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
	UDataTable* SubtitleTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
	FName SubtitleTableRowName = "0";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
	class UDataTable* DT_SubtitleSize0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
	class UDataTable* DT_SubtitleSize1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
	class UDataTable* DT_SubtitleSize2;
};
