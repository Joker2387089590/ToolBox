#pragma once
#ifndef TEXT_H
#define TEXT_H

#include "Definitions.hpp"

namespace Json
{
	// Convenient functions for transform to text
	namespace Text
	{
		using namespace Definition;

		inline DT::String fromInt(int i)
		{
		#if DATA_TYPE == TYPE_STD
			return std::to_string(i);
		#elif DATA_TYPE == TYPE_QT
			return QString::number(i);
		#else
			static_assert(false, "No correct data type, please define DATA_TYPE");
		#endif
		}

		inline DT::String tabStr(int tab_depth)
		{
			return DT::String(tab_depth, '\t');
		}

		inline bool isOneLineFormatText(const Node* node)
		{
			switch(auto t = node->type())
			{
			case NodeType::null:
				return true;
			case NodeType::object:
			{
				auto c = node->cast<Object>()->get();
				if(c.size() == 0) return true;
				if(c.size() == 1) return isOneLineFormatText(*std::begin(c));
				else return false;
			}
			case NodeType::array:
			{
				auto c = node->cast<Array>()->get();
				if(c.size() == 0) return true;
				if(c.size() == 1) return isOneLineFormatText(c[0]);
				else return false;
			}
			default:
				if(t & NodeType::value) return true;
				else return false;
			}
		}
	} // namespace Text

	namespace Definition
	{
		inline DT::String Null::text() const
		{
			return "null";
		}

		inline DT::String Boolean::text() const
		{
			return value ? "true" : "false";
		}

		inline DT::String Number::text() const
		{
			using Text::fromInt;
			auto itext = fromInt(i());
			auto ftext = (f() == 0) ? "" : ('.' + fromInt(f()));
			auto etext = (e() == 0) ? "" : ('e' + fromInt(e()));
			return itext + ftext + etext;
		}

		inline DT::String String::text() const
		{
			return '\"' + value + '\"';
		}

		inline DT::String Array::text() const
		{
			if (container.size() == 0) return "[]";
			DT::String r;
			r += '[';
			for (auto ai : container) r += (ai->text() + ',');
			*r.rbegin() = ']';
			return r;
		}

		inline DT::String Object::text() const
		{
			if (container.size() == 0) return "{}";
			DT::String r;
			r += '{';
			visit()([&r](const DT::String& key, const Node* value)
				  {
					  r += '\"' + key + '\"';
					  r += ':';
					  r += value->text();
					  r += ',';
				  });
			*r.rbegin() = '}';
			return r;
		}

		inline DT::String Null::formatText(int tab_depth) const
		{
			return Text::tabStr(tab_depth) + text();
		}

		template<typename T>
		inline DT::String Value<T>::formatText(int tab_depth) const
		{
			return Text::tabStr(tab_depth) + text();
		}

		inline DT::String Array::formatText(int tab_depth) const
		{
			const auto tabs = Text::tabStr(tab_depth);
			if (container.size() == 0) return tabs + "[]";
			if (container.size() == 1)
			{
				auto node = container[0];
				if (Text::isOneLineFormatText(node))
					return tabs + "[ " + node->formatText(0) + " ]";
				else
					return tabs + '[' + '\n' +
						   node->formatText(tab_depth + 1) + '\n' +
						   tabs + ']';
			}
			else
			{
				DT::String r;
				r += tabs + '[';
				for (auto ai : container)
				{
					r += '\n';
					r += ai->formatText(tab_depth + 1);
					r += ',';
				}
				*r.rbegin() = '\n';
				r += (tabs + ']');
				return r;
			}
		} // Array::formatText

		inline DT::String Object::formatText(int tab_depth) const
		{
			using namespace Text;
			const auto tabs = tabStr(tab_depth);
			if(container.size() == 0) return tabs + "{}";
			auto c = container.begin();
			if(container.size() == 1 && isOneLineFormatText(c.value()))
				return tabs + "{ \"" + c.key() + "\" : " +
					   c.value()->formatText(0) + " }";
			else
			{
				DT::String r;
				auto tab2 = tabStr(tab_depth + 1);
				r += tabs + "{";
				visit()([&](const DT::String& key, const Node* value)
				{
					r += '\n';
					r += tab2 + '"' + key + "\" :";
					if(isOneLineFormatText(value))
						r += ' ' + value->formatText(0) + ',';
					else
						r += "\n" + value->formatText(tab_depth + 1) + ',';
				});
				*(r.rbegin()) = '\n';
				r += (tabs + '}');
				return r;
			}
		} // Object::formatText
	} // namespace Definition
} // namespace Json

#endif // TEXT_H
