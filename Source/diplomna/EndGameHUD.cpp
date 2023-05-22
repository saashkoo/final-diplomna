// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameHUD.h"

AEndGameHUD::AEndGameHUD()
{

}

void AEndGameHUD::BeginPlay()
{
	Super::BeginPlay();
    GetOwningPlayerController()->bShowMouseCursor = true;
    GetOwningPlayerController()->bEnableClickEvents = true;
	EndGameWidget = CreateWidget<UEndGameWidget>(GetWorld(), EndGameWidgetClass);
	EndGameWidget->ReturnToMainMenuDelegate.BindUObject(this, &AEndGameHUD::ReturnToMainMenu);
	EndGameWidget->QuitGameDelegate.BindUObject(this, &AEndGameHUD::QuitGame);
    EndGameWidget->ConfirmNameDelegate.BindUObject(this, &AEndGameHUD::SaveFastestTime);
	ProcessString(GetWorld()->GetAuthGameMode()->OptionsString);
    EndGameWidget->WinningPlayerTextBlock->SetText(FText::FromString(FString("Player ").Append(FString::FromInt(WinningPlayer).Append("Has Won!"))));
    EndGameWidget->FastestLapTextBlock->SetText(FText::FromString(FString("The fastest Lap was done by Player ").Append(FString::FromInt(FastestLapPlayer).Append(", also known as:"))));
    EndGameWidget->ReturnToMainMenuButton->SetVisibility(ESlateVisibility::Hidden);
    EndGameWidget->QuitGameButton->SetVisibility(ESlateVisibility::Hidden);
    EndGameWidget->AddToViewport();
}

void AEndGameHUD::ReturnToMainMenu()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("MenuLevel"), true, "");
}

void AEndGameHUD::QuitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

void AEndGameHUD::ProcessString(FString InString)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *InString);
    InString.RemoveAt(0);
    WinningPlayer = FCString::Atoi(&InString[InString.Len() - 1]);
    InString.RemoveAt(InString.Len() - 1);
    InString.RemoveAt(InString.Len() - 1);
    FastestLapPlayer = FCString::Atoi(&InString[InString.Len() - 1]);
    InString.RemoveAt(InString.Len() - 1);
    InString.RemoveAt(InString.Len() - 1);
    FString LapTime;
    InString.Split(FString(" "), &MapName, &LapTime);
    FastestTime = FTimespan::FromSeconds(FCString::Atof(*LapTime));
}

void AEndGameHUD::SaveFastestTime()
{
    if (UFastestTimeSaveGame* LoadedGame = Cast<UFastestTimeSaveGame>(UGameplayStatics::LoadGameFromSlot(MapName, 0)))
    {
        for (auto It = LoadedGame->Times.CreateIterator(); It; ++It)
        {
            if (It->Key > 0.1f) 
            {
                LoadedGame->Times.Add(It->Key, It->Value);
                UE_LOG(LogTemp, Warning, TEXT("%f  %s"), It->Key, *(It->Value));
            }
          
        }
        LoadedGame->Times.Add((float)FastestTime.GetTotalSeconds(), EndGameWidget->PlayerNameEditableTextBox->GetText().ToString());
        LoadedGame->Times.KeySort([](float A, float B) { return A < B; });
        if (LoadedGame->Times.Num() > 10)
        {
            int I = 0;
            for (auto It = LoadedGame->Times.CreateIterator(); It; ++It)
            {
                UE_LOG(LogTemp, Error, TEXT("%f  %s"), It->Key, *(It->Value));
                if (I == 10 || It->Key < 0.1f)
                {
                    It.RemoveCurrent();
                    break;
                }
                I++;
            }//ensures there are only 10 entries in the leaderboard
        }
        if (UGameplayStatics::SaveGameToSlot(LoadedGame, MapName, 0))
        {

        }
    }
    else if (UFastestTimeSaveGame* SaveGameInstance = Cast<UFastestTimeSaveGame>(UGameplayStatics::CreateSaveGameObject(UFastestTimeSaveGame::StaticClass())))
    {
        SaveGameInstance->Times.Add(FastestTime.GetTotalSeconds(), EndGameWidget->PlayerNameEditableTextBox->GetText().ToString());
        SaveGameInstance->Times.KeySort([](float A, float B) { return A < B; });
        if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, MapName, 0))
        {

        }
    }
    EndGameWidget->ConfirmButton->SetVisibility(ESlateVisibility::Hidden);
    EndGameWidget->ReturnToMainMenuButton->SetVisibility(ESlateVisibility::Visible);
    EndGameWidget->QuitGameButton->SetVisibility(ESlateVisibility::Visible);
    EndGameWidget->PlayerNameEditableTextBox->SetIsReadOnly(true);
}
