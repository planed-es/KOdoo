import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import "qrc:/"

ModelIndex {
  id: root
  pageName: i18n("Contacts")
  columns: ["name", "vat"]
  collection: ContactCollection {
    id: collection
    limit: 15
  }
  filterComponent: Pane {
    GridLayout {
      flow: GridLayout.TopToBottom
      rows: 2

      Label { text: i18n("Name") }
      TextField {
        id: nameFilter
        placeholderText: i18n("Filter by name...")
        onTextChanged: root.updateFilters("name", text)
      }
    }
  }

  onCreateClicked: pageStack.push(Qt.resolvedUrl("ContactForm.qml"))
  onOpenClicked: pageStack.push(Qt.resolvedUrl("ContactForm.qml"), {loadModelId: model.id});
}
