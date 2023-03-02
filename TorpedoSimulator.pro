#-------------------------------------------------
#
# Project created by QtCreator 2023-02-28T15:36:27
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TorpedoSimulator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    TorpedoSimulator.cpp \
    HitEvaluator.cpp \
    Guidance.cpp \
    Searcher.cpp \
    Target.cpp \
    ModelPredictiveControl.cpp \
    ParticleFilterSearch.cpp

HEADERS += \
    TorpedoSimulator.h \
    HitEvaluator.h \
    Guidance.h \
    Searcher.h \
    Target.h \
    Types.h \
    ModelPredictiveControl.h \
    ParticleFilterSearch.h
