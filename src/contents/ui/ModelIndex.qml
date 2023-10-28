import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import org.kde.kirigami 2.19 as Kirigami

Kirigami.ScrollablePage {
  id: root
  property string pageName
  property var columns
  property var collection
  property int hoveredIndex: 0
  property alias filterComponent: view.header
  property var filters: ({})

  signal createClicked()
  signal openClicked(QtObject model)

  title: pageName + ` - Page ${collection.page + 1} / ${collection.pageCount}`

  function updateFilters(field, value) {
    if (value == null)
      delete filters[field];
    else
      filters[field] = value;
    collection.filter(filters);
  }

  actions {
    contextualActions: [
      Kirigami.Action {
        icon.name: "list-add"
        text: i18n("New")
        onTriggered: root.createClicked()
      },
      Kirigami.Action {
        icon.name: "go-previous"
        text: i18n("Previous page")
        enabled: collection.page > 0
        onTriggered: collection.page--
      },
      Kirigami.Action {
        icon.name: "go-next"
        text: i18n("Next page")
        enabled: (collection.page + 1) < collection.pageCount
        onTriggered: collection.page++
      }
    ]
  }

  Kirigami.CardsListView {
    id: view
    model: collection.models
    headerPositioning: ListView.PullBackHeader
    delegate: Kirigami.AbstractCard {
      property QtObject cardModel: root.collection.models[index]

      contentItem: Item {
        implicitWidth: delegateLayout.implicitWidth
        implicitHeight: delegateLayout.implicitHeight

        MouseArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
          onClicked: root.openClicked(cardModel)
        }

        GridLayout {
          id: delegateLayout
          anchors { left: parent.left; top: parent.top; right: parent.right }
          rowSpacing: Kirigami.Units.largeSpacing
          columnSpacing: Kirigami.Units.largeSpacing
          columns: width > Kirigami.Units.gridUnit * 20 ? 2 : 1
          clip: true

          Kirigami.Icon {
            source: "applications-graphics"
            Layout.fillHeight: true
            Layout.maximumHeight: Kirigami.Units.iconSizes.huge
            Layout.preferredHeight: height
          }
          ColumnLayout {
            Kirigami.Heading {
              level: 2
              text: cardModel[columns[0]]
            }
            Kirigami.Separator {
              Layout.fillWidth: true
            }
            Label {
              Layout.fillWidth: true
              wrapMode: Text.WordWrap
              text: {
                let result = "";
                for (var i = 1 ; i < columns.length ; ++i) {
                  if (i > 1) result += ' | ';
                  result += `<b>${columns[i]}:</b> ${cardModel[columns[i]]}`;
                }
                return result;
              }
            }
          }
        } // END GridLayout
      } // END Item
    } // END AbstractCard
  } // END CardsListView
}
