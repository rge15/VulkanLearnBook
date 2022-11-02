#pragma once
#include <utilities/config.hpp>
#include <utilities/TypeAliases.hpp>


namespace Graphics::Resource
{

	class BaseResource
	{
	private:
		inline static JoyID _srcIds { 0 };

		JoyID _ID { _srcIds++ };

	public:
		BaseResource(/* args */) = default;
		~BaseResource() = default;

		JoyID
		getResourceID() const noexcept
		{
			return _ID;
		};
	};

}