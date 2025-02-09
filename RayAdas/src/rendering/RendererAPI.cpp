#include "RApch.h"
#include "rendering/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace RayAdas {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	URef<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    RA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLRendererAPI>();
		}

		RA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}