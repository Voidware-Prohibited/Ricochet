// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#include "AttributeSets/RicochetRoundAttributeSet.h"
#include "Net/UnrealNetwork.h"

/**
* @file RicochetRoundAttributeSet.cpp
* @brief Attribute Set for Rounds
* @attribute Mass - 
* @attribute Diameter - 
* @attribute FormFactor - 
*/
URicochetRoundAttributeSet::URicochetRoundAttributeSet()
{
}

void URicochetRoundAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(URicochetRoundAttributeSet, Mass, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(URicochetRoundAttributeSet, Diameter, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(URicochetRoundAttributeSet, FormFactor, Params);

	// Owner Only
	// Params.Condition = COND_OwnerOnly;
	// DOREPLIFETIME_WITH_PARAMS_FAST(URicochetRoundAttributeSet, StaminaRegeneration, Params);
}

void URicochetRoundAttributeSet::OnRep_Mass(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URicochetRoundAttributeSet, Mass, OldValue);
}

void URicochetRoundAttributeSet::OnRep_Diameter(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URicochetRoundAttributeSet, Diameter, OldValue);
}

void URicochetRoundAttributeSet::OnRep_FormFactor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URicochetRoundAttributeSet, FormFactor, OldValue);
}