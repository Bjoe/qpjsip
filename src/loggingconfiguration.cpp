#include "loggingconfiguration.h"

namespace qpjsua {

LoggingConfiguration::LoggingConfiguration() : receiver(0), member(0), consoleLevel(0)
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

LoggingConfiguration &LoggingConfiguration::withLogOutput(const QObject *aReceiver, const char *aMember)
{
    receiver = aReceiver;
    member = aMember;
    return *this;
}

const QObject *LoggingConfiguration::getReceiver() const
{
    return receiver;
}

const char *LoggingConfiguration::getMember() const
{
    return member;
}

int LoggingConfiguration::getConsoleLevel() const
{
    return consoleLevel;
}

} // namespace qpjsua
