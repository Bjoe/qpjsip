#ifndef QPJSUA_LOGGINGCONFIGURATION_H
#define QPJSUA_LOGGINGCONFIGURATION_H

#include "pjsua.h"

namespace qpjsua {

class LoggingConfiguration
{
public:
    static LoggingConfiguration build();
    LoggingConfiguration &withConsoleLevel(int aLevel);

    pjsua_logging_config getPjsuaLoggingConfig() const
    {
        return configuration;
    }

private:
    pjsua_logging_config configuration;

    LoggingConfiguration();
};

} // namespace qpjsua

#endif // QPJSUA_LOGGINGCONFIGURATION_H
