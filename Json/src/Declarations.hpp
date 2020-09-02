#pragma once
#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <cstdint>

namespace Json::Definition
{
	class Node;

	class Null;

	template<typename T>
	class Value;
	class Boolean;
	class String;
	class Number;

	template<typename Sub, typename T>
	class Container;
	class Array;
	class Object;

	// Flags of Node Type
	using u8 = std::uint8_t;
	enum class NodeType : u8
	{
		invalid = 0,

		null	  = 0x01,
		boolean	  = 0x02,
		string	  = 0x04,
		number	  = 0x08,
		value	  = boolean | string | number,
		array	  = 0x10,
		object	  = 0x20,
		container = array | object,

		// This two bits can be used to extend new type.
		unused_7 = 0x40,
		unused_8 = 0x80
	};
	inline u8 operator&(NodeType l, NodeType r)
	{
		return static_cast<u8>(l) & static_cast<u8>(r);
	}

	// Trait every class to their enum,
	// Convenient for cast Node to Sub Node.
	template<typename T>
	struct toEnumTraits
	{
		static constexpr auto value = NodeType::invalid;
	};
	template<typename T>
	inline constexpr auto toEnum = toEnumTraits<T>::value;

} // namespace Json::Definition

#endif // DECLARATIONS_H
