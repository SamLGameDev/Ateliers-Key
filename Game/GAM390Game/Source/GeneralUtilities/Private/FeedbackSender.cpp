#include "FeedbackSender.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "FeedbackSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Components/MultiLineEditableText.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "TimerManager.h"

static bool bCooldownActive = false;
static int32 CooldownRemaining = 0;
static FTimerHandle CooldownTimerHandle;

void UFeedbackSender::SubmitReport(
    UObject* WorldContextObject,
    const FString& Category,
    const FString& Message,
    UMultiLineEditableText* StatusField)
{
    if (!WorldContextObject)
        return;

    UWorld* World = WorldContextObject->GetWorld();
    if (!World)
        return;

    if (bCooldownActive)
    {
        if (StatusField)
        {
            StatusField->SetText(FText::FromString(
                FString::Printf(TEXT("Please wait %d seconds before submitting again."),
                    CooldownRemaining)));
        }
        return;
    }

    FString WebhookUrl;

    if (!GConfig->GetString(
            TEXT("Feedback"),
            TEXT("WebhookURL"),
            WebhookUrl,
            GGameIni))
    {
        UE_LOG(LogTemp, Warning, TEXT("Feedback webhook missing in DefaultGame.ini"));
        return;
    }

    const UFeedbackSettings* Settings = GetDefault<UFeedbackSettings>();
    const FString BuildVer = Settings ? Settings->VersionName : TEXT("unknown");
    const FString Platform = UGameplayStatics::GetPlatformName();

    int32 Colour = 3447003;
    if (Category.Equals(TEXT("Bug"), ESearchCase::IgnoreCase)) Colour = 15158332;
    else if (Category.Equals(TEXT("Crash"), ESearchCase::IgnoreCase)) Colour = 10038562;
    else if (Category.Equals(TEXT("Feedback"), ESearchCase::IgnoreCase)) Colour = 16777215;

    auto MakeField = [](const FString& Name, const FString& Value, bool bInline)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("name"), Name);
        Obj->SetStringField(TEXT("value"), Value.IsEmpty() ? TEXT("(none)") : Value.Left(1024));
        Obj->SetBoolField(TEXT("inline"), bInline);
        return MakeShared<FJsonValueObject>(Obj);
    };

    TArray<TSharedPtr<FJsonValue>> Fields;
    Fields.Add(MakeField(TEXT("Platform"), Platform, true));
    Fields.Add(MakeField(TEXT("Build"), BuildVer, true));

    TSharedPtr<FJsonObject> Embed = MakeShared<FJsonObject>();
    Embed->SetStringField(TEXT("title"), FString::Printf(TEXT("%s Report"), *Category));
    Embed->SetNumberField(TEXT("color"), Colour);
    Embed->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());
    Embed->SetArrayField(TEXT("fields"), Fields);

    if (!Message.IsEmpty())
    {
        Embed->SetStringField(TEXT("description"), Message.Left(4096));
    }

    TArray<TSharedPtr<FJsonValue>> Embeds;
    Embeds.Add(MakeShared<FJsonValueObject>(Embed));

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetArrayField(TEXT("embeds"), Embeds);

    FString Payload;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Payload);
    FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
        FHttpModule::Get().CreateRequest();

    Request->SetURL(WebhookUrl);
    Request->SetVerb(TEXT("POST"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetContentAsString(Payload);

    TWeakObjectPtr<UMultiLineEditableText> WeakField(StatusField);

    Request->OnProcessRequestComplete().BindLambda(
        [WeakField](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bOk)
        {
            const bool bSuccess =
                bOk && Resp.IsValid() &&
                Resp->GetResponseCode() >= 200 &&
                Resp->GetResponseCode() < 300;

            UE_LOG(LogTemp, Log, TEXT("Feedback send result: %s"),
                bSuccess ? TEXT("Success") : TEXT("Failed"));

            if (WeakField.IsValid())
            {
                WeakField->SetText(FText::FromString(
                    bSuccess
                        ? TEXT("Thanks! Your feedback was sent.")
                        : TEXT("Couldn't send — please try again.")));
            }
        });

    constexpr int32 CooldownLength = 15;

    bCooldownActive = true;
    CooldownRemaining = CooldownLength;

    if (StatusField)
    {
        StatusField->SetText(FText::FromString(
            FString::Printf(TEXT("Please wait %d seconds..."), CooldownRemaining)));
    }

    TWeakObjectPtr<UMultiLineEditableText> WeakStatus(StatusField);

    World->GetTimerManager().SetTimer(
        CooldownTimerHandle,
        FTimerDelegate::CreateLambda([World, WeakStatus]()
        {
            CooldownRemaining--;

            if (CooldownRemaining <= 0)
            {
                bCooldownActive = false;
                World->GetTimerManager().ClearTimer(CooldownTimerHandle);

                if (WeakStatus.IsValid())
                {
                    WeakStatus->SetText(FText::FromString(
                        TEXT("You can now submit another report.")));
                }

                return;
            }

            if (WeakStatus.IsValid())
            {
                WeakStatus->SetText(FText::FromString(
                    FString::Printf(TEXT("Please wait %d seconds..."), CooldownRemaining)));
            }

        }),
        1.0f,
        true);

    Request->ProcessRequest();
}

FText UFeedbackSender::GetGameVersion()
{
    const UFeedbackSettings* Settings = GetDefault<UFeedbackSettings>();
    return FText::FromString(Settings ? Settings->VersionName : TEXT("unknown"));
}