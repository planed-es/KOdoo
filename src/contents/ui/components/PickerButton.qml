import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
  property var pickerView
  property var value: 0

  onClicked: {
    pageStack.layers.push(pickerView, {
      callback: function(modelId) {
        value = modelId;
        pageStack.layers.pop();
      }
    });
  }
}
