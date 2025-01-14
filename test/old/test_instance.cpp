#include "types/common.h"

#include "empty_aspects.h"
#include "empty_providers.h"
#include "basic_object.h"

using namespace bandit;
using namespace snowhouse;

using namespace craft;

go_bandit([]()
{
	/*
		Testing the properties of a generic instance class.
	*/
	describe("`craft::instance<>`", []()
	{
		instance<> inst;

		describe("when null,", [&]()
		{
			it("isNull is true", [&]()
			{
				AssertThat(inst.isNull(), IsTrue());
			});
			it("bool conversion is false", [&]()
			{
				AssertThat(static_cast<bool>(inst), IsFalse());
			});
			it("get is nullptr", [&]()
			{
				AssertThat(inst.get(), IsNull());
			});
			it("typeId is None", [&]()
			{
				AssertThat(inst.typeId(), Equals(types::None));
			});

			describe("empty providers,", std::bind(describe_no_empty_providers<void>, inst));
			describe("empty aspects,", std::bind(describe_no_empty_aspects<void>, inst));
		});

		describe("with std::string value \"test\",", [&]()
		{
			before_each([&]() {
				inst = instance<std::string>::make("test");
			});

			it("isNull is false", [&]()
			{
				AssertThat(inst.isNull(), IsFalse());
			});
			it("bool conversion is true", [&]()
			{
				AssertThat(static_cast<bool>(inst), IsTrue());
			});
			it("get is not nullptr", [&]()
			{
				AssertThat(inst.get(), !IsNull());
			});
			it(".typeId() is type<std::string>::typeId()", [&]()
			{
				AssertThat(inst.typeId(), Equals(types::cpptype<std::string>::typeDesc().asId()));
			});
			it("*(std::string*) .get() is \"test\"", [&]()
			{
				AssertThat(*(std::string*)inst.get(), Equals("test"));
			});

			describe("empty providers,", std::bind(describe_no_empty_providers<void>, inst));
			describe("empty aspects,", std::bind(describe_no_empty_aspects<void>, inst));
		});

		describe("with TestBasicObject,", [&]()
		{
			instance<TestBasicObject> t_inst;

			before_each([&]() {
				t_inst = instance<TestBasicObject>::make();
				inst = t_inst;
			});

			it("isNull is false", [&]()
			{
				AssertThat(inst.isNull(), IsFalse());
			});
			it("bool conversion is true", [&]()
			{
				AssertThat(static_cast<bool>(inst), IsTrue());
			});
			it("get is not nullptr", [&]()
			{
				AssertThat(inst.get(), !IsNull());
			});
			it(".typeId() is type<std::string>::typeId()", [&]()
			{
				AssertThat(inst.typeId(), Equals(types::cpptype<TestBasicObject>::typeDesc().asId()));
			});
			it(".typeId() is ::craft_s_typeId()", [&]()
			{
				AssertThat(inst.typeId(), Equals(TestBasicObject::craft_s_typeDesc().asId()));
			});

			describe("empty providers,", std::bind(describe_no_empty_providers<void>, inst));
			describe("empty aspects,", std::bind(describe_no_empty_aspects<void>, inst));

			describe("empty providers,", std::bind(describe_no_empty_providers<TestBasicObject>, t_inst));
			describe("empty aspects,", std::bind(describe_no_empty_aspects<TestBasicObject>, t_inst));
		});


		describe("as PParse for std::string,", [&]()
		{
			// Test holding a provider

			instance<std::string> sinst;

			before_each([&]() {
				inst = instance<std::string>::make("test");
				sinst = instance<std::string>::make("test");
			});

			it("hasFeature is true", [&]()
			{
				AssertThat(inst.hasFeature<types::PParse>(), IsTrue());
				AssertThat(sinst.hasFeature<types::PParse>(), IsTrue());
			});

			it("construct provider from void", [&]()
			{
				instance<types::PParse> prov(inst);
				AssertThat(prov.isNull(), IsFalse());
				AssertThat(prov.get(), Equals(inst.getFeature<types::PParse>()));

				instance<std::string> res = prov->parse("test");
				AssertThat(*res, Equals("test"));
			});
			it("assign provider from void", [&]()
			{
				instance<types::PParse> prov = inst;
				AssertThat(prov.isNull(), IsFalse());
				AssertThat(prov.get(), Equals(inst.getFeature<types::PParse>()));

				instance<std::string> res = prov->parse("test");
				AssertThat(*res, Equals("test"));
			});
			it("asFeature provider from void", [&]()
			{
				AssertThat(inst.asFeature<types::PParse>().isNull(), IsFalse());
				AssertThat(inst.asFeature<types::PParse>().get(), Equals(inst.getFeature<types::PParse>()));

				instance<std::string> res = inst.asFeature<types::PParse>()->parse("test");
				AssertThat(*res, Equals("test"));
			});
			it("by call cast from void", [&]()
			{
				typedef instance<types::PParse>(*fn)(instance<void>);
				fn c = (fn)(+[](instance<types::PParse> p) { return p; });
				instance<types::PParse> prov = c(inst);

				AssertThat(prov.isNull(), IsFalse());
				AssertThat(prov.get(), Equals(inst.getFeature<types::PParse>()));

				instance<std::string> res = prov->parse("test");
				AssertThat(*res, Equals("test"));
			});

			it("construct provider from concrete", [&]()
			{
				instance<types::PParse> prov(sinst);
				AssertThat(prov.isNull(), IsFalse());
				AssertThat(prov.get(), Equals(sinst.getFeature<types::PParse>()));

				instance<std::string> res = prov->parse("test");
				AssertThat(*res, Equals("test"));
			});
			it("assign provider from concrete", [&]()
			{
				instance<types::PParse> prov = sinst;
				AssertThat(prov.isNull(), IsFalse());
				AssertThat(prov.get(), Equals(sinst.getFeature<types::PParse>()));

				instance<std::string> res = prov->parse("test");
				AssertThat(*res, Equals("test"));
			});
			it("asFeature provider from concrete", [&]()
			{
				AssertThat(sinst.asFeature<types::PParse>().isNull(), IsFalse());
				AssertThat(sinst.asFeature<types::PParse>().get(), Equals(sinst.getFeature<types::PParse>()));

				instance<std::string> res = sinst.asFeature<types::PParse>()->parse("test");
				AssertThat(*res, Equals("test"));
			});
			it("by call cast from concrete", [&]()
			{
				typedef instance<types::PParse>(*fn)(instance<void>);
				fn c = (fn)(+[](instance<types::PParse> p) { return p; });
				instance<types::PParse> prov = c(sinst);

				AssertThat(prov.isNull(), IsFalse());
				AssertThat(prov.get(), Equals(sinst.getFeature<types::PParse>()));

				instance<std::string> res = prov->parse("test");
				AssertThat(*res, Equals("test"));
			});
		});
	});
});
