#pragma once
#include "types/common.h"

CRAFT_MULTIMETHOD_DECLARE(test_multimethod_expression, craft::types::ExpressionDispatcher);

CRAFT_MULTIMETHOD_DECLARE(test_multimethod_instance, craft::types::WithInstancesDispatcher<craft::types::ExpressionDispatcher>);
