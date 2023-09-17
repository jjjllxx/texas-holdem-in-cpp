#include "LoggerInitialiser.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>

void th::LoggerInitialiser::init(const Mode mode)
{
    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // The minimum level for the logger to output (at debug, always outputs).
    console->set_level(spdlog::level::debug);

    switch (mode)
    {
    case th::LoggerInitialiser::Mode::Debug:
        // [I] (PID) Class::Function::Line: Message
        console->set_pattern("%^[%L]%$ (%P) %s::%!():%#: %v");
        break;

    case th::LoggerInitialiser::Mode::Release:
        // [I] (PID) Message
        console->set_pattern("%^[%L]%$ (%P) %s: %v");
        break;

    default:
        break;
    }
    spdlog::set_default_logger(std::make_shared<spdlog::logger>("Logger", console));
}