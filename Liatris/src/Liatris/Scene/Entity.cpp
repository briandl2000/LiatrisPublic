#include "liapch.h"
#include "Entity.h"

namespace Liatris
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle)
		, m_Scene(scene)
	{
	}

}