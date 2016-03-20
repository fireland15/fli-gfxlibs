#pragma once

#include "vk_tostrings.hpp"

std::string ToString(VkResult result) {
	std::string ret = "";

	switch (result) {
	case VK_SUCCESS:
		ret = "success";
		break;
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		ret = "out of host memory";
		break;
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		ret = "out of device memory";
		break;
	case VK_ERROR_INITIALIZATION_FAILED:
		ret = "initialization failed";
		break;
	case VK_ERROR_LAYER_NOT_PRESENT:
		ret = "layer not present";
		break;
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		ret = "extension not present";
		break;
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		ret = "incompatible driver";
		break;
	case VK_ERROR_FEATURE_NOT_PRESENT:
		ret = "feature not present";
		break;
	case VK_ERROR_TOO_MANY_OBJECTS:
		ret = "too many objects";
		break;
	case VK_ERROR_DEVICE_LOST:
		ret = "device lost";
		break;
	default:
		ret = "'unknown error'";
		break;
	}

	return ret;
}

std::string ToString(VkPhysicalDeviceProperties* props) {
	std::stringstream ss;

	ss << "\tdevice-name:    " << props->deviceName << std::endl;
	ss << "\tvendor-id:      " << props->vendorID << std::endl;
	ss << "\tdevice-type:    " << ToString(props->deviceType) << std::endl;
	ss << "\tdevice-id:      " << props->deviceID << std::endl;
	ss << "\tapi-version:    " << props->apiVersion << std::endl;
	ss << "\tdriver-version: " << props->driverVersion << std::endl;

	return ss.str();
}

std::string ToString(VkPhysicalDeviceType type) {
	std::string deviceType = "";
	switch (type) {
	case VK_PHYSICAL_DEVICE_TYPE_OTHER:
		deviceType = "other";
		break;
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
		deviceType = "integrated gpu";
		break;
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
		deviceType = "discrete gpu";
		break;
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
		deviceType = "virtual gpu";
		break;
	case VK_PHYSICAL_DEVICE_TYPE_CPU:
		deviceType = "cpu";
		break;
	}
	return deviceType;
}

std::string ToString(VkQueueFamilyProperties* props) {
	std::stringstream ss;
	ss << "\tqueue flags:     " << ToString(props->queueFlags) << std::endl;
	ss << "\tqueue count:     " << props->queueCount << std::endl;
	ss << "\ttime stamp bits: " << props->timestampValidBits << std::endl;
	// TODO: Write minImageTransferGranularity to the stringstream
	return ss.str();
}

std::string ToString(VkQueueFlags flags) {
	std::stringstream ss;

	if (flags & VK_QUEUE_GRAPHICS_BIT)
		ss << "graphics ";
	if (flags & VK_QUEUE_COMPUTE_BIT)
		ss << "compute ";
	if (flags & VK_QUEUE_TRANSFER_BIT)
		ss << "transfer ";
	if (flags & VK_QUEUE_SPARSE_BINDING_BIT)
		ss << "sparse binding ";

	return ss.str();
}