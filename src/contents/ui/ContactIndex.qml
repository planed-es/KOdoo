import QtQuick 2.15
import "qrc:/"

ContactIndexBase {
  id: root
  pageName: i18n("Contacts")
  onCreateClicked: pageStack.push(Qt.resolvedUrl("ContactForm.qml"))
  onOpenClicked: pageStack.push(Qt.resolvedUrl("ContactForm.qml"), {loadModelId: model.id});
}
