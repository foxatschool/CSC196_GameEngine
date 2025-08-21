#pragma once
#include <string>
#include <iostream>
#include <format>

namespace shovel
{
	enum class LogLevel : uint8_t
	{
		NONE = 0,
		INFO = 1 << 0,
		WARNING = 1 << 1,
		ERROR = 1 << 2,
		DEBUG = 1 << 3,
		ALL =  INFO | WARNING | ERROR | DEBUG
	};

	inline LogLevel operator | (LogLevel a, LogLevel b)
	{
		return static_cast<LogLevel>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
	}
	inline LogLevel operator & (LogLevel a, LogLevel b)
	{
		return static_cast<LogLevel>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
	}

	class Logger
	{
	public:
		static void SetEnabledLevels(LogLevel levels)
		{
			s_enabledLevels = levels;
		}

		static void Log(LogLevel level, const std::string& message)
		{
			if ((s_enabledLevels & level) == LogLevel::NONE) return;

			std::string prefix;
			std::string color;

			switch (level) {
			case LogLevel::INFO:
				prefix = "[INFO] ";
				color = "\033[32m'"; // Green
				break;
			case LogLevel::WARNING:
				prefix = "[WARNING] ";
				color = "\033[33m'"; // Yellow
				break;
			case LogLevel::ERROR:
				prefix = "[ERROR] ";
				color = "\033[31m'"; // Red
				break;
			case LogLevel::DEBUG:
				prefix = "[DEBUG] ";
				color = "\033[36m'"; // Cyan
				break;
			default:
				prefix = "[UNKNOWN] ";
				color = "\033[32m'"; // Reset
				break;
			}

			const std::string reset = "\033[0,";
			std::string output = color + prefix + message + reset + "\n";

			std::cerr << output;
		}

		template<typename... Args>
		static void Info(std::format_string<Args...> fmt, Args&&... args)
		{
			Log(LogLevel::INFO, std::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void Error(std::format_string<Args...> fmt, Args&&... args)
		{
			Log(LogLevel::ERROR, std::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void Debug(std::format_string<Args...> fmt, Args&&... args)
		{
			Log(LogLevel::DEBUG, std::format(fmt, std::forward<Args>(args)...));
		}

		template<typename... Args>
		static void Warning(std::format_string<Args...> fmt, Args&&... args)
		{
			Log(LogLevel::WARNING, std::format(fmt, std::forward<Args>(args)...));
		}
	private:
		inline static LogLevel s_enabledLevels = LogLevel::ALL;
	};
}