import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        anchors.centerIn: parent

        onClicked: {
            //var path = Autho_engine.Direct_URL.toString();
            Qt.openUrlExternally(p_Direct_URL);
        }
    }
}
