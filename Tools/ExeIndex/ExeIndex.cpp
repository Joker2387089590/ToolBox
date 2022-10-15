#include <filesystem>
#include <vector>
#include <ranges>
#include <algorithm>
#include <QQmlEngineExtensionPlugin>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include "ExeIndex.h"

namespace ToolBox::ExeIndexs
{
namespace fs = std::filesystem;

using Launcher = fs::recursive_directory_iterator;
class IndexIter : private Launcher
{
public:
	using Launcher::Launcher;

	using Launcher::operator==;
	using Launcher::operator->;
	using Launcher::operator*;

	IndexIter& operator++()
	{
		++self();
		self() = std::ranges::find_if(self(), [](auto&& entry) {
			return entry.path().extension() == ".exe";
		});
		return *this;
	}

	QStringList dir() const
	{
		int depth = self().depth() + 1;
		QStringList dirs;
		dirs.reserve(depth);

		auto p = self()->path().end();
		for(int i = 0; i < depth; ++i)
			dirs.emplace_back(QString::fromStdWString((--p)->wstring()));
		return dirs;
	}

private:
	Launcher& self() noexcept { return *this; }
	const Launcher& self() const noexcept { return *this; }
};

inline IndexIter begin(IndexIter iter) noexcept { return iter; }
inline IndexIter end(IndexIter) noexcept { return {}; }

class ExeIndexData
{
public:
	IndexIter iter{};
	QStringList dirs{};
};

ExeIndex::ExeIndex(QObject* parent) :
	QObject(parent),
	d(new ExeIndexData)
{}

ExeIndex::~ExeIndex() { delete d; }

void ExeIndex::init(QQmlContext* root, QQmlEngine* engine)
{
	auto context = new QQmlContext(root);
	context->setContextProperty("backend", this);

	QQmlComponent component(engine, QUrl("qrc:/Tools/ExeIndex/ExeIndex.qml"));
	if(component.isError())
	{
		qDebug() << component.errorString();
		throw std::exception();
	}

	auto item = qobject_cast<QQmlComponent*>(component.create(context));
	if(!item) throw std::exception();
	context->setParent(item);

	setRoot(".");
	emit toolAdded("Link Make");
}

void ExeIndex::next()
{
	++d->iter;
	d->dirs = d->iter.dir();
	emit dirsChanged();
}

void ExeIndex::setRoot(const QString& root)
{
	d->iter = IndexIter(root.toStdWString());
}

QStringList ExeIndex::dirs() const { return d->dirs; }
}
