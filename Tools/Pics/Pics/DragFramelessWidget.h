#ifndef DRAG_FRAMELESS_WIDGET_H
#define DRAG_FRAMELESS_WIDGET_H

#include <QWidget>

class DragFramelessWidget : public QWidget
{
	Q_OBJECT

public:
	// A Widget can be dragged should have no parent widget.
	explicit DragFramelessWidget();
	~DragFramelessWidget() override;

	void setDragable(bool b);
	bool isDragable() const;

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;

	bool drag;
	QPoint old_mouse_pos;
	QPoint cur_mouse_pos;
	QPoint old_widget_pos;
};

#endif // DRAG_FRAMELESS_WIDGET_H
