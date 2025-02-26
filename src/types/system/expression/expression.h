#pragma once
#include "../../common.h"
#include "../../core.h"

namespace craft {
namespace types
{
	/******************************************************************************
	** Expression
	******************************************************************************/

	struct IExpression
	{
		virtual TypeId kind() const = 0;
		virtual void* ptr() const = 0;

		virtual std::string displayString() const = 0;
		virtual std::vector<IExpression*> const* children() const = 0;

		virtual void destroy() = 0;
		virtual IExpression* clone() const = 0;

	public:
		inline std::tuple<void*, void*> invokeArg() const { return std::make_tuple((TypeGraph::Node*)kind(), ptr()); }
	};

	/******************************************************************************
	** Expression Specials
	******************************************************************************/

	struct ExpressionAny final
		: public IExpression
	{
	private:
		ExpressionAny() = default;
		~ExpressionAny() = default;
	public:
		CRAFT_TYPES_EXPORTED static ExpressionAny Value;

		CRAFT_TYPES_EXPORTED virtual TypeId kind() const override;
		CRAFT_TYPES_EXPORTED virtual void* ptr() const override;

		CRAFT_TYPES_EXPORTED virtual std::string displayString() const override;
		CRAFT_TYPES_EXPORTED virtual std::vector<IExpression*> const* children() const override;

		CRAFT_TYPES_EXPORTED virtual void destroy() override;
		CRAFT_TYPES_EXPORTED virtual IExpression* clone() const override;
	};

	struct ExpressionVoid final
		: public IExpression
	{
	private:
		ExpressionVoid() = default;
		~ExpressionVoid() = default;
	public:
		CRAFT_TYPES_EXPORTED static ExpressionVoid Value;

		CRAFT_TYPES_EXPORTED virtual TypeId kind() const override;
		CRAFT_TYPES_EXPORTED virtual void* ptr() const override;

		CRAFT_TYPES_EXPORTED virtual std::string displayString() const override;
		CRAFT_TYPES_EXPORTED virtual std::vector<IExpression*> const* children() const override;

		CRAFT_TYPES_EXPORTED virtual void destroy() override;
		CRAFT_TYPES_EXPORTED virtual IExpression* clone() const override;
	};

	struct ExpressionBottom final
		: public IExpression
	{
	private:
		ExpressionBottom() = default;
		~ExpressionBottom() = default;
	public:
		CRAFT_TYPES_EXPORTED static ExpressionBottom Value;

		CRAFT_TYPES_EXPORTED virtual TypeId kind() const override;
		CRAFT_TYPES_EXPORTED virtual void* ptr() const override;

		CRAFT_TYPES_EXPORTED virtual std::string displayString() const override;
		CRAFT_TYPES_EXPORTED virtual std::vector<IExpression*> const* children() const override;

		CRAFT_TYPES_EXPORTED virtual void destroy() override;
		CRAFT_TYPES_EXPORTED virtual IExpression* clone() const override;
	};

	/******************************************************************************
	** ExpressionConcrete
	******************************************************************************/

	struct ExpressionConcrete final
		: public IExpression
	{
	public:
		TypeGraph::Node* node;

		CRAFT_TYPES_EXPORTED ExpressionConcrete(TypeId node);
		CRAFT_TYPES_EXPORTED ~ExpressionConcrete();

	public:
		CRAFT_TYPES_EXPORTED virtual TypeId kind() const override;
		CRAFT_TYPES_EXPORTED virtual void* ptr() const override;

		CRAFT_TYPES_EXPORTED virtual std::string displayString() const override;
		CRAFT_TYPES_EXPORTED virtual std::vector<IExpression*> const* children() const override;

		CRAFT_TYPES_EXPORTED virtual void destroy() override;
		CRAFT_TYPES_EXPORTED virtual IExpression* clone() const override;
	};

	/******************************************************************************
	** ExpressionArrow
	******************************************************************************/

	struct ExpressionArrow final
		: public IExpression
	{
	public:
		IExpression* input;
		IExpression* output;

		CRAFT_TYPES_EXPORTED ExpressionArrow(IExpression* input, IExpression* output);
		CRAFT_TYPES_EXPORTED ~ExpressionArrow();

	public:
		CRAFT_TYPES_EXPORTED virtual TypeId kind() const override;
		CRAFT_TYPES_EXPORTED virtual void* ptr() const override;

		CRAFT_TYPES_EXPORTED virtual std::string displayString() const override;
		CRAFT_TYPES_EXPORTED virtual std::vector<IExpression*> const* children() const override;

		CRAFT_TYPES_EXPORTED virtual void destroy() override;
		CRAFT_TYPES_EXPORTED virtual IExpression* clone() const override;
	};

	/******************************************************************************
	** ExpressionTuple
	******************************************************************************/

	struct ExpressionTuple final
		: public IExpression
	{
	public:
		std::vector<IExpression*> entries;
		IExpression* varType;

		CRAFT_TYPES_EXPORTED ExpressionTuple(std::vector<IExpression*> const&, IExpression* varType = nullptr);
		CRAFT_TYPES_EXPORTED ~ExpressionTuple();

	public:
		CRAFT_TYPES_EXPORTED virtual TypeId kind() const override;
		CRAFT_TYPES_EXPORTED virtual void* ptr() const override;

		CRAFT_TYPES_EXPORTED virtual std::string displayString() const override;
		CRAFT_TYPES_EXPORTED virtual std::vector<IExpression*> const* children() const override;

		CRAFT_TYPES_EXPORTED virtual void destroy() override;
		CRAFT_TYPES_EXPORTED virtual IExpression* clone() const override;
	};

	/******************************************************************************
	** ExpressionStore
	******************************************************************************/

	class ExpressionStore final
	{
		std::shared_ptr<IExpression> _root;

		bool _building;

	public:
		CRAFT_TYPES_EXPORTED ExpressionStore();
		CRAFT_TYPES_EXPORTED ExpressionStore(IExpression* ptr);
		CRAFT_TYPES_EXPORTED ExpressionStore(ExpressionStore const&);
		CRAFT_TYPES_EXPORTED ~ExpressionStore();

		CRAFT_TYPES_EXPORTED void finish();

		CRAFT_TYPES_EXPORTED IExpression const* root()  const;
	};
}}
