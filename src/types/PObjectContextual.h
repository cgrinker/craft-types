#pragma once
#include "common.h"
#include "core.h"

namespace craft {
	/******************************************************************************
	** PObjectContextual
	******************************************************************************/
	
	class Context;

	/* T:
	Provides an interface for naming things, and reversing those names into actual objects.
	*/

	class PObjectContextual abstract
		: public Provider
	{
		CRAFT_PROVIDER_DECLARE(PObjectContextual, "types.context", Singleton)
	public:
		virtual void contextualize(instance<>, std::shared_ptr<Context>) = 0;
	};

	/******************************************************************************
	** ObjectConversion
	******************************************************************************/

	template <typename TType>
	class ObjectContextualWrapper
		: public Implements<PObjectContextual>::For<TType>
	{
	public:
		typedef typename void (TType::*t_context)(std::shared_ptr<Context> c);

	private:
		t_context _context_func;

		inline virtual void contextualize(instance<> i, std::shared_ptr<Context> c)
		{
			SPDLOG_TRACE(engine()->log, "{0}::contextualize", type<TType>::name());
			std::invoke(this->_context_func, i.asType<TType>().get(), c);
		}
	public:

		inline ObjectContextualWrapper<TType>* withContextualizer(t_context f) { _context_func = f; return this; }
	};
}