QT += widgets

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    SortFilterProxyModel.cpp

HEADERS += \
    MainWindow.h \
    SortFilterProxyModel.h


TARGET = dirview
TEMPLATE = app

# Для отладки (опционально)
# CONFIG += debug