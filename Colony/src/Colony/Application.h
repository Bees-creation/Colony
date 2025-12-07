#pragma once

#include "Core.h"

namespace Colony
{
	class COLONY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
