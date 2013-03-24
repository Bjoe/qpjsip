#ifndef QPJSUA_LOGGINGCONFIGURATION_H
#define QPJSUA_LOGGINGCONFIGURATION_H

#include <QObject>

namespace qpjsua {

class LoggingConfiguration
{
public:
    static LoggingConfiguration build();
    LoggingConfiguration &withConsoleLevel(int aLevel);
    LoggingConfiguration &withLogOutput(const QObject *aReceiver, const char *aMember);

    int getConsoleLevel() const;
    const QObject *getReceiver() const;
    const char *getMember() const;

private:
    const QObject *receiver;
    const char *member;
    int consoleLevel;

    LoggingConfiguration();
};

} // namespace qpjsua

#endif // QPJSUA_LOGGINGCONFIGURATION_H
