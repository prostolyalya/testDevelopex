import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import "ui"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Developex Test Task")

    SwipeView {
        id: view
        currentIndex: 0
        anchors.fill: parent
        Page {

            StartPage {
                id: startPage
            }
        }
        Page {
            ResultPage {
                id: resultPage
            }
        }
    }

}
