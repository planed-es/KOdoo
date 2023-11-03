import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.20 as Kirigami

Item {
  id: root
  property var columns: []
  property var model: []
  property var defaultCellComponent: gridTableDefaultCellComponent
  property int hoveredRow: -1

  signal modelClicked(QtObject model, int row)
  signal requestNewLine()

  implicitHeight: layout.height

  function cellComponentAt(row, column) {
    return defaultCellComponent;
  }

  onModelChanged: console.log("Model changed", model.length, model)

  GridLayout {
    id: layout
    columns: root.columns.length
    anchors { left: parent.left; right: parent.right }

    Repeater {
      model: root.columns.length
      delegate: Label {
        text: root.columns[index].label
        font.bold: true
        Layout.fillWidth: root.columns[index].isMain
      }
    }

    Repeater {
      model: root.columns.length * root.model.length
      delegate: Rectangle {
        property int rowIndex:    index / root.columns.length
        property int columnIndex: index % root.columns.length
        property QtObject model:  root.model[rowIndex]
        property var column:      root.columns[columnIndex]
        implicitWidth: loader.implicitWidth
        implicitHeight: loader.implicitHeight
        Layout.fillWidth: true
        border.width: 1
        border.color: Kirigami.Theme.textColor
        visible: !model.markedForDeletion
        Kirigami.Theme.colorSet: Kirigami.Theme.View
        color: {
          if (rowIndex == root.hoveredRow)
            return Kirigami.Theme.activeBackgroundColor;
          if ((rowIndex % 2) == 0)
            return Kirigami.Theme.alternateBackgroundColor;
          return Kirigami.Theme.backgroundColor;
        }
        Loader {
          id: loader
          property int rowIndex:    parent.rowIndex
          property int columnIndex: parent.columnIndex
          property QtObject model:  parent.model
          property var column:      parent.column
          sourceComponent: root.cellComponentAt(rowIndex, columnIndex)
          anchors.fill: parent
          anchors.leftMargin: 5
          anchors.rightMargin: 5
          clip: true
        }
        MouseArea {
          anchors.fill: parent
          hoverEnabled: true
          onEntered: root.hoveredRow = rowIndex
          onExited:  root.hoveredRow = -1
          onClicked: root.modelClicked(model, rowIndex)
        }
      }
    }

    Button {
      Layout.fillWidth: true
      Layout.columnSpan: parent.columns
      text: i18n("Add line")
      onClicked: root.requestNewLine()
    }
  }

  Component {
    id: gridTableDefaultCellComponent
    Label {
      text: model ? column.valueFor(model).toString() : "N/A"
      Connections {
        target: column
        function onPropertyChanged() {
          text = column.valueFor(model).toString();
        }
      }
    }
  }
}

