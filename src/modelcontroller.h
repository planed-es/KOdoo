#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QPointer>
#include <odoo-qt/QOdoo.h>

class ModelControllerInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QOdooModel *model MEMBER model NOTIFY modelChanged)
    Q_PROPERTY(int modelId READ id NOTIFY modelChanged)
public:
    explicit ModelControllerInterface(QObject *parent = nullptr);

    static OdooService &service();

    template<typename MODEL>
    void create()
    {
        model = new MODEL(this);
        emit modelChanged();
    }

    template<typename MODEL>
    void load(int id, std::function<void(MODEL *)> callback = std::function<void(MODEL *)>())
    {
        QPointer<ModelControllerInterface> self(this);

        service().fetch<MODEL>(id, [self, this, callback](MODEL *result) {
            if (!self.isNull()) {
                model = result;
                if (callback)
                    callback(result);
                emit modelChanged();
            }
        });
    }

    Q_INVOKABLE void save();
    Q_INVOKABLE void requestPropertyRefresh();

    QOdooModel::IdType id() const
    {
        return model ? model->id() : 0;
    }

signals:
    void modelChanged();
    void modelSaved();
    void errorReceived(QString);

protected:
    QOdooModel *model = nullptr;
};

#endif // MODELCONTROLLER_H
