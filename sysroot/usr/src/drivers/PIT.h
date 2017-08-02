#pragma once

#include <stddef.h>
#include <stdint.h>

#include "../common/kstdlib.h"

namespace Devices {
	class PIT {
		public:
			PIT();

			static bool initialized;
	};
}
