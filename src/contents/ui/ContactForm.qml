import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.kodooexample 1.0
import "."

ModelForm {
  id: pageRoot

  controller: ContactController {
    id: controller
    onModelChanged: function() {
      countryIdInput.modelChanged();
    }
    onModelSaved: modelSaved.visible = true;
  }

  onApplyChangesToModel: {
    with (controller.model) {
      name = nameInput.text;
      vat = vatInput.text;
      phone = phoneInput.text;
      city = cityInput.text;
      street = streetInput.text;
      zip = zipInput.text;
      countryId = countryIdInput.currentValue;
      stateId = stateIdInput.currentValue;
      comment = commentInput.text;
    }
  }

  resources: [
    CountryCollection {
      id: countries
    },

    CountryStateCollection {
      id: countryStates
      countryId: countryIdInput.currentValue
    }
  ]

  TextField {
    id: nameInput
    Kirigami.FormData.label: "Name"
    text: controller.model.name
  }

  TextField {
    id: vatInput
    Kirigami.FormData.label: "VAT"
    text: controller.model.vat
  }

  TextField {
    id: phoneInput
    Kirigami.FormData.label: "Phone"
    text: controller.model.phone
  }

  Kirigami.Separator {
    Kirigami.FormData.isSection: true
    Kirigami.FormData.label: "Address"
  }

  ComboBox {
    id: countryIdInput
    Kirigami.FormData.label: "Country"
    model: countries.models
    textRole: "name"
    valueRole: "id"
    onModelChanged: currentIndex = indexOfValue(controller.model.countryId)
  }

  ComboBox {
    id: stateIdInput
    Kirigami.FormData.label: "State"
    model: countryStates.models
    textRole: "name"
    valueRole: "id"
    onModelChanged: currentIndex = indexOfValue(controller.model.stateId)
  }

  TextField {
    id: cityInput
    Kirigami.FormData.label: "City"
    text: controller.model.city
  }

  TextField {
    id: streetInput
    Kirigami.FormData.label: "Street"
    text: controller.model.street
  }

  TextField {
    id: zipInput
    Kirigami.FormData.label: "Zip"
    text: controller.model.zip
  }

  Kirigami.Separator {
    Kirigami.FormData.isSection: true
    Kirigami.FormData.label: "Additional data"
  }

  TextField {
    id: commentInput
    Kirigami.FormData.label: "Comment"
    text: controller.model.comment
  }
}
