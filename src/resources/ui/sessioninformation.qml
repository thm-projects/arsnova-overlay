import QtQuick 1.1

Rectangle {
    id: rectangle2
    width: 200
    height: 42
    color: "#00000000"

    property int unreadMessages: 1
    property int userCount: 2
    property int feedbackCount: 3

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
        x: 128
        y: 14
        width: 64
        height: 16
        color: "#20ffffff"
        radius: 2
        border.width: 1
        border.color: "#40ffffff"

        Text {
            id: feedbackCountText
            y: 0
            width: 24
            color: "#ffffff"
            text: feedbackCount.toString()
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            anchors.left: parent.left
            anchors.leftMargin: 4
            font.pixelSize: 14
        }

        Rectangle {
            id: rectangle1
            x: 32
            y: 0
            width: 1
            height: 16
            color: "#40ffffff"
        }

        Text {
            id: useCountText
            x: 43
            y: 0
            width: 24
            color: "#ffffff"
            text: userCount.toString()
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            anchors.right: parent.right
            anchors.rightMargin: 4
            font.pixelSize: 14
        }


    }
}
