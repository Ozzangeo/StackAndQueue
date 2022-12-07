#ifndef __COMPONENTS__
#define __COMPONENTS__

#include "stdafx.h"
#include "Scenes.h"

using namespace Components;

enum Tags {
	Tag_Camera,
	Tag_StackBar,
	Tag_QueueBar,
	Tag_Stack,
	Tag_Queue,
	Tag_Text,
	Tag_System
};

namespace nComponent {
	class Bar : public Component {
	private:
		void Update() override;

	public:
		EnumColor color;
		WCHAR text = L' ';
	};

	class StackBar : public Component {
	private:
		int count = 0;

		void Update() override;
		void Remove() override;

	public:
		vector<Bar*> bars;
		stack<WCHAR> texts;

		void SetSize(int size);
	};
	class QueueBar : public Component {
	private:
	private:
		int count = 0;

		void Update() override;
		void Remove() override;

	public:
		vector<Bar*> bars;
		queue<WCHAR> texts;
		
		void SetSize(int size);
	};

	class Text : public Component {
	private:
		bool isStart = false;

		void Awake() override;
		void Update() override;

	public:
		wstring text;
		wstring targetText;

		void SetText(wstring text);
	};
	class System : public Component {
	private:
		SceneManager* manager = nullptr;

		Audio* audio = nullptr;
		StackBar* stackBar = nullptr;
		QueueBar* queueBar = nullptr;
		Text* text = nullptr;
		std::chrono::system_clock::time_point start;

		const int MAX_SIZE = 8;
		float time = 0.0f;

		bool isSetup = false;
		bool isDownKey = false;
		bool choice = false;

		void Start() override;
		void Update() override;
		void Remove() override;
	};
}

#endif // !__COMPONENTS__

