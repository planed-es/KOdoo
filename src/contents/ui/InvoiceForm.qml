import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import com.planed.odoo 1.0 as Odoo
import "."
import "./components"

Kirigami.ScrollablePage {
  id: pageRoot
  property int loadModelId: 0

  InvoiceController {
    id: controller
    onModelSaved: modelSaved.visible = true
  }

  signal applyChangesToModel()

  onApplyChangesToModel: {
    with (controller.model) {
      name = nameInput.text;
      ref = refInput.text;
      partnerId = partnerInput.value
    }
  }

  Component.onCompleted: {
    if (loadModelId === 0)
    {
      loader.visible = false;
      form.visible = true;
      controller.create();
    }
    else
      controller.load(loadModelId);
  }

  actions {
    main: Kirigami.Action {
      text: i18n("Save")
      icon.name: "document-save"
      tooltip: i18n("Persist the changes to the remote Odoo server")
      onTriggered: {
        modelSaved.visible = false;
        applyChangesToModel();
        controller.save();
      }
    }
    contextualActions: [
    ]
  }

  Connections {
    target: controller
    function onModelChanged() {
      loader.visible = false;
      form.visible = true;
    }
    function onModelReceived(message) {
      faultDisplay.visible = true;
      faultDisplay.text = message;
    }
  }

  BusyIndicator {
    id: loader
    visible: true
  }

  ColumnLayout {
    id: form
    visible: false
    GridLayout {
      columns: 2

      Kirigami.FormLayout {
        Layout.fillWidth: true

        Kirigami.InlineMessage {
          id: modelSaved
          Layout.fillWidth: true
          text: i18n("Your changes have been saved")
          type: Kirigami.MessageType.Positive
        }

        Kirigami.InlineMessage {
          id: faultDisplay
          Layout.fillWidth: true
          type: Kirigami.MessageType.Error
        }

        TextField {
          id: nameInput
          Kirigami.FormData.label: "Name"
          text: controller.model.name
        }

        TextField {
          id: refInput
          Kirigami.FormData.label: "Reference"
          text: controller.model.ref
        }

        PickerButton {
          id: partnerInput
          Kirigami.FormData.label: "Contact"
          pickerView: Qt.resolvedUrl("ContactPicker.qml")
          value: controller.model.partnerId
          text: controller.partner ? controller.partner.name : "N/A"
          onValueChanged: controller.fetchPartner(value)
        }
      }

      Kirigami.FormLayout {
        Layout.fillWidth: true
      }
    }

    Kirigami.Separator {
      Layout.fillWidth: true
    }

    GridTable {
      Layout.fillWidth: true
      id: tableView
      model: controller.lines
      columns: controller.lineColumns
      onModelClicked: function(line, row) {
        pageStack.push(Qt.resolvedUrl("InvoiceLineForm.qml"), {invoiceController: controller, loadModelId: row + 1});
      }
      onRequestNewLine: controller.addLine()
    }

    //
  }
}
