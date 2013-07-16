import QtQuick 1.1

Rectangle {
    width: 180
    height: 100
    color: "#00000000"

    Rectangle {
        id: okBar
        objectName: "okBar"
        x: 20
        y: 100 - height
        width: 32
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
    }

    Rectangle {
        id: toSlowBar
        objectName: "toSlowBar"
        x: 56
        y: 100 - height
        width: 32
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
    }

    Rectangle {
        id: toFastBar
        objectName: "toFastBar"
        x: 92
        y: 100 - height
        width: 32
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
    }

    Rectangle {
        id: awayBar
        objectName: "awayBar"
        x: 128
        y: 100 - height
        width: 32
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
    }

    Rectangle {
        id: baseline
        x: 10
        y: 99
        width: 160
        height: 1
        rotation: 0
        color: "#9e9e9e"
    }
}
