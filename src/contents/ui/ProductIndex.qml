import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import "qrc:/"

ModelIndex {
  id: root
  pageName: i18n("Products")
  columns: ["name", "defaultCode"]
  collection: ProductCollection {
    id: collection
    limit: 15
  }
  filterComponent: Pane {
    GridLayout {
      flow: GridLayout.TopToBottom
      rows: 2

      Label { text: i18n("Name") }
      TextField {
        placeholderText: i18n("Filter by name...")
        onTextChanged: root.updateFilters("name", text)
      }

      Label { text: i18n("Default code") }
      TextField {
        placeholderText: i18n("Filter by default code...")
        onTextChanged: root.updateFilters("defaultCode", text)
      }
    }
  }

  onCreateClicked: pageStack.push(Qt.resolvedUrl("ProductForm.qml"))
  onOpenClicked: pageStack.push(Qt.resolvedUrl("ProductForm.qml"), {loadModelId: model.id});
}

