#-------------------------------------------------
#
# Project created by QtCreator 2019-02-05T13:34:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessing
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++1z

SOURCES += \
        main.cpp \
    ProcessSettingDialog.cpp \
    ScaleProcessor.cpp \
    GrayProcessor.cpp \
    ImageController.cpp \
    MainWindow.cpp \
    GrayProcessSettingDialog.cpp \
    BinaryProcessSettingDialog.cpp \
    BinaryProcessor.cpp \
    SaltAndPapeerNoiseProcessor.cpp \
    SaltAndPepeerNoiseSettingDialog.cpp \
    GaussianNoiseProcessor.cpp \
    ColorCorrectionProcessor.cpp \
    ColorCorrectionProcessSettingDialog.cpp \
    BaseMatrixCoreProcessor.cpp \
    BorderSelectionProcessor.cpp \
    LowPassFilterProcessor.cpp \
    HighPassFilterProcessor.cpp \
    GaussianBlureProcessor.cpp \
    FormHighPassFilterSettingDialog.cpp \
    KernelSetupWidget.cpp \
    GaussianBlureSetupDialog.cpp \
    EmbossProcessor.cpp \
    EmbossSettingDialog.cpp \
    LowPassFilterSettingDialog.cpp \
    BorderSelectionSettingDialog.cpp \
    MedianFilterProcessor.cpp \
    MedianFilterSettingDialog.cpp

HEADERS += \
    ImageController.hpp \
    GrayProcessor.hpp \
    MainWindow.hpp \
    ProcessSettingDialog.hpp \
    ScaleProcessor.hpp \
    GrayProcessSettingDialog.hpp \
    BinaryProcessSettingDialog.hpp \
    BinaryProcessor.hpp \
    SaltAndPapeerNoiseProcessor.hpp \
    SaltAndPepeerNoiseSettingDialog.hpp \
    GaussianNoiseProcessor.hpp \
    ColorCorrectionProcessor.hpp \
    ColorCorrectionProcessSettingDialog.hpp \
    BaseMatrixCoreProcessor.hpp \
    BorderSelectionProcessor.hpp \
    LowPassFilterProcessor.hpp \
    HighPassFilterProcessor.hpp \
    GaussianBlureProcessor.hpp \
    FormHighPassFilterSettingDialog.hpp \
    KernelSetupWidget.hpp \
    GaussianBlureSetupDialog.hpp \
    EmbossProcessor.hpp \
    EmbossSettingDialog.hpp \
    LowPassFilterSettingDialog.hpp \
    BorderSelectionSettingDialog.hpp \
    MedianFilterProcessor.hpp \
    MedianFilterSettingDialog.hpp

FORMS += \
        mainwindow.ui \
    ProcessSettingDialog.ui \
    GrayProcessSettingDialog.ui \
    BinaryProcessSettingDialog.ui \
    SaltAndPepeerNoiseSettingDialog.ui \
    ColorCorrectionProcessSettingDialog.ui \
    CoreSetupWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
