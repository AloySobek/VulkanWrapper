/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:34:16 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 14:36:31 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_PHYSICAL_DEVICE_HPP
# define FB_CLASS_PHYSICAL_DEVICE_HPP

# include "firebreak.hpp"

class FbDevice
{
	public:
		FbDevice(VkDeviceCreateInfo info = {}, VkAllocationCallbacks allocation = {});
		FbDevice(VkAllocationCallbacks allocation) : FbDevice({}, allocation) { }

		virtual VkDevice				&getSelf()			{ assert(self); return (self); }
		virtual VkPhysicalDevice		&getPhysicalSelf()	{ assert(physicalSelf); return (physicalSelf); }
		virtual VkDeviceCreateInfo		&getCreateInfo()	{ return (sCreateInfo); }
		virtual VkAllocationCallbacks	&getAllocation()	{ return (sAllocation); }
		virtual int32_t					getErrorCode()		{ return (codeOfError); }

		virtual void create();
		virtual void destroy();

		virtual ~FbDevice() { destroy(); }

	protected:
		VkDevice				self			= VK_NULL_HANDLE;
		VkPhysicalDevice		physicalSelf	= VK_NULL_HANDLE;
		VkDeviceCreateInfo		sCreateInfo		= {};
		VkAllocationCallbacks	sAllocation		= {};

		int32_t codeOfError;
};

class FbDevice2 : public FbDevice
{
	public:
		FbDevice2() : FbDevice() { }

		VkPhysicalDeviceFeatures			*getFeatures();
		VkPhysicalDeviceProperties			*getProperties();
		VkPhysicalDeviceMemoryProperties	*getMemoryProperties();
		VkLayerProperties					*getLayers(uint32_t *size = nullptr);
		VkExtensionProperties				*getExtensions(uint32_t *size = nullptr);
		VkQueueFamilyProperties				*getQueueFamilyProperties(uint32_t *size = nullptr);

		void retrieveQueues();
		void attachPhysicalDevice(Instance &instance, uint32_t type);
		void pushQueue(int32_t type);
		void setLayers(const char **desiredLayers, uint32_t size);
		void setExtensions(const char **desiredExtensions, uint32_t size);

		bool setQueue(uint32_t type, VkExtent3D minImageTransferGranularity, uint32_t timestampValidBits, uint32_t queueCount, float priority);
		bool setPresentQueue(Surface &surface, VkExtent3D minImageTransferGranularity, uint32_t timestampValidBits, uint32_t queueCount, float priority);

		uint32_t *requireIndexArray();

	private:
		VkPhysicalDeviceFeatures			sFeatures			= {};
		VkPhysicalDeviceProperties			sProperties			= {};
		VkPhysicalDeviceMemoryProperties	sMemoryProperties	= {};

		VkLayerProperties		*pAvailableLayers			= nullptr;
		VkExtensionProperties	*pAvailableExtensions		= nullptr;
		VkQueueFamilyProperties	*pAvailableQueuesFamilies	= nullptr;

		uint32_t				availableLayersCount			= 0;
		uint32_t				availableExtensionsCount		= 0;
		uint32_t				availableQueuesFamiliesCount	= 0;

		bool isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size);
		bool isExtensionSuitable(VkExtensionProperties sExtensions, const char **desiredExtensions, uint32_t size);
		bool isQueueFamilySuitable(VkQueueFamilyProperties queueProperties, VkExtent3D minImageTransferGranularity, uint32_t timestampValidBits, uint32_t queueCount);
		bool isPhysicalDeviceSuitable(VkPhysicalDevice device, uint32_t type);
};

#endif