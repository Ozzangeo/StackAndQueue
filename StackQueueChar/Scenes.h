#ifndef __SCENES__
#define __SCENES__

#include "GameObjects.h"

namespace nScene {
	class STACKQUEUE : public Scene {
		void GameObjects() override;
		void Work() override;
	};
}

#endif // !__SCENES__

