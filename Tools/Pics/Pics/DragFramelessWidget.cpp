#include <QMouseEvent>
#include <QGuiApplication>
#include "DragFramelessWidget.h"

static inline void setCursor(const QCursor& cur)
{
	QGuiApplication::setOverrideCursor(cur);
}

DragFramelessWidget::DragFramelessWidget() :
	QWidget(nullptr, Qt::FramelessWindowHint)
{
	this->setMouseTracking(true);
	::setCursor(Qt::ArrowCursor);
}

DragFramelessWidget::~DragFramelessWidget()
{
	QGuiApplication::restoreOverrideCursor();
}

void DragFramelessWidget::mousePressEvent(QMouseEvent* event)
{
	old_mouse_pos = event->globalPos();
	old_widget_pos = this->pos();
	this->mouseMoveEvent(event);
}

void DragFramelessWidget::mouseMoveEvent(QMouseEvent* event)
{
	using namespace Qt;
	auto cursor_pos = QCursor::pos();
	if(drag && event->buttons().testFlag(LeftButton)
	   && !windowState().testFlag(WindowMaximized))
		this->move(old_widget_pos + cursor_pos - old_mouse_pos);
	/*
	else
	{
		const int r = 5;
		const QPoint r_rd(r, -r);
		const QPoint r_ru(r, r);

		const QPoint w_lu = this->geometry().topLeft();
		const QPoint w_ru = this->geometry().topRight();
		const QPoint w_ld = this->geometry().bottomLeft();
		const QPoint w_rd = this->geometry().bottomRight();

		if(QRect(w_lu - r_rd, w_lu + r_rd).contains(cursor_pos) ||
		   QRect(w_rd - r_rd, w_rd + r_rd).contains(cursor_pos))
			::setCursor(SizeFDiagCursor);
		else
			if(QRect(w_ru - r_rd, w_ru + r_rd).contains(cursor_pos) ||
			   QRect(w_ld - r_rd, w_ld + r_rd).contains(cursor_pos))
			::setCursor(SizeBDiagCursor);
		else
			if(QRect(w_lu + r_ru, w_ru - r_rd).contains(cursor_pos) ||
			   QRect(w_ld + r_ru, w_rd - r_rd).contains(cursor_pos))
			::setCursor(SizeVerCursor);
		else
			if(QRect(w_lu - r_ru, w_ld + r_ru).contains(cursor_pos) ||
			   QRect(w_ru - r_ru, w_rd - r_rd).contains(cursor_pos))
			::setCursor(SizeHorCursor);
	}
	*/
	return QWidget::mouseMoveEvent(event);
}

void DragFramelessWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	using namespace Qt;
	if(event->button() == LeftButton)
		setWindowState(windowState() == WindowNoState ?
						   WindowMaximized : WindowNoState);
	else if(event->button() == RightButton) this->close();
	return QWidget::mouseDoubleClickEvent(event);
}
