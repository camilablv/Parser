import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

import "Components"

Window {
    id: window
    visible: true
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Parser")
    Test{
        size: 6
    }
    Item {
        id: settings
        width: parent.width
        height: parent.height / 2
        Rectangle {
            anchors.fill: parent
            anchors.margins: parent.height * 0.05
            anchors.centerIn: parent
            color: "#e9bfee"
        }
    }

    Item {
        width: parent.width
        height: parent.height / 2
        anchors.top: settings.bottom
        Rectangle {
            anchors.fill: parent
            anchors.margins: parent.height * 0.05
            anchors.centerIn: parent
            color: "#f7ff00"
            Column {
                anchors.fill: parent
                Rectangle {
                    width: parent.width
                    height: parent.height / 3
                    Row {
                        width: parent.width * 0.9
                        height: parent.height * 0.4
                        Item {
                            width: parent.width * 0.4
                            height: parent.height
                            Text {
                                anchors.fill: parent
                                text: "Имя файла:"
                                font.pixelSize: height * 0.9
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                        Item {
                            width: parent.width * 0.6
                            height: parent.height
                            Rectangle {
                                anchors.fill: parent
                                border.width: 1
                                TextInput {
                                    anchors.fill: parent
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    width: parent.width
                    height: parent.height / 3
                    Button {
                        width: parent.width * 0.4
                        height: parent.height * 0.6
                        anchors.centerIn: parent
                        text: "Start"
                        font.pixelSize: height * 0.9
                        onClicked: {
                            controller.start()
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / 3
                    ProgressBar {
                        width: parent.width
                        height: parent.height * 0.2
                        anchors.centerIn: parent
                        value: 0.4
                    }
                }
            }
        }
    }
}
