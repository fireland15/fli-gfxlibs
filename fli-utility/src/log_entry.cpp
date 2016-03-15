#include "log_entry.hpp"
#pragma once

namespace fli {
	namespace util {
		namespace log {

			std::string LogEntry::FormatDetails() {
				std::string str = details.str();
				if (str.size() == 0)
					return std::string();

				std::string out("\t");
				std::string temp;
				std::stringstream ss(str);

				while (std::getline(ss, temp)) {
					out.append(temp);
					out.append("\n\t");
				}
				out = out.substr(0, out.size() - 2);

				return out;
			}

			inline std::string LogEntry::ToString(LogLvl level) {
				switch (level) {
				case LogLvl::all:
					return "all";
				case LogLvl::err:
					return "err";
				case LogLvl::inf:
					return "inf";
				case LogLvl::non:
					return "non";
				case LogLvl::wrn:
					return "wrn";
				default:
					return "";
				}
			}

			std::string LogEntry::ToString()
			{
				std::stringstream ss;
				ss << "[" << ToString(level) << "] " << GetTimeStamp() << " [" << sender.substr(0, 6) << "] " << entry.str() << std::endl;
				std::string d = details.str();
				if (d.size() > 0)
					ss << FormatDetails() << std::endl;
				return ss.str();
			}

			std::string LogEntry::GetTimeStamp()
			{
				time_t rawtime;
				tm timeinfo;
				time(&rawtime);
				localtime_s(&timeinfo, &rawtime);
				char buf[26];
				asctime_s(buf, 26, &timeinfo);
				buf[24] = '\0';
				return std::string(buf);
			}

		}
	}
}
