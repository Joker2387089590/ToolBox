#pragma once
#ifndef NODE_H
#define NODE_H

#include "../DataType.hpp"

namespace Json::Definition
{
	// Short name of DataType
	namespace DT = DataType;

	// All Json type base
	class Node
	{
	public:
		virtual ~Node() = default;
		virtual NodeType type() const { return NodeType::invalid; }

		// Transform Node to text
		// The function implementations is in namespace Text in Text.h
		// No whitespace text
		virtual DT::String text() const = 0;
		// Text inserted tab, space and newline
		virtual DT::String formatText(int tab_depth) const = 0;

		// safe cast to type, return nullptr if failed
		template<typename T>
		inline const T* cast() const
		{
			if (this->type() & toEnum<T>)
				return static_cast<const T*>(this);
			else
				return nullptr;
		}
		template<typename T>
		inline T* cast()
		{
			return const_cast<T*>(static_cast<const Node*>(this)->cast<T>());
		}

		// Convenient operator for Array[int]
		const Node& operator[](int i) const;
		inline Node&	   operator[](int i)
		{
			return const_cast<Node&>(static_cast<const Node&>(*this)[i]);
		}

		// convenient operator for Object[inner::string]
		const Node& operator[](const DT::String& key) const;
		inline Node& operator[](const DT::String& key)
		{
			return const_cast<Node&>(static_cast<const Node&>(*this)[key]);
		}
	}; // class Node

} // namespace Json::Definition

#endif
