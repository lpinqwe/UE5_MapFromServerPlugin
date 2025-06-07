#include "ChunkManager.h"
#include "ChunkInterfaces.h"
#include "ChunkConfig.h"
#include "ChunkProviderREST.h"

// Инициализация подсистемы
void UChunkManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: Initialized"));

    // Создаём ChunkProvider
    ChunkProvider = NewObject<UChunkProviderREST>(this);
}

// Деинициализация подсистемы
void UChunkManager::Deinitialize()
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: Deinitialized"));
    ChunkCache.Empty();
    ChunkProvider = nullptr;
    Super::Deinitialize();
}

// Инициализация менеджера чанков
void UChunkManager::InitializeChunkManager_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: InitializeChunkManager called"));

    // Загружаем конфигурацию
    Config = Cast<UChunkConfig>(GEngine->GetClassFromAsset(TEXT("/MyChunkLoaderPlugin/DataAssets/DA_ChunkConfig.DA_ChunkConfig")));
    if (Config)
    {
        UE_LOG(LogTemp, Log, TEXT("ChunkManager: Loaded config with ChunkSize (%f, %f) and LoadRadius %d"),
               Config->ChunkSize.X, Config->ChunkSize.Y, Config->LoadRadius);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ChunkManager: Failed to load ChunkConfig"));
    }
}

// Запрашивает загрузку чанка
void UChunkManager::LoadChunk_Implementation(FVector2D ChunkID)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: LoadChunk called for ChunkID (%f, %f)"), ChunkID.X, ChunkID.Y);

    // Проверяем, есть ли чанк в кэше
    if (ChunkCache.Contains(ChunkID))
    {
        UE_LOG(LogTemp, Log, TEXT("ChunkManager: ChunkID (%f, %f) found in cache"), ChunkID.X, ChunkID.Y);
        ProcessChunkData_Implementation(*ChunkCache.Find(ChunkID));
        OnChunkLoaded.Broadcast(ChunkID);
        return;
    }

    // Запрашиваем чанк через ChunkProvider
    if (ChunkProvider)
    {
        ChunkProvider->Execute_RequestChunk(ChunkProvider.GetObject(), ChunkID);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ChunkManager: ChunkProvider is null"));
        OnChunkFailed.Broadcast(ChunkID, TEXT("ChunkProvider not initialized"));
    }
}

// Выгружает чанк
void UChunkManager::UnloadChunk_Implementation(FVector2D ChunkID)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: UnloadChunk called for ChunkID (%f, %f)"), ChunkID.X, ChunkID.Y);

    // Удаляем чанк из кэша
    ChunkCache.Remove(ChunkID);
    // TODO: Вызвать LandscapeController::RemoveLandscapeForChunk
}

// Обрабатывает данные чанка
void UChunkManager::ProcessChunkData_Implementation(const FChunkData& Data)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkManager: ProcessChunkData called for ChunkID (%f, %f)"), 
           Data.ChunkID.X, Data.ChunkID.Y);

    // Сохраняем в кэш
    ChunkCache.Add(Data.ChunkID, Data);

    // TODO: Передать данные в LandscapeController::CreateLandscapeForChunk
    OnChunkLoaded.Broadcast(Data.ChunkID);
}