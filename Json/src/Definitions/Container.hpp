#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

#include "Node.hpp"

namespace Json::Definition
{
	// All Container type base class
	// Only used as pointer or reference
	class ContainerPointer : public Node
	{
	protected:
		ContainerPointer() = default;
		~ContainerPointer() = default;
	};

	// CTRF to make Subclasses consistent
	template<typename Sub, typename T>
	class Container : public ContainerPointer
	{
	protected:
		T container;
		using Base = Container<Sub, T>;

	public:
		// Proxy Subclasses' constructor

		Container(T&& c = T()) noexcept : container(std::move(c)) {}
		Container(const T& c) noexcept : container(c) {}

		Container(Sub&& other) noexcept : container(std::move(other.container)) {}
		Container(const Sub& other) noexcept : container(other.container) {}

		Sub& operator=(const T& c) noexcept { container = c; return *this; }
		Sub& operator=(T&& c) noexcept { container = std::move(c); return *this; }

		Sub& operator=(const Sub& other) noexcept { if(this != &other) container = other.container; return *this; }
		Sub& operator=(Sub&& other) noexcept { this->container = std::move(other.container); return *this; }

		inline T&		get() 			{ return container; }
		inline const T& get() const 	{ return container; }
		inline void		set(const T& c) { container = c; }

		inline auto size() const { return container.size(); }

		// Subclasses due to clean elements in their containers.
		~Container() = 0;
	}; // class Container

	template<typename Sub, typename T>
	Container<Sub, T>::~Container() {}

	template<>
	struct toEnumTraits<ContainerPointer>
	{
		static constexpr auto value = NodeType::container;
	};

} // namespace Json::Definition

#endif
