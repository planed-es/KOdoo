import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0

Kirigami.ScrollablePage {
  id: pageRoot

  implicitWidth: Kirigami.Units.gridUnit * 20

  leftPadding: 0
  rightPadding: 0
  bottomPadding: 0
  topPadding: 0
  title: i18n("Main Menu")

  ListModel {
    id: menuEntries

    ListElement {
      title: "Contacts"
      targetPage: "ContactIndex.qml"
    }

    ListElement {
      title: "Products"
      targetPage: "ProductIndex.qml"
    }

    ListElement {
      title: "Taxes"
      targetPage: "TaxIndex.qml"
    }

    ListElement {
      title: "Invoices"
      targetPage: "InvoiceIndex.qml"
    }
  }

  background: Rectangle {
    anchors.fill: parent
    Kirigami.Theme.colorSet: Kirigami.Theme.View
    color: Kirigami.Theme.backgroundColor
  }

  Kirigami.PagePool {
    id: mainPagePool
  }

  ColumnLayout {
    spacing: 0
    Repeater {
      focus: true
      model: menuEntries
      delegate: Kirigami.BasicListItem {
        label: title
action: Action {
  onTriggered: pageStack.push(Qt.resolvedUrl(targetPage));
}
/*
        action: Kirigami.PagePoolAction {
          pagePool: mainPagePool
          basePage: pageRoot
          page: 'qrc:' + targetPage
        }
*/
      }
    }
  }
}
