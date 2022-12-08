#ifndef __GAMEOBJECTS__
#define __GAMEOBJECTS__

#include "Components.h"

namespace nGameObject {
	class NullObject : public GameObject {
	private:
		void Components() override {}
	};

	class StackBar : public GameObject {
	private:
		void Components() override;
		void Work() override;
	};
	class QueueBar : public GameObject {
	private:
		void Components() override;
		void Work() override;
	};

	class Stack : public GameObject {
	private:
		void Components() override;
		void Work() override;
	};
	class Queue : public GameObject {
	private:
		void Components() override;
		void Work() override;
	};

	class TextObject : public GameObject {
	private:
		void Components() override;
		void Work() override;
	};
	class System : public GameObject {
	private:
		void Components() override;
		void Work() override;
	};
}

#endif // !__GAMEOBJECTS__

