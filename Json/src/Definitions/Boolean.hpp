#pragma once
#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "Value.hpp"

namespace Json::Definition
{
	class Boolean : public Value<bool>
	{
	public:
		Boolean(bool b = false) : Base(b) {}

		NodeType   type() const override { return NodeType::boolean; }
		DT::String text() const override;
	}; // class Boolean

	template<>
	struct toEnumTraits<Boolean>
	{
		static constexpr auto value = NodeType::boolean;
	};

} // namespace Json::Definition

#endif