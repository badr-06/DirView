QT += widgets

DESTDIR = $$PWD/build

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/SortFilterProxyModel.cpp \
    src/FileSystemModel.cpp

HEADERS += \
    src/MainWindow.h \
    src/SortFilterProxyModel.h \
    src/FileSystemModel.h


TARGET = dirview
TEMPLATE = app

# Для отладки (опционально)
# CONFIG += debug