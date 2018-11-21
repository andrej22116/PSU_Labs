import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

import Database.Controls 1.0

Column {
    anchors.centerIn: parent
    opacity: 0;

    property int elementWidth: 200;

    Label { text: "Authorization on PostgreSQL DB"; font.pointSize: 24 }

    DbConnectionDialog {
        id: connectDialog
        login: textLogin.text
        password: textPassword.text
        database: textDatabase.text
        host: textHost.text
        port: textPort.text
    }

    TextField {
        id: textLogin
        text: "postgres"
        placeholderText: "Login"
        width: parent.elementWidth
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: textPassword
        placeholderText: "Password"
        width: parent.elementWidth
        echoMode: TextField.Password
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: textDatabase
        text: "postgres"
        placeholderText: "Database"
        width: parent.elementWidth
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: textHost
        text: "localhost"
        placeholderText: "Host"
        width: parent.elementWidth
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: textPort
        text: "5432"
        placeholderText: "Port"
        width: parent.elementWidth
        validator: IntValidator { bottom: 0; top: 65535; }
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: textStatus
        text: connectDialog.status
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: buttonOk
        text: "Connect"
        width: parent.elementWidth
        onClicked: closeAnimation_connect.running = connectDialog.onConnectHandler()
        anchors.horizontalCenter: parent.horizontalCenter
    }


}
