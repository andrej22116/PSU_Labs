import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Item {
    opacity: 0

    anchors.fill: parent

    Label {
        text: "ololololololoololo"
    }

    Grid {

    }

    MouseArea {
        anchors.fill: parent
        onClicked: closeAnimation_menager.running = true
    }
}
