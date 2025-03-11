#pragma once

namespace Debug
{
	static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 DisplayTime = 7.0f, int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, DisplayTime, Color, Msg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}

	static void PrintString(const FString& FloatTitle, float FloatValue, const FColor& Color = FColor::MakeRandomColor(), int32 DisplayTime = 7.0f, int32 InKey = -1)
	{
		if (GEngine)
		{
			const FString Msg = FloatTitle + TEXT(" : ") + FString::SanitizeFloat(FloatValue);

			GEngine->AddOnScreenDebugMessage(InKey, DisplayTime, Color, Msg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}
}