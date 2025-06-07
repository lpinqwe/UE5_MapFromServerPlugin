#include "ChunkProviderREST.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "ImageUtils.h"
#include "ChunkConfig.h"

// Запрашивает чанк с сервера
void UChunkProviderREST::RequestChunk_Implementation(FVector2D ChunkID)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkProviderREST: RequestChunk called for ChunkID (%f, %f)"), 
           ChunkID.X, ChunkID.Y);

    // Получаем URL сервера из конфигурации
    FString ServerURL = TEXT("http://your-server"); // По умолчанию, будет перезаписано из Config
    if (UChunkConfig* Config = Cast<UChunkConfig>(GEngine->GetClassFromAsset(TEXT("/MyChunkLoaderPlugin/DataAssets/DA_ChunkConfig.DA_ChunkConfig"))))
    {
        ServerURL = Config->ServerURL;
    }

    // Формируем URL запроса
    FString URL = FString::Printf(TEXT("%s/command_post?x=%d&y=%d"), *ServerURL, (int32)ChunkID.X, (int32)ChunkID.Y);

    // Создаём HTTP-запрос
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetVerb("GET");
    Request->SetURL(URL);
    Request->OnProcessRequestComplete().BindUObject(this, &UChunkProviderREST::OnHttpResponseReceived);
    Request->ProcessRequest();
}

// Обрабатывает HTTP-ответ
void UChunkProviderREST::OnHttpResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("ChunkProviderREST: HTTP request failed"));
        OnChunkFailed.Broadcast(FVector2D(0, 0), TEXT("HTTP request failed"));
        return;
    }

    // Получаем бинарные данные (предполагается изображение PNG)
    TArray<uint8> ImageData = Response->GetContent();

    // Преобразуем изображение в высотную карту
    FChunkData ChunkData;
    ChunkData.ChunkID = FVector2D(0, 0); // Будет обновлено из метаданных или URL

    // Парсим параметры из URL для ChunkID
    FString URL = Request->GetURL();
    TArray<FString> URLParts;
    URL.ParseIntoArray(URLParts, TEXT("?"));
    if (URLParts.Num() > 1)
    {
        TArray<FString> Params;
        URLParts[1].ParseIntoArray(Params, TEXT("&"));
        for (const FString& Param : Params)
        {
            TArray<FString> KeyValue;
            Param.ParseIntoArray(KeyValue, TEXT("="));
            if (KeyValue.Num() == 2)
            {
                if (KeyValue[0] == TEXT("x")) ChunkData.ChunkID.X = FCString::Atoi(*KeyValue[1]);
                if (KeyValue[0] == TEXT("y")) ChunkData.ChunkID.Y = FCString::Atoi(*KeyValue[1]);
            }
        }
    }

    // Преобразуем изображение в высотную карту
    // Предполагаем, что изображение в градациях серого, где яркость пикселя = высота
    UTexture2D* Texture = FImageUtils::ImportBufferAsTexture2D(ImageData);
    if (Texture)
    {
        int32 Width = Texture->GetSizeX();
        int32 Height = Texture->GetSizeY();
        ChunkData.Heightmap.Reserve(Width * Height);

        // Получаем пиксели изображения
        FColor* PixelData = static_cast<FColor*>(Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY));
        for (int32 i = 0; i < Width * Height; ++i)
        {
            // Преобразуем яркость пикселя (R) в высоту (0-255 -> 0.0-1.0)
            float HeightValue = PixelData[i].R / 255.0f;
            ChunkData.Heightmap.Add(HeightValue);
        }
        Texture->PlatformData->Mips[0].BulkData.Unlock();

        // Добавляем метаданные (пример)
        ChunkData.Metadata.Add(TEXT("Texture"), TEXT("MoonSurface"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ChunkProviderREST: Failed to parse image"));
        OnChunkFailed.Broadcast(ChunkData.ChunkID, TEXT("Failed to parse image"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("ChunkProviderREST: Parsed ChunkID (%f, %f)"), 
           ChunkData.ChunkID.X, ChunkData.ChunkID.Y);
    OnChunkReceived_Implementation(ChunkData);
}

// Обрабатывает полученные данные
void UChunkProviderREST::OnChunkReceived_Implementation(const FChunkData& Data)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkProviderREST: OnChunkReceived called for ChunkID (%f, %f)"), 
           Data.ChunkID.X, Data.ChunkID.Y);
    // Данные автоматически передаются в ChunkManager
}

// Проверяет статус чанка
bool UChunkProviderREST::GetChunkStatus_Implementation(FVector2D ChunkID, EChunkStatus& OutStatus)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkProviderREST: GetChunkStatus called for ChunkID (%f, %f)"), 
           ChunkID.X, ChunkID.Y);
    OutStatus = EChunkStatus::Unloaded; // TODO: Реализовать отслеживание статуса
    return false;
}