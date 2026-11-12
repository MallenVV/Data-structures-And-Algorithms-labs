macx {
  cache()
}

TEMPLATE = app

CONFIG -= qt
CONFIG -= app_bundle

SOURCES = $$files($$PWD/*.cpp)
HEADERS = $$files($$PWD/*.h) \
    Node.h \
    node.h

QMAKE_CXXFLAGS += -std=c++17 -Wall -Wextra -Wpedantic

cache()
