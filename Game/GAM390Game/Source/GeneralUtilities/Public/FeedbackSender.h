#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FeedbackSender.generated.h"

class UMultiLineEditableText;

UCLASS()
class GENERALUTILITIES_API UFeedbackSender : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Feedback", meta=(WorldContext="WorldContextObject"))
	static void SubmitReport(
		UObject* WorldContextObject,
		const FString& Category,
		const FString& Message,
		UMultiLineEditableText* StatusField);

	UFUNCTION(BlueprintPure, Category="Feedback")
	static FText GetGameVersion();
};