// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RicochetAttributeSetBase.h"
#include "RicochetRoundAttributeSet.generated.h"

/**
* @file RicochetRoundAttributeSet.h
* @brief Attribute Set for Rounds
* @attribute Mass - 
* @attribute Diameter - 
* @attribute FormFactor - 
*/
UCLASS()
class RICOCHET_API URicochetRoundAttributeSet : public URicochetAttributeSetBase
{
	GENERATED_BODY()

public:
	URicochetRoundAttributeSet();

	// Attribute Set Overrides.
	// virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	// virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// The attributes for the bullet round
	UPROPERTY(BlueprintReadOnly, Category = "Bullet", ReplicatedUsing = OnRep_Mass)
	FGameplayAttributeData Mass;
	ATTRIBUTE_ACCESSORS(URicochetRoundAttributeSet, Mass);

	UPROPERTY(BlueprintReadOnly, Category = "Bullet", ReplicatedUsing = OnRep_Diameter)
	FGameplayAttributeData Diameter;
	ATTRIBUTE_ACCESSORS(URicochetRoundAttributeSet, Diameter);

	UPROPERTY(BlueprintReadOnly, Category = "Bullet", ReplicatedUsing = OnRep_FormFactor)
	FGameplayAttributeData FormFactor;
	ATTRIBUTE_ACCESSORS(URicochetRoundAttributeSet, FormFactor);

protected:
	// Replication functions
	UFUNCTION()
	virtual void OnRep_Mass(const FGameplayAttributeData& OldMass);

	UFUNCTION()
	virtual void OnRep_Diameter(const FGameplayAttributeData& OldDiameter);

	UFUNCTION()
	virtual void OnRep_FormFactor(const FGameplayAttributeData& OldFormFactor);
	
};
