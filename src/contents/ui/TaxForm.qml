import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import com.planed.odoo 1.0 as Odoo
import "."

ModelForm {
  id: pageRoot

  controller: TaxController {
    onModelSaved: modelSaved.visible = true;
    onModelChanged: {
      taxTypeInput.currentIndex =
        taxTypeInput.indexOfValue(controller.model.typeTaxUse);
      taxScopeInput.currentIndex =
        taxScopeInput.indexOfValue(controller.model.taxScope);
      amountTypeInput.currentIndex =
        amountTypeInput.indexOfValue(controller.model.amountType);
    }
  }

  onApplyChangesToModel: {
    with (controller.model) {
      name = nameInput.text;
      description = descriptionInput.text;
      typeTaxUse = taxTypeInput.currentValue;
      amountType = amountTypeInput.currentValue;
      taxScope = taxScopeInput.currentValue;
      active = activeInput.checked;
      priceInclude = priceIncludeInput.checked;
      includeBaseAmount = includeBaseAmountInput.checked;
      isBaseAffected = isBaseAffected.checked;
      amount = parseFloat(amount.text);
    }
  }

  TextField {
    id: nameInput
    Kirigami.FormData.label: "Name"
    text: controller.model.name
  }

  TextField {
    id: descriptionInput
    Kirigami.FormData.label: "Description"
    text: controller.model.description
  }

  ComboBox {
    id: taxTypeInput
    Kirigami.FormData.label: "Tax type"
    model: [
      { text: "Undefined", value: Odoo.Tax.NoTaxType },
      { text: "Sale",      value: Odoo.Tax.SaleTax },
      { text: "Purchase",  value: Odoo.Tax.PurchaseTax }
    ]
    textRole: "text"
    valueRole: "value"
  }

  ComboBox {
    id: amountTypeInput
    Kirigami.FormData.label: "Amount type"
    model: [
      { text: "Undefined", value: Odoo.Tax.NoAmountType },
      { text: "Grouped",   value: Odoo.Tax.GroupedAmount },
      { text: "Fixed",     value: Odoo.Tax.FixedAmount },
      { text: "Percent",   value: Odoo.Tax.PercentAmount },
      { text: "Division",  value: Odoo.Tax.DivisionAmount }
    ]
    textRole: "text"
    valueRole: "value"
  }

  ComboBox {
    id: taxScopeInput
    Kirigami.FormData.label: "Tax scope"
    model: [
      { text: "Undefined",  value: Odoo.Tax.NoTaxScope },
      { text: "Consumible", value: Odoo.Tax.Consumible },
      { text: "Service",    value: Odoo.Tax.Service }
    ]
    textRole: "text"
    valueRole: "value"
  }

  TextField {
    id: amountInput
    Kirigami.FormData.label: "Amount"
    text: controller.model.amount
    validator: DoubleValidator {}
  }

  CheckBox {
    id: activeInput
    Kirigami.FormData.label: "Active"
    checked: controller.model.active
  }

  CheckBox {
    id: priceIncludeInput
    Kirigami.FormData.label: "Price include"
    checked: controller.model.priceInclude
  }

  CheckBox {
    id: includeBaseAmountInput
    Kirigami.FormData.label: "Includes base amount"
    checked: controller.model.includeBaseAmount
  }

  CheckBox {
    id: isBaseAffectedInput
    Kirigami.FormData.label: "Is base affected"
    checked: controller.model.isBaseAffected
  }
}

