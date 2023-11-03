import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import com.planed.odoo 1.0 as Odoo
import "."

ModelForm {
  id: pageRoot

  controller: AccountController {
    onModelSaved: modelSaved.visible = true;
  }

  onApplyChangesToModel: {
    with (controller.model) {
      name = nameInput.text;
      code = codeInput.text;
      reconcile = reconcileInput.checked;
      deprecated = deprecated.checked;
      nonTrade = nonTrade.checked;
      // groupId
    }
  }

  TextField {
    id: nameInput
    Kirigami.FormData.label: "Name"
    text: controller.model.name
  }

  TextField {
    id: codeInput
    Kirigami.FormData.label: "Default code"
    validator: IntValidator {}
    text: controller.model.code
  }

  CheckBox {
    id: reconcileInput
    Kirigami.FormData.label: "Reconcile"
    checked: controller.model.reconcile
  }

  CheckBox {
    id: deprecatedInput
    Kirigami.FormData.label: "Deprecated"
    checked: controller.model.deprecated
  }

  CheckBox {
    id: nonTradeInput
    Kirigami.FormData.label: "Non-Trade"
    checked: controller.model.nonTrade
  }
}

