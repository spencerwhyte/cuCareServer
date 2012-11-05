#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include <XMLRequest.h>
#include "User.h"

class LoginRequest : public XMLRequest
{
    Q_OBJECT
public:
    explicit LoginRequest(QString &data);
    
    virtual QString * getResponse();
signals:
    
public slots:
    
};

#endif // LOGINREQUEST_H
