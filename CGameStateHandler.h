#pragma once
// Last updated: 04.02.16

#include <vector>

using namespace std;

class CGameState;

class CGameStateHandler
{
private:
	// the stack of states
	vector<CGameState*> mpGameStates;

public:
	// Setup and destroy the state handler
	void Init();
	void Cleanup();

	// Transition between states
	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();

	// Game loop actions
	void HandleEvents();
	void Update();
	void Draw();

	// Exit game loop
	void Quit();
};