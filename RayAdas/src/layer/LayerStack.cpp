#include "RApch.h"
#include "LayerStack.h"

namespace RayAdas {

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	//void LayerStack::PopLayer(Layer* layer)
	//{
	//	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	//	if (it != m_Layers.end())
	//	{
	//		m_Layers.erase(it);
	//		m_LayerInsertIndex--;
	//		layer->OnDetach();
	//	}
	//}

	void LayerStack::PopLayer(Layer* layer)
	{
		//auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		//if (it != m_Layers.end())
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			layer->OnDetach();
				m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		//auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			overlay->OnDetach();
			m_Layers.erase(it);

		}
	}

}