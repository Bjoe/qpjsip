#ifndef QPJSUA_LOGGINGCONFIGURATION_H
#define QPJSUA_LOGGINGCONFIGURATION_H

#include "engine.h"

namespace qpjsua {

class LoggingConfiguration
{
public:
    static LoggingConfiguration build();
    LoggingConfiguration &withConsoleLevel(int aLevel);

private:
    int consoleLevel;

    LoggingConfiguration();

    friend class Engine;
};

} // namespace qpjsua

#endif // QPJSUA_LOGGINGCONFIGURATION_H
