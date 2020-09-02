#pragma once
#ifndef STRING_H
#define STRING_H

#include "Value.hpp"

namespace Json::Definition
{

	class String : public Value<DT::String>
	{
	public:
		// construct from string
		String(DT::String&& v = DT::String()) noexcept : Base(std::move(v)) {}
		String(const DT::String& v) noexcept : Base(v) {}

		// construct from this class
		String(String&& other) noexcept : Base(std::move(other.value)) {}
		String(const String& other) noexcept : Base(other.value) {}

		// assign from string
		String& operator=(const DT::String& v) noexcept
		{
			value = v;
			return *this;
		}
		String& operator=(DT::String&& v) noexcept
		{
			value = std::move(v);
			return *this;
		}

		// assign from this class
		String& operator=(const String& other) noexcept
		{
			if (this != &other) this->value = other.value;
			return *this;
		}
		String& operator=(String&& other) noexcept
		{
			this->value = std::move(other.value);
			return *this;
		}

		inline NodeType	  type() const override { return NodeType::string; }
		DT::String text() const override;
	}; // class String

	template<>
	struct toEnumTraits<String>
	{
		static constexpr auto value = NodeType::string;
	};

} // namespace Json::Definition

#endif
