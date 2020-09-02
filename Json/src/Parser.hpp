#pragma once
#ifndef PARSER_H
#define PARSER_H

#include "Definitions.hpp"

namespace Json::Parser
{
	using namespace Definition;

	// The operations which is necessary for parsing.
	// You need to implement it if your specified type is used.
	inline namespace Helper
	{
		using Sptr	= DT::String::iterator;
		using Scptr = DT::String::const_iterator;
		using Char	= DT::String::value_type;

		inline auto toUnicode(Scptr p)
		{
		#if DATA_TYPE == TYPE_STD
			return *p;
		#elif DATA_TYPE == TYPE_QT
			return p->unicode();
		#else
			static_assert(false, "No correct data type, please define DATA_TYPE");
		#endif
		}

		inline bool inList(std::initializer_list<Char> list, Scptr p)
		{
			for (auto ci : list)
				if (toUnicode(p) == ci) return true;
			return false;
		}

		inline bool isWhiteSpace(Scptr p)
		{
			return inList({' ', '\n', '\t', '\r'}, p);
		}

		// Construct from ptr
		inline DT::String str(Scptr p, int size)
		{
		#if DATA_TYPE == TYPE_STD
			return DT::String(p, p + size);
		#elif DATA_TYPE == TYPE_QT
			return DT::String(p, size);
		#else
			static_assert(false, "No correct data type, please define DATA_TYPE");
		#endif
		}

		inline DT::String toLower(const DT::String& text)
		{
		#if DATA_TYPE == TYPE_STD
			DT::String r;
			r.resize(text.size());
			std::transform(text.begin(), text.end(), r.begin(), ::tolower);
			return r;
		#elif DATA_TYPE == TYPE_QT
			return text.toLower();
		#else
			static_assert(false, "No correct data type, please define DATA_TYPE");
		#endif
		}

		// Test if p is a digit or a sign symbol
		inline bool isDigit(Scptr p)
		{
		#if DATA_TYPE == TYPE_STD
			return !!std::isdigit(static_cast<unsigned char>(*p));
		#elif DATA_TYPE == TYPE_QT
			return p->isDigit();
		#else
			static_assert(false, "No correct data type, please define DATA_TYPE");
		#endif
		}
		inline int toDigit(Scptr p)
		{
		#if DATA_TYPE == TYPE_STD
			return *p - '0';
		#elif DATA_TYPE == TYPE_QT
			return p->digitValue();
		#else
			static_assert(false, "No correct data type, please define DATA_TYPE");
		#endif
		}

		inline bool isPrint(Scptr p)
		{
		#if DATA_TYPE == TYPE_STD
			return std::isprint(*p);
		#elif DATA_TYPE == TYPE_QT
			return p->isPrint();
		#else
			static_assert(false, "No correct data type, please define DATA_TYPE");
		#endif
		}

		inline std::uint16_t castUnicode(const DT::String& u, bool& check)
		{
			#if DATA_TYPE == TYPE_STD
			try
			{
				std::size_t convert_count;
				auto r = std::stoul(u, &convert_count, 16);
				if (convert_count != 4) throw;
				check = true;
				return static_cast<std::uint16_t>(r);}
			catch (...)
			{
				check = false;
				return 0;
			}
			#elif DATA_TYPE == TYPE_QT
				return static_cast<std::uint16_t>(u.toUInt(&check, 16));
			#else
				static_assert(false, "No correct data type, please define DATA_TYPE");
			#endif
		}

		inline bool contains(const DT::Map& m, const DT::String& key)
		{
			return m.find(key) != m.end();
		}

		inline void insert(DT::Map& m, const DT::String& key, Node* value)
		{
		#if DATA_TYPE == TYPE_STD
			m.insert({key, value});
		#elif DATA_TYPE == TYPE_QT
			m.insert(key, value);
		#else
			static_assert(false, "No correct data type, please define DATA_TYPE");
		#endif
		}
	} // inline namespace Helper

	// Forward Declarations of token parser functions

	// If returns normally,
	// p locates at next to the null literal's last letter.
	[[nodiscard]] inline Null* meetNull(Scptr& p, const Scptr te);

	// If returns normally,
	// p locates at next to the boolean literal's last letter.
	[[nodiscard]] inline Boolean* meetBoolean(Scptr& p, const Scptr te);

	// if the function returns normally,
	// p locates at next to the number's last digit.
	[[nodiscard]] inline Number* meetNumber(Scptr& p, const Scptr te);

	// Begin ptr, p, should be next to left _"_.
	// If returns normally, p is at the location of right _"_.
	[[nodiscard]] inline String* meetString(Scptr& p, const Scptr te);

	// Begin ptr, p, should be next to _[_.
	// If returns normally, p is at the location of _]_.
	[[nodiscard]] inline Array* meetArray(Scptr& p, const Scptr te);

	// Begin ptr, p, should be next to _{_.
	// If returns normally, p is at the location of _}_.
	[[nodiscard]] inline Object* meetObject(Scptr& p, const Scptr te);

	Null* meetNull(Scptr& p, const Scptr te)
	{
		if ((toUnicode(p) == 'n' || toUnicode(p) == 'N') && (te - p > 4))
		{
			auto nulltext = str(p, 4);
			p += 4;
			if (toLower(nulltext) == "null") return new Null;
		}
		throw NodeType::null;
	} // meet Null

	Boolean* meetBoolean(Scptr& p, Scptr const te)
	{
		if ((toUnicode(p) == 't' || toUnicode(p) == 'T') && (te - p > 4))
		{
			auto truetext = str(p, 4);
			p += 4;
			if (toLower(truetext) == "true") return new Boolean(true);
		}
		if ((toUnicode(p) == 'f' || toUnicode(p) == 'F') && (te - p > 5))
		{
			auto falsetext = str(p, 4);
			p += 5;
			if (toLower(falsetext) == "false") return new Boolean(false);
		}
		throw NodeType::boolean;
	} // meet Boolean

	Number* meetNumber(Scptr& p, Scptr const te)
	{
		auto isEnd = [](Scptr p)
		{
			return inList({']', '}', ','}, p) || isWhiteSpace(p);
		};

		int integer	 = 0;
		int fraction = 0;
		int exponent = 0;

		bool issuccess = isDigit(p);

		bool ispositive = true;
		if(toUnicode(p) == '-')
		{
			ispositive = false;
			++p;
		}

		bool isexppos = true; // test exp positive

		if (toUnicode(p) == '0')
		{
			++p;
			issuccess = isEnd(p) || inList({'.', 'e', 'E'}, p);
		}

		for (int* cur = &integer; issuccess; ++p)
		{
			if (p == te)
			{
				issuccess = false;
				break;
			}

			// Only here the function exits normally,
			// and ++p would not execute
			if (isEnd(p)) break;

			if (isDigit(p))
			{
				try
				{
					// overflow ? (*cur * 10) || (*cur + toDigit(p))
					*cur *= 10;
					int pd = toDigit(p);
					*cur += pd;
					if(*cur < pd) throw;
					continue;
				}
				catch (...)
				{
					issuccess = false;
					break;
				}
			}

			switch (toUnicode(p))
			{
			case '.':
				if (cur != &integer)
					issuccess = false;
				else
					cur = &fraction;
				continue;

			case 'e':
			case 'E':
				if (cur == &exponent)
					issuccess = false;
				else
					cur = &exponent;
				continue;

			case '+':
			case '-':
				if (cur != &exponent)
					issuccess = false;
				else
					isexppos = (toUnicode(p) == '+');
				continue;

			default: issuccess = false; break;
			} // switch toUnicode(p)
		} // for issuccess

		integer = ispositive ? integer : -integer;
		if (issuccess) return new Number(integer, fraction, exponent);

		throw NodeType::number;
	} // meet Number

	String* meetString(Scptr& p, const Scptr te)
	{
		bool issuccess = ((*(p - 1)) == '\"');
		for (DT::String r; issuccess; ++p)
		{
			if (p == te || !isPrint(p))
			{
				issuccess = false;
				break;
			}
			if (toUnicode(p) == '\"') return new String(std::move(r));

			if (toUnicode(p) == '\\')
			{
				++p;
				switch (toUnicode(p))
				{
				case '\"':
				case '/':
				case '\\': break;

				// Whitespace
				case 'b': r.push_back('\b'); continue;
				case 'f': r.push_back('\f'); continue;
				case 'n': r.push_back('\n'); continue;
				case 'r': r.push_back('\r'); continue;
				case 't': r.push_back('\t'); continue;

				// hex unicode charactor
				case 'u':
				{
					if (te - ++p > 4)
					{
						bool b;
						auto v = castUnicode(str(p, 4), b);
						if (!b)
							issuccess = false;
						else
						{
							r.push_back(Char(v));
							p += 3;
						}
					}
					else
						issuccess = false;
					continue;
				}

				default: issuccess = false; continue;
				} // switch toUnicode(p)
			} // if p == '\\'
			r.push_back(toUnicode(p));
		} // for issuccess
		throw NodeType::string;
	} // meet String

	Array* meetArray(Scptr& p, const Scptr te)
	{
		bool issuccess = (*(p - 1) == '[');
		bool isfin	   = false;
		for (DT::Vector r; issuccess; ++p)
		{
			if (p == te) throw NodeType::array;

			if (isWhiteSpace(p)) continue;

			switch (toUnicode(p))
			{
			case ']':
				if (!isfin)
				{
					issuccess = false;
					continue;
				}
				return new Array(std::move(r));

			case ',':
				if (!isfin)
					issuccess = false;
				else
					isfin = false;
				continue;

			case '\"':
				if (isfin)
					issuccess = false;
				else
				{
					r.push_back(meetString(++p, te));
					isfin = true;
				}
				continue;

			case '{':
				if (isfin)
					issuccess = false;
				else
				{
					r.push_back(meetObject(++p, te));
					isfin = true;
				}
				continue;

			case '[':
				if (isfin)
					issuccess = false;
				else
				{
					r.push_back(meetArray(++p, te));
					isfin = true;
				}
				continue;

			case 'n':
			case 'N':
				if (isfin)
					issuccess = false;
				else
				{
					r.push_back(meetNull(p, te));
					isfin = true;
					--p;
				}
				continue;

			case 't':
			case 'T':
			case 'f':
			case 'F':
				if (isfin)
					issuccess = false;
				else
				{
					r.push_back(meetBoolean(p, te));
					isfin = true;
					--p;
				}
				continue;

			default:
				if (!isfin && (isDigit(p) || toUnicode(p) == '-'))
				{
					r.push_back(meetNumber(p, te));
					isfin = true;
					--p;
				}
				else
					issuccess = false;
				continue;
			} // switch toUnicode(p)
		} // for issuccess
		throw NodeType::array;
	} // meet Array

	Object* meetObject(Scptr& p, Scptr const te)
	{
		bool issuccess = (*(p - 1) == '{');

		String* curkey	 = nullptr;
		Node*	curvalue = nullptr;

		// This flag will be changed only meet _,_ or _:_
		bool iskey = true;

		// test if it has finished getting a key or a value.
		bool isfin = false;

		for (DT::Map r; issuccess; ++p)
		{
			if (p == te)
			{
				issuccess = false;
				break;
			}
			if (isWhiteSpace(p)) continue;

			switch (toUnicode(p))
			{
			case ':':
				if (!iskey || !isfin || !curkey || contains(r, curkey->get()))
					issuccess = false;
				else
				{
					iskey = false;
					isfin = false;
				}
				continue;

			case ',':
				if (iskey || !isfin || !curvalue)
					issuccess = false;
				else
				{
					iskey = true;
					isfin = false;
					insert(r, curkey->get(), curvalue);
					delete curkey;
					curkey = nullptr;
				}
				continue;

			case '}':
				if (iskey || !isfin || !curvalue)
					issuccess = false;
				else
				{
					insert(r, curkey->get(), curvalue);
					delete curkey;
					curkey = nullptr;
					return new Object(std::move(r));
				}
				continue;

			case '\"':
			{
				if (isfin)
					issuccess = false;
				else
				{
					if (iskey)
						curkey = meetString(++p, te);
					else
						curvalue = meetString(++p, te);
					isfin = true;
				}
				continue;
			}

			case '{':
			{
				if (iskey || isfin)
					issuccess = false;
				else
				{
					curvalue = meetObject(++p, te);
					isfin	 = true;
				}
				continue;
			}
			case '[':
			{
				if (iskey || isfin)
					issuccess = false;
				else
				{
					curvalue = meetArray(++p, te);
					isfin	 = true;
				}
				continue;
			}

			case 'n':
			case 'N':
			{
				if (iskey || isfin)
					issuccess = false;
				else
				{
					curvalue = meetNull(p, te);
					isfin	 = true;
					--p;
				}
				continue;
			}

			case 't':
			case 'T':
			case 'f':
			case 'F':
			{
				if (iskey || isfin)
					issuccess = false;
				else
				{
					curvalue = meetBoolean(p, te);
					isfin	 = true;
					--p;
				}
				continue;
			}

			default:
				if (iskey || isfin || !(isDigit(p) || (toUnicode(p) == '-')))
					issuccess = false;
				else
				{
					curvalue = meetNumber(p, te);
					isfin	 = true;
					--p;
				}
				--p;
				continue;
			} // switch toUnicode(p)
		} // for issuccess
		throw NodeType::object;
	} // meet Object

	[[nodiscard]] inline Node* textToJson(const DT::String& content)
	{
		Scptr p = content.begin();
		Scptr te = content.end();
		for(; p != te; ++p)
		{
			if(isWhiteSpace(p)) continue;
			switch(toUnicode(p))
			{
			case '{': return meetObject(++p, te);
			case '[': return meetArray(++p, te);
			default : return nullptr;
			}
		}
		return nullptr;
	}
} // namespace Json::Parser

#endif
