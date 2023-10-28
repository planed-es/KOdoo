import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import org.planed.odoo 1.0
import "."

ModelForm {
  id: pageRoot

  controller: ProductController {
    onModelSaved: modelSaved.visible = true;
    onModelChanged: {
      productTypeInput.currentIndex =
        productTypeInput.indexOfValue
          (controller.model.productType);
    }
  }

  onApplyChangesToModel: {
    with (controller.model) {
      name = nameInput.text;
      defaultCode = defaultCodeInput.text;
      barcode = barcodeInput.text;
      productType = productTypeValue();
      standardPrice = parseFloat(standardPriceInput.text);
      lstPrice = parseFloat(lstPriceInput.text);
      // taxesIds
    }
  }

  TextField {
    id: nameInput
    Kirigami.FormData.label: "Name"
    text: controller.model.name
  }

  TextField {
    id: defaultCodeInput
    Kirigami.FormData.label: "Default code"
    text: controller.model.defaultCode
  }

  TextField {
    id: barcodeInput
    Kirigami.FormData.label: "Barcode"
    text: controller.model.barcode
  }

  function productTypeValue() {
    switch (productTypeInput.currentIndex) {
      case 0: return QOdooPartner.NoProductType;
      case 1: return QOdooPartner.Consumible;
      case 2: return QOdooPartner.Service;
    }
  }

  ComboBox {
    id: productTypeInput
    Kirigami.FormData.label: "Product type"
    model: ListModel {
      ListElement { text: "Undefined" }
      ListElement { text: "Consumible" }
      ListElement { text: "Service" }
    }
    textRole: "text"
  }

  TextField {
    id: standardPriceInput
    Kirigami.FormData.label: "StandardPrice"
    text: controller.model.standardPrice
    validator: DoubleValidator {}
  }

  TextField {
    id: lstPriceInput
    Kirigami.FormData.label: "LST Price"
    text: controller.model.lstPrice
  }
}
