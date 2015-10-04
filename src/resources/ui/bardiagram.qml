import QtQuick 1.1

Rectangle {
    width: 120
    height: 120
    color: "#00000000"

    Rectangle {
        id: okBar
        objectName: "okBar"
        x: 6
        y: 112 - height
        width: 24
        height: 0
        color: "#80ba24"

        Behavior on height { PropertyAnimation { easing.type: Easing.OutBounce; easing.amplitude: 2.0; easing.period: 1.5; duration: 750 } }
    }

    Rectangle {
        id: toSlowBar
        objectName: "toSlowBar"
        x: 34
        y: 112 - height
        width: 24
        height: 0
        color: "#f2a900"

        Behavior on height { PropertyAnimation { easing.type: Easing.OutBounce; easing.amplitude: 2.0; easing.period: 1.5; duration: 750 } }
    }

    Rectangle {
        id: toFastBar
        objectName: "toFastBar"
        x: 62
        y: 112 - height
        width: 24
        height: 0
        color: "#971b2f"
	
        Behavior on height { PropertyAnimation { easing.type: Easing.OutBounce; easing.amplitude: 2.0; easing.period: 1.5; duration: 750 } }
    }

    Rectangle {
        id: awayBar
        objectName: "awayBar"
        x: 90
        y: 112 - height
        width: 24
        height: 0
        color: "#4a5c66"

        Behavior on height { PropertyAnimation { easing.type: Easing.OutBounce; easing.amplitude: 2.0; easing.period: 1.5; duration: 750 } }
    }

    Rectangle {
        id: baseline
        x: 4
        y: 111
        width: 112
        height: 1
        rotation: 0
        color: "#9e9e9e"
    }
}
