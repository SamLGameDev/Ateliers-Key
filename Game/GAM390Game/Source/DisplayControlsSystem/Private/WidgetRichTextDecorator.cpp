// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetRichTextDecorator.h"

#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "Framework/Text/RichTextLayoutMarshaller.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SNullWidget.h"
#include "Engine/Engine.h"

class FWidgetRichTextDecorator : public FRichTextDecorator
{
public:
    FWidgetRichTextDecorator(URichTextBlock* InOwner, const UWidgetRichTextDecorator* InDecorator)
        : FRichTextDecorator(InOwner)
        , Decorator(InDecorator)
    {
    }

protected:
    const UWidgetRichTextDecorator* Decorator;

    virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override
    {
        return RunParseResult.Name == TEXT("widget");
    }

    virtual TSharedPtr<SWidget> CreateDecoratorWidget(
        const FTextRunInfo& RunInfo,
        const FTextBlockStyle& TextStyle) const override
    {
        return Decorator->CreateWidget(RunInfo);
    }
};

TSharedPtr<ITextDecorator> UWidgetRichTextDecorator::CreateDecorator(URichTextBlock* InOwner)
{
    return MakeShareable(new FWidgetRichTextDecorator(InOwner, this));
}

TSharedPtr<SWidget> UWidgetRichTextDecorator::CreateWidget(const FTextRunInfo& RunInfo) const
{
    const FString* WidgetName = RunInfo.MetaData.Find(TEXT("name"));
    if (!WidgetName)
    {
        return SNullWidget::NullWidget;
    }

    const TSubclassOf<UUserWidget>* WidgetClass = WidgetMap.Find(FName(**WidgetName));
    if (!WidgetClass || !(*WidgetClass))
    {
        return SNullWidget::NullWidget;
    }

    URichTextBlock* Owner = Cast<URichTextBlock>(GetOuter());
    if (!Owner)
    {
        return SNullWidget::NullWidget;
    }

    UWorld* World = Owner->GetWorld();
    if (!World)
    {
        return SNullWidget::NullWidget;
    }

    UUserWidget* Widget = ::CreateWidget<UUserWidget>(World, *WidgetClass);
    if (!Widget)
    {
        return SNullWidget::NullWidget;
    }

    // Get alignment metadata
    const FString* Alignment = RunInfo.MetaData.Find(TEXT("align"));

    EHorizontalAlignment HAlign = HAlign_Left;

    if (Alignment)
    {
        if (Alignment->Equals(TEXT("center"), ESearchCase::IgnoreCase))
        {
            HAlign = HAlign_Center;
        }
        else if (Alignment->Equals(TEXT("right"), ESearchCase::IgnoreCase))
        {
            HAlign = HAlign_Right;
        }
    }

    return SNew(SHorizontalBox)

        + SHorizontalBox::Slot()
        .HAlign(HAlign)
        .AutoWidth()
        [
            Widget->TakeWidget()
        ];
}