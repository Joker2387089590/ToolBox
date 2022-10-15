import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Window {
    id: window
    objectName: "window"
    width: 1280
    height: 720
    visible: true
    title: qsTr("Tool Box!")

    ToolBar {
        id: openSide
        width: btnExpandSide.checked ? 50 : 300
        height: 50

        ToolButton {
            id: btnExpandSide
            checkable: true
            width: 40
            height: 40
            text: checked ? ">" : "<"
        }
    }

    ColumnLayout {
        id: side
        spacing: 2
        x: 0
        y: 50
        width: openSide.width
        anchors.top: openSide.bottom
        anchors.bottom: parent.bottom

        Repeater {
            model: tools
            ToolButton {
                Layout.fillHeight: true
                Layout.fillWidth: true
                property var name: modelData

                contentItem: Text {
                    text: parent.name
                    color: parent.down ? "#17a81a" : "#21be2b"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    opacity: enabled ? 1.0 : 0.3
                }

                background: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 40
                    color: Qt.darker("#33333333", parent.enabled
                                     && (parent.checked
                                         || parent.highlighted) ? 1.5 : 1.0)
                    opacity: enabled ? 1 : 0.3
                    visible: parent.down || (parent.enabled
                                             && (parent.checked
                                                 || parent.highlighted))
                }
            }
        }
    }

    Rectangle {
        id: back
        color: "#cc000000"
        anchors.left: side.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Loader {
            id: curLoader
            anchors.fill: back
        }
    }

    property Component curTool
    onCurToolChanged: {
        curLoader.sourceComponent = curTool
        console.log("curTool changed")
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
