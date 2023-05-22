// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderboardWidget.h"

void ULeaderboardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BackButton->OnClicked.AddDynamic(this, &ULeaderboardWidget::BackButtonPressed);
	PrevButton->OnClicked.AddDynamic(this, &ULeaderboardWidget::PrevButtonPressed);
	NextButton->OnClicked.AddDynamic(this, &ULeaderboardWidget::NextButtonPressed);
	LoadSaveGame();
}

void ULeaderboardWidget::BackButtonPressed()
{
	ReturnToMainMenuDelegate.ExecuteIfBound();
}

void ULeaderboardWidget::PrevButtonPressed()
{
	CurrentMapIndex--;
	if (0 > CurrentMapIndex)
	{
		CurrentMapIndex = MapSavesNames.Num()-1;
	}
	LoadSaveGame();
}

void ULeaderboardWidget::NextButtonPressed()
{
	CurrentMapIndex++;
	if (MapSavesNames.Num() <= CurrentMapIndex)
	{
		CurrentMapIndex = 0;
	}
	LoadSaveGame();
}

void ULeaderboardWidget::LoadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(MapSavesNames[CurrentMapIndex], 0)) {
		if (UFastestTimeSaveGame* LoadedGame = Cast<UFastestTimeSaveGame>(UGameplayStatics::LoadGameFromSlot(MapSavesNames[CurrentMapIndex], 0)))
		{
			MapName->SetText(FText::FromString(MapSavesNames[CurrentMapIndex]));
			int I = 0;
			for (auto It = LoadedGame->Times.CreateIterator(); It; ++It)
			{
				UHorizontalBox* Row = Cast<UHorizontalBox>(Leaderboard->GetChildAt(I));
				if (Row)
				{
					UTextBlock* PlayerTime = Cast<UTextBlock>(Row->GetChildAt(2));
					UTextBlock* PlayerName = Cast<UTextBlock>(Row->GetChildAt(1));
					PlayerTime->SetText(FText::FromString(FTimespan::FromSeconds(It.Key()).ToString()));
					PlayerName->SetText(FText::FromString(It.Value()));
					I++;
					UE_LOG(LogTemp, Warning, TEXT("Leaderboard:%f  %s"), It->Key, *(It->Value));
				}
			}
			while (I < 10)
			{
				UHorizontalBox* Row = Cast<UHorizontalBox>(Leaderboard->GetChildAt(I));
				if (Row)
				{
					UTextBlock* PlayerTime = Cast<UTextBlock>(Row->GetChildAt(2));
					UTextBlock* PlayerName = Cast<UTextBlock>(Row->GetChildAt(1));
					PlayerTime->SetText(FText::FromString("--:--.--"));
					PlayerName->SetText(FText::FromString("-"));
					I++;
				}
			}
		}
	}
}