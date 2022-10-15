#pragma once
#include <QObject>
#include <QtQml/QtQml>

namespace ToolBox::ExeIndexs
{
class ExeIndexData;
class ExeIndex : public QObject
{
	Q_OBJECT
	QML_ELEMENT
	Q_PROPERTY(QStringList dirs READ dirs NOTIFY dirsChanged)
public:
	explicit ExeIndex(QObject* parent = nullptr);
	~ExeIndex();

public:
	QStringList dirs() const;

public slots:
	void init(QQmlContext* root, QQmlEngine* engine);
	Q_INVOKABLE void next();
	void setRoot(const QString& root);

signals:
	void inited(QQmlComponent* item);
	void toolAdded(const QString& name);
	void dirsChanged();

private:
	ExeIndexData* d;
};
}
