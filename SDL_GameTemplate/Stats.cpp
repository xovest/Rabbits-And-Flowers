#include "Stats.h"

Stats::Stats() {
	P1_score = 0;
	P2_score = 0;

	P1_victories = 0;
	P2_victories = 0;

	gameplayTime = 0;
	stateGameplayEnd = EndMode::NOT_STARTED;
}

void Stats::SetP1Score(unsigned int score) {
	P1_score = score;
}

void Stats::SetP2Score(unsigned int score) {
	P2_score = score;
}

void Stats::SetP1Victories(unsigned int victories) {
	P1_victories = victories;
}

void Stats::SetP2Victories(unsigned int victories) {
	P2_victories = victories;
}

void Stats::P1AddVictory() {
	P1_victories++;
}

void Stats::P2AddVictory() {
	P2_victories++;
}

void Stats::SetGameplayTime(float time) {
	gameplayTime = time;
}

void Stats::SetStateGameplayEnd(EndMode mode) {
	stateGameplayEnd = mode;
}

unsigned int Stats::GetP1Score() {
	return P1_score;
}

unsigned int Stats::GetP2Score() {
	return P2_score;
}

unsigned int Stats::GetP1Victories() {
	return P1_victories;
}

unsigned int Stats::GetP2Victories() {
	return P2_victories;
}

float Stats::GetGameplayTime() {
	return gameplayTime;
}

EndMode Stats::GetStateGameplayEnd() {
	return stateGameplayEnd;
}

