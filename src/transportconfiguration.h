#ifndef QPJSUA_TRANSPORTCONFIGURATION_H
#define QPJSUA_TRANSPORTCONFIGURATION_H

#include "pjsua.h"

namespace qpjsua {

class TransportConfiguration
{
public:
    static TransportConfiguration build();
    TransportConfiguration &withPort(int aPort);

    pj_status_t create() const;

private:
    pjsua_transport_config configuration;

    TransportConfiguration();
};

} // namespace qpjsua

#endif // QPJSUA_TRANSPORTCONFIGURATION_H
