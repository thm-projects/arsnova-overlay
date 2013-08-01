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
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#7ab844"
            }

            GradientStop {
                position: 1
                color: "#52901c"
            }
        }

        Behavior on height { PropertyAnimation { easing.type: Easing.OutBounce; easing.amplitude: 2.0; easing.period: 1.5; duration: 750 } }
    }

    Rectangle {
        id: toSlowBar
        objectName: "toSlowBar"
        x: 34
        y: 112 - height
        width: 24
        height: 0
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#fec929"
            }

            GradientStop {
                position: 1
                color: "#d6a100"
            }
        }

        Behavior on height { PropertyAnimation { easing.type: Easing.OutBounce; easing.amplitude: 2.0; easing.period: 1.5; duration: 750 } }
    }

    Rectangle {
        id: toFastBar
        objectName: "toFastBar"
        x: 62
        y: 112 - height
        width: 24
        height: 0
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ed601c"
            }

            GradientStop {
                position: 1
                color: "#c53800"
            }
        }

        Behavior on height { PropertyAnimation { easing.type: Easing.OutBounce; easing.amplitude: 2.0; easing.period: 1.5; duration: 750 } }
    }

    Rectangle {
        id: awayBar
        objectName: "awayBar"
        x: 90
        y: 112 - height
        width: 24
        height: 0
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ebebeb"
            }

            GradientStop {
                position: 1
                color: "#c3c3c3"
            }
        }

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
