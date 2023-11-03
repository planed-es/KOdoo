import QtQuick 2.15
import org.kde.kodooexample 1.0
import "qrc:/"

ProductIndexBase {
  id: root
  pageName: i18n("Products")
  onCreateClicked: pageStack.push(Qt.resolvedUrl("ProductForm.qml"))
  onOpenClicked: pageStack.push(Qt.resolvedUrl("ProductForm.qml"), {loadModelId: model.id});
}
