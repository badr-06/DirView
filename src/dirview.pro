QT += widgets

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    SortFilterProxyModel.cpp \
    FileSystemModel.cpp

HEADERS += \
    MainWindow.h \
    SortFilterProxyModel.h \
    FileSystemModel.h


TARGET = dirview
TEMPLATE = app

# Для отладки (опционально)
# CONFIG += debug