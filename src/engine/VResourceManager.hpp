#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <utilities/concepts.hpp>
#include "VKObjects/Resources/VShader.hpp"
#include <engine/MetaProg/mpUtils.hpp>

namespace Graphics
{

	class VResourceManager
	{
		template < GraphicResource T >
		using ResourceMap = Map< JoyID, UniqPtr< T >>;
		
		private:
			VkDevice& _device;
			//This will be a tuple probably
			Tuple< ResourceMap< VShader > > _resources {};

			//TODO [1] : Use metaprog with tagdispatching for the template overloading
			//-----------------------------------------------------------------
			//Base template declaration
			//-----------------------------------------------------------------
			template <GraphicResource GraphSrc, typename... params>
			UniqPtr<GraphSrc>
			addGraphicResource( params&&... p_params ) noexcept;

			//-----------------------------------------------------------------
			//Template overloading with TagDispatching declarations
			//-----------------------------------------------------------------
			inline UniqPtr<VShader>
			addGraphicResource( MP::value_type<VShader>, std::string&& p_shaderPath, VShader::ShaderType p_shaderType ) noexcept;


		public:
			VResourceManager( VkDevice& p_deviceOwner ) noexcept;
			~VResourceManager() noexcept = default;

			template <GraphicResource GraphSrc, typename... params>
			Tuple< JoyID, GraphSrc& >
			loadGraphicResource( params&&... p_params ) noexcept;


	};
}

#include "VResourceManager.tpp"