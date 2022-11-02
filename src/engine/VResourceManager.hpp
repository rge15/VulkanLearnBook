#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <utilities/concepts.hpp>
#include "VKObjects/Resources/VShader.hpp"

namespace Graphics
{

	class VResourceManager
	{
		template < GraphicResource T >
		using ResourceMap = Map< JoyID, UniqPtr< T >>;
		//Empezar con el mapa de cosas de recursos
		private:
			//This will be a tuple probably
			ResourceMap< VShader > _shaderMap {};

			//TODO [1] : Use metaprog with tagdispatching for the template overloading
			//TODO : Create a VPipeline object that contains a VKRenderPass & VKPipelineLayout  & VKPipeline

			//Base template definition
			template <GraphicResource GraphSrc, typename... params>
			UniqPtr<GraphSrc>
			addGraphicResource( params&&... p_params ) noexcept;

		public:
			VResourceManager() noexcept = default;
			~VResourceManager() noexcept = default;

			template <GraphicResource GraphSrc, typename... params>
			Tuple< JoyID, GraphSrc& >
			loadGraphicResource( params&&... p_params ) noexcept;


	};
}

#include "VResourceManager.tpp"