// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "RicochetMuzzleAttachment.h"
#include "Components/PrimitiveComponent.h"
#include "Data/RicochetEnums.h"
#include "RicochetReceiver.generated.h"

class URicochetBarrel;
struct FGameplayTag;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeforeShotFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShotFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAmmoDepleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReadyToShoot);

/**
* @file RicochetReceiver.h
* @brief Core firearm component that defines Calibers, Fire Modes, Fire Rate, Base Recoil, and has Barrel and Magazine Attachments
*/
UCLASS()
class RICOCHET_API URicochetReceiver : public UPrimitiveComponent, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	URicochetReceiver();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	float GetReceiverWeight() const;

	virtual float GetTotalWeaponWeight();

	virtual float GetTotalCalculatedRecoil();

	/**
	 * @brief  Weapon Properties
	 * @todo Turn into Structs and Data Assets
	 */

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TArray<FGameplayTag> FireModes;
	
	/**
	 * @brief Attributes / Weapon Properties
	 * @todo Turn into Attributes and/or Structs and Data Assets
	 */
	

	float ReceiverWeight = 1.0;

	
	

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float Dirtiness = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	bool bUsesDetachableMagazine {true};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	bool bUsesDetachableBarrel {true};

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float FailureToExtractProbability = 0.0f;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float FailureToEjectProbability = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TArray<TSubclassOf<URicochetBarrel>> Barrels;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FGameplayTagContainer CompatibleCalibers;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FGameplayTagContainer CompatibleMagazines;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FGameplayTagContainer CompatibleBarrels;
	 
	FRandomStream RandomStream;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity", meta = (ToolTip = "Amount of recoil applied to the barrel, only works with physics enabled"))
	TSoftObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	// Velocity
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Flight")
	float MuzzleVelocityMin = 100000.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Flight")
	float MuzzleVelocityMax = 100000.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity", meta = (ToolTip = "Bullet inherits barrel velocity, only works with physics enabled or with additional velocity set"))
	float InheritVelocity = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float MuzzleVelocityMultiplierMin = 1.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float MuzzleVelocityMultiplierMax = 1.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity", meta = (ToolTip = "Additional velocity, for use with InheritVelocity"))
	FVector AdditionalVelocity = FVector(0,0,0);
	
	// Spread
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon", meta = (ToolTip = "Additional Spread, applied on top of bullet spread"))
	float Spread = 0.0f;
	
	
	// Fire Rate
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float FireRateMin = 1.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float FireRateMax = 1.0f;

	// Cycle Ammo
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ammo")
	bool CycleAmmo = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ammo", meta = (EditCondition = "CycleAmmo"))
	bool CycleAmmoUnlimited = true;

	// Shotgun
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shotgun")
	bool Shotgun = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shotgun", meta = (EditCondition = "Shotgun"))
	int ShotCount=10;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shotgun", meta = (EditCondition = "Shotgun"))
	float ShotSpread=0.01;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shotgun", meta = (EditCondition = "Shotgun"))
	float ShotVelocitySpread = 0.01;

	// Burst Fire
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	int BurstCount = 3;

	// Gatling Fire
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	float GatlingRPS = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon", meta = (ToolTip = "Automatically spin up gatling when trigger is being held down"))
	bool GatlingAutoSpool = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float GatlingSpoolUpTime = 1.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float  GatlingSpoolDownTime = 1.0f;
	
	// Safe Launch
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Safe launch")
	bool SafeLaunch = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Safe launch", Meta = (EditCondition = "SafeLaunch"))
	bool SafeLaunchIgnoreAttachParent = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Safe launch", Meta = (EditCondition = "SafeLaunchIgnoreAttachParent"))
	bool SafeLaunchIgnoreAllAttached = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Safe launch", Meta = (EditCondition = "SafeLaunch"))
	float SafeDelay = 1.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Safe launch", Meta = (EditCondition = "SafeLaunch")) TArray<AActor*>
	SafeLaunchIgnoredActors;
	

	// State
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	ERicochetFireMode FireMode = ERicochetFireMode::FM_Semiauto;
	
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	bool ShootingBlocked = false;
	
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Ammo")
	TArray<TSubclassOf<class ARicochetBullet>> Ammo;
	
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Ammo", meta = (EditCondition = "CycleAmmo"))
	int CycleAmmoCount = 0;
	
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Ammo", meta = (EditCondition = "CycleAmmo"))
	int CycleAmmoPos = 0;
	
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "WeaponState")
	TSubclassOf<class ARicochetBullet> ChamberedBullet;
	
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "WeaponState")
	bool Shooting = false;
	
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "WeaponState")
	bool Spooling = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "WeaponState")
	bool LoadNext=true;
	
	UPROPERTY(BlueprintReadWrite, Category = "WeaponState")
	float Cooldown = 0.0f;

	// Burst
	UPROPERTY(BlueprintReadWrite, Category = "WeaponState")
	int BurstRemaining = 0;
	
	//Gatling
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	float  GatlingPhase = 0.0f;
	

	// Replication
	UPROPERTY(EditAnywhere, Category = "Replication") 
	bool ReplicateVariables = true;
	
	UPROPERTY(EditAnywhere, Category = "Replication") 
	bool ReplicateShotFiredEvents = true;
	
	UPROPERTY(EditAnywhere, Category = "Replication") 
	bool ClientSideAim = false;
	
	UPROPERTY(EditAnywhere, Category = "Replication") 
	float ClientAimUpdateFrequency = 30.0f;
	
	UPROPERTY(EditAnywhere, Category = "Replication") 
	float ClientAimDistanceLimit = 200.0f;

	// Debug
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug") float DebugArrowSize = 100.0f;

	// Delegate Properties
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FBeforeShotFired BeforeShotFired;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FShotFired ShotFired;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAmmoDepleted AmmoDepleted;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FReadyToShoot ReadyToShoot;

protected:
	// Ability System Component for the bullet (optional, or can be tied to instigator)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

private:
	FVector Aim = FVector(0,0,0);;
	FVector Location = FVector(0,0,0);;
	bool RemoteAimReceived = false;
	float TimeSinceAimUpdate = 0.0f;
};
