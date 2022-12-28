#include "Components.h"

using namespace std;
using namespace Components;
using namespace nComponent;

void Bar::Update() {
	graphic.Fill((*gameobject->pos + Vector3f(-2, -0, -1)), (*gameobject->pos + Vector3f(2, 0, -1)), color);
	graphic.Text((*gameobject->pos), text, color + 15);
}

void StackBar::Update() {
	wstring text = to_wstring(texts.size()) + L"/" + to_wstring(count);

	graphic.Text(*gameobject->pos + Vector3f(-1, 1, 0), text);
	graphic.Text(*gameobject->pos + Vector3f(-2, (static_cast<float>(count) * -2.0f) + 1, 0), L"stack");
}
void StackBar::SetSize(int size) {
	if (size < 0) { return; }
	for (auto* bar : bars) {
		scene->RemoveGameObject(bar->GetGameObject());
	}
	bars.clear();

	for (int i = 0, s = texts.size(); i < s; i++) { texts.pop(); }

	for (int i = 0; i < size; i++) {
		auto* object = scene->AddGameObject<nGameObject::StackBar>(L"StackBar" + to_wstring(i), Tag_StackBar);
		*object->pos = *gameobject->pos - Vector3f(0, i * 2.0f, 0);

		auto* bar = object->GetComponent<Bar>();
		bar->color = Color_Blue;
		bars.push_back(bar);
	}
	count = size;
}
void StackBar::Remove() {}

void QueueBar::Update() {
	wstring text = to_wstring(texts.size()) + L"/" + to_wstring(count);
	graphic.Text(*gameobject->pos + Vector3f(-1, 1, 0), text);
	graphic.Text(*gameobject->pos + Vector3f(-2, (static_cast<float>(count) * -2.0f) + 1, 0), L"queue");
}
void QueueBar::Remove() {}
void QueueBar::SetSize(int size) {
	if (size < 0) { return; }
	for (auto* bar : bars) {
		scene->RemoveGameObject(bar->GetGameObject());
	}
	bars.clear();

	for (int i = 0, s = texts.size(); i < s; i++) { texts.pop(); }

	for (int i = 0; i < size; i++) {
		auto* object = scene->AddGameObject<nGameObject::StackBar>(L"StackBar" + to_wstring(i), Tag_StackBar);
		*object->pos = *gameobject->pos - Vector3f(0, i * 2.0f, 0);

		auto* bar = object->GetComponent<Bar>();
		bar->color = Color_Green;
		bars.push_back(bar);
	}
	count = size;
}

void Text::Awake() {
	srand(static_cast<UINT>(std::time(NULL)));
}
void Text::Update() {
	graphic.Text(Vector3f(-(targetText.length() * 0.5f), -10, 0), targetText, Color_SkyBlue + 15);
	graphic.Text(Vector3f(-(targetText.length() * 0.5f), -9, 0), L'^');

	graphic.Text(Vector3f(-(text.length() * 0.5f), -13, 0), text);
}
void Text::SetText(wstring text) {
	this->text = text;

	do { random_shuffle(text.begin(), text.end()); } while (this->text == text);

	this->targetText = text;
	isStart = true;
}

void System::Start() {
	manager = &SceneManager::GetInstance();

	stackBar = scene->GetGameObject<nGameObject::Stack>(Tag_Stack)->GetComponent<StackBar>();
	queueBar = scene->GetGameObject<nGameObject::Queue>(Tag_Queue)->GetComponent<QueueBar>();
	text = scene->GetGameObject<nGameObject::TextObject>(Tag_Text)->GetComponent<Text>();
	audio = gameobject->AddComponent<Audio>();

	wifstream file(resultPath);

	wstring text;
	getline(file, text);
	wstringstream ss(text);

	getline(ss, text, L':');
	getline(ss, text, L':');

	try { bestTime = (stoi(text) << 16) * 0.000001f; }
	catch (exception e) { bestTime = 100.0f; }

	file.close();

	audio->LoadAudio("Music/pop.mp3");
	audio->LoadAudio("Music/push.mp3");
	audio->LoadAudio("Music/background.mp3");
	audio->LoadAudio("Music/newRecord.mp3");
}
void System::Update() {
	if (!isSetup && keyboard.isKeyDown(KeyCode_ENTER)) {
		stackBar->SetSize(MAX_SIZE);
		queueBar->SetSize(MAX_SIZE);
		
		start = std::chrono::system_clock::now();
		audio->PlayAudio(3, true);

		isSetup = true;
	}

	if (keyboard.isKeyDown(KeyCode_ESC)) {
		audio->CloseAudio(1);
		audio->CloseAudio(2);
		audio->CloseAudio(3);
		audio->CloseAudio(4);

		manager->StopEngine();
	}
	if (keyboard.isKeyDown(KeyCode_F5)) { manager->ChangeScene<nScene::STACKQUEUE>(); }

	if (text->targetText == text->text) {
		if (isWrite) { graphic.Text(Vector3f(-48, 13, 0), L"진행시간:" + to_wstring(time) + L"초", Color_Red + 15); }
		else { graphic.Text(Vector3f(-48, 13, 0), L"진행시간:" + to_wstring(time) + L"초"); }

		if ((time < bestTime && !isWrite) || bestTime == 0.0f) {
			audio->PlayAudio(4);

			wofstream file(resultPath);

			file << L"최고기록:" << to_wstring(static_cast<int>(time * 1000000) >> 16) << L"초";

			file.close();
			isWrite = true;
		}
	}
	else if(isSetup) {
		
		if (choice) { graphic.Text({ 10, 12, 0 }, L'^'); }
		else { graphic.Text({ -10, 12, 0 }, L'^'); }

		if ((keyboard.isKeyDown(KeyCode_LEFT) || keyboard.isKeyDown((KeyCode)'A')) || (keyboard.isKeyDown(KeyCode_RIGHT) || keyboard.isKeyDown((KeyCode)'D'))) { choice = !choice; }
		// 삽입
		if ((keyboard.isKeyDown(KeyCode_DOWN) || keyboard.isKeyDown((KeyCode)'S') || keyboard.isKeyDown(KeyCode_SPACE)) && isDownKey) {
			if (choice) {
				if (static_cast<int>(stackBar->texts.size()) < MAX_SIZE)
				{
					stackBar->bars[stackBar->texts.size()]->text = text->targetText[0];
					stackBar->texts.push(text->targetText[0]);
					text->targetText.erase(0, 1);
					audio->PlayAudio(2);
				}
			}
			else {
				if (static_cast<int>(queueBar->texts.size()) < MAX_SIZE)
				{
					queueBar->bars[queueBar->texts.size()]->text = text->targetText[0];
					queueBar->texts.push(text->targetText[0]);
					text->targetText.erase(0, 1);
					audio->PlayAudio(2);
				}
			}

			isDownKey = false;
		}
		// 삭제
		else if ((keyboard.isKeyDown(KeyCode_UP) || keyboard.isKeyDown((KeyCode)'W')) && isDownKey) {
			if (choice) {
				if (stackBar->texts.size() > 0)
				{
					text->targetText += stackBar->texts.top();
					stackBar->texts.pop();

					stackBar->bars[stackBar->texts.size()]->text = L' ';
					audio->PlayAudio(1);
				}
			}
			else {
				if (queueBar->texts.size() > 0)
				{
					text->targetText += queueBar->texts.front();
					queueBar->texts.pop();

					queueBar->bars[0]->text = L' ';
					for (int i = 0; i < MAX_SIZE - 1; i++) { queueBar->bars[i]->text = queueBar->bars[i + 1]->text; }
					queueBar->bars[MAX_SIZE - 1]->text = L' ';
					audio->PlayAudio(1);
				}
			}

			isDownKey = false;
		}
		else { isDownKey = true; }

		time = duration<float>(std::chrono::system_clock::now() - start).count();
		graphic.Text(Vector3f(-48, 13, 0), L"진행시간:" + to_wstring(time) + L"초");
	}
	graphic.Text(Vector3f(-48, 12, 0), L"최고기록:" + to_wstring(bestTime) + L"초");
	graphic.Text(Vector3f(-48, -14, 0), L"LEFT(A) or RIGHT(D) : 자료구조 전환");
	graphic.Text(Vector3f(-48, -13, 0), L"DOWN(S, SPACE) : Push");
	graphic.Text(Vector3f(-48, -12, 0), L"UP(W) : Pop");
	graphic.Text(Vector3f(-48, -11, 0), L"ENTER : 시작");
	graphic.Text(Vector3f(-48, -10, 0), L"F5 : 재시작");
}

void System::Remove() {}
