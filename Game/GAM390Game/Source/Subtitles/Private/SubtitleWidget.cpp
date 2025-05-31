// Fill out your copyright notice in the Description page of Project Settings.


#include "SubtitleWidget.h"

#include "GI_Accessibility.h"
#include "Components/Border.h"
#include "Components/RichTextBlock.h"

void USubtitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(UGameInstance* GameInstance = GetGameInstance())
	{
		if(UGI_SanctumSettings* SanctumSettings = Cast<UGI_SanctumSettings>(GameInstance))
		{
			int32 SubtitleSize = SanctumSettings->m_SubtitleSize;

			switch(SubtitleSize)
			{
			case 0:
				SubtitleText->SetTextStyleSet(DT_SubtitleSize0);
				break;
			case 1:
				SubtitleText->SetTextStyleSet(DT_SubtitleSize1);
				break;
			case 2:
				SubtitleText->SetTextStyleSet(DT_SubtitleSize2);
				break;
			default:
				break;
			}
		}
	}

	FName RowName = SubtitleTableRowName;
	const FSubtitle* SubtitleRow = SubtitleTable->FindRow<FSubtitle>(RowName, TEXT(""));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Subtitle Row: %s"), *RowName.ToString()));
	if(!SubtitleRow->Text.IsEmpty())
	{
		SubtitleIndex = 1;
		IterateRow(*SubtitleRow);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DISPLAYING TEXT69"));
	}
}

void USubtitleWidget::IterateRow(const FSubtitle& row)
{
	UGameInstance* GameInstance = GetGameInstance();
	UGI_SanctumSettings* SanctumSettings = Cast<UGI_SanctumSettings>(GameInstance);

	if (!SanctumSettings->bSubtitlesEnabled)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else 
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	if(!SubtitleTable|| SubtitleTable->GetRowMap().Num() == 0)
	{
		return;
	}

	const TArray<FName> RowNames = SubtitleTable->GetRowNames();

	if(SubtitleIndex< RowNames.Num())
	{
		FName CurrentRowName = RowNames[SubtitleIndex];
		const FSubtitle* CurrentRow = SubtitleTable->FindRow<FSubtitle>(CurrentRowName, TEXT(""));

		if(CurrentRow)
		{
			ShowSubtitle(*CurrentRow);
			
			GetWorld()->GetTimerManager().SetTimer(SubtitleDelayHandle, FTimerDelegate::CreateLambda([this, CurrentRow]()
			{
				OnSubtitleDelayComplete(*CurrentRow);
			}), CurrentRow->Time, false);
        }
	}
	else {
		RemoveFromParent();
		
	}
}

void USubtitleWidget::OnSubtitleDelayComplete(const FSubtitle& Row)
{
	SubtitleIndex++;
	IterateRow(Row);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DISPLAYING SUBTITLES"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Current Row Time: %.2f"), Row.Time));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Subtitle Row: %i"), SubtitleIndex));
}

void USubtitleWidget::ShowSubtitle(const FSubtitle& Subtitle)
{
	if(SubtitleText)
	{
		FText FormattedText = FText::FromString(Subtitle.Text.ToString());
		if (SubtitleText->IsValidLowLevel())
		{
			SubtitleText->SetText(FormattedText);
		}

	}

	if(Border)
	{
		Border->InvalidateLayoutAndVolatility();
	}
}

void USubtitleWidget::SetSubtitleData(UDataTable* Table)
{
	SubtitleTable = Table;
}

void USubtitleWidget::SetRowName(FName Name)
{
	SubtitleTableRowName = Name;
}





