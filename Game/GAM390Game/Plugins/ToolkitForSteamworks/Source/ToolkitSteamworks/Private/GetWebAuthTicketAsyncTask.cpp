/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/


#include "GetWebAuthTicketAsyncTask.h"

void UGetWebAuthTicketAsyncTask::SteamCallback(UEResult Result, int32 Ticket, TArray<uint8> Data)
{
	Completed.Broadcast(Result, Ticket, Data);
	SetReadyToDestroy();
}

UGetWebAuthTicketAsyncTask* UGetWebAuthTicketAsyncTask::SteamGetWebAuthTicket(FString Identity, UObject* WorldContextObject)
{
	UGetWebAuthTicketAsyncTask* Node = NewObject<UGetWebAuthTicketAsyncTask>();
	Node->_Identity = Identity;
	return Node;
}

void UGetWebAuthTicketAsyncTask::Activate()
{
	USteamToolsSubsystem* Subsystem = GEngine->GetWorld()->GetGameInstance()->GetSubsystem<USteamToolsSubsystem>();
	FWebApiResponseCallbackDelegate callback;
	callback.BindUFunction(this, FName("SteamCallback"));
	int32 handle = SteamUser()->GetAuthTicketForWebApi(StringCast<ANSICHAR>(*_Identity).Get());
	Subsystem->GetWebAuthRequests.Add(handle, callback);
}
