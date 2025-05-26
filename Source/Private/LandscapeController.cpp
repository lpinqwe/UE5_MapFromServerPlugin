#include "LandscapeController.h"
#include "Landscape.h"

// constructor
// use: init components
ALandscapeController::ALandscapeController()
{
    PrimaryActorTick.bCanEverTick = false;
    UE_LOG(LogTemp, Log, TEXT("LandscapeController: Constructed"));
}

// create landscape for chunk
// use: for creating ULandscapeComponent based on FChunkData
void ALandscapeController::CreateLandscapeForChunk(const FChunkData& ChunkData)
{
    UE_LOG(LogTemp, Log, TEXT("LandscapeController: CreateLandscapeForChunk called for ChunkID (%f, %f)"), 
           ChunkData.ChunkID.X, ChunkData.ChunkID.Y);
    // TODO: create ULandscapeComponent and import height map
}

// update landscape
// use: change map/textures
void ALandscapeController::UpdateLandscapeForChunk(FVector2D ChunkID, const TArray<float>& NewHeightmap)
{
    UE_LOG(LogTemp, Log, TEXT("LandscapeController: UpdateLandscapeForChunk called for ChunkID (%f, %f)"), 
           ChunkID.X, ChunkID.Y);
    // TODO: update ULandscapeComponent with new hegthmap
}

// delete landscape
// use: when chunk unloaded
void ALandscapeController::RemoveLandscapeForChunk(FVector2D ChunkID)
{
    UE_LOG(LogTemp, Log, TEXT("LandscapeController: RemoveLandscapeForChunk called for ChunkID (%f, %f)"), 
           ChunkID.X, ChunkID.Y);
    // TODO: delete ULandscapeComponent from LandscapeCache
}