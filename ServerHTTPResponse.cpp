#include "ServerHTTPResponse.h"

/*
  Constructs a ServerHTTPResponse with the TCP
  socket over which the response will be sent
*/
ServerHTTPResponse::ServerHTTPResponse(int TCPSocket) : ServerTCPResponse(TCPSocket){

}

/*
  Takes the body and sends it back to the client
  as an HTTP response over TCP
  */
int ServerHTTPResponse::fillHTTPResponse(QString & body){
    QString responseData;

    QString header;
    header.append("HTTP/1.1 200 OK\n");
    header.append("Content-Length: ");
    header.append(new QString(body.length()));
    header.append("\n");
    header.append("\r\n");

    responseData.append(header);
    responseData.append(body);

    int result = fillTCPResponse(responseData);

    if(result == 0){

    }else{

    }

    return result;
}

// Destructor
ServerHTTPResponse::~ServerHTTPResponse(){

}
