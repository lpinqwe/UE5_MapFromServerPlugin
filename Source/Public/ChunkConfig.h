#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChunkConfig.generated.h"

// config for chunk system 
// use: for set param in UE5 (like chunk size,server url)
UCLASS(BlueprintType)
class MYCHUNKLOADERPLUGIN_API UChunkConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    // chunk size ( UE5 units, like 256x256)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChunkConfig")
    FVector2D ChunkSize;

    // chunk radius load (around the player)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChunkConfig")
    int32 LoadRadius;

    // url servera
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChunkConfig")
    FString ServerURL;

    // size chunk (like 256x256)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChunkConfig")
    FIntPoint HeightmapResolution;
};