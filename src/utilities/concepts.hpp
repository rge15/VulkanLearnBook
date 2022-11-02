#pragma once
#include <concepts>
#include <type_traits>
#include <engine/VKObjects/Resources/BaseResource.hpp>


using namespace Graphics::Resource;

template <class T>
concept GraphicResource = 
	std::is_base_of_v< BaseResource, T >;