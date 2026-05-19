/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/


#include "BeginAuthSessionAsyncTask.h"

void UBeginAuthSessionAsyncTask::SteamCallback(const int64 User, const int64 Owner, const UEAuthSessionResponse Response)
{
	Request.User = User;
	Request.Owner = Owner;
	Request.RequestResponse = Response;

	Completed.Broadcast(Request);
	SetReadyToDestroy();
}

UBeginAuthSessionAsyncTask* UBeginAuthSessionAsyncTask::SteamBeginAuthSessionUser(TArray<uint8> Ticket, int64 SteamId, UObject* WorldContextObject)
{
	UBeginAuthSessionAsyncTask* Node = NewObject<UBeginAuthSessionAsyncTask>();
	Node->Request.Ticket = Ticket;
	Node->Request.User = SteamId;
	return Node;
}

UBeginAuthSessionAsyncTask* UBeginAuthSessionAsyncTask::SteamBeginAuthSessionServer(TArray<uint8> Ticket, int64 SteamId, UObject* WorldContextObject)
{
	UBeginAuthSessionAsyncTask* Node = NewObject<UBeginAuthSessionAsyncTask>();
	Node->Request.Ticket = Ticket;
	Node->Request.User = SteamId;
	return Node;
}

void UBeginAuthSessionAsyncTask::Activate()
{
	USteamToolsSubsystem* Subsystem = GEngine->GetWorld()->GetGameInstance()->GetSubsystem<USteamToolsSubsystem>();
	FBeginAuthSessionCallbackDelegate callback;
	callback.BindUFunction(this, FName("SteamCallback"));

	Subsystem->BeginAuthRequests.Add(Request.User, callback);

	int32 TicketLength = Request.Ticket.Num();
	const uint8* TicketData = Request.Ticket.GetData();

	EBeginAuthSessionResult result = SteamUser()->BeginAuthSession(TicketData, TicketLength, INT64_TO_STEAMID(Request.User));
	Request.RequestState = static_cast<UEBeginAuthSessionResult>(result);
}
