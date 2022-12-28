#pragma once
#include <SDL.h>

enum class EndMode { PLAY_MODE, NORMAL_END, GOT_EATEN_MODE, POISONED_MODE, NOT_STARTED, FINISHED };

class Stats {
private:
	unsigned int P1_score;
	unsigned int P2_score;

	unsigned int P1_victories;
	unsigned int P2_victories;

	float gameplayTime;
	EndMode stateGameplayEnd;
public:
	Stats();

	void SetP1Score(unsigned int score = 0);
	void SetP2Score(unsigned int score = 0);
	void SetP1Victories(unsigned int victories = 0);
	void SetP2Victories(unsigned int victories = 0);
	void P1AddVictory();
	void P2AddVictory();
	void SetGameplayTime(float time = 0); 
	void SetStateGameplayEnd(EndMode mode);

	unsigned int GetP1Score();
	unsigned int GetP2Score();
	unsigned int GetP1Victories();
	unsigned int GetP2Victories();
	float GetGameplayTime();
	EndMode GetStateGameplayEnd();
};