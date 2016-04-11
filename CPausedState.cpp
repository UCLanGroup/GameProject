#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPausedState.h"

CPausedState CPausedState::mPausedState;

// Setup and destroy state
void CPausedState::Init()
{
	gEngine->PauseAutoUpdates();
	mFont = gEngine->LoadFont("Rockwell", 60U);

	mFrame.reset(new CPanel());
	mFrame->SetSize(gEngine->GetWidth(), gEngine->GetHeight());
	mFrame->SetAlignments(Alignment::Center, Alignment::Center);

	mPausedLabel.reset(new CLabel(mFont, "Paused"));
	mPausedLabel->SetAlignments(Alignment::Center, Alignment::Center);
	mFrame->Add(mPausedLabel.get());
}

void CPausedState::Cleanup()
{
	mFrame.reset();
	mPausedLabel.reset();

	gEngine->RemoveFont(mFont);
	gEngine->UnpauseAutoUpdates();
}

// Temporarily transition to another state
void CPausedState::Pause()
{

}
void CPausedState::Resume()
{

}

// Game loop actions
void CPausedState::HandleEvents(CGameStateHandler* game)
{
	if(gEngine->KeyHit(KEY_PAUSE))
	{
		game->PopState();
	}
}
void CPausedState::Update(CGameStateHandler* game)
{
	mDelta = gEngine->Timer();
}
void CPausedState::Draw(CGameStateHandler* game)
{
	mFrame->Draw();
	gEngine->DrawScene();
}