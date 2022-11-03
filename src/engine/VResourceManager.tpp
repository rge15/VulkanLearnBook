

namespace Graphics
{
	
	template <GraphicResource GraphSrc, typename... params>
	Tuple< JoyID, GraphSrc& >
	VResourceManager::loadGraphicResource( params&&... p_params ) noexcept
	{
		auto rsc = addGraphicResource<GraphSrc>( std::forward<params>(p_params)... );
		const auto id = rsc.get()->getResourceID();
		
		auto& map = std::get< ResourceMap<GraphSrc> >( _resources );
		map[id] = std::move(rsc);


		return { id, *map[id] };
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	UniqPtr<VShader>
	VResourceManager::addGraphicResource(
		MP::value_type<VShader>,
		std::string&& p_shaderPath,
		VShader::ShaderType p_shaderType
	) noexcept
	{
		return std::make_unique<VShader>( _device, p_shaderPath, p_shaderType );
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	template <GraphicResource GraphSrc, typename... params>
	UniqPtr<GraphSrc>
	VResourceManager::addGraphicResource( params&&... p_params ) noexcept
	{
		return addGraphicResource( MP::value_type<GraphSrc>{}, std::forward<params>(p_params)... );
	}

}