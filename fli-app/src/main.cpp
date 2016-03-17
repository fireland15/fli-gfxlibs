#include <iostream>
#include <fstream>
#include <functional>

#include "logger_concurrent.hpp"

std::mutex m;
int count;

int main() {
#ifdef _DEBUG
	std::ofstream file("log.txt");
	fli::util::log::ConcurrentLogger* logger = new fli::util::log::ConcurrentLogger(file, fli::util::log::LogLvl::inf);
#endif
	count = 0;

	std::vector<std::thread> v;

	for (int i = 0; i < 10; i++) {
		std::function<void(fli::util::log::ConcurrentLogger*)> f = [logger](fli::util::log::ConcurrentLogger* l) {
			for (int i = 0; i < 10; i++) {
				std::unique_lock<std::mutex> lock(m);
				std::unique_ptr<fli::util::log::LogEntry> entry(new fli::util::log::LogEntry);
				entry->level = fli::util::log::LogLvl::inf;
				entry->sender = std::to_string(count++);
				entry->entry << "The renderer drew a banana";
				entry->details << "Color = yellow" << std::endl;
				entry->details << "TimeToDraw = 321ms" << std::endl;

				l->Log(std::move(entry));
				lock.unlock();
			}
			return;
		};

		//f(logger);

		v.push_back(std::thread(std::bind(f, logger)));
	}

	//std::this_thread::sleep_for(std::chrono::seconds(1));

	for (int i = 0; i < 10; i++) {
		v[i].join();
	}

	//std::cout << "here" << std::endl;

	delete logger;

	return 0;
}