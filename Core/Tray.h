#pragma once
#include <QMenu>
namespace ToolBox::Cores
{
class TrayPrivate;
class Tray : public QMenu
{
	Q_OBJECT
	Q_PROPERTY(bool remainWhenShow
			   READ isRemainWhenShow
			   WRITE setRemainWhenShow
			   NOTIFY remainWhenShowChanged)
public:
	explicit Tray(QWidget* parent = nullptr);
	~Tray();

	bool isRemainWhenShow() const;
	void setRemainWhenShow(bool value);

	void add(const QString& text, const std::function<void(QAction*)>& init);

signals:
	void actived();
	void remainWhenShowChanged(bool remain);

private:
	TrayPrivate* d;
};
}
