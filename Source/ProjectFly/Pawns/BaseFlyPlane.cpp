// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectFly/Pawns/BaseFlyPlane.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABaseFlyPlane::ABaseFlyPlane()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create a static mesh
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    SetRootComponent(StaticMesh);

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;       // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);  // Attach the camera to the end of the boom and let the boom
                                                                                                  // adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false;                                                // Camera does not rotate relative to arm
}

// Called to bind functionality to input
void ABaseFlyPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("PitchControl", this, &ABaseFlyPlane::PitchControl);
    PlayerInputComponent->BindAxis("YawControl", this, &ABaseFlyPlane::YawControl);
}

// Called when the game starts or when spawned
void ABaseFlyPlane::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseFlyPlane::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    // Calculate Thrust
    const float CurrentAcc = -GetActorRotation().Pitch * DeltaTime * Acceleration;
    const float NewForwardSpeed = CurrentForwardSpeed + CurrentAcc;
    CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);

    const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);
    AddActorLocalOffset(LocalMove, true);

    // Calculate delta rotation
    FRotator DeltaRotation(0,0,0);
    DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
    DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;
    DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;

    // Add rotation to actor rotation
    AddActorLocalRotation(DeltaRotation);
}

void ABaseFlyPlane::PitchControl(float Value) 
{
    ProcessPitch(Value);
}

void ABaseFlyPlane::YawControl(float Value) 
{
    ProcessYaw(Value);
}

void ABaseFlyPlane::ProcessPitch(float Value) 
{
    const float TargetPitchSpeed = Value * PitchRateMultiplier;
    CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ABaseFlyPlane::ProcessYaw(float Value) 
{
    const float TargetYawSpeed = Value * PitchRateMultiplier;
    CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}