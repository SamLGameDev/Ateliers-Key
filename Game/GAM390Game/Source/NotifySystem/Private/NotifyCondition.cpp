// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyCondition.h"

#include "Notification.h"

UNotifyCondition::UNotifyCondition()
{
	bPassed = false;
}

void UNotifyCondition::AddNotification(UNotification* Notification)
{
	if (Notifications.Contains(Notification)) return;
	Notifications.Add(Notification);
}

void UNotifyCondition::RemoveNotification(UNotification* Notification)
{
	Notifications.Remove(Notification);
}

void UNotifyCondition::Complete()
{
	bPassed = true;
	for (const auto& notification : Notifications)
	{
		notification->OnConditionPassed.Broadcast();
	}
}

void UNotifyCondition::MarkUnComplete()
{
	bPassed = false;
}
