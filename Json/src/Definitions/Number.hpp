#pragma once
#ifndef NUMBER_H
#define NUMBER_H

#include "Value.hpp"

namespace Json::Definition
{
	class Number : public Value<int[3]>
	{
		inline int& i() { return value[0]; }
		inline int& f() { return value[1]; }
		inline int& e() { return value[2]; }

		inline const int& i() const { return value[0]; }
		inline const int& f() const { return value[1]; }
		inline const int& e() const { return value[2]; }

	public:
		Number(int integer = 0, int fraction = 0, int exponent = 0) noexcept :
			Base(integer, fraction, exponent) {}

		inline NodeType	type() const override { return NodeType::number; }
		DT::String text() const override;

		inline int toInt() const
		{
			if (f() == 0 && e() == 0) return i();
			throw "This number is not a interger.";
		}

		inline double toDouble() const
		{
			std::int64_t fc = 1;
			for (auto fi = f() / 10; fi > 0; fi /= 10) fc *= 10;
			return (i() + double(f()) / fc) * pow(10, e());
		}

		inline void set(int ii, int ff, int ee)
		{
			i() = ii;
			f() = ff;
			e() = ee;
		}
	}; // class Number

	template<>
	struct toEnumTraits<Number>
	{
		static constexpr auto value = NodeType::number;
	};

} // namespace Json::Definition

#endif
