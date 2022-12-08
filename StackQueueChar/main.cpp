#include "Scenes.h"

using namespace nScene;

/*
문제점
씬 교체(삭제)가 제대로 되지 않음 ( 기말 끝나고 개선할 것 )
*/

int main() {
	ConsoleEngine engine;

	engine.Run<STACKQUEUE>(L"Stack & Queue!");

	engine.Release();

	return 0;
}