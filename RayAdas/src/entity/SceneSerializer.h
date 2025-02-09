#pragma once

#include "Scene.h"

namespace RayAdas {

	class SceneSerializer
	{
	public:
		SceneSerializer(const SRef<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);
	private:
		SRef<Scene> m_Scene;
	};

}