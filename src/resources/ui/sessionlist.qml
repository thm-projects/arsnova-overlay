import QtQuick 1.1

Item {
    id: item1
    visible: true
    width: 760
    height: 220

    signal sessionChanged(string sessionkey)

    function append(newSession) {
        var doinsert = true;
        for (var i = 0; i < sessionListView.model.count; i++) {
            sessionListView.model.get(i).active = false;
            if (sessionListView.model.get(i).keyword === newSession.keyword) {
                doinsert = false;
                sessionListView.model.get(i).active = true;
            }
        }
        if (doinsert) {
            emptyListText.visible = false;
            sessionListView.model.append(newSession)
        }
    }

    function formatSessionKey(sessionKey) {
        var result = String();
        for (var i = 0; i < 8; i++) {
            result += String(sessionKey).charAt(i);
            if ((i+1) % 2 == 0) {
                result += " ";
            }
        }
        return result;
    }

    function stripWhitespaces(sessionKey) {
        var plainKey = sessionKey;
        do {
            plainKey = plainKey.replace(/\s/,"");
        } while (plainKey.match(/\d*\s\d*/));
        return plainKey;
    }

    Rectangle {
        x: 0
        y: 0
        z: 1
        width: parent.width
        height: 40
        color: "white"

        Row {
            x: 8
            y: 0
            height: parent.height
            spacing: 8

            Rectangle {
                id: sessionIdRectangle
                anchors.verticalCenter: parent.verticalCenter
                border.color: "#dedede"
                height: 32
                width: 200 - 8
                x: 8
                TextInput {
                    id: sessionIdTextInput
                    anchors.centerIn: parent
                    font.family: "Courier New"
                    font.bold: true
                    font.pixelSize: 22
                    maximumLength: 8
                    focus: true
                    selectionColor: "#408ad4"
                    //validator: RegExpValidator {regExp: /\d{8}/}
                    inputMask: "99 99 99 99;_"
                    onTextChanged: {
                        if (!text.match(/(\d{2}\s){3}\d{2}/)) {
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
                                text.match(/(\d{2}\s){3}\d{2}/)
                                && (event.key === Qt.Key_Enter || event.key === Qt.Key_Return)
                                ) {
                            sessionChanged(stripWhitespaces(sessionIdTextInput.text));
                        }
                    }
                    Text {
                        id: sessionIdPlaceholderText
                        color: "#a0676963"
                        text: "Session Key"
                        anchors.centerIn: parent
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
                width: 64
                height: 32
                anchors.verticalCenter: parent.verticalCenter

                property color loginbuttonColor: "#55ad3d"

                Text {
                    id: loginbuttonLabel
                    color: "#ffffff"
                    anchors.centerIn: parent
                    text: qsTr("+")
                    font.bold: true
                    font.pixelSize: 20
                }

                MouseArea {
                    id: loginbuttonMouseArea
                    anchors.fill: parent
                    onClicked: {
                        if (sessionIdTextInput.text.match(/(\d{2}\s){3}\d{2}/)) {
                            sessionChanged(stripWhitespaces(sessionIdTextInput.text));
                        }
                    }
                    hoverEnabled: true
                }

                color: loginbuttonColor != "#777777" && (loginbuttonMouseArea.pressed || loginbuttonMouseArea.containsMouse) ? Qt.darker(loginbuttonColor, 1.5) : loginbuttonColor
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Add this session")
                font.pixelSize: 14
            }
        }
    }

    ListView {
        id: sessionListView
        x: 0
        y: 48
        width: 760
        height: 172

        model: ListModel {}

        delegate: Item {
            width: parent.width
            height: 34
            Row {
                id: sessionRow
                width: parent.width
                Rectangle {
                    width: 8
                    height: 32
                    color: active ? "green" : "gray"
                }
                Rectangle {
                    width: parent.width - 4
                    height: 32
                    color: active ? "#e7efe7" : "#fff"
                    Row {
                        x: 24
                        width: 200
                        anchors.verticalCenter: parent.verticalCenter
                        Text {
                            text: formatSessionKey(keyword);
                            font.family: "Courier New"
                            font.bold: true
                            font.pixelSize: 22
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Column {
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                text: name
                                font.bold: true
                            }
                            Text {
                                text: shortName
                            }
                        }
                        spacing: 16
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            sessionChanged(keyword);
                            for (var i = 0; i < sessionListView.model.count; i++) {
                                sessionListView.model.get(i).active = (sessionListView.model.get(i).keyword === keyword);
                            }
                        }
                    }
                }
            }
        }

        Text {
            id: emptyListText
            x: 8
            text: qsTr("Not connected to any session")
            font.bold: true
            font.pixelSize: 16
        }
    }
}
