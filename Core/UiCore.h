#ifndef UI_CORE_H
#define UI_CORE_H

#include <QWidget>
#include <QIcon>
#include <QGridLayout>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QToolButton>

QT_BEGIN_NAMESPACE

class UiCore
{
public:
	QToolButton*	caller_account;
	QToolButton*	caller_pics;

	QStackedWidget* work_panel;

	void setupUi(QWidget* w)
	{
		using SP = QSizePolicy::Policy;

		w->setWindowTitle("Tool Box");
		w->setWindowIcon(QIcon(":/ToolBox.png"));
		{
			auto layout = new QGridLayout(w);

			auto side_bar = new QWidget(w);
			side_bar->setSizePolicy(SP::Fixed, SP::Preferred);
			{
				auto layout = new QVBoxLayout(side_bar);
				layout->setSpacing(0);
				layout->setContentsMargins(0, 0, 0, 0);
				QSizePolicy sp(SP::Expanding, SP::Preferred);

				caller_account = new QToolButton(side_bar);
				caller_account->setSizePolicy(sp);
				layout->addWidget(caller_account);

				caller_pics = new QToolButton(side_bar);
				caller_pics->setSizePolicy(sp);
				layout->addWidget(caller_pics);

				auto spacer = new QSpacerItem(20, 40, SP::Fixed, SP::Expanding);
				layout->addItem(spacer);
			}
			layout->addWidget(side_bar, 0, 0, 1, 1);

			work_panel = new QStackedWidget(w);
			layout->addWidget(work_panel, 0, 1, 1, 1);
		}
	}

	void appendWorkPanel(QWidget* w)
	{
		if(!w) return;
		work_panel->addWidget(w);

		work_panel->setCurrentWidget(w);
	}
};

namespace Ui { class Core : public UiCore {}; }

QT_END_NAMESPACE

#endif // UI_CORE_H
