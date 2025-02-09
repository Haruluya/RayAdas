#pragma once

#include "rendering/RendererAPI.h"
#include "rendering/VertexArray.h"

namespace RayAdas {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const SRef<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
		virtual void DrawLines(const SRef<VertexArray>& vertexArray, uint32_t vertexCount) override;

		virtual void SetLineWidth(float width) override;
	};


}