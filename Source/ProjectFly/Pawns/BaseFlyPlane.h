// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseFlyPlane.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECTFLY_API ABaseFlyPlane : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ABaseFlyPlane();

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime);

    // Plane control settings

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Control, meta = (ClampMin = 0.0f))
    float Acceleration = 30.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Control, meta = (ClampMin = 0.0f))
    float MaxSpeed = 4000.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Control, meta = (ClampMin = 0.0f))
    float MinSpeed = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Control, meta = (ClampMin = 0.0f))
    float PitchRateMultiplier = 200.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Control, meta = (ClampMin = 0.0f))
    float YawRateMultiplier = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Control, meta = (ClampMin = 0.0f))
    float CurrentForwardSpeed = 500.0f;

private:
    // Input process

    void PitchControl(float Value);

    void YawControl(float Value);

    // Rotation calculation

    void ProcessPitch(float Value);

    void ProcessYaw(float Value);

    // Plane rotation speed

    float CurrentYawSpeed = 0.0f;

    float CurrentPitchSpeed = 0.0f;

    float CurrentRollSpeed = 0.0f;

    // Camera boom positioning the camera behind the character
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> CameraBoom;

    // Follow camera
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FollowCamera;

    // Static mesh
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> StaticMesh;
};
