import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import "qrc:/"

ModelIndex {
  property alias moveType: collection.moveType
  pageName: i18n("Invoices")
  columns: ["name", "ref", "date", "state"]
  collection: InvoiceCollection {
    id: collection
    limit: 10
  }

  onCreateClicked: pageStack.push(Qt.resolvedUrl("InvoiceForm.qml"), {moveType: moveType})
  onOpenClicked: pageStack.push(Qt.resolvedUrl("InvoiceForm.qml"), {loadModelId: model.id});
}
