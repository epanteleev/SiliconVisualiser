QT       += core gui datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include/
DEPENDPATH += src/

SOURCES += \
    src/CellGenerator.cpp \
    src/DialogSizeScatter.cpp \
    src/DialogWelcome.cpp \
    src/SiliconCell.cpp \
    src/main.cpp \
    src/Application.cpp

HEADERS += \
    include/AbstractDialog.h \
    include/Application.h \
    include/AtomSet.h \
    include/CellGenerator.h \
    include/CellProperty.h \
    include/DialogSizeScatter.h \
    include/DialogWelcome.h \
    include/Settings.h \
    include/SiliconCell.h \

FORMS += \
    forms/DialogSizeScatter.ui \
    forms/DialogWelcome.ui \
    forms/GuiApplication.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release) {
    message( "enable release mode" )
    win32-g++ {
        message("used g++")
       # QMAKE_CXXFLAGS += -O3
    }
}

CONFIG(debug, debug|release) {
    message( "enable debug mode" )
}

RESOURCES += \
    SiliconVisualiser.qrc

documentation.path = $$PWD
documentation.files = README.txt

INSTALLS += documentation
