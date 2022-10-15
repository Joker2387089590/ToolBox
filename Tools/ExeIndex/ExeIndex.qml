import QtQuick 2.4
import QtQuick.Controls 6.2
import Tools.ExeIndex 0.1

Component {
    Item {
        id: exeIndex
        anchors.fill: parent

        property var dirs
        Connections {
            target: backend
            function onDirsChanged() {
                console.log("dirs changed", backend.dirs)
                dirs = backend.dirs
            }
        }

        Column {
            id: column
            x: parent.x
            y: parent.y

            width: 200
            height: parent.height

            Repeater {
                id: repeater
                model: exeIndex.dirs

                Rectangle {
                    width: column.width
                    height: 30
                    color: ["white", "gray"][index]
                    Text {
                        text: modelData
                        anchors.fill: parent
                    }
                }

            }
        }

        Button {
            id: btnNext
            x: 301
            y: 211
            width: 139
            height: 58
            text: qsTr("Next")
            onClicked: backend.next()
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
