#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkInterfaces.h"
#include "LandscapeController.generated.h"

// Контроллер для создания и управления ландшафтом
// Используется: для преобразования данных чанка (FChunkData) в ландшафт UE5
UCLASS()
class MYCHUNKLOADERPLUGIN_API ALandscapeController : public AActor
{
    GENERATED_BODY()

public:
    ALandscapeController();

    // Создаёт ландшафт для чанка
    // Используется: когда ChunkManager передаёт данные чанка
    UFUNCTION(BlueprintCallable, Category = "Landscape")
    void CreateLandscapeForChunk(const FChunkData& ChunkData);

    // Обновляет ландшафт (например, текстуры или высоты)
    // Используется: при изменении данных чанка
    UFUNCTION(BlueprintCallable, Category = "Landscape")
    void UpdateLandscapeForChunk(FVector2D ChunkID, const TArray<float>& NewHeightmap);

    // Удаляет ландшафт для чанка
    // Используется: при выгрузке чанка
    UFUNCTION(BlueprintCallable, Category = "Landscape")
    void RemoveLandscapeForChunk(FVector2D ChunkID);

protected:
    // Ссылка на компонент ландшафта
    // Используется: для управления ландшафтом в мире
    UPROPERTY()
    class ULandscapeComponent* LandscapeComponent;

    // Кэш созданных ландшафтов
    // Используется: для отслеживания активных чанков
    TMap<FVector2D, class ALandscape*> LandscapeCache;
};