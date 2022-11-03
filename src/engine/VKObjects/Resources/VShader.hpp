#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/assertMacros.hpp>
#include "BaseResource.hpp"

namespace Graphics::Resource
{

	class VShader : public BaseResource
	{
		public:
			using ShaderType = VkShaderStageFlagBits;

		private:
			//Esto alomejor no es const
			const VkDevice& _ownerDevice;
			//El modulo del shader
			VkShaderModule _shaderModule;
			//Shader Type 
			ShaderType _shaderType;
			//Shader code
			Vector<char> _code;
			//Shader Module Info
			VkShaderModuleCreateInfo _info;
			//Shader into pipeline stage info
			VkPipelineShaderStageCreateInfo _stageInfo;

		public:

			VShader(VkDevice& p_ownerDevice, std::string& p_shaderPath, ShaderType p_shaderType ) noexcept;

			~VShader() noexcept;

		private:

			void
			readFile( std::string& p_shaderPath ) noexcept;

			void
			initCreationInfo() noexcept;

			void
			initPipelineStageInfo() noexcept;

			void
			createShader() noexcept;

	};

}