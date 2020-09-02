#pragma once
#ifndef VALUE_H
#define VALUE_H

#include "Node.hpp"

namespace Json::Definition
{
	// All Value type base class
	template<typename T>
	class Value : public Node
	{
	protected:
		T value;
		using Base = Value<T>;

		// for array member init
		template<typename... U>
		Value(U... v) : value{v...} {}
		
	public:
		inline T&		get() { return value; }
		inline const T& get() const { return value; }
		inline void		set(const T& v) { value = v; }

		DT::String formatText(int tab_depth) const override;
	}; // class Value

	template<typename T>
	struct toEnumTraits<Value<T>>
	{
		static constexpr auto value = NodeType::value;
	};

} // namespace Json::Definition

#endif