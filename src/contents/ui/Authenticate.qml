import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.settings 1.0
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0

Kirigami.Page {
  id: root

  title: i18n("Configure Odoo Server")

  actions.main: Kirigami.Action {
    text: i18n("Connect")
    icon.name: "network-connect"
    tooltip: i18n("Logs in using your Odoo server's XMLRPC API")
    onTriggered: {
      busyIndicator.visible = true;
      authenticateError.visible = form.visible = false;
      odooSettings.url = serverUrlInput.text;
      odooSettings.database = databaseInput.text;
      odooSettings.username = usernameInput.text;
      odooSettings.password = passwordInput.text;
      odooSettings.authenticate();
    }
  }

  Settings {
    category: "odooSettings"
    property alias serverUrl: serverUrlInput.text
    property alias database: databaseInput.text
    property alias username: usernameInput.text
    property alias password: passwordInput.text
  }

  Connections {
    target: odooSettings
    function onAuthenticationFailure() {
      busyIndicator.visible = false;
      authenticateError.visible = form.visible = true;
    }
  }

  BusyIndicator {
    id: busyIndicator
    visible: false
    anchors.centerIn: parent
  }

  Kirigami.FormLayout {
    id: form
    visible: true
    anchors.centerIn: parent

    Kirigami.InlineMessage {
      id: authenticateError
      Layout.columnSpan: 2
      Layout.fillWidth: true
      text: i18n("Could not authenticate to the Odoo server")
      type: Kirigami.MessageType.Error
    }
    
    TextField {
      id: serverUrlInput
      Kirigami.FormData.label: "Odoo Server URL"
    }

    TextField {
      id: databaseInput
      Kirigami.FormData.label: "Odoo Database"
    }

    TextField {
      id: usernameInput
      Kirigami.FormData.label: "Username"
    }

    TextField {
      id: passwordInput
      Kirigami.FormData.label: "API key"
      echoMode: TextInput.Password
    }

    Button {
      action: root.actions.main
    }
  }
}
