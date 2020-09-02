#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include "Container.hpp"

namespace Json::Definition
{
	class Array : public Container<Array, DT::Vector>
	{
	private:
		using Base::container;

	public:
		using ContainerType = DT::Vector;
		using Base::Base;
		Array(std::initializer_list<Node*> list) : Base(DT::Vector{list}) {}

		~Array()
		{
			std::for_each(container.rbegin(), container.rend(),
						  [](Node* ci) { delete ci; });
		}

		inline Node*	   operator[](const int& i) 		{ return container[i]; }
		inline const Node* operator[](const int& i) const 	{ return container[i]; }
		inline Node*	   at(const int& i) 				{ return container[i]; }
		inline const Node* at(const int& i) const 			{ return container[i]; }

		inline NodeType type() const override { return NodeType::array; }

		DT::String text() const override;
		DT::String formatText(int tab_depth) const override;

	}; // class Array

	inline const Node& Node::operator[](int i) const
	{
		if (this->type() == NodeType::array)
			return *(this->cast<Array>()->at(i));
		else
			throw NodeType::array;
	}

	template<>
	struct toEnumTraits<Array>
	{
		static constexpr auto value = NodeType::array;
	};
} // namespace Json::Definition

#endif
