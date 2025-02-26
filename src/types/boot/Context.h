#pragma once
#include "../common.h"
#include "../core.h"

namespace craft {
namespace types
{
	class IContextQueryable abstract
	{
	public:
		CRAFT_TYPES_EXPORTED virtual ~IContextQueryable();

		virtual std::shared_ptr<IContextQueryable> byName(std::string const&) const = 0;
		virtual std::shared_ptr<IContextQueryable> byType(TypeId const&) const = 0;

		virtual std::set<instance<>> objects() const = 0;
		virtual instance<> prime() const = 0;

		inline instance<> only() const
		{
			auto res = this->objects();
			return res.size() == 1 ? *res.begin() : nullptr;
		}
	};

	/******************************************************************************
	** Context
	******************************************************************************/

	namespace _details
	{
		class _ContextQueryable;
	}

	class Context
		: public std::enable_shared_from_this<Context>
		, public virtual Object
		, public IContextQueryable
	{
		CRAFT_OBJECT_DECLARE(craft::types::Context);

		std::vector<instance<>> _all;
		instance<> _prime;

		std::map<TypeId, std::set<instance<>>> _objectsByType;
		std::map<std::string, std::set<instance<>>> _objectsByName;

		std::map<TypeId, instance<>> _primesByType;
		std::map<std::string, instance<>> _primesByName;

		std::shared_ptr<Context> _parent;
		std::vector<std::shared_ptr<Context>> _children;
		bool _finalized;
		size_t _tree_depth;

		friend class _details::_ContextQueryable;
	
	public:
		CRAFT_TYPES_EXPORTED Context(instance<> prime);
		CRAFT_TYPES_EXPORTED virtual ~Context();
		
		CRAFT_TYPES_EXPORTED static std::shared_ptr<Context> makeChildContext(std::shared_ptr<Context> parent, instance<> prime);
		CRAFT_TYPES_EXPORTED static std::shared_ptr<Context> makeMentorContext(std::shared_ptr<Context> mentor, instance<> prime);

		CRAFT_TYPES_EXPORTED std::shared_ptr<Context> copy() const;
		CRAFT_TYPES_EXPORTED std::shared_ptr<Context> parent() const;

		CRAFT_TYPES_EXPORTED void addOnName(std::string const& name, instance<> obj);
		CRAFT_TYPES_EXPORTED void addOnType(TypeId t_id, instance<> obj);

		template<typename T,
			typename std::enable_if<cpptype<T>::isObject || cpptype<T>::isLegacyFeature>::type* = nullptr>
		inline void add(instance<T> obj)
		{
			this->addOnType(cpptype<T>::typeDesc(), static_cast<instance<>>(obj));
		}

		CRAFT_TYPES_EXPORTED void promoteOnName(std::string const& name, instance<> obj);
		CRAFT_TYPES_EXPORTED void promoteOnType(TypeId t_id, instance<> obj);

		template<typename T,
			typename std::enable_if<cpptype<T>::isObject || cpptype<T>::isLegacyFeature>::type* = nullptr>
		inline void promote(instance<T> obj)
		{
			this->promoteOnType(cpptype<T>::typeDesc(), static_cast<instance<>>(obj));
		}

		CRAFT_TYPES_EXPORTED void finalize();
		CRAFT_TYPES_EXPORTED bool finalized() const;

		CRAFT_TYPES_EXPORTED virtual std::shared_ptr<IContextQueryable> byName(std::string const&) const override;
		CRAFT_TYPES_EXPORTED virtual std::shared_ptr<IContextQueryable> byType(TypeId const&) const override;
		
		template<typename T,
			typename std::enable_if<cpptype<T>::isObject || cpptype<T>::isLegacyFeature>::type* = nullptr>
		inline std::shared_ptr<IContextQueryable> by()
		{
			return this->byType(cpptype<T>::typeDesc());
		}

		CRAFT_TYPES_EXPORTED virtual std::set<instance<>> objects() const override;
		CRAFT_TYPES_EXPORTED virtual instance<> prime() const override;


	private:
		void recurse_expand(std::map<instance<>, bool>& expanded);
		void recurse_contextualize(std::map<instance<>, bool>& expanded);

	public:
		CRAFT_TYPES_EXPORTED void fishtacos();
	};
}}
