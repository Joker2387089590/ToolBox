#pragma once
#ifndef NULL_H
#define NULL_H

#include "Node.hpp"

namespace Json::Definition
{
	class Null : public Node
	{
	public:
		NodeType   type() const override { return NodeType::null; }
		DT::String text() const override;
		DT::String formatText(int tab_depth) const override;
	};

	template<>
	struct toEnumTraits<Null>
	{
		static constexpr auto value = NodeType::null;
	};

} // namespace Json::Definition

#endif