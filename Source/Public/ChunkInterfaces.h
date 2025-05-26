```cpp
#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ChunkInterfaces.generated.h"

// data struct for chunk
// use: transcieve map & metadata for UE5
USTRUCT(BlueprintType)
struct FChunkData
{
    GENERATED_BODY()

    // ID chunk (coordinates , like X=0, Y=0)
    UPROPERTY(BlueprintReadWrite, Category = "Chunk")
    FVector2D ChunkID;

    // height map (массив высот для ландшафта, например, 256x256 значений)
    UPROPERTY(BlueprintReadWrite, Category = "Chunk")
    TArray<float> Heightmap;

        // metadata (example texture type, objects in chunk)
        //note: use with resourse map & easter egg
    UPROPERTY(BlueprintReadWrite, Category = "Chunk")
    TMap<FString, FString> Metadata;
};

// chunk status 
// use: load chunk status  (unloaded, loading, ready, error)
UENUM(BlueprintType)
enum class EChunkStatus : uint8
{
    Unloaded,    // not requested
    Loading,     // currently loading
    Loaded,      // ready
    Failed       // error
};

// interface used for getting chunks trought api (example from server through REST or WebSocket)
// use: as interfase that allow usage another ways to get chunks
UINTERFACE(Blueprintable)
class UChunkProvider : public UInterface
{
    GENERATED_BODY()
};

class MYCHUNKLOADERPLUGIN_API IChunkProvider
{
    GENERATED_BODY()

public:
    // reqyest chunk by ID
    // use: when ChunkManager define, that playr getting in new place 
    UFUNCTION(BlueprintNativeEvent, Category = "ChunkLoader")
    void RequestChunk(FVector2D ChunkID);

    // Called when chunk data is received from the server
    // use: to transfer data to ChunkManager, which transmits them to LandscapeController
    UFUNCTION(BlueprintNativeEvent, Category = "ChunkLoader")
    void OnChunkReceived(const FChunkData& Data);

    // Checks the status of a chunk
    // use: to check the status before using or requesting again
    UFUNCTION(BlueprintNativeEvent, Category = "ChunkLoader")
    bool GetChunkStatus(FVector2D ChunkID, EChunkStatus& OutStatus);
};

// Interface for managing chunks in the game world
// use: to coordinate loading/unloading of chunks and integration with World Partition
UINTERFACE(Blueprintable)
class UChunkManager : public UInterface
{
    GENERATED_BODY()
};

class MYCHUNKLOADERPLUGIN_API IChunkManager
{
    GENERATED_BODY()

public:
    // Initializes the chunk manager
    // use: when starting a world to read the configuration (eg loading radius)
    UFUNCTION(BlueprintNativeEvent, Category = "ChunkManager")
    void InitializeChunkManager();

    // request chunks load by ID
    // use: when player in new environment/place
    UFUNCTION(BlueprintNativeEvent, Category = "ChunkManager")
    void LoadChunk(FVector2D ChunkID);

    // delete chunk ftom mem
    // use: free resourses , when unloaded
    UFUNCTION(BlueprintNativeEvent, Category = "ChunkManager")
    void UnloadChunk(FVector2D ChunkID);

    // process data when chunk loaded
    // use: transmit data to LandscapeController for landscape
    UFUNCTION(BlueprintNativeEvent, Category = "ChunkManager")
    void ProcessChunkData(const FChunkData& Data);

    // delegate that report about chunk status
    // use: spawn object or UI update, etc
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChunkLoaded, FVector2D, ChunkID);

    // delegate for process errors
    // use: for err log and/or retry
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChunkFailed, FVector2D, ChunkID, const FString&, ErrorMessage);
};

