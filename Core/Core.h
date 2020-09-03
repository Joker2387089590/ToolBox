#ifndef CORE_H
#define CORE_H

#include <QShowEvent>
#include <QCloseEvent>
#include <type_traits>

#include <Account.h>
#include <Pics.h>
#include "Tray.h"

namespace Ui { class Core; }

class Core : public QWidget
{
	Q_OBJECT

public:
	Core(QWidget *parent = nullptr);
	~Core();

	bool isTrayRemainWhenShow() const;
	void setTrayRemainWhenShow(bool value);
	Tray* tray();

signals:
	void aboutToQuit();

protected:
	void showEvent(QShowEvent *event) override;
	void closeEvent(QCloseEvent *event) override;

private:
	Ui::Core* ui;

	Account* account{nullptr};
	Pics* pics{nullptr};
	void initSideBar();

	template<typename W,
			 std::enable_if_t<std::is_convertible_v<W*, QWidget*>, int> = 0>
	void changeWorkPanel(W*& w);

	void activeAccount();

	Tray* tray_icon;
	bool tray_remain_when_show{false};
	void initTrayAction();
	void activeTray(QSystemTrayIcon::ActivationReason r);

	void exitApp();
};

#endif // CORE_H
