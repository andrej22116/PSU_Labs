#-------------------------------------------------
#
# Project created by QtCreator 2018-12-26T07:37:56
#
#-------------------------------------------------

QT       += core gui widgets sql

TARGET = GameStore
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
        mainwindow.cpp \
    code/control/ClassDatabaseBaseController/databasebasecontroller.cpp \
    code/control/ClassGameDatabaseController/gamedatabasecontroller.cpp \
    code/control/ClassUserDatabaseController/userdatabasecontroller.cpp \
    code/control/ClassNewsDatabaseController/newsdatabasecontroller.cpp \
    code/control/ClassCommentsDatabaseController/commentsdatabasecontroller.cpp \
    code/control/ClassGameListItem/gamelistitem.cpp \
    code/control/ClassElidedLabel/elidedlabel.cpp \
    code/control/ClassGameTabController/gametabcontroller.cpp \
    code/control/ClassLibraryTabController/librarytabcontroller.cpp \
    code/control/ClassGlobalNewsTabController/globalnewstabcontroller.cpp \
    code/control/ClassDevelopmentTabController/developmenttabcontroller.cpp \
    code/control/ClassUserProfileTabController/userprofiletabcontroller.cpp \
    code/control/ClassGameInfoWidget/gameinfowidget.cpp \
    code/control/ClassCommentaryWidget/commentarywidget.cpp \
    code/control/ClassAccountController/accountcontroller.cpp \
    code/control/ClassBaseOverlayDialog/baseoverlaydialog.cpp \
    code/control/ClassLoginWidget/loginwidget.cpp

HEADERS += \
        mainwindow.h \
    code/model/game.h \
    code/model/user.h \
    code/model/game_addon.h \
    code/model/commentary.h \
    code/model/developer.h \
    code/model/news.h \
    code/model/purchase.h \
    code/model/constants.h \
    code/control/ClassDatabaseBaseController/databasebasecontroller.h \
    code/control/ClassGameDatabaseController/gamedatabasecontroller.h \
    code/control/ClassUserDatabaseController/userdatabasecontroller.h \
    code/model/game_statistic.h \
    code/model/full_game_info.h \
    code/control/ClassNewsDatabaseController/newsdatabasecontroller.h \
    code/control/ClassCommentsDatabaseController/commentsdatabasecontroller.h \
    code/model/user_profile.h \
    code/control/ClassGameListItem/gamelistitem.h \
    code/control/ClassElidedLabel/elidedlabel.h \
    code/control/ClassGameTabController/gametabcontroller.h \
    code/control/ClassLibraryTabController/librarytabcontroller.h \
    code/control/ClassGlobalNewsTabController/globalnewstabcontroller.h \
    code/control/ClassDevelopmentTabController/developmenttabcontroller.h \
    code/control/ClassUserProfileTabController/userprofiletabcontroller.h \
    code/control/ClassGameInfoWidget/gameinfowidget.h \
    code/control/ClassCommentaryWidget/commentarywidget.h \
    code/control/ClassAccountController/accountcontroller.h \
    code/control/ClassBaseOverlayDialog/baseoverlaydialog.h \
    code/control/ClassLoginWidget/loginwidget.h

FORMS += \
        mainwindow.ui \
    code/control/ClassGameListItem/gamelistitem.ui \
    code/control/ClassGameInfoWidget/gameinfowidget.ui \
    code/control/ClassCommentaryWidget/commentarywidget.ui \
    code/control/ClassLoginWidget/loginwidget.ui

CONFIG += mobility
MOBILITY = 


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/sources.qrc
