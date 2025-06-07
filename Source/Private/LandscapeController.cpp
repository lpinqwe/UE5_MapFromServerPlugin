#include "LandscapeController.h"
#include "Landscape.h"
#include "LandscapeStreamingProxy.h"

// Конструктор
ALandscapeController::ALandscapeController()
{
    PrimaryActorTick.bCanEverTick = false;
    UE_LOG(LogTemp, Log, TEXT("LandscapeController: Constructed"));
}

// Создаёт ландшафт для чанка
void ALandscapeController::CreateLandscapeForChunk(const FChunkData& ChunkData)
{
    UE_LOG(LogTemp, Log, TEXT("LandscapeController: CreateLandscapeForChunk called for ChunkID (%f, %f)"), 
           ChunkData.ChunkID.X, ChunkData.ChunkID.Y);

    // TODO: Создать ALandscape и настроить ULandscapeComponent
    if (UWorld* World = GetWorld())
    {
        ALandscape* Landscape = World->SpawnActor<ALandscape>();
        LandscapeCache.Add(ChunkData.ChunkID, Landscape);
        UE_LOG(LogTemp, Log, TEXT("LandscapeController: Spawned ALandscape for ChunkID (%f, %f)"), 
               ChunkData.ChunkID.X, ChunkData.ChunkID.Y);
        // TODO: Импортировать ChunkData.Heightmap с помощью FLandscapeImportData
    }
}

// Обновляет ландшафт
void ALandscapeController::UpdateLandscapeForChunk(FVector2D ChunkID, const TArray<float>& NewHeightmap)
{
    UE_LOG(LogTemp, Log, TEXT("LandscapeController: UpdateLandscapeForChunk called for ChunkID (%f, %f)"), 
           ChunkID.X, ChunkID.Y);
    // TODO: Обновить высотную карту в ULandscapeComponent
}

// Удаляет ландшафт
void ALandscapeController::RemoveLandscapeForChunk(FVector2D ChunkID)
{
    UE_LOG(LogTemp, Log, TEXT("LandscapeController: RemoveLandscapeForChunk called for ChunkID (%f, %f)"), 
           ChunkID.X, ChunkID.Y);
    
    if (ALandscape** Landscape = LandscapeCache.Find(ChunkID))
    {
        (*Landscape)->Destroy();
        LandscapeCache.Remove(ChunkID);
        UE_LOG(LogTemp, Log, TEXT("LandscapeController: Removed ALandscape for ChunkID (%f, %f)"), 
               ChunkID.X, ChunkID.Y);
    }
}