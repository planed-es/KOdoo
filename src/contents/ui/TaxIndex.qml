import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import "qrc:/"

ModelIndex {
  id: root
  pageName: i18n("Taxes")
  columns: ["name", "id", "amountType", "amount"]
  collection: TaxCollection {
    id: collection
    limit: 10
  }

  onCreateClicked: pageStack.push(Qt.resolvedUrl("TaxForm.qml"))
  onOpenClicked: pageStack.push(Qt.resolvedUrl("TaxForm.qml"), {loadModelId: model.id})
}
