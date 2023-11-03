import QtQuick 2.15
import org.kde.kodooexample 1.0
import "qrc:/"

AccountIndexBase {
  id: root
  pageName: i18n("Accounts")
  onCreateClicked: pageStack.push(Qt.resolvedUrl("AccountForm.qml"))
  onOpenClicked: pageStack.push(Qt.resolvedUrl("AccountForm.qml"), {loadModelId: model.id});
}
