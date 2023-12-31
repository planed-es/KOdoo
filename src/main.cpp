#include "merdemodel.h"
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QUrl>
#include <odoo-qt/QOdoo.h>
#ifdef Q_OS_ANDROID
#include <GuiQApplication>
#else
#include <QApplication>
#endif

#include "app.h"
#include "version-kodooexample.h"
#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedString>

#include "accountcollection.h"
#include "accountcontroller.h"
#include "contactcollection.h"
#include "contactcontroller.h"
#include "countrycollection.h"
#include "countrystatecollection.h"
#include "invoicecollection.h"
#include "invoicecontroller.h"
#include "invoicelinecontroller.h"
#include "kodooexampleconfig.h"
#include "odoosettings.h"
#include "productcollection.h"
#include "productcontroller.h"
#include "taxcollection.h"
#include "taxcontroller.h"
#include <iostream>
#include <odoo-qt/QOdooTableModel.h>

using namespace std;

OdooService *odooService = nullptr;

#ifdef Q_OS_ANDROID
Q_DECL_EXPORT
#endif
int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef Q_OS_ANDROID
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle(QStringLiteral("org.kde.breeze"));
#else
    QApplication app(argc, argv);

    // Default to org.kde.desktop style unless the user forces another style
    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    }
#endif

#ifdef Q_OS_WINDOWS
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }

    QApplication::setStyle(QStringLiteral("breeze"));
    auto font = app.font();
    font.setPointSize(10);
    app.setFont(font);
#endif

    KLocalizedString::setApplicationDomain("kodooexample");
    QCoreApplication::setOrganizationName(QStringLiteral("KDE"));

    KAboutData aboutData(
        // The program name used internally.
        QStringLiteral("kodooexample"),
        // A displayable program name string.
        i18nc("@title", "KOdoo"),
        // The program version string.
        QStringLiteral(KODOOEXAMPLE_VERSION_STRING),
        // Short description of what the app does.
        i18n("Kirigami-based client for Odoo, by PlanED S.L."),
        // The license this code is released under.
        KAboutLicense::GPL,
        // Copyright Statement.
        i18n("(c) 2023"));
    QImage applicationIcon(":/images/logo.png");
    aboutData.addAuthor(i18nc("@info:credit", "Michael Martin Moro"),
                        i18nc("@info:credit", "Maintainer"),
                        QStringLiteral("michael@planed.es"),
                        QStringLiteral("https://github.com/Plaristote"));
    // aboutData.setTranslator(i18nc("NAME OF TRANSLATORS", "Your names"), i18nc("EMAIL OF TRANSLATORS", "Your emails"));
    aboutData.setBugAddress("https://github.com/planed-es/KOdoo/issues");
    aboutData.setHomepage("https://github.com/planed-es/KOdoo");
    aboutData.setProgramLogo(applicationIcon);
    KAboutData::setApplicationData(aboutData);
    QGuiApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("org.kde.kodooexample")));

    QQmlApplicationEngine engine;

    auto config = KOdooExampleConfig::self();

    qmlRegisterSingletonInstance("org.kde.kodooexample", 1, 0, "Config", config);

    qmlRegisterSingletonType("org.kde.kodooexample", 1, 0, "About", [](QQmlEngine *engine, QJSEngine *) -> QJSValue {
        return engine->toScriptValue(KAboutData::applicationData());
    });

    qmlRegisterType<ContactCollection>("org.kde.kodooexample", 1, 0, "ContactCollection");
    qmlRegisterType<ContactController>("org.kde.kodooexample", 1, 0, "ContactController");
    qmlRegisterType<CountryCollection>("org.kde.kodooexample", 1, 0, "CountryCollection");
    qmlRegisterType<CountryStateCollection>("org.kde.kodooexample", 1, 0, "CountryStateCollection");
    qmlRegisterType<ProductCollection>("org.kde.kodooexample", 1, 0, "ProductCollection");
    qmlRegisterType<ProductTemplateCollection>("org.kde.kodooexample", 1, 0, "ProductTemplateCollection");
    qmlRegisterType<ProductController>("org.kde.kodooexample", 1, 0, "ProductController");
    qmlRegisterType<TaxCollection>("org.kde.kodooexample", 1, 0, "TaxCollection");
    qmlRegisterType<TaxController>("org.kde.kodooexample", 1, 0, "TaxController");
    qmlRegisterType<AccountCollection>("org.kde.kodooexample", 1, 0, "AccountCollection");
    qmlRegisterType<AccountController>("org.kde.kodooexample", 1, 0, "AccountController");
    qmlRegisterType<InvoiceCollection>("org.kde.kodooexample", 1, 0, "InvoiceCollection");
    qmlRegisterType<InvoiceController>("org.kde.kodooexample", 1, 0, "InvoiceController");
    qmlRegisterType<InvoiceLineController>("org.kde.kodooexample", 1, 0, "InvoiceLineController");

    qmlRegisterType<QOdooProduct>("com.planed.odoo", 1, 0, "Product");
    qmlRegisterType<QOdooTax>("com.planed.odoo", 1, 0, "Tax");
    qmlRegisterType<QOdooAccount>("com.planed.odoo", 1, 0, "Account");
    qmlRegisterType<QOdooInvoice>("com.planed.odoo", 1, 0, "Invoice");
    qmlRegisterType<QOdooInvoiceLine>("com.planed.odoo", 1, 0, "InvoiceLine");
    qmlRegisterType<QOdooTableColumn>("com.planed.odoo", 1, 0, "TableColumn");
    qmlRegisterType<QOdooTableModel>("com.planed.odoo", 1, 0, "TableModel");
    qmlRegisterType<MerdeModel>("com.planed.odoo", 1, 0, "MerdeModel");
    qRegisterMetaType<QOdooModel *>("QOdooModel*");
    qRegisterMetaType<const QOdooModel *>("const QOdooModel*");
    qRegisterMetaType<const QOdooInvoiceLine *>("const QOdooInvoiceLine*");

    App application;
    qmlRegisterSingletonInstance("org.kde.kodooexample", 1, 0, "App", &application);

    OdooSettings odooSettings;
    engine.rootContext()->setContextProperty(QString("odooSettings"), &odooSettings);

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
