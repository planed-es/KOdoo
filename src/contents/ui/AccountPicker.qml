import QtQuick 2.15
import "qrc:/"

AccountIndexBase {
  property var callback;
  pageName: i18n("Account Picker")
  createEnabled: false
  onOpenClicked: {
    if (typeof callback == "function")
      callback(model.id);
    pageStack.pop();
  }
}
