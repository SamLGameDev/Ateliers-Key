// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBar.h"

void UBossBar::UpdateHealthBar(UDamageSystem* damageSystem)
{
	if (healthBar)
	{
		float curHealth = damageSystem->CurrentHealth;
		float maxHealth = damageSystem->MaxHealth;
		
		/*healthBar->Percent(curHealth / maxHealth);*/
	}
}
