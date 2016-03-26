#include "vk_instance.hpp"

// TODO: Decide if need a constructor for enabling wsi extensions or if we can change this function call.
VulkanInstance::VulkanInstance(Logger_t & logger, Config_t & config) 
	: m_logger(logger)
	, m_config(config)
{
	std::string appName;
	m_config.Get("applicationName", appName);


	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = nullptr;
	appInfo.pApplicationName = appName.c_str();
	appInfo.applicationVersion = 0;
	appInfo.pEngineName = nullptr;
	appInfo.engineVersion = 0;
	appInfo.apiVersion = VK_API_VERSION;

	VkInstanceCreateInfo createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;
	createInfo.enabledExtensionCount = 0;
	createInfo.ppEnabledExtensionNames = nullptr;

	VkResult result;
	result = vkCreateInstance(&createInfo, nullptr, &m_instance);

#ifdef _DEBUG
	std::unique_ptr<LogEntry_t> entry(new LogEntry_t);
	entry->sender = "Vulkan";
	entry->level = LogLvl::inf;
	entry->entry << "Attempted to create VkInstance";
	entry->details << "Result: " << ToString(result);
	m_logger.Log(std::move(entry));
#endif

	if (result != VK_SUCCESS)
		throw VulkanException("vkCreateInstance() failed: " + ToString(result));
}

VulkanInstance::~VulkanInstance() {
	vkDestroyInstance(m_instance, nullptr);
}

VulkanDevice VulkanInstance::GetDevice() {
	uint32_t physicalDeviceCount = UINT32_MAX;
	VkPhysicalDevice* physicalDevices = new VkPhysicalDevice[physicalDeviceCount];

	VkResult result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);
#ifdef _DEBUG
	std::unique_ptr<LogEntry_t> entry(new LogEntry_t);
	entry->sender = "Vulkan";
	entry->level = LogLvl::inf;
	entry->entry << "Queried number of physical devices.";
	entry->details << "Result: " << ToString(result) << std::endl;
	entry->details << physicalDeviceCount << " physical devices";
	m_logger.Log(std::move(entry));
#endif

	if (result != VK_SUCCESS)
		throw VulkanException("");

	return VulkanDevice();
}
