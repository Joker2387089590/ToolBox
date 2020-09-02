#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <functional>
#include <tuple>
#include "Container.hpp"

namespace Json::Definition
{
	class Object : public Container<Object, DT::Map>
	{
	private:
		using Base::container;

	public:
		using Base::Base;

		inline Node* at(const DT::String& key) { return container[key]; }
		inline const Node* at(const DT::String& key) const
		{
		#if DATA_TYPE == TYPE_STD
			return container.at(key);
		#elif DATA_TYPE == TYPE_QT
			// QMap has no member function named "at".
			return container[key];
		#else
			static_assert(false, "No correct data type, define DATA_TYPE!");
		#endif
		}
		inline Node* operator[](const DT::String& key)
		{
			return container[key];
		}
		inline const Node* operator[](const DT::String& key) const
		{
		#if DATA_TYPE == TYPE_STD
			// std::map::operator[] has no const version overload
			return container.at(key);
		#elif DATA_TYPE == TYPE_QT
			return container[key];
		#else
			static_assert(false, "No correct data type, define DATA_TYPE!");
		#endif
		}

		inline NodeType type() const override { return NodeType::object; }

		DT::String text() const override;
		DT::String formatText(int tab_depth) const override;

	private:
		template<typename ObjectPoint, typename... Args>
		class VisitFunctor;
		template<typename Obj, typename... Args>
		friend class VisitFunctor;

	public:
		/*
		 * Usage:
		 * auto f =
		 *     void(*)(const DT::String& key,
		 *			   const? Node* value,
		 *			   Args... args);
		 * visit(args...)(f);
		*/
		template<typename... Args>
		inline auto visit(Args&&... args) const
		{
			return VisitFunctor(this, std::forward<Args&&>(args)...);
		}
		template<typename... Args>
		inline auto visit(Args&&... args)
		{
			return VisitFunctor(this, std::forward<Args&&>(args)...);
		}
	}; // class Object

	template<typename ObjectPoint, typename... Args>
	class Object::VisitFunctor
	{
	public:
		VisitFunctor(ObjectPoint o, Args&&... as) :
			obj(o), args(std::forward<Args>(as)...) {}

		template<typename Fn>
		inline void operator()(Fn f)
		{
		#if DATA_TYPE == TYPE_STD
			for(auto&& ci : obj->container)
				f(ci.first, ci.second, args...);
		#elif DATA_TYPE == TYPE_QT
			auto ce = obj->container.end();
			for(auto ci = obj->container.begin(); ci != ce; ++ci)
				proxy(std::bind(f, ci.key(), ci.value()), args);
		#else
			static_assert(false, "No correct data type, define DATA_TYPE!");
		#endif
		}

	private:
		const ObjectPoint obj;
		std::tuple<Args...> args;

		// 1. An interface to expand args into the arguments list of f
		template<typename Fn, typename... As>
		inline void proxy(Fn f, const std::tuple<As...>& as)
		{
			// 2.
			// Get tuple's length sizeof...(As),
			// and create a IndexPack<0, 1, ..., N-1>
			proxyHelper(f, makeIndexPack<sizeof...(As)>(), as);
		}

		template<size_t ...>
		struct IndexPack{};

		// 8. Trait <i...> from IndexPack<i...>
		template<typename F, size_t... i, typename T>
		inline void proxyHelper(F f, IndexPack<i...>, T&& as)
		{
			// 9.
			// At last, use std::get<i>(tuple),
			// to put every elements in args to f
			// The symbol "..." means, for every i in <typename... i>,
			// expr(i)... == expr(i[0]), expr(i[1]), ..., expr(i[N-1])
			// (just add a "," between to two template args)
			f(std::get<i>(as)...); // = f(as[0], as[1], ..., as[N-1])
		}

		// 4. At beginning, S... == void
		template<size_t N, size_t ...S>
		struct IndexProxy :
			IndexProxy <N - 1, N - 1, S...> { };

		// 5. At finish, S... == <0, ..., N-1>
		template<size_t ...S>
		struct IndexProxy <0, S...>
		{
			// 6. Save S... into IndexPack
			using type = IndexPack<S...>;
		};

		// 7.
		// Now, makeIndexPack is a function-like type,
		// use it to instantiate a IndexPack<S...> object,
		// sent the object to proxyHelper
		template<size_t N> using makeIndexPack =
			// 3. Compiler is trying to instantiate IndexProxy
			typename IndexProxy<N>::type;

		/* 10. Type derivation:
		 *
		 * makeIndexPack<N>
		 * = IndexProxy<N>::type
		 * = IndexProxy<N, (S... == void)>::type
		 * = IndexProxy<N-1, N-1>::type
		 * = IndexProxy<N-2, N-2, N-1>::type
		 * = ...
		 * = IndexProxy<1, 1, 2, ..., N-1>::type
		 * = IndexProxy<0, 0, 1, ..., N-1>::type
		 *				   |  |        |
		 *				  (0, 1, ..., N-1 == S...)
		 * = IndexPack<S...>
		 * = IndexPack<0, 1, 2, ..., N-1>,
		 *
		 * proxy(f, args)
		 * = proxyHelper(f, IndexPack<0, 1, ..., N-1>(), args)
		 * = f(std::get<i>(
		*/
	}; // class Object::VisitFunctor

	inline const Node& Node::operator[](const DT::String& key) const
	{
		if (this->type() == NodeType::object)
			return *(this->cast<Object>()->at(key));
		else
			throw NodeType::object;
	}

	template<>
	struct toEnumTraits<Object>
	{
		static constexpr auto value = NodeType::object;
	};

} // namespace Json::Definition

#endif
