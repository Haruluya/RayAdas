#include "AppTest.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace RayAdasApp {

	AppTest::AppTest()
		: Layer("AppTest"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
	{
	}

	void AppTest::OnAttach()
	{
		RA_PROFILE_FUNCTION();

		m_CheckerboardTexture = RayAdas::Texture2D::Create("resources/textures/haruluya.jpg");

		RayAdas::FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = RayAdas::Framebuffer::Create(fbSpec);
	}

	void AppTest::OnDetach()
	{
		RA_PROFILE_FUNCTION();
	}

	void AppTest::OnUpdate(RayAdas::Timestep ts)
	{
		RA_PROFILE_FUNCTION();

		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		RayAdas::RenderUtils::ResetStats();
		{
			RA_PROFILE_SCOPE("Renderer Prep");
			RayAdas::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RayAdas::RenderCommand::Clear();
		}

		{
			static float rotation = 0.0f;
			rotation += ts * 50.0f;

			RA_PROFILE_SCOPE("Renderer Draw");
			RayAdas::RenderUtils::BeginScene(m_CameraController.GetCamera());
			RayAdas::RenderUtils::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
			RayAdas::RenderUtils::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			RayAdas::RenderUtils::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
			RayAdas::RenderUtils::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
			RayAdas::RenderUtils::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
			RayAdas::RenderUtils::EndScene();

			RayAdas::RenderUtils::BeginScene(m_CameraController.GetCamera());
			for (float y = -5.0f; y < 5.0f; y += 0.5f)
			{
				for (float x = -5.0f; x < 5.0f; x += 0.5f)
				{
					glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
					RayAdas::RenderUtils::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
				}
			}
			RayAdas::RenderUtils::EndScene();
			m_Framebuffer->Unbind();
		}
	}

	void AppTest::OnImGuiRender()
	{
		RA_PROFILE_FUNCTION();

		// Note: Switch this to true to enable dockspace
		static bool dockingEnabled = true;
		if (dockingEnabled)
		{
			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;


			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;


			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					// Disabling fullscreen would allow the window to be moved to the front of other windows, 
					// which we can't undo at the moment without finer window depth/z control.
					//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

					if (ImGui::MenuItem("Exit"))RayAdas::Application::Get().Close();
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			ImGui::Begin("Settings");

			auto stats =RayAdas::RenderUtils::GetStats();
			ImGui::Text("RenderUtils Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

			ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
			uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
			ImGui::Image((void*)textureID, ImVec2{ 1280, 720 });
			ImGui::End();

			ImGui::End();
		}
		else
		{
			ImGui::Begin("Settings");

			auto stats =RayAdas::RenderUtils::GetStats();
			ImGui::Text("RenderUtils Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

			ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

			uint32_t textureID = m_CheckerboardTexture->GetRendererID();
			ImGui::Image((void*)textureID, ImVec2{ 1280, 720 });
			ImGui::End();
		}
	}

	void AppTest::OnEvent(RayAdas::Event& e)
	{
		m_CameraController.OnEvent(e);
	}
}