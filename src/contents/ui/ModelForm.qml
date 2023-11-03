import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0

Kirigami.ScrollablePage {
  id: pageRoot
  property int loadModelId: 0
  property QtObject controller
  property bool withReset: true
  default property alias content: form.children

  signal applyChangesToModel()

  Component.onCompleted: {
    console.log("Creating view with loadModelId =", loadModelId);
    if (loadModelId === 0)
    {
      loader.visible = false;
      form.visible = true;
      controller.create();
    }
    else
      controller.load(loadModelId);
  }

  title: controller.model.name

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
      Kirigami.Action {
        icon.name: "reload"
        text: i18n("Reset")
        tooltip: i18n("Reset all the fields to their initial value")
        onTriggered: controller.requestPropertyRefresh()
        enabled: withReset
        visible: withReset
      }
    ]
  }

  Connections {
    target: controller
    function onModelChanged() {
      loader.visible = false;
      form.visible = true;
    }
  }

  BusyIndicator {
    id: loader
    visible: true
  }

  Kirigami.FormLayout {
    id: form
    visible: false

    Kirigami.InlineMessage {
      id: modelSaved
      Layout.fillWidth: true
      text: i18n("Your changes have been saved")
      type: Kirigami.MessageType.Positive
    }
  }
}
