import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import ResultPage 1.0

Item {
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        Text {
            id: titlePageText
            text: qsTr("Result:")
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 16
        }
        ScrollView {
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: titlePageText.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 60
            anchors.margins: 10
            clip: true

            TextArea {
                id: textResult
                selectByMouse: true

                anchors.left: parent.left
                anchors.top: parent.top
                width: parent.width; height: parent.height
                text: resultData.res
                Rectangle {
                    anchors.fill: parent
                    color: "#ebcbf4"
                    opacity: 0.2
                }
            }

        }
        Rectangle {
            id: buttonStop
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: 70; height: 40
            color: "#ebcbf4"
            Text {
                anchors.centerIn: parent
                font.pixelSize: 16
                text: qsTr("Stop")

            }
            MouseArea {
                anchors.fill: parent
                onClicked: resultData.stop()
            }
        }
        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 10
            anchors.topMargin: 10
            width: 40; height: 40
            color: "#7cafc4"
            Text {
                anchors.centerIn: parent
                text: qsTr("<")
            }
            MouseArea {
                anchors.fill: parent
                onClicked: view.currentIndex = 0
            }
        }
        Text {
            anchors.left: buttonStop.right
            anchors.top: buttonStop.top
            anchors.leftMargin: 10
            visible: resultData.ready
            text: qsTr("Please wait...")
        }

    }


}
