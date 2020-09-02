#pragma once
#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#define TYPE_STD 	0
#define TYPE_QT 	1
#define TYPE_BASIC 	2

// Select the data type of class inner implement
#ifndef DATA_TYPE
	#ifdef QT_VERSION
		#define DATA_TYPE TYPE_QT
	#else
		#define DATA_TYPE TYPE_STD
	#endif
#endif

#include "Declarations.hpp"

#if DATA_TYPE == TYPE_STD
	#include <cctype>
	#include <string>
	#include <map>
	#include <vector>
	#include <algorithm>

	// Choose what type the inner implement uses
	namespace Json::DataType
	{
		using Definition::Node;

		using Vector = std::vector<Node*>;
		using String = std::string;
		using Map 	 = std::map<String, Node*>;

	} // namespace Json::DataType

#elif DATA_TYPE == TYPE_QT
	#include <QString>
	#include <QMap>
	#include <QVector>
	#include <algorithm>

	// Choose what type the inner implement uses
	namespace Json::DataType
	{
		using Definition::Node;

		using Vector = QVector<Node*>;
		using String = QString;
		using Map 	 = QMap<String, Node*>;

	} // namespace Json::DataType

#elif DATA_TYPE == BASIC
#endif

#endif // DATA_TYPE_H
