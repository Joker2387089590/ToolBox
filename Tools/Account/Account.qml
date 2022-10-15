import QtQuick 2.0
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.0
import QtQml.Models

Item {
    Component {
        id: objNode
        Item {
            id: obj
            property string name: "title"
            property var content: {
                "a": 1,
                "b": "x",
                "c": [1, 2],
                "d": {}
            }

            Component {
                id: baseNode
                Item {
                    property string name
                    property var content: undefined
                    Text {
                        text: name + ": " + content
                    }
                }
            }

            ObjectModel {
                id: items
            }

            onContentChanged: {
                items.clear()
                for (let k in content) {
                    let o = content[k]
                    let item = undefined
                    if (o instanceof Object)
                        item = objNode.createObject()
                    else if (o instanceof Array)
                        item = arrNode.createObject()
                    else
                        item = baseNode.createObject()
                    item.name = k
                    item.content = o
                    items.append(item)
                }
            }

            ToolBar {
                id: title
                anchors.left: parent.left
                anchors.right: parent.right
                height: 30
                ToolButton {
                    id: expander
                    width: 30
                    height: parent.height
                    text: nextNodeArea.visible ? "-" : "+"
                    onClicked: {
                        nextNodeArea.visible = !nextNodeArea.visible
                    }
                }
                Text {
                    id: nodeText
                    anchors.left: expander.right
                    anchors.right: parent.right
                    verticalAlignment: Text.AlignVCenter
                    height: parent.height
                    text: obj.name
                }
            }

            Item {
                id: placeholder
                anchors.left: parent.left
                width: 30
                height: nextNodeArea.height
            }

            ColumnLayout {
                id: nextNodeArea
                anchors.top: title.bottom
                anchors.left: placeholder.right
                anchors.right: parent.right
                spacing: 2

                Repeater {
                    model: items
                }
            }
        }
    }

    Component {
        id: arrNode
        Item {
            ToolBar {}
        }
    }

    ScrollView {
        id: scrollView
        anchors.fill: parent
        Loader {
            id: loader
            anchors.fill: parent
            sourceComponent: objNode

            ColumnLayout {
                id: columnLayout
                x: 189
                y: 359
                width: 100
                height: 100
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/

