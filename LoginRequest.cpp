#include "LoginRequest.h"

LoginRequest::LoginRequest(QString & data): XMLRequest(data)
{


}

QString * getLoginFailureMessage(){
    QString * output = new QString();
    QXmlStreamWriter writer(output);
    writer.writeStartDocument();
    writer.writeTextElement(QString("errormessage"), QString("Unable to authenticate, please ensure that your username and password are correct"));
    return output;
}

QString * LoginRequest::getResponse(){
    User * u = new User();
    u->fromXML(*getDocument());
    bool authenticated = getDatabase()->authenticateUser(*u);
    if(authenticated){
        return u->toXML();
    }else{
        return getLoginFailureMessage();
    }

    delete u;
}
