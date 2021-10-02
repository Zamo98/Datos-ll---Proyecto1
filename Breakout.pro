QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bola.cpp \
    colision.cpp \
    comun.cpp \
    dobles.cpp \
    juego.cpp \
    main.cpp \
    profundos.cpp \
    raqueta.cpp \
    sorpresa.cpp \
    triples.cpp \
    ventana.cpp

HEADERS += \
    bola.h \
    colision.h \
    comun.h \
    dobles.h \
    juego.h \
    profundos.h \
    raqueta.h \
    sorpresa.h \
    triples.h \
    ventana.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recursos.qrc
