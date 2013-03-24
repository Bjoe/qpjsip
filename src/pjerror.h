#ifndef QPJSUA_PJERROR_H
#define QPJSUA_PJERROR_H

#include <QString>
#include <pj/types.h>

namespace qpjsua {

class PjError
{
public:
    PjError();

    void setStatus(pj_status_t aStatus);
    void setMessage(const QString &aMessage);

    QString getMessage() const;
    pj_status_t getStatus() const;

private:
    QString message;
    pj_status_t status;
};

} // namespace qpjsua

#endif // QPJSUA_PJERROR_H
