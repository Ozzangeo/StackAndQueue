#include "Scenes.h"

using namespace nScene;

int main() {
	ConsoleEngine engine;

	engine.Run<STACKQUEUE>(L"Stack & Queue!");

	engine.Release();

	return 0;
}