QT += widgets

TARGET = VisualDBEditor
TEMPLATE = app

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    Controller.cpp \
    Table.cpp \
    XmlDB.cpp \
    AbstractDB.cpp \
    DBHandler.cpp \
    DraggableWidget.cpp \
    TableView.cpp \
    MainWindow.cpp \
    Relation.cpp \
    TablesDrawingArea.cpp \
    AddClass.cpp \
    RelationsManager.cpp

HEADERS += \
    Controller.h \
    GlobalDefinitions.h \
    Table.h \
    XmlDB.h \
    AbstractDB.h \
    DBHandler.h \
    DraggableWidget.h \
    TableView.h \
    MainWindow.h \
    Relation.h \
    TablesDrawingArea.h \
    AddClass.h \
    RelationsManager.h

FORMS += \
    MainWindow.ui \
    addclass.ui

include( ../../common.pri )

DESTDIR = $${BIN_PATH}/
