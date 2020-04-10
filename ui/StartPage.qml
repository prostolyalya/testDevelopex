import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Item {
    anchors.fill: parent
    TextField {
        id: textUrl
        width: 300; height: 50
        anchors.centerIn: parent
        selectByMouse: true
        placeholderText: qsTr("example: https://www.google.com/")
    }
    TextField {
        id: textSearch
        width: 300; height: 50
        anchors.top: textUrl.bottom
        anchors.topMargin: 10
        anchors.left: textUrl.left
        selectByMouse: true
        placeholderText: qsTr("text for search")
    }
    TextField {
        id: textCountThreads
        width: 100; height: 50
        anchors.bottom: textUrl.top
        anchors.bottomMargin: 10
        anchors.left: textUrl.left
        selectByMouse: true
        text: "1"
    }
    TextField {
        id: textCountUrl
        width: 100; height: 50
        anchors.bottom: textUrl.top
        anchors.bottomMargin: 10
        anchors.right: textUrl.right
        selectByMouse: true
        text: "1"
    }
    Text {
        id: textThread
        anchors.bottom: textCountThreads.top
        anchors.bottomMargin: 10
        anchors.left: textCountThreads.left
        text: qsTr("Threads:")
    }
    Text {
        id: textUrls
        anchors.bottom: textCountUrl.top
        anchors.bottomMargin: 10
        anchors.right: textCountUrl.right
        text: qsTr("Urls count:")
    }
    Rectangle {
        id: buttonSearch
        width: 300; height: 50
        anchors.left: textSearch.left
        anchors.top: textSearch.bottom
        anchors.topMargin: 10
        color: "#7cafc4"
        Text {
            id: textButtonSearch
            anchors.centerIn: parent
            text: qsTr("Search")
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                var err = checkValid()
                if (!err) {
                    view.currentIndex = 1
                    startData.search(textSearch.text, textUrl.text, textCountThreads.text, textCountUrl.text)
                }
                else {
                    switch(err)
                    {
                    case(1):
                        textSearch.forceActiveFocus()
                        break

                    case(2):
                        textUrl.forceActiveFocus()
                        break

                    case(3):
                        textCountThreads.forceActiveFocus()
                        break

                    case(4):
                        textCountUrl.forceActiveFocus()
                        break

                    }

                }
            }
        }
    }
    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 10
        anchors.topMargin: 10
        width: 40; height: 40
        color: "#7cafc4"
        Text {
            anchors.centerIn: parent
            text: qsTr(">")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: view.currentIndex = 1
        }
    }
    function checkValid() {
        if(textSearch.text === "")
            return 1;
        if(textUrl.text === "")
            return 2;
        if(textCountThreads.text < 1 || textCountThreads.text > 32)
            return 3;
        if(textCountUrl.text < 1)
            return 4;
        return 0;
    }
}
