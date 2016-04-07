#pragma once

namespace tle
{
	//The ILoadScreen allows you to define a load screen
	//that the engine can update to show progress of loading
	//There is no implementing class, therefore you must write your own
	class ILoadScreen
	{
	private:
		//The amount of items to be loaded
		int mLoadAmount;
		
		//The amount of items that have been loaded
		int mLoadProgress;

		//The current load action
		string mLoadMessage;

	public:
		//Used by the engine to update the load screen
		virtual void Update(float delta) = 0;

		//Used by the engine to set the load amount
		void SetLoadAmount(int loadAmount) { mLoadAmount = loadAmount; };

		//Gets the load amount
		int GetLoadAmount() { return mLoadAmount; };

		//Used by the engine to update the load progress
		void SetLoadProgress(int loadProgress) { mLoadProgress = loadProgress; };

		//Gets the load progress
		int GetLoadProgress() { return mLoadProgress; };

		//Used by the engine to pass the current load action being performed to the load screen
		void SetLoadMessage(const string& message) { mLoadMessage = message; };

		//Gets the load message
		string& GetLoadMessage() { return mLoadMessage; };
	};
}