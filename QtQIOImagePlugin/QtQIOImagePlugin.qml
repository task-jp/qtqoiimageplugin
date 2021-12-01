import QtQuick
import QtQuick.Window

Window {
    width: 300
    height: 300
    visible: true
    title: qsTr("Hello QOI Image")

    Image {
        anchors.centerIn: parent
        source: 'len_std.qoi'
    }
}
