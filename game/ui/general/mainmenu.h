#pragma once

#include "framework/stage.h"

namespace OpenApoc
{

class Form;

class MainMenu : public Stage
{
  private:
	sp<Form> mainmenuform;

  public:
	MainMenu();
	~MainMenu() override;
	// Stage control
	void begin() override;
	void pause() override;
	void resume() override;
	void finish() override;
	void eventOccurred(Event *e) override;
	void update() override;
	void render() override;
	bool isTransition() override;
};
}; // namespace OpenApoc
