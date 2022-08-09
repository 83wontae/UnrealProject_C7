// Fill out your copyright notice in the Description page of Project Settings.


#include "BountyDashParticle.h"
#include "Particles/ParticleSystemComponent.h"
#include "EngineUtils.h"
#include "Particles/ParticleSystem.h"

ABountyDashParticle::ABountyDashParticle()
{
	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	check(particleSystem);

	ConstructorHelpers::FObjectFinder<UParticleSystem> thisSys(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	if (thisSys.Succeeded())
	{
		particleSystem->SetTemplate(thisSys.Object);
	}

	particleSystem->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}
