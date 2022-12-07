#include "Scenes.h"

using namespace nScene;

void STACKQUEUE::GameObjects() {
	AddGameObject<GameObjects::Camera>(L"Camera", Tag_Camera);
	AddGameObject<nGameObject::Stack>(L"Stack", Tag_Stack);
	AddGameObject<nGameObject::Queue>(L"Queue", Tag_Queue);
	AddGameObject<nGameObject::TextObject>(L"Text", Tag_Text);
	AddGameObject<nGameObject::System>(L"System", Tag_System);
}

void STACKQUEUE::Work() {
	Color color;
	color.SetColor({ 0x4B, 0x53, 0x2B }, 0);
	color.SetColor({ 0x6F, 0x90, 0x3A }, 1);
	color.SetColor({ 0x4D, 0xA5, 0xA7 }, 2);
	color.SetColor({ 0x2C, 0x43, 0x1E }, 3);

	color.SetColor({ 255, 255, 255 }, 15);

	auto* camera = GetGameObject<GameObjects::Camera>(Tag_Camera)->GetComponent<Components::Camera>();
	auto* stack = GetGameObject<nGameObject::Stack>(Tag_Stack);
	auto* queue = GetGameObject<nGameObject::Queue>(Tag_Queue);

	camera->SetCameraScale(8, 16);
	camera->SetCameraSize({ 96, 28 });
	
	*stack->pos = Vector3f(10, 10, 1);
	*queue->pos = Vector3f(-10, 10, 1);
}
