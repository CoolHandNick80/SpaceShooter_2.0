// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/MySaveGame.h"
#include "Engine/Engine.h"
#include "GameInstances/MyGameInstance.h"

UMySaveGame* UGlobalFunctions::SaveGame(int32 InSlot, const FPlayerData & InPlayerData, const FName & InCurrentLevelName)
{
	FString SlotName = "MySaveSlot";

	int32 Slot = InSlot;
	
	SlotName.Append(FString::FromInt(Slot));

	UMySaveGame* SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

	SaveGameObject->CurrentLevelName = InCurrentLevelName;
	SaveGameObject->SavedPlayerData = InPlayerData;
	SaveGameObject->SaveDateTime = FDateTime::Now();
	

	if (UGameplayStatics::SaveGameToSlot(SaveGameObject, SlotName, 0))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Successfully saved game on disk.");
		return SaveGameObject;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Unable to save game on disk.");
		return nullptr;
	}
}

void UGlobalFunctions::LoadGame(int32 InSlot, UObject * InWorldContext)
{
	FString SlotName = "MySaveSlot";

	int32 Slot = InSlot;

	SlotName.Append(FString::FromInt(Slot));

	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UMySaveGame* SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

		SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, SaveGameObject->CurrentLevelName.ToString());

		UGameplayStatics::OpenLevel(InWorldContext, SaveGameObject->CurrentLevelName);

		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(InWorldContext));
		verify(GameInstance != nullptr);

		GameInstance->SetPLayerData(SaveGameObject->SavedPlayerData);
		GameInstance->SetCurrentLevel(SaveGameObject->CurrentLevelName);
	}
	else
	{
		{
			//UGameplayStatics::OpenLevel(InWorldContext, FName("Main"));

			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Couldn't find any savegame!");
		}
	}

}
