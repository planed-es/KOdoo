import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import com.planed.odoo 1.0 as Odoo
import "."
import "./components"

ModelForm {
  id: pageRoot
  property QtObject invoiceController
  property QtObject invoice: invoiceController.model

  title: i18n("Invoice line #") + loadModelId
  withReset: false

  controller: InvoiceLineController {
    id: controller
    invoice: pageRoot.invoice
    onModelSaved: {
      invoiceController.lineChanged(model);
      pageStack.pop();
    }
  }

  actions.main: Kirigami.Action {
    text: i18n("Apply changes")
    icon.name: "answer-correct"
    tooltip: i18n("Confirm the changes applied to the invoice line")
    onTriggered: {
      applyChangesToModel();
      controller.save();
    }
  }

  onApplyChangesToModel: {
    with (controller.model) {
      name = nameInput.text
      accountId = accountInput.value;
      productId = productInput.value;
      quantity = parseFloat(quantityInput.text);
      priceUnit = parseFloat(priceUnitInput.text);
    }
  }

  PickerButton {
    id: productInput
    Kirigami.FormData.label: "Product"
    pickerView: Qt.resolvedUrl("ProductPicker.qml")
    value: controller.model.productId
    text: controller.product ? controller.product.name : "N/A"
    onValueChanged: controller.fetchProduct(value)
  }

  TextField {
    id: nameInput
    Kirigami.FormData.label: "Name"
    text: controller.model.name
  }

  PickerButton {
    id: accountInput
    Kirigami.FormData.label: "Account"
    pickerView: Qt.resolvedUrl("AccountPicker.qml")
    value: controller.model.accountId
    text: controller.account ? controller.account.name : "N/A"
    onValueChanged: controller.fetchAccount(value)
  }

  TextField {
    id: quantityInput
    Kirigami.FormData.label: "Quantity"
    validator: DoubleValidator {}
    text: controller.model.quantity
  }

  TextField {
    id: priceUnitInput
    Kirigami.FormData.label: "Price unit"
    validator: DoubleValidator {}
    text: controller.model.priceUnit
  }
}
