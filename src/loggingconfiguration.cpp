#include "loggingconfiguration.h"

namespace qpjsua {

LoggingConfiguration::LoggingConfiguration() : configuration()
{
    pjsua_logging_config_default(&configuration);
}

LoggingConfiguration LoggingConfiguration::build()
{
    return LoggingConfiguration();
}

LoggingConfiguration &LoggingConfiguration::withConsoleLevel(int aLevel)
{
    configuration.console_level = aLevel;
    return *this;
}

} // namespace qpjsua
