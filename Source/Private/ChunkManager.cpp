#include "ChunkManager.h"
#include "ChunkInterfaces.h"
#include "ChunkConfig.h"

// Инициализация подсистемы
// Используется: для настройки менеджера чанков при старте мира
void UChunkManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: Initialized"));
}

// Деинициализация подсистемы
// Используется: для очистки ресурсов при закрытии мира
void UChunkManager::Deinitialize()
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: Deinitialized"));
    Super::Deinitialize();
}

// Инициализация менеджера чанков
// Используется: для чтения конфигурации и настройки ChunkProvider
void UChunkManager::InitializeChunkManager_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: InitializeChunkManager called"));
    // TODO: Загрузить UChunkConfig и инициализировать ChunkProvider
}

// Запрашивает загрузку чанка
// Используется: для вызова IChunkProvider::RequestChunk
void UChunkManager::LoadChunk_Implementation(FVector2D ChunkID)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: LoadChunk called for ChunkID (%f, %f)"), ChunkID.X, ChunkID.Y);
    // TODO: Вызвать ChunkProvider->RequestChunk(ChunkID)
}

// Выгружает чанк
// Используется: для удаления чанка из кэша и ландшафта
void UChunkManager::UnloadChunk_Implementation(FVector2D ChunkID)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: UnloadChunk called for ChunkID (%f, %f)"), ChunkID.X, ChunkID.Y);
    // TODO: Удалить чанк из ChunkCache и вызвать LandscapeController::RemoveLandscapeForChunk
}

// Обрабатывает данные чанка
// Используется: для передачи данных в LandscapeController
void UChunkManager::ProcessChunkData_Implementation(const FChunkData& Data)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: ProcessChunkData called for ChunkID (%f, %f)"), Data.ChunkID.X, Data.ChunkID.Y);
    // TODO: Передать Data в LandscapeController::CreateLandscapeForChunk
}