# Add more folders to ship with the application, here
folder_01.source = qml/cuCareServer
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE0A37947

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    CUCareDatabase.cpp \
    User.cpp \
    PatientRecord.cpp \
    ConsultationRecord.cpp \
    CUCareServer.cpp \
    QueryFilter.cpp \
    Request.cpp \
    PatientRecordRequest.cpp \
    CUCareServerThread.cpp \
    HTTPRequest.cpp \
    XMLRequest.cpp \
    LoginRequest.cpp \
    HTTPResponse.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    CUCareDatabase.h \
    User.h \
    PatientRecord.h \
    ConsultationRecord.h \
    CUCareServer.h \
    QueryFilter.h \
    Request.h \
    PatientRecordRequest.h \
    CUCareServerThread.h \
    HTTPRequest.h \
    XMLRequest.h \
    LoginRequest.h \
    HTTPResponse.h

QT += sql
QT += network
QT += xml
