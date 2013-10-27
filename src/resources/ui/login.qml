import QtQuick 1.1

Rectangle {
    id: widgetRectangle
    objectName: "widgetRectangle"
    width: 640
    height: 400

    signal loginButtonClick()
    signal exitButtonClick()

    Image {
        id: toplogo
        x: 0
        y: 0
        source: "qrc:/images/images/splash.png"
    }
    
    Rectangle {
        id: sessionIdRectangle
        objectName: "sessionIdRectangle"
        x: 140
        y: 140
        width: 361
        height: 41
        border.color: sessionIdTextInput.focus ? "#55ad3d" : "#dddddd"
        radius: 2
        anchors.horizontalCenter: parent.horizontalCenter

        TextInput {
            id: sessionIdTextInput
            objectName: "sessionIdTextInput"
            x: 18
            y: 10
            width: 133
            height: 21
            color: "#333333"
            text: ""
            cursorVisible: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            font.family: "DejaVu Sans Mono"
            horizontalAlignment: TextInput.AlignHCenter
            font.pixelSize: 18
            maximumLength: 8
            focus: true
            validator: RegExpValidator {regExp: /\d{8}/}
            onTextChanged: {
                if (!text.match(/\d{8}/)) {
                    sessionIdRectangle.border.color = "#c33333"
                    sessionIdRectangle.color = "#fffff7"
                    loginbutton.loginbuttonColor = "#777777"
                }
                else {
                    sessionIdRectangle.border.color = "#dddddd"
                    sessionIdRectangle.color = "#ffffff"
                    loginbutton.loginbuttonColor = "#55ad3d"
                }
            }
            Keys.onPressed: {
                if (
                    text.match(/\d{8}/)
                    && (event.key === Qt.Key_Enter || event.key === Qt.Key_Return)
                ) {
                    widgetRectangle.loginButtonClick()
                }
            }
            Text {
                id: sessionIdPlaceholderText
                color: "#a0676963"
                text: "Session Key"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                font.bold: false
                font.pixelSize: 18
                verticalAlignment: Text.AlignTop
                z: 1
                visible: (sessionIdTextInput.text == "")
            }
        }
    }

    Rectangle {
        id: loginbutton
        x: 139
        y: 200
        width: 160
        height: 40
        radius: 2

        property color loginbuttonColor: "#55ad3d"

        Text {
            id: loginbuttonLabel
            color: "#ffffff"
            anchors.centerIn: parent
            text: qsTr("Login")
            font.bold: true
            font.pixelSize: 12
        }

        MouseArea {
            id: loginbuttonMouseArea
            anchors.fill: parent
            onClicked: {
                if (sessionIdTextInput.text.match(/\d{8}/)) {
                    widgetRectangle.loginButtonClick()
                }
            }
            hoverEnabled: true
        }

        color: loginbuttonColor != "#777777" && (loginbuttonMouseArea.pressed || loginbuttonMouseArea.containsMouse) ? Qt.darker(loginbuttonColor, 1.5) : loginbuttonColor
    }

    Rectangle {
        id: exitbutton
        objectName: "exitbutton"
        x: 340
        y: 200
        width: 160
        height: 40
        radius: 2

        property color exitbuttonColor: "#cf3434"

        Text {
            id: exitbuttonLabel
            color: "#ffffff"
            anchors.centerIn: parent
            text: qsTr("Exit")
            font.bold: true
            font.pixelSize: 12
        }

        MouseArea {
            id: exitbuttonMouseArea
            anchors.fill: parent
            onClicked: widgetRectangle.exitButtonClick()
            hoverEnabled: true
        }

        color: exitbuttonMouseArea.pressed || exitbuttonMouseArea.containsMouse ? Qt.darker(exitbuttonColor, 1.5) : exitbuttonColor
    }
}
