#ifndef QPJSUA_LOGGINGCONFIGURATION_H
#define QPJSUA_LOGGINGCONFIGURATION_H

namespace qpjsua {

class LoggingConfiguration
{
public:
    static LoggingConfiguration build();
    LoggingConfiguration &withConsoleLevel(int aLevel);

    int getConsoleLevel() const;

private:
    int consoleLevel;

    LoggingConfiguration();
};

} // namespace qpjsua

#endif // QPJSUA_LOGGINGCONFIGURATION_H
