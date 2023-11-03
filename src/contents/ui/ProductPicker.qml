import QtQuick 2.15
import "qrc:/"

ProductIndexBase {
  property var callback;
  pageName: i18n("Product Picker")
  createEnabled: false
  onOpenClicked: {
    if (typeof callback == "function")
      callback(model.id);
    pageStack.pop();
  }
}
