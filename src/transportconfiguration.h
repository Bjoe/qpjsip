#ifndef QPJSUA_TRANSPORTCONFIGURATION_H
#define QPJSUA_TRANSPORTCONFIGURATION_H

namespace qpjsua {

class TransportConfiguration
{
public:
    static TransportConfiguration build();
    TransportConfiguration &withPort(unsigned aPort);

    unsigned getPort() const;

private:
    unsigned port;

    TransportConfiguration();
};

} // namespace qpjsua

#endif // QPJSUA_TRANSPORTCONFIGURATION_H
