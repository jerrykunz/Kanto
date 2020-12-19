#include "knpch.h"
#include "Kanto/LayerStack.h"

namespace Kanto {

	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			//layer->OnDetach();
			delete layer;
		}
	}

	//emplace pushes before the first one
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_LayerInsert, layer);
	}

	//emplace_back pushes after the last one
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			//layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			//overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}