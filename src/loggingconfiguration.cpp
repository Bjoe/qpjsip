#include "loggingconfiguration.h"

namespace qpjsua {

LoggingConfiguration::LoggingConfiguration() : consoleLevel(0)
{
}

LoggingConfiguration LoggingConfiguration::build()
{
    return LoggingConfiguration();
}

LoggingConfiguration &LoggingConfiguration::withConsoleLevel(int aLevel)
{
    consoleLevel = aLevel;
    return *this;
}

} // namespace qpjsua
