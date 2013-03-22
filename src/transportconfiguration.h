#ifndef QPJSUA_TRANSPORTCONFIGURATION_H
#define QPJSUA_TRANSPORTCONFIGURATION_H

namespace qpjsua {

class TransportConfiguration
{
public:
    static TransportConfiguration build();
    TransportConfiguration &withPort(int aPort);

    int getPort() const;

private:
    int port;

    TransportConfiguration();
};

} // namespace qpjsua

#endif // QPJSUA_TRANSPORTCONFIGURATION_H
