﻿// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RicochetAttributeSetBase.h"
#include "RicochetRecoilAttributeSet.generated.h"

/**
* @file RicochetRecoilAttributeSet.h
* @brief Attribute Set for Recoil
* @attribute Recoil - 
*/
UCLASS()
class RICOCHET_API URicochetRecoilAttributeSet : public URicochetAttributeSetBase
{
	GENERATED_BODY()

public:
	URicochetRecoilAttributeSet();

	// Attribute Set Overrides.
	// virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	// virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// The attributes for the bullet round
	UPROPERTY(BlueprintReadOnly, Category = "Bullet", ReplicatedUsing = OnRep_Recoil)
	FGameplayAttributeData Recoil;
	ATTRIBUTE_ACCESSORS(URicochetRecoilAttributeSet, Recoil);

protected:
	// Replication functions
	UFUNCTION()
	virtual void OnRep_Recoil(const FGameplayAttributeData& OldValue);	
};
