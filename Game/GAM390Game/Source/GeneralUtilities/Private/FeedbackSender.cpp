// Fill out your copyright notice in the Description page of Project Settings.


#include "FeedbackSender.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "FeedbackSettings.h"
#include "Kismet/GameplayStatics.h"

void UFeedbackSender::SubmitReport(const FString& Category, const FString& Message)
{
	const FString WebhookUrl = TEXT("https://discord.com/api/webhooks/1515354866447286453/N8IOYKPyywki_kFrxB6v_fsrTn3aWEsX5PQRk9Wu6kZVyK0fBDZfLtlSpeF2sis3S1Lj");

	// Pull some context automatically so you're not relying on the player to describe their setup
	const UFeedbackSettings* Settings = GetDefault<UFeedbackSettings>();
    const FString BuildVer = Settings ? Settings->VersionName : TEXT("unknown");
	const FString Platform  = UGameplayStatics::GetPlatformName();

	int32 Colour = 3447003; // blue, default
    if (Category.Equals(TEXT("Bug"), ESearchCase::IgnoreCase))        Colour = 15158332; // red
    else if (Category.Equals(TEXT("Crash"), ESearchCase::IgnoreCase)) Colour = 10038562; // dark red
    else if (Category.Equals(TEXT("Feedback"), ESearchCase::IgnoreCase)) Colour = 3066993; // green

    // Helper to build a field object
    auto MakeField = [](const FString& Name, const FString& Value, bool bInline)
    {
        TSharedPtr<FJsonObject> F = MakeShared<FJsonObject>();
        F->SetStringField(TEXT("name"), Name);
        F->SetStringField(TEXT("value"), Value.IsEmpty() ? TEXT("(none)") : Value.Left(1024));
        F->SetBoolField(TEXT("inline"), bInline);
        return TSharedPtr<FJsonValue>(MakeShared<FJsonValueObject>(F));
    };

    TArray<TSharedPtr<FJsonValue>> Fields;
    Fields.Add(MakeField(TEXT("Platform"), Platform, true));
    Fields.Add(MakeField(TEXT("Build"),    BuildVer, true));

    // The embed itself
    TSharedPtr<FJsonObject> Embed = MakeShared<FJsonObject>();
    Embed->SetStringField(TEXT("title"), FString::Printf(TEXT("%s Report"), *Category));
    Embed->SetNumberField(TEXT("color"), Colour);
    Embed->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());
    Embed->SetArrayField(TEXT("fields"), Fields);
    if (!Message.IsEmpty())
    {
        // Long text goes in description (4096 limit) rather than a field (1024 limit)
        Embed->SetStringField(TEXT("description"), Message.Left(4096));
    }

    TArray<TSharedPtr<FJsonValue>> Embeds;
    Embeds.Add(MakeShared<FJsonValueObject>(Embed));

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetArrayField(TEXT("embeds"), Embeds);

    FString Payload;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Payload);
    FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(WebhookUrl);
    Request->SetVerb(TEXT("POST"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetContentAsString(Payload);

    Request->OnProcessRequestComplete().BindLambda(
        [](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bOk)
    {
        if (bOk && Resp.IsValid())
        {
            UE_LOG(LogTemp, Log, TEXT("Feedback sent: %d"), Resp->GetResponseCode());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Feedback failed to send"));
        }
    });

    Request->ProcessRequest();
}

FText UFeedbackSender::GetGameVersion()
{
    const UFeedbackSettings* Settings = GetDefault<UFeedbackSettings>();
    const FString Version = Settings ? Settings->VersionName : TEXT("unknown");
    return FText::FromString(Version);
}
