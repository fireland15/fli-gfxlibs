#include "device.hpp"

#ifdef LOGGING
#define LOG(level, poster, msg) Logger::Instance()->Write(level, poster, msg)
#else
#define LOG(level, poster, msg)
#endif // LOGGING

int main() {
	Logger::Instance()->Open("log.txt");
	Logger::Instance()->SetLoggingLevel(DbgLevel::none);
	VulkanDevice device();
	Logger::Instance()->Close();
	return 0;
}