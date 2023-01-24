#include "VShader.hpp"

namespace Graphics::Resource
{

	VShader::VShader(VkDevice& p_ownerDevice, std::string& p_shaderPath, ShaderType p_shaderType ) noexcept
	: _ownerDevice { p_ownerDevice }, _shaderType { p_shaderType }
	{
		readFile( p_shaderPath );
		initCreationInfo();
		createShader();
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	VShader::~VShader() noexcept
	{
		vkDestroyShaderModule( _ownerDevice, _shaderModule, nullptr );
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VShader::readFile( std::string& p_shaderPath ) noexcept
	{
		std::ifstream file( p_shaderPath, std::ios::ate | std::ios::binary | std::ios::in );
	
		ASSERT( file.is_open(), "The shader could not be opened" )

		size_t fileSize = (size_t)file.tellg();

		Vector<char> code;

		code.resize( fileSize );
		_codeInt.resize( fileSize>>2 );

		file.seekg(0);
		file.read( code.data(), fileSize );
	
		memcpy(_codeInt.data(), code.data(), fileSize);

		file.close();
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VShader::initCreationInfo() noexcept
	{
		_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		_info.pNext = nullptr;
		_info.flags = 0;
		_info.codeSize = _codeInt.size() << 2;
		_info.pCode = _codeInt.data();
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VShader::createShader() noexcept
	{
		VkResult shaderCreationResult = vkCreateShaderModule( _ownerDevice, &_info, nullptr, &_shaderModule );
	
		ASSERT( (shaderCreationResult == VK_SUCCESS), "ShaderModule Creation failed ;c")
	
		initPipelineStageInfo();
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VShader::initPipelineStageInfo() noexcept
	{
		_stageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		_stageInfo.pNext = nullptr;
		_stageInfo.pName = "main";
		_stageInfo.module = _shaderModule;
		_stageInfo.stage = _shaderType;
		_stageInfo.flags = 0;

		//Aquí la gracia
		_stageInfo.pSpecializationInfo = nullptr;
	}

}