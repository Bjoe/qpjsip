#ifndef QPJSUA_TRANSPORTCONFIGURATION_H
#define QPJSUA_TRANSPORTCONFIGURATION_H

#include "engine.h"

namespace qpjsua {

class TransportConfiguration
{
public:
    static TransportConfiguration build();
    TransportConfiguration &withPort(int aPort);

private:
    int port;

    TransportConfiguration();

    friend class Engine;
};

} // namespace qpjsua

#endif // QPJSUA_TRANSPORTCONFIGURATION_H
