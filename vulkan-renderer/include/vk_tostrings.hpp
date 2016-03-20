#pragma once

#include <string>
#include <sstream>

#include "vulkan.h"

std::string ToString(VkResult result);
std::string ToString(VkPhysicalDeviceProperties* props);
std::string ToString(VkPhysicalDeviceType type);
std::string ToString(VkQueueFamilyProperties* props);
std::string ToString(VkQueueFlags flags);