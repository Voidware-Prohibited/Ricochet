// MIT

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h" 
#include "RicochetBullet.generated.h"

class UGameplayEffect;

UCLASS()
class RICOCHET_API ARicochetBullet : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARicochetBullet();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Server function to activate the bullet from the pool
	UFUNCTION(BlueprintCallable, Category = "BulletPool")
	void ActivateBullet(const FVector& SpawnLocation, const FRotator& SpawnRotation);
    
	// Replicated callback to notify clients that the bullet is active
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_ActivateBullet(const FVector& SpawnLocation, const FRotator& SpawnRotation);

	// Server-side: Spawn and initialize the bullet
	void InitializeBullet(FVector StartLocation, FRotator StartRotation, float InitialSpeed);

	// Function to apply GAS effects and set initial velocity
	void ApplyInitialVelocityEffects(UAbilitySystemComponent* InstigatorASC);

	// Initial velocity property, potentially modified by GAS
	UPROPERTY(ReplicatedUsing=OnRep_InitialVelocity)
	FVector InitialVelocity;

	// Function to deactivate the bullet and return it to the pool
	void DeactivateBullet();

	// A replicated variable to track the bullet's active state
	UPROPERTY(ReplicatedUsing=OnRep_IsActive)
	bool bIsActive;

	// RepNotify handler for bIsActive
	UFUNCTION()
	void OnRep_IsActive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Ability System Component for the bullet (optional, or can be tied to instigator)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// Gameplay Effect to apply to the bullet's initial velocity
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> InitialVelocityGE;

	UPROPERTY(ReplicatedUsing = OnRep_InitialVelocity)
	FVector_NetQuantize InitialVelocityReplicated;

	UFUNCTION()
	void OnRep_InitialVelocity();

	// Client-side prediction state for rollback
	struct FBulletPredictionState
	{
		FVector Location;
		FVector Velocity;
		// Add other relevant state like rotation, etc.
	};

	TArray<FBulletPredictionState> PredictionHistory;

	// Server-side function to apply rollback if necessary
	void Server_CorrectClientPrediction(FVector ClientPredictedLocation);

private:
	// Example for deriving initial velocity from a GAS attribute
	// In a real scenario, this would likely be passed from the spawning ability
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	FGameplayAttribute InitialSpeedAttribute; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
