QT += quick
CONFIG += c++11

folder_qml.source = QML
folder_qml.target = /
DEPLOYMENTFOLDERS += folder_qml

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller.cpp \
    Document.cpp \
    JsonReader.cpp \
    Listing.cpp \
    Olx.cpp \
    OlxListing.cpp \
    OlxQueryBuilder.cpp \
    Parser.cpp \
    Requesting.cpp \
    Site.cpp \
    UyBor.cpp \
    UyBorListing.cpp \
    UyBorQueryBuilder.cpp \
    Zor.cpp \
    ZorListing.cpp \
    ZorQueryBuilder.cpp \
        main.cpp

RESOURCES += resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = QML

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include($$PWD/../libs/QtXlsxWriter-master/src/xlsx/qtxlsx.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/QGumboParser/QGumboParser/release/ -lQGumboParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/QGumboParser/QGumboParser/debug/ -lQGumboParser
else:unix: LIBS += -L$$OUT_PWD/../libs/QGumboParser/QGumboParser/ -lQGumboParser

INCLUDEPATH += $$PWD/../libs/QGumboParser/QGumboParser \
    C:/Program Files (x86)/OpenSSL-Win32
DEPENDPATH += $$PWD/../libs/QGumboParser/QGumboParser

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/release/libQGumboParser.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/debug/libQGumboParser.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/release/QGumboParser.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/debug/QGumboParser.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/libQGumboParser.a

RC_FILE = appIcon.rc

HEADERS += \
    Controller.h \
    Document.h \
    Iterable.h \
    JsonReader.h \
    Listing.h \
    Olx.h \
    OlxListing.h \
    OlxQueryBuilder.h \
    Parser.h \
    Requesting.h \
    Site.h \
    UyBor.h \
    UyBorListing.h \
    UyBorQueryBuilder.h \
    Zor.h \
    ZorListing.h \
    ZorQueryBuilder.h

DISTFILES += \
    QML/Components/Test.qml \
    QML/main.qml
