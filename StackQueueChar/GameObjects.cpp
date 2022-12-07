#include "GameObjects.h"

using namespace nGameObject;

void StackBar::Components() {
	AddComponent<nComponent::Bar>();
}
void StackBar::Work() {
	auto* bar = GetComponent<nComponent::Bar>();
	bar->color = Color_Blue;
}

void QueueBar::Components() {
	AddComponent<nComponent::Bar>();
}
void QueueBar::Work() {
	auto* bar = GetComponent<nComponent::Bar>();
	bar->color = Color_Green;
}

void Stack::Components() {
	AddComponent<nComponent::StackBar>();
}
void Stack::Work() {
}
void Queue::Components() {
	AddComponent<nComponent::QueueBar>();
}
void Queue::Work() {
}

void TextObject::Components() {
	AddComponent<nComponent::Text>();
}
void TextObject::Work() {
	auto* text = GetComponent<nComponent::Text>();

	srand(static_cast<UINT>(std::time(NULL)));

	switch (rand() % 4)
	{
	case 0:	{ text->SetText(L"queue is free!");   } break;
	case 1:	{ text->SetText(L"stack is free!");   } break;
	case 2:	{ text->SetText(L"doby is free!");    } break;
	case 3: { text->SetText(L"stack and queue!"); } break;
	}
}

void System::Components() {
	AddComponent<nComponent::System>();
}
void System::Work() {
}
