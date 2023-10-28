import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import "."

Kirigami.ApplicationWindow {
    property bool loggedIn: false
    id: root

    title: i18n("KOdooExample")

    minimumWidth: Kirigami.Units.gridUnit * 20
    minimumHeight: Kirigami.Units.gridUnit * 20

    onClosing: App.saveWindowGeometry(root)

    onWidthChanged: saveWindowGeometryTimer.restart()
    onHeightChanged: saveWindowGeometryTimer.restart()
    onXChanged: saveWindowGeometryTimer.restart()
    onYChanged: saveWindowGeometryTimer.restart()

    Component.onCompleted: App.restoreWindowGeometry(root)

    // This timer allows to batch update the window size change to reduce
    // the io load and also work around the fact that x/y/width/height are
    // changed when loading the page and overwrite the saved geometry from
    // the previous session.
    Timer {
        id: saveWindowGeometryTimer
        interval: 1000
        onTriggered: App.saveWindowGeometry(root)
    }

    property int counter: 0

    globalDrawer: Kirigami.GlobalDrawer {
        title: i18n("KOdooExample")
        titleIcon: "applications-graphics"
        isMenu: !root.isMobile
        actions: [
            Kirigami.Action {
                text: i18n("Disconnect")
                enabled: loggedIn
                icon.name: "network-disconnect"
                onTriggered: loggedIn = false
            },
            Kirigami.Action {
                text: i18n("About KOdooExample")
                icon.name: "help-about"
                onTriggered: pageStack.layers.push('qrc:About.qml')
            },
            Kirigami.Action {
                text: i18n("Quit")
                icon.name: "application-exit"
                onTriggered: Qt.quit()
            }
        ]
    }

    contextDrawer: Kirigami.ContextDrawer {
        id: contextDrawer
    }

    pageStack.initialPage: loggedIn ? mainView : authenticatePage

    Component {
      id: authenticatePage
      Authenticate {}
    }

    Component {
      id: mainView
      MainView {}
    }

    Connections {
      target: odooSettings
      function onAuthenticated() {
        loggedIn = true;
      }
    }
}
