#pragma once
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ChunkInterfaces.h"
#include "ChunkManager.generated.h"

// Менеджер чанков, управляющий загрузкой/выгрузкой чанков
// Используется: как центральный компонент плагина, координирующий работу с IChunkProvider и LandscapeController
UCLASS()
class MYCHUNKLOADERPLUGIN_API UChunkManager : public UWorldSubsystem, public IChunkManager
{
    GENERATED_BODY()

public:
    // Инициализирует менеджер чанков (чтение конфигурации, настройка ChunkProvider)
    // Используется: при старте мира для подготовки системы
    virtual void InitializeChunkManager_Implementation() override;

    // Запрашивает загрузку чанка
    // Используется: когда игрок входит в новую область
    virtual void LoadChunk_Implementation(FVector2D ChunkID) override;

    // Выгружает чанк
    // Используется: для освобождения памяти
    virtual void UnloadChunk_Implementation(FVector2D ChunkID) override;

    // Обрабатывает данные чанка
    // Используется: для передачи данных в LandscapeController
    virtual void ProcessChunkData_Implementation(const FChunkData& Data) override;

    // Делегаты для уведомления о событиях
    // Используется: для связи с другими системами (например, спавн объектов)
    UPROPERTY(BlueprintAssignable, Category = "ChunkManager")
    FOnChunkLoaded OnChunkLoaded;

    UPROPERTY(BlueprintAssignable, Category = "ChunkManager")
    FOnChunkFailed OnChunkFailed;

protected:
    // Вызывается при инициализации подсистемы
    // Используется: для настройки начальных параметров
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // Вызывается при деинициализации подсистемы
    // Используется: для очистки ресурсов
    virtual void Deinitialize() override;

private:
    // Кэш загруженных чанков
    // Используется: для быстрого доступа к данным чанков
    TMap<FVector2D, FChunkData> ChunkCache;

    // Ссылка на провайдер чанков
    // Используется: для запросов данных с сервера
    TScriptInterface<IChunkProvider> ChunkProvider;

    // Конфигурация чанков
    // Используется: для хранения настроек (например, радиус загрузки)
    UPROPERTY()
    class UChunkConfig* Config;
};