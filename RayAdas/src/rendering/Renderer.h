#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
namespace RayAdas {



	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};


}