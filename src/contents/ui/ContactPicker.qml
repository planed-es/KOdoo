import QtQuick 2.15
import "qrc:/"

ContactIndexBase {
  property var callback;
  pageName: i18n("Contact Picker")
  createEnabled: false
  onOpenClicked: {
    if (typeof callback == "function")
      callback(model.id);
    pageStack.pop();
  }
}
