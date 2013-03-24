#include "output.h"

#include <QByteArray>
#include <iostream>

namespace tests {

Output::Output(QObject *parent) :
    QObject(parent)
{
}

void Output::out(const qpjsua::PjError &anError, const QString &aMessage)
{
    QByteArray msg = aMessage.toLatin1();
    if(anError.getStatus() != PJ_SUCCESS) {
        msg = QString("%1 Code: %2").arg(anError.getMessage()).arg(anError.getStatus()).toLatin1();
    }
    std::cout << msg.constData() << std::endl;
}

void Output::onLog(int level, QString message)
{
    std::cout << "Level " << level << " " << message.toLatin1().constData() << std::endl;
}

} // namespace tests
