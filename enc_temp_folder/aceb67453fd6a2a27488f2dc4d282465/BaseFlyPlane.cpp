// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectFly/Pawns/BaseFlyPlane.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABaseFlyPlane::ABaseFlyPlane()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // Create a static mesh
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    SetRootComponent(StaticMesh);

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;       // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

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

void ABaseFlyPlane::PitchControl(float Value) {}

void ABaseFlyPlane::YawControl(float Value) {}
