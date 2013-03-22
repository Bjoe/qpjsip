#ifndef QPJSUA_MEDIACONFIGURATION_H
#define QPJSUA_MEDIACONFIGURATION_H

#include "engine.h"

namespace qpjsua {

class MediaConfiguration
{
public:
    static MediaConfiguration build();

private:
    MediaConfiguration();

    friend class Engine;
};

} // namespace qpjsua

#endif // QPJSUA_MEDIACONFIGURATION_H
