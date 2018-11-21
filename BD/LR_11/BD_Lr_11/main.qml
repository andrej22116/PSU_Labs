import QtQuick 2.10
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: mainWindow
    visible: true

    title: qsTr("Базы данных: Лабораторная работа №11 - Администрирование")

    width: 480
    height: 640
    minimumWidth: 480
    minimumHeight: 640

    DbConnectionDialog {
        id: dbConnectionDialog
        visible: true

        OpacityAnimator on opacity {
                id: openAnimation_connect
                from: 0;
                to: 1;
                duration: 250

                onStarted: {
                    dbConnectionDialog.visible = true
                }
            }

        OpacityAnimator on opacity {
                id: closeAnimation_connect
                running: false
                from: 1
                to: 0
                duration: 500

                onStopped: {
                    dbConnectionDialog.visible = false
                    openAnimation_menager.running = true
                }
            }
    }

    DbPermissionMenager {
        id: dbPermissionMenager
        visible: false

        OpacityAnimator on opacity {
                id: openAnimation_menager
                running: false
                from: 0;
                to: 1;
                duration: 250

                onStarted: {
                    dbPermissionMenager.visible = true
                }
            }

        OpacityAnimator on opacity {
                id: closeAnimation_menager
                running: false
                from: 1
                to: 0
                duration: 500
                onStopped: {
                    dbPermissionMenager.visible = false
                    openAnimation_connect.running = true
                }
            }
    }
}
