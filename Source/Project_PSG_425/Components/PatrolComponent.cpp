#include "PatrolComponent.h"
#include "Global.h"
#include "Objects/PatrolPath.h"
#include "Components/SplineComponent.h"

UPatrolComponent::UPatrolComponent()
{
}


void UPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

}

bool UPatrolComponent::GetMoveToLocation(FVector& OutLocation)
{
	OutLocation = FVector::ZeroVector;
	CheckNullResult(Path, false);

	OutLocation = Path->GetSpline()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);

	return true;
}

void UPatrolComponent::UpdateNextIndex()
{
	CheckNull(Path);

	int32 count = Path->GetSpline()->GetNumberOfSplinePoints();

	//Reverse
	if (bReverse)
	{
		if (Index > 0)
		{
			Index--;
			return;
		}
		if (Path->GetSpline()->IsClosedLoop())
		{
			Index = count - 1;
			return;
		}
	}
	//Forward
	if (Index < count - 1)
	{
		Index++;
		return;
	}

	if (Path->GetSpline()->IsClosedLoop())
	{
		Index = 0;
		return;
	}

	Index = count - 2;
	bReverse = true;
}
