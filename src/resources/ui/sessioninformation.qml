import QtQuick 1.1

Rectangle {
    id: rectangleWidget
    width: 160
    height: 42
    color: "#00000000"
    radius: 3
    smooth: true

    property int unreadMessages: 1
    property int userCount: 2
    property int feedbackCount: 3

    signal closeButtonClick()

    Image {
        id: backgroundImage
        anchors.fill: parent
        fillMode: Image.Tile
        source: "qrc:/images/images/background.png"
        opacity: .3
    }

    Image {
        id: image1
        x: 10
        y: 6
        width: 32
        height: 32
        anchors.verticalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        fillMode: Image.PreserveAspectFit
        source: "qrc:/images/images/mail-mark-unread.png"
        opacity: unreadMessages > 0 ? 1 : .5
    }

    Rectangle {
        id: rectangleMessagesShadow
        x: 48 - width
        y: 4
        width: text.text.length > 1 ? 24 : 16;
        height: 16
        radius: 8
        border.width: 3
        border.color: "#555555"
        visible: unreadMessages > 0 ? true : false
    }

    Rectangle {
        id: rectangleMessages
        x: 48 - width
        y: 4
        width: text.text.length > 1 ? 24 : 16;
        height: 16
        color: "#b91414"
        radius: 8
        border.width: 2
        border.color: "#ffffff"
        visible: unreadMessages > 0 ? true : false

        Text {
            id: text
            color: "#ffffff"
            text: unreadMessages > 99 ? "..." : unreadMessages.toString()
            verticalAlignment: Text.AlignVCenter
            transformOrigin: Item.Center
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.bold: true
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: rectangleCount
        x: 56
        y: 10
        width: 42
        height: 22
        color: "#ff606060"
        radius: 2
        anchors.horizontalCenter: parent.horizontalCenter
        border.width: 1
        border.color: "#99ffffff"

        Text {
            id: countText
            y: 0
            anchors.fill: parent
            color: "#ffffff"
            text: feedbackCount.toString() + "/" + userCount.toString()
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            font.pixelSize: 14
        }
    }

    Image {
        id: closeButton
        x: 134
        y: 12
        width: 18
        height: 18

        source: "qrc:/images/images/close.png"

        MouseArea {
            id: closeButtonMouseArea
            anchors.fill: parent
            onClicked: {
                rectangleWidget.closeButtonClick()
            }
        }
    }


}
