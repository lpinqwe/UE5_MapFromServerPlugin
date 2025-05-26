#include "ChunkProviderREST.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

// request chunk from server
// use: http-request
void UChunkProviderREST::RequestChunk_Implementation(FVector2D ChunkID)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkProviderREST: RequestChunk called for ChunkID (%f, %f)"), 
           ChunkID.X, ChunkID.Y);
    // TODO: send http using FHttpModule
}

// process recieved data
// use: transmit data to ChunkManager
void UChunkProviderREST::OnChunkReceived_Implementation(const FChunkData& Data)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkProviderREST: OnChunkReceived called for ChunkID (%f, %f)"), 
           Data.ChunkID.X, Data.ChunkID.Y);
    // TODO: transmit data to ChunkManager
}

// check chunk status
// use: check load status
bool UChunkProviderREST::GetChunkStatus_Implementation(FVector2D ChunkID, EChunkStatus& OutStatus)
{
    UE_LOG(LogTemp, Log, TEXT("ChunkProviderREST: GetChunkStatus called for ChunkID (%f, %f)"), 
           ChunkID.X, ChunkID.Y);
    OutStatus = EChunkStatus::Unloaded;
    return false; // TODO: return actual status
}