/*
  By: Spencer Whyte
  # 100817664
  Carleton University
  */



/*

void HTTPRequest::setHeader(QStringList * h ){
    if(header){
        delete header;
    }
    header = h;
}


QStringList* HTTPRequest::getHeader(){
    return header;/*
}

HTTPRequest::HTTPRequestOperation HTTPRequest::getOperation(){
     QString httpHeader = getHeader()->at(0);
     QStringList fields = httpHeader.split(" ");
     QString operation = fields.at(0);
     if(operation == "POST"){
        return POST;
     }else if(operation == "GET"){
        return GET;
     }
     return INVALID;
}

QString*  HTTPRequest::getPath(){
     QString httpHeader = getHeader()->at(0);
     QStringList fields = httpHeader.split(" ");
     QString * operation = new QString(fields.at(1));
     return operation;
}


bool HTTPRequest::isHTTPProtocol(){
     QString httpHeader = getHeader()->at(0);
     QStringList fields = httpHeader.split(" ");
     QString operation = fields.at(2).trimmed();
     return operation == "HTTP/1.1";
}

long HTTPRequest::getContentLength(){
    for(int i= 0 ; i < getHeader()->length(); i++){
        if(getHeader()-> at(i).startsWith("Content-Length: ")){
            QString headerField = getHeader()->at(i);
            QString numberString= headerField.replace(QString("Content-Length: "), QString(""));
            return numberString.toLong();
        }
    }
    return 0;
}

HTTPRequest::HTTPRequest(QTcpSocket &tcpSocket) : header(NULL)
{
    qDebug() << "1";
    setHeader(new QStringList());
    while(!tcpSocket.canReadLine()){
        tcpSocket.waitForReadyRead(10);
    }
    QString currentLine;
    currentLine = tcpSocket.readLine();
    qDebug() << "2";
    while(currentLine != "\r\n" && getHeader()->length() < 50){
       qDebug() << "READ: " << currentLine;
       getHeader()-> append(currentLine);
       while(!tcpSocket.canReadLine()){
           tcpSocket.waitForReadyRead(10);
       }
       currentLine = tcpSocket.readLine();
    }
    qDebug() << "4";
    qDebug() << "CONTENT LENGTH: " << getContentLength();
    long contentLength = getContentLength();
    if(isHTTPProtocol()){
        qDebug() << "5";
        if(getOperation() == POST){
            qDebug() << "6";
            while(tcpSocket.bytesAvailable() < contentLength){
                tcpSocket.waitForReadyRead(10);
            }

            QString * path = getPath();
            QString data(tcpSocket.read(contentLength));
            QString * responseXML = NULL;

            if(path ->startsWith("/login")){
                qDebug() << "7";

                LoginRequest loginRequest(data);
                responseXML = loginRequest.getResponse();

            }else if(path->startsWith("/query/patient")){
                qDebug() << "MIRACLE";

                QueryPatientRequest queryRequest(data);
                responseXML = queryRequest.getResponse();

            }else if(path->startsWith("/add/consultation")){
                AddConsultationRequest queryRequest(data);
                responseXML = queryRequest.getResponse();
            }else if(path->startsWith("/edit/consultation")){
                EditConsultationRequest queryRequest(data);
                responseXML = queryRequest.getResponse();
            }else if(path->startsWith("/query/consultation")){
                QueryConsultationRequest queryRequest(data);
                responseXML = queryRequest.getResponse();
            }else if(path->startsWith("/add/patient")){

            }else if(path->startsWith("/edit/patient")){

            }else if(path->startsWith("/add/patient")){

            }else if(path->startsWith("/edit/patient")){

            }
            if(responseXML){
                HTTPResponse response(responseXML);
                QByteArray * responseData=response.getResponseData();
                tcpSocket.write(*responseData);
                delete responseData;
            }
            tcpSocket.flush();
            tcpSocket.waitForBytesWritten(3000);

            delete path;

        }
    }



}

HTTPRequest::~HTTPRequest(){
    delete header;
}
*/
