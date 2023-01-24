#pragma once
#include <utilities/config.hpp>
#include <utilities/assertMacros.hpp>
#include <vulkan/vulkan.h>
#include <engine/VKObjects/Helpers/GetVKObjects.hpp>
#include <utilities/graphicsInclude.hpp>

namespace Graphics::Manager
{
	struct SwapchainInfo
	{
		VkSurfaceCapabilitiesKHR _surfaceCapabilities	{};
		std::vector<VkSurfaceFormatKHR> _formats		{};
		std::vector<VkPresentModeKHR> _presentModes		{};

		VkSurfaceFormatKHR 	_finalFormat		{};
		VkPresentModeKHR	_finalPresentMode	{};
		VkExtent2D			_swapchainExtent	{};


		/**
		 * 	@brief Checks if the physical device fits the swapchain and surface requeriments
		 * 
		 * 	@param p_phDevice Vulkan physical device to check with
		 * 	@param p_surface Surface to check with the properties
		*/
		bool
		checkSuitableDevice( VkPhysicalDevice& p_phDevice, VkSurfaceKHR& p_surface ) noexcept;

		/**
		 * 	@brief Set the swapchain final format configuration
		*/
		void
		getFinalFormat() noexcept;

		/**
		 * 	@brief Set the swapchain final present mode configuration
		*/
		void
		getFinalPresentMode() noexcept;

		/**
		 * 	@brief Set the swapchain final extent configuration
		*/
		void
		getFinalExtent( GLFWwindow& p_window ) noexcept;

		private:

		/**
		 * 	@brief Cleans all the swapchain support related info
		*/
		void
		cleanSupportInfo() noexcept;

	};
}