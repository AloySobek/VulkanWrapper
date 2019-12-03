/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkClassVulkan.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:59:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/27 13:55:32 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_VULKAN_HPP
# define VK_CLASS_VULKAN_HPP

typedef struct	instanceInfo_s
{
	u_int32_t	availableInstanceLayersCount	= 0;
	u_int32_t	selectedInstanceLayersCount		= 0;

	u_int32_t	availableInstanceExtensionsCount	= 0;
	u_int32_t	selectedInstanceExtensionsCount		= 0;

	std::vector<VkLayerProperties>		pAvailableInstanceLayers;
	std::vector<const char *>			ppAvailableInstanceLayersNames;

	std::vector<VkExtensionProperties>	pAvailableInstanceExtensions;
	std::vector<const char *>			ppAvailableInstanceExtensionsNames;

	VkApplicationInfo		sAppCreateInfo		= {};

	VkInstanceCreateInfo	sInstanceCreateInfo	= {};
	VkInstance				instanceObject		= VK_NULL_HANDLE;
}				instanceInfo_t;

typedef struct	surfaceInfo_s
{
	;
}				surfaceInfo_t;

class Vulkan
{
	public:
		instanceInfo_t instanceProperties;
		/*
		** Window surface choosing and setup
		*/
		VkSurfaceKHR				surfaceObj					= VK_NULL_HANDLE;
		VkSurfaceCapabilitiesKHR	capabilities				= {};
		uint32_t					khrFormatsCount				= 0;
		VkSurfaceFormatKHR			*pKHRFormats				= nullptr;
		uint32_t					khrPresentModesCount		= 0;
		VkPresentModeKHR			*pKHRPresentModes			= nullptr;
		/*
		** Physical Device finding and setup ----------------------------------------------
		*/
		VkPhysicalDevice			physicalDeviceObj							= VK_NULL_HANDLE;
		u_int32_t					availablePhysicalDeviceLayersCount			= 0;
		u_int32_t					selectedPhysicalDeviceLayersCount			= 0;
		VkLayerProperties			*pAvailablePhysicalDeviceLayers				= nullptr;
		const char					**ppAvailablePhysicalDeviceLayersNames		= nullptr;
		u_int32_t					selectedPhysicalDeviceExtensionsCount		= 0;
		u_int32_t					availablePhysicalDeviceExtensionsCount		= 0;
		VkExtensionProperties		*pAvailablePhysicalDeviceExtensions			= nullptr;
		const char					**ppAvailablePhysicalDeviceExtensionsNames	= nullptr;
		VkPhysicalDevice			*pAvailablePhysicalDevices					= nullptr;
		VkPhysicalDeviceFeatures	sPhysicalDeviceFeatures						= {};
		VkPhysicalDeviceProperties	sPhysicalDeviceProperties					= {};
		u_int32_t					availablePhysicalDeviceCount				= 0;
		/*
		** Finding and selecting queue families and particular queue we need --------------
		*/
		u_int32_t				availablePhysicalDeviceQueuesCount		= 0;
		VkQueueFamilyProperties	*pAvailablePhysicalDeviceQueuesFamily 	= nullptr;
		VkQueue					graphicQueueFamily						= VK_NULL_HANDLE;
		VkDeviceQueueCreateInfo sDeviceGraphicQueueFamilyCreateInfo		= {};
		int32_t					graphicQueueFamilyIndex					= -1;
		VkQueue					presentQueueFamily						= VK_NULL_HANDLE;
		VkDeviceQueueCreateInfo sDevicePresentQeueuFamilyCreateInfo		= {};
		int32_t					presentQueueFamilyIndex					= -1;
		VkBool32				presentQueueFamilySupport				= false;
		uint32_t				deviceQueueFamilyCreateInfoCount		= 0;
		VkDeviceQueueCreateInfo *psDeviceQueueFamilyCreateInfoList		= nullptr;
		/*
		** Create logical device and setup it --------------------------------------------
		*/
		VkDevice				deviceObj				= VK_NULL_HANDLE;
		VkDeviceCreateInfo		sCreateDeviceInfo		= {};
		/*
		** Create swap chain and setup it
		*/
		VkSurfaceFormatKHR			sBestSwapChainFormat		= {};
		VkPresentModeKHR			sBestSwapChainPresentMode	= {};
		VkExtent2D					sBestSwapChainResolution	= {};
		uint32_t					imageCount					= 0;
		VkSwapchainCreateInfoKHR	sSwapChainCreateInfo		= {};
		VkSwapchainKHR				swapchainObj				= VK_NULL_HANDLE;
		VkImage						*pImageObjList				= nullptr;
		/*
		** Create Image view and setup it
		*/
		VkImageView	*pImageViewList	= nullptr;

		VkRenderPass		renderPass = VK_NULL_HANDLE;

		VkPipelineLayout	layoutObj = VK_NULL_HANDLE;

		VkPipeline			pipelineObj = VK_NULL_HANDLE;

		std::vector<VkFramebuffer> swapChainFrameBuffers;

		VkCommandPool		commandPool;

		std::vector<VkCommandBuffer> commandBuffer;

		VkSemaphore		imageAvailableSemaphore;
		VkSemaphore		renderFinishedSemaphore;

		int				error;

		Vulkan(): error(false), presentQueueFamilyIndex(-1) {}
		void run(GLFWwindow *pWindow);

		void vkSetupAppInfo				();
		void vkSetupInstanceLayers		();
		bool vkIsLayerSuitable			(VkLayerProperties sLayer);
		void vkSetupInstanceExtensions	();
		bool vkIsExtensionSuitable		(VkExtensionProperties sExtension);
		void vkSetupInstanceCreateInfo	();
		void vkCreateInstanceObj		();

		void vkCreateSurface(GLFWwindow *pWindow);

		void vkChoosePhysicalDeviceObj		();
		void vkCheckSwapChainSupport		();
		bool vkIsDeviceSuitable				(VkPhysicalDevice physicalDevice);
		void vkSetupPhysicalDeviceExtensions();
		void vkSetupPhysicalDeviceLayers	();
		void vkQueryPhysicalDeviceQueue		();

		void vkSetupDeviceQueueCreateInfo	(float queuePriority);
		void vkSetupDeviceCreateInfo		();
		void vkCreateNewDevice				();

		void vkSetupSwapChain			();
		void vkSetupSwapChainCreateInfo	();
		void vkCreateSwapChain			();

		VkImageViewCreateInfo 	vkSetupImageViewCreateInfo	(VkImage image);
		void 					vkCreateNewImageView			();

		void	vkCreateNewRenderPass();

		void 				vkCreateNewGraphicsPipeline();
		std::vector<char> 	vkReadFile				(const char *filename);
		VkShaderModule		vkCreateNewShaderModule	(const std::vector<char> &code);

		void 				vkCreateNewFrameBuffer();

		void				vkCreateNewCommandPool();

		void				vkCreateNewCommandBuffers();

		void 				vkCreateNewSemaphore();

		void				vkDrawFrame();

		void				fbCleanUp();
};

#endif