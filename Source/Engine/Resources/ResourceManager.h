#pragma once
#include "Resource.h"
#include "Core/StringHelper.h"
#include "Core/Singleton.h"
#include <string>
#include <map>
#include <iostream>

namespace shovel
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		void Clear()
		{
			m_resources.clear();
		}

		template <typename T, typename ... Args>
		res_t<T> Get(const std::string& name, Args&& ... args);

		template <typename T, typename ... Args>
		res_t<T> GetWithID(const std::string& id, const std::string& name, Args&& ... args);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};
	template<typename T, typename ... Args>
	res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args)
	{
		return GetWithID<T>(name, name, std::forward<Args>(args)...); // Use the ID version to ensure consistency
	}

	template<typename T, typename ... Args>
	res_t<T> ResourceManager::GetWithID(const std::string& id,const std::string& name, Args&& ... args)
	{
		std::string key = shovel::toLower(id);

		auto iter = m_resources.find(key);

		if (iter != m_resources.end())
		{
			auto base = iter->second;
			auto resource = std::dynamic_pointer_cast<T>(base);

			if (!resource)
			{
				std::cerr << "Resource type mismach" << key << std::endl;
				return res_t<T>();
			}
			return resource;
		}

		res_t<T> resource = std::make_shared<T>();
		if (!(resource->Load(name, std::forward<Args>(args)...)))
		{
			std::cerr << "Failed to load resource: " << name << std::endl;
			return res_t<T>();
		}
		m_resources[key] = resource;

			return resource;
	}
	inline ResourceManager& Resources() 
	{
		return ResourceManager::Instance();
	}

}