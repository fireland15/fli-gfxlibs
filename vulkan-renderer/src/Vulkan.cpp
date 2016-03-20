#include "Vulkan.hpp"

Vulkan::Vulkan(Logger_t & logger, Config_t & config) : m_logger(logger), m_config(config) {
#ifdef _DEBUG
	std::unique_ptr<LogEntry_t> entry(new LogEntry_t);
	entry->level = LogLvl::inf;
	entry->sender = "Vulkan";
	entry->entry << "Constructing Vulkan Class";
	logger.Log(std::move(entry));
#endif

	
}
