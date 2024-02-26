

#include "Python.h"
#include "pycore_ast.h"
#include "pycore_ast_state.h"
#include "pycore_ceval.h"
#include "pycore_lock.h"
#include "pycore_interp.h"
#include "pycore_pystate.h"
#include <stddef.h>

struct validator {
    int recursion_depth;            /* current recursion depth */
    int recursion_limit;            /* recursion limit */
};

// Forward declaration
static int init_types(struct ast_state *state);

static struct ast_state*
get_ast_state(void)
{
    PyInterpreterState *interp = _PyInterpreterState_GET();
    struct ast_state *state = &interp->ast;
    assert(!state->finalized);
    if (_PyOnceFlag_CallOnce(&state->once, (_Py_once_fn_t *)&init_types, state) < 0) {
        return NULL;
    }
    return state;
}

void _PyAST_Fini(PyInterpreterState *interp)
{
    struct ast_state *state = &interp->ast;

    Py_CLEAR(state->AST_type);
    Py_CLEAR(state->Add_singleton);
    Py_CLEAR(state->Add_type);
    Py_CLEAR(state->And_singleton);
    Py_CLEAR(state->And_type);
    Py_CLEAR(state->AnnAssign_type);
    Py_CLEAR(state->Assert_type);
    Py_CLEAR(state->Assign_type);
    Py_CLEAR(state->AsyncFor_type);
    Py_CLEAR(state->AsyncFunctionDef_type);
    Py_CLEAR(state->AsyncWith_type);
    Py_CLEAR(state->Attribute_type);
    Py_CLEAR(state->AugAssign_type);
    Py_CLEAR(state->Await_type);
    Py_CLEAR(state->BinOp_type);
    Py_CLEAR(state->BitAnd_singleton);
    Py_CLEAR(state->BitAnd_type);
    Py_CLEAR(state->BitOr_singleton);
    Py_CLEAR(state->BitOr_type);
    Py_CLEAR(state->BitXor_singleton);
    Py_CLEAR(state->BitXor_type);
    Py_CLEAR(state->BoolOp_type);
    Py_CLEAR(state->Break_type);
    Py_CLEAR(state->Call_type);
    Py_CLEAR(state->ClassDef_type);
    Py_CLEAR(state->Compare_type);
    Py_CLEAR(state->Constant_type);
    Py_CLEAR(state->Continue_type);
    Py_CLEAR(state->Del_singleton);
    Py_CLEAR(state->Del_type);
    Py_CLEAR(state->Delete_type);
    Py_CLEAR(state->DictComp_type);
    Py_CLEAR(state->Dict_type);
    Py_CLEAR(state->Div_singleton);
    Py_CLEAR(state->Div_type);
    Py_CLEAR(state->Eq_singleton);
    Py_CLEAR(state->Eq_type);
    Py_CLEAR(state->ExceptHandler_type);
    Py_CLEAR(state->Expr_type);
    Py_CLEAR(state->Expression_type);
    Py_CLEAR(state->FloorDiv_singleton);
    Py_CLEAR(state->FloorDiv_type);
    Py_CLEAR(state->For_type);
    Py_CLEAR(state->FormattedValue_type);
    Py_CLEAR(state->FunctionDef_type);
    Py_CLEAR(state->FunctionType_type);
    Py_CLEAR(state->GeneratorExp_type);
    Py_CLEAR(state->Global_type);
    Py_CLEAR(state->GtE_singleton);
    Py_CLEAR(state->GtE_type);
    Py_CLEAR(state->Gt_singleton);
    Py_CLEAR(state->Gt_type);
    Py_CLEAR(state->IfExp_type);
    Py_CLEAR(state->If_type);
    Py_CLEAR(state->ImportFrom_type);
    Py_CLEAR(state->Import_type);
    Py_CLEAR(state->In_singleton);
    Py_CLEAR(state->In_type);
    Py_CLEAR(state->Interactive_type);
    Py_CLEAR(state->Invert_singleton);
    Py_CLEAR(state->Invert_type);
    Py_CLEAR(state->IsNot_singleton);
    Py_CLEAR(state->IsNot_type);
    Py_CLEAR(state->Is_singleton);
    Py_CLEAR(state->Is_type);
    Py_CLEAR(state->JoinedStr_type);
    Py_CLEAR(state->LShift_singleton);
    Py_CLEAR(state->LShift_type);
    Py_CLEAR(state->Lambda_type);
    Py_CLEAR(state->ListComp_type);
    Py_CLEAR(state->List_type);
    Py_CLEAR(state->Load_singleton);
    Py_CLEAR(state->Load_type);
    Py_CLEAR(state->LtE_singleton);
    Py_CLEAR(state->LtE_type);
    Py_CLEAR(state->Lt_singleton);
    Py_CLEAR(state->Lt_type);
    Py_CLEAR(state->MatMult_singleton);
    Py_CLEAR(state->MatMult_type);
    Py_CLEAR(state->MatchAs_type);
    Py_CLEAR(state->MatchClass_type);
    Py_CLEAR(state->MatchMapping_type);
    Py_CLEAR(state->MatchOr_type);
    Py_CLEAR(state->MatchSequence_type);
    Py_CLEAR(state->MatchSingleton_type);
    Py_CLEAR(state->MatchStar_type);
    Py_CLEAR(state->MatchValue_type);
    Py_CLEAR(state->Match_type);
    Py_CLEAR(state->Mod_singleton);
    Py_CLEAR(state->Mod_type);
    Py_CLEAR(state->Module_type);
    Py_CLEAR(state->Mult_singleton);
    Py_CLEAR(state->Mult_type);
    Py_CLEAR(state->Name_type);
    Py_CLEAR(state->NamedExpr_type);
    Py_CLEAR(state->Nonlocal_type);
    Py_CLEAR(state->NotEq_singleton);
    Py_CLEAR(state->NotEq_type);
    Py_CLEAR(state->NotIn_singleton);
    Py_CLEAR(state->NotIn_type);
    Py_CLEAR(state->Not_singleton);
    Py_CLEAR(state->Not_type);
    Py_CLEAR(state->Or_singleton);
    Py_CLEAR(state->Or_type);
    Py_CLEAR(state->ParamSpec_type);
    Py_CLEAR(state->Pass_type);
    Py_CLEAR(state->Pow_singleton);
    Py_CLEAR(state->Pow_type);
    Py_CLEAR(state->RShift_singleton);
    Py_CLEAR(state->RShift_type);
    Py_CLEAR(state->Raise_type);
    Py_CLEAR(state->Return_type);
    Py_CLEAR(state->SetComp_type);
    Py_CLEAR(state->Set_type);
    Py_CLEAR(state->Slice_type);
    Py_CLEAR(state->Starred_type);
    Py_CLEAR(state->Store_singleton);
    Py_CLEAR(state->Store_type);
    Py_CLEAR(state->Sub_singleton);
    Py_CLEAR(state->Sub_type);
    Py_CLEAR(state->Subscript_type);
    Py_CLEAR(state->TryStar_type);
    Py_CLEAR(state->Try_type);
    Py_CLEAR(state->Tuple_type);
    Py_CLEAR(state->TypeAlias_type);
    Py_CLEAR(state->TypeIgnore_type);
    Py_CLEAR(state->TypeVarTuple_type);
    Py_CLEAR(state->TypeVar_type);
    Py_CLEAR(state->UAdd_singleton);
    Py_CLEAR(state->UAdd_type);
    Py_CLEAR(state->USub_singleton);
    Py_CLEAR(state->USub_type);
    Py_CLEAR(state->UnaryOp_type);
    Py_CLEAR(state->While_type);
    Py_CLEAR(state->With_type);
    Py_CLEAR(state->YieldFrom_type);
    Py_CLEAR(state->Yield_type);
    Py_CLEAR(state->__dict__);
    Py_CLEAR(state->__doc__);
    Py_CLEAR(state->__match_args__);
    Py_CLEAR(state->__module__);
    Py_CLEAR(state->_attributes);
    Py_CLEAR(state->_fields);
    Py_CLEAR(state->alias_type);
    Py_CLEAR(state->annotation);
    Py_CLEAR(state->arg);
    Py_CLEAR(state->arg_type);
    Py_CLEAR(state->args);
    Py_CLEAR(state->argtypes);
    Py_CLEAR(state->arguments_type);
    Py_CLEAR(state->asname);
    Py_CLEAR(state->ast);
    Py_CLEAR(state->attr);
    Py_CLEAR(state->bases);
    Py_CLEAR(state->body);
    Py_CLEAR(state->boolop_type);
    Py_CLEAR(state->bound);
    Py_CLEAR(state->cases);
    Py_CLEAR(state->cause);
    Py_CLEAR(state->cls);
    Py_CLEAR(state->cmpop_type);
    Py_CLEAR(state->col_offset);
    Py_CLEAR(state->comparators);
    Py_CLEAR(state->comprehension_type);
    Py_CLEAR(state->context_expr);
    Py_CLEAR(state->conversion);
    Py_CLEAR(state->ctx);
    Py_CLEAR(state->decorator_list);
    Py_CLEAR(state->defaults);
    Py_CLEAR(state->elt);
    Py_CLEAR(state->elts);
    Py_CLEAR(state->end_col_offset);
    Py_CLEAR(state->end_lineno);
    Py_CLEAR(state->exc);
    Py_CLEAR(state->excepthandler_type);
    Py_CLEAR(state->expr_context_type);
    Py_CLEAR(state->expr_type);
    Py_CLEAR(state->finalbody);
    Py_CLEAR(state->format_spec);
    Py_CLEAR(state->func);
    Py_CLEAR(state->generators);
    Py_CLEAR(state->guard);
    Py_CLEAR(state->handlers);
    Py_CLEAR(state->id);
    Py_CLEAR(state->ifs);
    Py_CLEAR(state->is_async);
    Py_CLEAR(state->items);
    Py_CLEAR(state->iter);
    Py_CLEAR(state->key);
    Py_CLEAR(state->keys);
    Py_CLEAR(state->keyword_type);
    Py_CLEAR(state->keywords);
    Py_CLEAR(state->kind);
    Py_CLEAR(state->kw_defaults);
    Py_CLEAR(state->kwarg);
    Py_CLEAR(state->kwd_attrs);
    Py_CLEAR(state->kwd_patterns);
    Py_CLEAR(state->kwonlyargs);
    Py_CLEAR(state->left);
    Py_CLEAR(state->level);
    Py_CLEAR(state->lineno);
    Py_CLEAR(state->lower);
    Py_CLEAR(state->match_case_type);
    Py_CLEAR(state->mod_type);
    Py_CLEAR(state->module);
    Py_CLEAR(state->msg);
    Py_CLEAR(state->name);
    Py_CLEAR(state->names);
    Py_CLEAR(state->op);
    Py_CLEAR(state->operand);
    Py_CLEAR(state->operator_type);
    Py_CLEAR(state->ops);
    Py_CLEAR(state->optional_vars);
    Py_CLEAR(state->orelse);
    Py_CLEAR(state->pattern);
    Py_CLEAR(state->pattern_type);
    Py_CLEAR(state->patterns);
    Py_CLEAR(state->posonlyargs);
    Py_CLEAR(state->rest);
    Py_CLEAR(state->returns);
    Py_CLEAR(state->right);
    Py_CLEAR(state->simple);
    Py_CLEAR(state->slice);
    Py_CLEAR(state->step);
    Py_CLEAR(state->stmt_type);
    Py_CLEAR(state->subject);
    Py_CLEAR(state->tag);
    Py_CLEAR(state->target);
    Py_CLEAR(state->targets);
    Py_CLEAR(state->test);
    Py_CLEAR(state->type);
    Py_CLEAR(state->type_comment);
    Py_CLEAR(state->type_ignore_type);
    Py_CLEAR(state->type_ignores);
    Py_CLEAR(state->type_param_type);
    Py_CLEAR(state->type_params);
    Py_CLEAR(state->unaryop_type);
    Py_CLEAR(state->upper);
    Py_CLEAR(state->value);
    Py_CLEAR(state->values);
    Py_CLEAR(state->vararg);
    Py_CLEAR(state->withitem_type);

    Py_CLEAR(_Py_INTERP_CACHED_OBJECT(interp, str_replace_inf));

    state->finalized = 1;
    state->once = (_PyOnceFlag){0};
}

static int init_identifiers(struct ast_state *state)
{
    if ((state->__dict__ = PyUnicode_InternFromString("__dict__")) == NULL) return -1;
    if ((state->__doc__ = PyUnicode_InternFromString("__doc__")) == NULL) return -1;
    if ((state->__match_args__ = PyUnicode_InternFromString("__match_args__")) == NULL) return -1;
    if ((state->__module__ = PyUnicode_InternFromString("__module__")) == NULL) return -1;
    if ((state->_attributes = PyUnicode_InternFromString("_attributes")) == NULL) return -1;
    if ((state->_fields = PyUnicode_InternFromString("_fields")) == NULL) return -1;
    if ((state->annotation = PyUnicode_InternFromString("annotation")) == NULL) return -1;
    if ((state->arg = PyUnicode_InternFromString("arg")) == NULL) return -1;
    if ((state->args = PyUnicode_InternFromString("args")) == NULL) return -1;
    if ((state->argtypes = PyUnicode_InternFromString("argtypes")) == NULL) return -1;
    if ((state->asname = PyUnicode_InternFromString("asname")) == NULL) return -1;
    if ((state->ast = PyUnicode_InternFromString("ast")) == NULL) return -1;
    if ((state->attr = PyUnicode_InternFromString("attr")) == NULL) return -1;
    if ((state->bases = PyUnicode_InternFromString("bases")) == NULL) return -1;
    if ((state->body = PyUnicode_InternFromString("body")) == NULL) return -1;
    if ((state->bound = PyUnicode_InternFromString("bound")) == NULL) return -1;
    if ((state->cases = PyUnicode_InternFromString("cases")) == NULL) return -1;
    if ((state->cause = PyUnicode_InternFromString("cause")) == NULL) return -1;
    if ((state->cls = PyUnicode_InternFromString("cls")) == NULL) return -1;
    if ((state->col_offset = PyUnicode_InternFromString("col_offset")) == NULL) return -1;
    if ((state->comparators = PyUnicode_InternFromString("comparators")) == NULL) return -1;
    if ((state->context_expr = PyUnicode_InternFromString("context_expr")) == NULL) return -1;
    if ((state->conversion = PyUnicode_InternFromString("conversion")) == NULL) return -1;
    if ((state->ctx = PyUnicode_InternFromString("ctx")) == NULL) return -1;
    if ((state->decorator_list = PyUnicode_InternFromString("decorator_list")) == NULL) return -1;
    if ((state->defaults = PyUnicode_InternFromString("defaults")) == NULL) return -1;
    if ((state->elt = PyUnicode_InternFromString("elt")) == NULL) return -1;
    if ((state->elts = PyUnicode_InternFromString("elts")) == NULL) return -1;
    if ((state->end_col_offset = PyUnicode_InternFromString("end_col_offset")) == NULL) return -1;
    if ((state->end_lineno = PyUnicode_InternFromString("end_lineno")) == NULL) return -1;
    if ((state->exc = PyUnicode_InternFromString("exc")) == NULL) return -1;
    if ((state->finalbody = PyUnicode_InternFromString("finalbody")) == NULL) return -1;
    if ((state->format_spec = PyUnicode_InternFromString("format_spec")) == NULL) return -1;
    if ((state->func = PyUnicode_InternFromString("func")) == NULL) return -1;
    if ((state->generators = PyUnicode_InternFromString("generators")) == NULL) return -1;
    if ((state->guard = PyUnicode_InternFromString("guard")) == NULL) return -1;
    if ((state->handlers = PyUnicode_InternFromString("handlers")) == NULL) return -1;
    if ((state->id = PyUnicode_InternFromString("id")) == NULL) return -1;
    if ((state->ifs = PyUnicode_InternFromString("ifs")) == NULL) return -1;
    if ((state->is_async = PyUnicode_InternFromString("is_async")) == NULL) return -1;
    if ((state->items = PyUnicode_InternFromString("items")) == NULL) return -1;
    if ((state->iter = PyUnicode_InternFromString("iter")) == NULL) return -1;
    if ((state->key = PyUnicode_InternFromString("key")) == NULL) return -1;
    if ((state->keys = PyUnicode_InternFromString("keys")) == NULL) return -1;
    if ((state->keywords = PyUnicode_InternFromString("keywords")) == NULL) return -1;
    if ((state->kind = PyUnicode_InternFromString("kind")) == NULL) return -1;
    if ((state->kw_defaults = PyUnicode_InternFromString("kw_defaults")) == NULL) return -1;
    if ((state->kwarg = PyUnicode_InternFromString("kwarg")) == NULL) return -1;
    if ((state->kwd_attrs = PyUnicode_InternFromString("kwd_attrs")) == NULL) return -1;
    if ((state->kwd_patterns = PyUnicode_InternFromString("kwd_patterns")) == NULL) return -1;
    if ((state->kwonlyargs = PyUnicode_InternFromString("kwonlyargs")) == NULL) return -1;
    if ((state->left = PyUnicode_InternFromString("left")) == NULL) return -1;
    if ((state->level = PyUnicode_InternFromString("level")) == NULL) return -1;
    if ((state->lineno = PyUnicode_InternFromString("lineno")) == NULL) return -1;
    if ((state->lower = PyUnicode_InternFromString("lower")) == NULL) return -1;
    if ((state->module = PyUnicode_InternFromString("module")) == NULL) return -1;
    if ((state->msg = PyUnicode_InternFromString("msg")) == NULL) return -1;
    if ((state->name = PyUnicode_InternFromString("name")) == NULL) return -1;
    if ((state->names = PyUnicode_InternFromString("names")) == NULL) return -1;
    if ((state->op = PyUnicode_InternFromString("op")) == NULL) return -1;
    if ((state->operand = PyUnicode_InternFromString("operand")) == NULL) return -1;
    if ((state->ops = PyUnicode_InternFromString("ops")) == NULL) return -1;
    if ((state->optional_vars = PyUnicode_InternFromString("optional_vars")) == NULL) return -1;
    if ((state->orelse = PyUnicode_InternFromString("orelse")) == NULL) return -1;
    if ((state->pattern = PyUnicode_InternFromString("pattern")) == NULL) return -1;
    if ((state->patterns = PyUnicode_InternFromString("patterns")) == NULL) return -1;
    if ((state->posonlyargs = PyUnicode_InternFromString("posonlyargs")) == NULL) return -1;
    if ((state->rest = PyUnicode_InternFromString("rest")) == NULL) return -1;
    if ((state->returns = PyUnicode_InternFromString("returns")) == NULL) return -1;
    if ((state->right = PyUnicode_InternFromString("right")) == NULL) return -1;
    if ((state->simple = PyUnicode_InternFromString("simple")) == NULL) return -1;
    if ((state->slice = PyUnicode_InternFromString("slice")) == NULL) return -1;
    if ((state->step = PyUnicode_InternFromString("step")) == NULL) return -1;
    if ((state->subject = PyUnicode_InternFromString("subject")) == NULL) return -1;
    if ((state->tag = PyUnicode_InternFromString("tag")) == NULL) return -1;
    if ((state->target = PyUnicode_InternFromString("target")) == NULL) return -1;
    if ((state->targets = PyUnicode_InternFromString("targets")) == NULL) return -1;
    if ((state->test = PyUnicode_InternFromString("test")) == NULL) return -1;
    if ((state->type = PyUnicode_InternFromString("type")) == NULL) return -1;
    if ((state->type_comment = PyUnicode_InternFromString("type_comment")) == NULL) return -1;
    if ((state->type_ignores = PyUnicode_InternFromString("type_ignores")) == NULL) return -1;
    if ((state->type_params = PyUnicode_InternFromString("type_params")) == NULL) return -1;
    if ((state->upper = PyUnicode_InternFromString("upper")) == NULL) return -1;
    if ((state->value = PyUnicode_InternFromString("value")) == NULL) return -1;
    if ((state->values = PyUnicode_InternFromString("values")) == NULL) return -1;
    if ((state->vararg = PyUnicode_InternFromString("vararg")) == NULL) return -1;
    return 0;
};

GENERATE_ASDL_SEQ_CONSTRUCTOR(mod, mod_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(stmt, stmt_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(expr, expr_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(comprehension, comprehension_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(excepthandler, excepthandler_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(arguments, arguments_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(arg, arg_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(keyword, keyword_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(alias, alias_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(withitem, withitem_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(match_case, match_case_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(pattern, pattern_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(type_ignore, type_ignore_ty)
GENERATE_ASDL_SEQ_CONSTRUCTOR(type_param, type_param_ty)

static PyObject* ast2obj_mod(struct ast_state *state, struct validator *vstate,
                             void*);
static const char * const Module_fields[]={
    "body",
    "type_ignores",
};
static const char * const Interactive_fields[]={
    "body",
};
static const char * const Expression_fields[]={
    "body",
};
static const char * const FunctionType_fields[]={
    "argtypes",
    "returns",
};
static const char * const stmt_attributes[] = {
    "lineno",
    "col_offset",
    "end_lineno",
    "end_col_offset",
};
static PyObject* ast2obj_stmt(struct ast_state *state, struct validator
                              *vstate, void*);
static const char * const FunctionDef_fields[]={
    "name",
    "args",
    "body",
    "decorator_list",
    "returns",
    "type_comment",
    "type_params",
};
static const char * const AsyncFunctionDef_fields[]={
    "name",
    "args",
    "body",
    "decorator_list",
    "returns",
    "type_comment",
    "type_params",
};
static const char * const ClassDef_fields[]={
    "name",
    "bases",
    "keywords",
    "body",
    "decorator_list",
    "type_params",
};
static const char * const Return_fields[]={
    "value",
};
static const char * const Delete_fields[]={
    "targets",
};
static const char * const Assign_fields[]={
    "targets",
    "value",
    "type_comment",
};
static const char * const TypeAlias_fields[]={
    "name",
    "type_params",
    "value",
};
static const char * const AugAssign_fields[]={
    "target",
    "op",
    "value",
};
static const char * const AnnAssign_fields[]={
    "target",
    "annotation",
    "value",
    "simple",
};
static const char * const For_fields[]={
    "target",
    "iter",
    "body",
    "orelse",
    "type_comment",
};
static const char * const AsyncFor_fields[]={
    "target",
    "iter",
    "body",
    "orelse",
    "type_comment",
};
static const char * const While_fields[]={
    "test",
    "body",
    "orelse",
};
static const char * const If_fields[]={
    "test",
    "body",
    "orelse",
};
static const char * const With_fields[]={
    "items",
    "body",
    "type_comment",
};
static const char * const AsyncWith_fields[]={
    "items",
    "body",
    "type_comment",
};
static const char * const Match_fields[]={
    "subject",
    "cases",
};
static const char * const Raise_fields[]={
    "exc",
    "cause",
};
static const char * const Try_fields[]={
    "body",
    "handlers",
    "orelse",
    "finalbody",
};
static const char * const TryStar_fields[]={
    "body",
    "handlers",
    "orelse",
    "finalbody",
};
static const char * const Assert_fields[]={
    "test",
    "msg",
};
static const char * const Import_fields[]={
    "names",
};
static const char * const ImportFrom_fields[]={
    "module",
    "names",
    "level",
};
static const char * const Global_fields[]={
    "names",
};
static const char * const Nonlocal_fields[]={
    "names",
};
static const char * const Expr_fields[]={
    "value",
};
static const char * const expr_attributes[] = {
    "lineno",
    "col_offset",
    "end_lineno",
    "end_col_offset",
};
static PyObject* ast2obj_expr(struct ast_state *state, struct validator
                              *vstate, void*);
static const char * const BoolOp_fields[]={
    "op",
    "values",
};
static const char * const NamedExpr_fields[]={
    "target",
    "value",
};
static const char * const BinOp_fields[]={
    "left",
    "op",
    "right",
};
static const char * const UnaryOp_fields[]={
    "op",
    "operand",
};
static const char * const Lambda_fields[]={
    "args",
    "body",
};
static const char * const IfExp_fields[]={
    "test",
    "body",
    "orelse",
};
static const char * const Dict_fields[]={
    "keys",
    "values",
};
static const char * const Set_fields[]={
    "elts",
};
static const char * const ListComp_fields[]={
    "elt",
    "generators",
};
static const char * const SetComp_fields[]={
    "elt",
    "generators",
};
static const char * const DictComp_fields[]={
    "key",
    "value",
    "generators",
};
static const char * const GeneratorExp_fields[]={
    "elt",
    "generators",
};
static const char * const Await_fields[]={
    "value",
};
static const char * const Yield_fields[]={
    "value",
};
static const char * const YieldFrom_fields[]={
    "value",
};
static const char * const Compare_fields[]={
    "left",
    "ops",
    "comparators",
};
static const char * const Call_fields[]={
    "func",
    "args",
    "keywords",
};
static const char * const FormattedValue_fields[]={
    "value",
    "conversion",
    "format_spec",
};
static const char * const JoinedStr_fields[]={
    "values",
};
static const char * const Constant_fields[]={
    "value",
    "kind",
};
static const char * const Attribute_fields[]={
    "value",
    "attr",
    "ctx",
};
static const char * const Subscript_fields[]={
    "value",
    "slice",
    "ctx",
};
static const char * const Starred_fields[]={
    "value",
    "ctx",
};
static const char * const Name_fields[]={
    "id",
    "ctx",
};
static const char * const List_fields[]={
    "elts",
    "ctx",
};
static const char * const Tuple_fields[]={
    "elts",
    "ctx",
};
static const char * const Slice_fields[]={
    "lower",
    "upper",
    "step",
};
static PyObject* ast2obj_expr_context(struct ast_state *state, struct validator
                                      *vstate, expr_context_ty);
static PyObject* ast2obj_boolop(struct ast_state *state, struct validator
                                *vstate, boolop_ty);
static PyObject* ast2obj_operator(struct ast_state *state, struct validator
                                  *vstate, operator_ty);
static PyObject* ast2obj_unaryop(struct ast_state *state, struct validator
                                 *vstate, unaryop_ty);
static PyObject* ast2obj_cmpop(struct ast_state *state, struct validator
                               *vstate, cmpop_ty);
static PyObject* ast2obj_comprehension(struct ast_state *state, struct
                                       validator *vstate, void*);
static const char * const comprehension_fields[]={
    "target",
    "iter",
    "ifs",
    "is_async",
};
static const char * const excepthandler_attributes[] = {
    "lineno",
    "col_offset",
    "end_lineno",
    "end_col_offset",
};
static PyObject* ast2obj_excepthandler(struct ast_state *state, struct
                                       validator *vstate, void*);
static const char * const ExceptHandler_fields[]={
    "type",
    "name",
    "body",
};
static PyObject* ast2obj_arguments(struct ast_state *state, struct validator
                                   *vstate, void*);
static const char * const arguments_fields[]={
    "posonlyargs",
    "args",
    "vararg",
    "kwonlyargs",
    "kw_defaults",
    "kwarg",
    "defaults",
};
static PyObject* ast2obj_arg(struct ast_state *state, struct validator *vstate,
                             void*);
static const char * const arg_attributes[] = {
    "lineno",
    "col_offset",
    "end_lineno",
    "end_col_offset",
};
static const char * const arg_fields[]={
    "arg",
    "annotation",
    "type_comment",
};
static PyObject* ast2obj_keyword(struct ast_state *state, struct validator
                                 *vstate, void*);
static const char * const keyword_attributes[] = {
    "lineno",
    "col_offset",
    "end_lineno",
    "end_col_offset",
};
static const char * const keyword_fields[]={
    "arg",
    "value",
};
static PyObject* ast2obj_alias(struct ast_state *state, struct validator
                               *vstate, void*);
static const char * const alias_attributes[] = {
    "lineno",
    "col_offset",
    "end_lineno",
    "end_col_offset",
};
static const char * const alias_fields[]={
    "name",
    "asname",
};
static PyObject* ast2obj_withitem(struct ast_state *state, struct validator
                                  *vstate, void*);
static const char * const withitem_fields[]={
    "context_expr",
    "optional_vars",
};
static PyObject* ast2obj_match_case(struct ast_state *state, struct validator
                                    *vstate, void*);
static const char * const match_case_fields[]={
    "pattern",
    "guard",
    "body",
};
static const char * const pattern_attributes[] = {
    "lineno",
    "col_offset",
    "end_lineno",
    "end_col_offset",
};
static PyObject* ast2obj_pattern(struct ast_state *state, struct validator
                                 *vstate, void*);
static const char * const MatchValue_fields[]={
    "value",
};
static const char * const MatchSingleton_fields[]={
    "value",
};
static const char * const MatchSequence_fields[]={
    "patterns",
};
static const char * const MatchMapping_fields[]={
    "keys",
    "patterns",
    "rest",
};
static const char * const MatchClass_fields[]={
    "cls",
    "patterns",
    "kwd_attrs",
    "kwd_patterns",
};
static const char * const MatchStar_fields[]={
    "name",
};
static const char * const MatchAs_fields[]={
    "pattern",
    "name",
};
static const char * const MatchOr_fields[]={
    "patterns",
};
static PyObject* ast2obj_type_ignore(struct ast_state *state, struct validator
                                     *vstate, void*);
static const char * const TypeIgnore_fields[]={
    "lineno",
    "tag",
};
static const char * const type_param_attributes[] = {
    "lineno",
    "col_offset",
    "end_lineno",
    "end_col_offset",
};
static PyObject* ast2obj_type_param(struct ast_state *state, struct validator
                                    *vstate, void*);
static const char * const TypeVar_fields[]={
    "name",
    "bound",
};
static const char * const ParamSpec_fields[]={
    "name",
};
static const char * const TypeVarTuple_fields[]={
    "name",
};



typedef struct {
    PyObject_HEAD
    PyObject *dict;
} AST_object;

static void
ast_dealloc(AST_object *self)
{
    /* bpo-31095: UnTrack is needed before calling any callbacks */
    PyTypeObject *tp = Py_TYPE(self);
    PyObject_GC_UnTrack(self);
    Py_CLEAR(self->dict);
    freefunc free_func = PyType_GetSlot(tp, Py_tp_free);
    assert(free_func != NULL);
    free_func(self);
    Py_DECREF(tp);
}

static int
ast_traverse(AST_object *self, visitproc visit, void *arg)
{
    Py_VISIT(Py_TYPE(self));
    Py_VISIT(self->dict);
    return 0;
}

static int
ast_clear(AST_object *self)
{
    Py_CLEAR(self->dict);
    return 0;
}

static int
ast_type_init(PyObject *self, PyObject *args, PyObject *kw)
{
    struct ast_state *state = get_ast_state();
    if (state == NULL) {
        return -1;
    }

    Py_ssize_t i, numfields = 0;
    int res = -1;
    PyObject *key, *value, *fields;
    if (PyObject_GetOptionalAttr((PyObject*)Py_TYPE(self), state->_fields, &fields) < 0) {
        goto cleanup;
    }
    if (fields) {
        numfields = PySequence_Size(fields);
        if (numfields == -1) {
            goto cleanup;
        }
    }

    res = 0; /* if no error occurs, this stays 0 to the end */
    if (numfields < PyTuple_GET_SIZE(args)) {
        PyErr_Format(PyExc_TypeError, "%.400s constructor takes at most "
                     "%zd positional argument%s",
                     _PyType_Name(Py_TYPE(self)),
                     numfields, numfields == 1 ? "" : "s");
        res = -1;
        goto cleanup;
    }
    for (i = 0; i < PyTuple_GET_SIZE(args); i++) {
        /* cannot be reached when fields is NULL */
        PyObject *name = PySequence_GetItem(fields, i);
        if (!name) {
            res = -1;
            goto cleanup;
        }
        res = PyObject_SetAttr(self, name, PyTuple_GET_ITEM(args, i));
        Py_DECREF(name);
        if (res < 0) {
            goto cleanup;
        }
    }
    if (kw) {
        i = 0;  /* needed by PyDict_Next */
        while (PyDict_Next(kw, &i, &key, &value)) {
            int contains = PySequence_Contains(fields, key);
            if (contains == -1) {
                res = -1;
                goto cleanup;
            } else if (contains == 1) {
                Py_ssize_t p = PySequence_Index(fields, key);
                if (p == -1) {
                    res = -1;
                    goto cleanup;
                }
                if (p < PyTuple_GET_SIZE(args)) {
                    PyErr_Format(PyExc_TypeError,
                        "%.400s got multiple values for argument '%U'",
                        Py_TYPE(self)->tp_name, key);
                    res = -1;
                    goto cleanup;
                }
            }
            res = PyObject_SetAttr(self, key, value);
            if (res < 0) {
                goto cleanup;
            }
        }
    }
  cleanup:
    Py_XDECREF(fields);
    return res;
}

/* Pickling support */
static PyObject *
ast_type_reduce(PyObject *self, PyObject *unused)
{
    struct ast_state *state = get_ast_state();
    if (state == NULL) {
        return NULL;
    }

    PyObject *dict;
    if (PyObject_GetOptionalAttr(self, state->__dict__, &dict) < 0) {
        return NULL;
    }
    if (dict) {
        return Py_BuildValue("O()N", Py_TYPE(self), dict);
    }
    return Py_BuildValue("O()", Py_TYPE(self));
}

static PyMemberDef ast_type_members[] = {
    {"__dictoffset__", Py_T_PYSSIZET, offsetof(AST_object, dict), Py_READONLY},
    {NULL}  /* Sentinel */
};

static PyMethodDef ast_type_methods[] = {
    {"__reduce__", ast_type_reduce, METH_NOARGS, NULL},
    {NULL}
};

static PyGetSetDef ast_type_getsets[] = {
    {"__dict__", PyObject_GenericGetDict, PyObject_GenericSetDict},
    {NULL}
};

static PyType_Slot AST_type_slots[] = {
    {Py_tp_dealloc, ast_dealloc},
    {Py_tp_getattro, PyObject_GenericGetAttr},
    {Py_tp_setattro, PyObject_GenericSetAttr},
    {Py_tp_traverse, ast_traverse},
    {Py_tp_clear, ast_clear},
    {Py_tp_members, ast_type_members},
    {Py_tp_methods, ast_type_methods},
    {Py_tp_getset, ast_type_getsets},
    {Py_tp_init, ast_type_init},
    {Py_tp_alloc, PyType_GenericAlloc},
    {Py_tp_new, PyType_GenericNew},
    {Py_tp_free, PyObject_GC_Del},
    {0, 0},
};

static PyType_Spec AST_type_spec = {
    "ast.AST",
    sizeof(AST_object),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC,
    AST_type_slots
};

static PyObject *
make_type(struct ast_state *state, const char *type, PyObject* base,
          const char* const* fields, int num_fields, const char *doc)
{
    PyObject *fnames, *result;
    int i;
    fnames = PyTuple_New(num_fields);
    if (!fnames) return NULL;
    for (i = 0; i < num_fields; i++) {
        PyObject *field = PyUnicode_InternFromString(fields[i]);
        if (!field) {
            Py_DECREF(fnames);
            return NULL;
        }
        PyTuple_SET_ITEM(fnames, i, field);
    }
    result = PyObject_CallFunction((PyObject*)&PyType_Type, "s(O){OOOOOOOs}",
                    type, base,
                    state->_fields, fnames,
                    state->__match_args__, fnames,
                    state->__module__,
                    state->ast,
                    state->__doc__, doc);
    Py_DECREF(fnames);
    return result;
}

static int
add_attributes(struct ast_state *state, PyObject *type, const char * const *attrs, int num_fields)
{
    int i, result;
    PyObject *s, *l = PyTuple_New(num_fields);
    if (!l)
        return -1;
    for (i = 0; i < num_fields; i++) {
        s = PyUnicode_InternFromString(attrs[i]);
        if (!s) {
            Py_DECREF(l);
            return -1;
        }
        PyTuple_SET_ITEM(l, i, s);
    }
    result = PyObject_SetAttr(type, state->_attributes, l);
    Py_DECREF(l);
    return result;
}

/* Conversion AST -> Python */

static PyObject* ast2obj_list(struct ast_state *state, struct validator *vstate, asdl_seq *seq,
                              PyObject* (*func)(struct ast_state *state, struct validator *vstate, void*))
{
    Py_ssize_t i, n = asdl_seq_LEN(seq);
    PyObject *result = PyList_New(n);
    PyObject *value;
    if (!result)
        return NULL;
    for (i = 0; i < n; i++) {
        value = func(state, vstate, asdl_seq_GET_UNTYPED(seq, i));
        if (!value) {
            Py_DECREF(result);
            return NULL;
        }
        PyList_SET_ITEM(result, i, value);
    }
    return result;
}

static PyObject* ast2obj_object(struct ast_state *Py_UNUSED(state), struct validator *Py_UNUSED(vstate), void *o)
{
    PyObject *op = (PyObject*)o;
    if (!op) {
        op = Py_None;
    }
    return Py_NewRef(op);
}
#define ast2obj_constant ast2obj_object
#define ast2obj_identifier ast2obj_object
#define ast2obj_string ast2obj_object

static PyObject* ast2obj_int(struct ast_state *Py_UNUSED(state), struct validator *Py_UNUSED(vstate), long b)
{
    return PyLong_FromLong(b);
}

/* Conversion Python -> AST */

static int obj2ast_object(struct ast_state *Py_UNUSED(state), PyObject* obj, PyObject** out, PyArena* arena)
{
    if (obj == Py_None)
        obj = NULL;
    if (obj) {
        if (_PyArena_AddPyObject(arena, obj) < 0) {
            *out = NULL;
            return -1;
        }
        *out = Py_NewRef(obj);
    }
    else {
        *out = NULL;
    }
    return 0;
}

static int obj2ast_constant(struct ast_state *Py_UNUSED(state), PyObject* obj, PyObject** out, PyArena* arena)
{
    if (_PyArena_AddPyObject(arena, obj) < 0) {
        *out = NULL;
        return -1;
    }
    *out = Py_NewRef(obj);
    return 0;
}

static int obj2ast_identifier(struct ast_state *state, PyObject* obj, PyObject** out, PyArena* arena)
{
    if (!PyUnicode_CheckExact(obj) && obj != Py_None) {
        PyErr_SetString(PyExc_TypeError, "AST identifier must be of type str");
        return -1;
    }
    return obj2ast_object(state, obj, out, arena);
}

static int obj2ast_string(struct ast_state *state, PyObject* obj, PyObject** out, PyArena* arena)
{
    if (!PyUnicode_CheckExact(obj) && !PyBytes_CheckExact(obj)) {
        PyErr_SetString(PyExc_TypeError, "AST string must be of type str");
        return -1;
    }
    return obj2ast_object(state, obj, out, arena);
}

static int obj2ast_int(struct ast_state* Py_UNUSED(state), PyObject* obj, int* out, PyArena* arena)
{
    int i;
    if (!PyLong_Check(obj)) {
        PyErr_Format(PyExc_ValueError, "invalid integer value: %R", obj);
        return -1;
    }

    i = PyLong_AsInt(obj);
    if (i == -1 && PyErr_Occurred())
        return -1;
    *out = i;
    return 0;
}

static int add_ast_fields(struct ast_state *state)
{
    PyObject *empty_tuple;
    empty_tuple = PyTuple_New(0);
    if (!empty_tuple ||
        PyObject_SetAttrString(state->AST_type, "_fields", empty_tuple) < 0 ||
        PyObject_SetAttrString(state->AST_type, "__match_args__", empty_tuple) < 0 ||
        PyObject_SetAttrString(state->AST_type, "_attributes", empty_tuple) < 0) {
        Py_XDECREF(empty_tuple);
        return -1;
    }
    Py_DECREF(empty_tuple);
    return 0;
}



static int
init_types(struct ast_state *state)
{
    if (init_identifiers(state) < 0) {
        return -1;
    }
    state->AST_type = PyType_FromSpec(&AST_type_spec);
    if (!state->AST_type) {
        return -1;
    }
    if (add_ast_fields(state) < 0) {
        return -1;
    }
    state->mod_type = make_type(state, "mod", state->AST_type, NULL, 0,
        "mod = Module(stmt* body, type_ignore* type_ignores)\n"
        "    | Interactive(stmt* body)\n"
        "    | Expression(expr body)\n"
        "    | FunctionType(expr* argtypes, expr returns)");
    if (!state->mod_type) return -1;
    if (add_attributes(state, state->mod_type, NULL, 0) < 0) return -1;
    state->Module_type = make_type(state, "Module", state->mod_type,
                                   Module_fields, 2,
        "Module(stmt* body, type_ignore* type_ignores)");
    if (!state->Module_type) return -1;
    state->Interactive_type = make_type(state, "Interactive", state->mod_type,
                                        Interactive_fields, 1,
        "Interactive(stmt* body)");
    if (!state->Interactive_type) return -1;
    state->Expression_type = make_type(state, "Expression", state->mod_type,
                                       Expression_fields, 1,
        "Expression(expr body)");
    if (!state->Expression_type) return -1;
    state->FunctionType_type = make_type(state, "FunctionType",
                                         state->mod_type, FunctionType_fields,
                                         2,
        "FunctionType(expr* argtypes, expr returns)");
    if (!state->FunctionType_type) return -1;
    state->stmt_type = make_type(state, "stmt", state->AST_type, NULL, 0,
        "stmt = FunctionDef(identifier name, arguments args, stmt* body, expr* decorator_list, expr? returns, string? type_comment, type_param* type_params)\n"
        "     | AsyncFunctionDef(identifier name, arguments args, stmt* body, expr* decorator_list, expr? returns, string? type_comment, type_param* type_params)\n"
        "     | ClassDef(identifier name, expr* bases, keyword* keywords, stmt* body, expr* decorator_list, type_param* type_params)\n"
        "     | Return(expr? value)\n"
        "     | Delete(expr* targets)\n"
        "     | Assign(expr* targets, expr value, string? type_comment)\n"
        "     | TypeAlias(expr name, type_param* type_params, expr value)\n"
        "     | AugAssign(expr target, operator op, expr value)\n"
        "     | AnnAssign(expr target, expr annotation, expr? value, int simple)\n"
        "     | For(expr target, expr iter, stmt* body, stmt* orelse, string? type_comment)\n"
        "     | AsyncFor(expr target, expr iter, stmt* body, stmt* orelse, string? type_comment)\n"
        "     | While(expr test, stmt* body, stmt* orelse)\n"
        "     | If(expr test, stmt* body, stmt* orelse)\n"
        "     | With(withitem* items, stmt* body, string? type_comment)\n"
        "     | AsyncWith(withitem* items, stmt* body, string? type_comment)\n"
        "     | Match(expr subject, match_case* cases)\n"
        "     | Raise(expr? exc, expr? cause)\n"
        "     | Try(stmt* body, excepthandler* handlers, stmt* orelse, stmt* finalbody)\n"
        "     | TryStar(stmt* body, excepthandler* handlers, stmt* orelse, stmt* finalbody)\n"
        "     | Assert(expr test, expr? msg)\n"
        "     | Import(alias* names)\n"
        "     | ImportFrom(identifier? module, alias* names, int? level)\n"
        "     | Global(identifier* names)\n"
        "     | Nonlocal(identifier* names)\n"
        "     | Expr(expr value)\n"
        "     | Pass\n"
        "     | Break\n"
        "     | Continue");
    if (!state->stmt_type) return -1;
    if (add_attributes(state, state->stmt_type, stmt_attributes, 4) < 0) return
        -1;
    if (PyObject_SetAttr(state->stmt_type, state->end_lineno, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->stmt_type, state->end_col_offset, Py_None) ==
        -1)
        return -1;
    state->FunctionDef_type = make_type(state, "FunctionDef", state->stmt_type,
                                        FunctionDef_fields, 7,
        "FunctionDef(identifier name, arguments args, stmt* body, expr* decorator_list, expr? returns, string? type_comment, type_param* type_params)");
    if (!state->FunctionDef_type) return -1;
    if (PyObject_SetAttr(state->FunctionDef_type, state->returns, Py_None) ==
        -1)
        return -1;
    if (PyObject_SetAttr(state->FunctionDef_type, state->type_comment, Py_None)
        == -1)
        return -1;
    state->AsyncFunctionDef_type = make_type(state, "AsyncFunctionDef",
                                             state->stmt_type,
                                             AsyncFunctionDef_fields, 7,
        "AsyncFunctionDef(identifier name, arguments args, stmt* body, expr* decorator_list, expr? returns, string? type_comment, type_param* type_params)");
    if (!state->AsyncFunctionDef_type) return -1;
    if (PyObject_SetAttr(state->AsyncFunctionDef_type, state->returns, Py_None)
        == -1)
        return -1;
    if (PyObject_SetAttr(state->AsyncFunctionDef_type, state->type_comment,
        Py_None) == -1)
        return -1;
    state->ClassDef_type = make_type(state, "ClassDef", state->stmt_type,
                                     ClassDef_fields, 6,
        "ClassDef(identifier name, expr* bases, keyword* keywords, stmt* body, expr* decorator_list, type_param* type_params)");
    if (!state->ClassDef_type) return -1;
    state->Return_type = make_type(state, "Return", state->stmt_type,
                                   Return_fields, 1,
        "Return(expr? value)");
    if (!state->Return_type) return -1;
    if (PyObject_SetAttr(state->Return_type, state->value, Py_None) == -1)
        return -1;
    state->Delete_type = make_type(state, "Delete", state->stmt_type,
                                   Delete_fields, 1,
        "Delete(expr* targets)");
    if (!state->Delete_type) return -1;
    state->Assign_type = make_type(state, "Assign", state->stmt_type,
                                   Assign_fields, 3,
        "Assign(expr* targets, expr value, string? type_comment)");
    if (!state->Assign_type) return -1;
    if (PyObject_SetAttr(state->Assign_type, state->type_comment, Py_None) ==
        -1)
        return -1;
    state->TypeAlias_type = make_type(state, "TypeAlias", state->stmt_type,
                                      TypeAlias_fields, 3,
        "TypeAlias(expr name, type_param* type_params, expr value)");
    if (!state->TypeAlias_type) return -1;
    state->AugAssign_type = make_type(state, "AugAssign", state->stmt_type,
                                      AugAssign_fields, 3,
        "AugAssign(expr target, operator op, expr value)");
    if (!state->AugAssign_type) return -1;
    state->AnnAssign_type = make_type(state, "AnnAssign", state->stmt_type,
                                      AnnAssign_fields, 4,
        "AnnAssign(expr target, expr annotation, expr? value, int simple)");
    if (!state->AnnAssign_type) return -1;
    if (PyObject_SetAttr(state->AnnAssign_type, state->value, Py_None) == -1)
        return -1;
    state->For_type = make_type(state, "For", state->stmt_type, For_fields, 5,
        "For(expr target, expr iter, stmt* body, stmt* orelse, string? type_comment)");
    if (!state->For_type) return -1;
    if (PyObject_SetAttr(state->For_type, state->type_comment, Py_None) == -1)
        return -1;
    state->AsyncFor_type = make_type(state, "AsyncFor", state->stmt_type,
                                     AsyncFor_fields, 5,
        "AsyncFor(expr target, expr iter, stmt* body, stmt* orelse, string? type_comment)");
    if (!state->AsyncFor_type) return -1;
    if (PyObject_SetAttr(state->AsyncFor_type, state->type_comment, Py_None) ==
        -1)
        return -1;
    state->While_type = make_type(state, "While", state->stmt_type,
                                  While_fields, 3,
        "While(expr test, stmt* body, stmt* orelse)");
    if (!state->While_type) return -1;
    state->If_type = make_type(state, "If", state->stmt_type, If_fields, 3,
        "If(expr test, stmt* body, stmt* orelse)");
    if (!state->If_type) return -1;
    state->With_type = make_type(state, "With", state->stmt_type, With_fields,
                                 3,
        "With(withitem* items, stmt* body, string? type_comment)");
    if (!state->With_type) return -1;
    if (PyObject_SetAttr(state->With_type, state->type_comment, Py_None) == -1)
        return -1;
    state->AsyncWith_type = make_type(state, "AsyncWith", state->stmt_type,
                                      AsyncWith_fields, 3,
        "AsyncWith(withitem* items, stmt* body, string? type_comment)");
    if (!state->AsyncWith_type) return -1;
    if (PyObject_SetAttr(state->AsyncWith_type, state->type_comment, Py_None)
        == -1)
        return -1;
    state->Match_type = make_type(state, "Match", state->stmt_type,
                                  Match_fields, 2,
        "Match(expr subject, match_case* cases)");
    if (!state->Match_type) return -1;
    state->Raise_type = make_type(state, "Raise", state->stmt_type,
                                  Raise_fields, 2,
        "Raise(expr? exc, expr? cause)");
    if (!state->Raise_type) return -1;
    if (PyObject_SetAttr(state->Raise_type, state->exc, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->Raise_type, state->cause, Py_None) == -1)
        return -1;
    state->Try_type = make_type(state, "Try", state->stmt_type, Try_fields, 4,
        "Try(stmt* body, excepthandler* handlers, stmt* orelse, stmt* finalbody)");
    if (!state->Try_type) return -1;
    state->TryStar_type = make_type(state, "TryStar", state->stmt_type,
                                    TryStar_fields, 4,
        "TryStar(stmt* body, excepthandler* handlers, stmt* orelse, stmt* finalbody)");
    if (!state->TryStar_type) return -1;
    state->Assert_type = make_type(state, "Assert", state->stmt_type,
                                   Assert_fields, 2,
        "Assert(expr test, expr? msg)");
    if (!state->Assert_type) return -1;
    if (PyObject_SetAttr(state->Assert_type, state->msg, Py_None) == -1)
        return -1;
    state->Import_type = make_type(state, "Import", state->stmt_type,
                                   Import_fields, 1,
        "Import(alias* names)");
    if (!state->Import_type) return -1;
    state->ImportFrom_type = make_type(state, "ImportFrom", state->stmt_type,
                                       ImportFrom_fields, 3,
        "ImportFrom(identifier? module, alias* names, int? level)");
    if (!state->ImportFrom_type) return -1;
    if (PyObject_SetAttr(state->ImportFrom_type, state->module, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->ImportFrom_type, state->level, Py_None) == -1)
        return -1;
    state->Global_type = make_type(state, "Global", state->stmt_type,
                                   Global_fields, 1,
        "Global(identifier* names)");
    if (!state->Global_type) return -1;
    state->Nonlocal_type = make_type(state, "Nonlocal", state->stmt_type,
                                     Nonlocal_fields, 1,
        "Nonlocal(identifier* names)");
    if (!state->Nonlocal_type) return -1;
    state->Expr_type = make_type(state, "Expr", state->stmt_type, Expr_fields,
                                 1,
        "Expr(expr value)");
    if (!state->Expr_type) return -1;
    state->Pass_type = make_type(state, "Pass", state->stmt_type, NULL, 0,
        "Pass");
    if (!state->Pass_type) return -1;
    state->Break_type = make_type(state, "Break", state->stmt_type, NULL, 0,
        "Break");
    if (!state->Break_type) return -1;
    state->Continue_type = make_type(state, "Continue", state->stmt_type, NULL,
                                     0,
        "Continue");
    if (!state->Continue_type) return -1;
    state->expr_type = make_type(state, "expr", state->AST_type, NULL, 0,
        "expr = BoolOp(boolop op, expr* values)\n"
        "     | NamedExpr(expr target, expr value)\n"
        "     | BinOp(expr left, operator op, expr right)\n"
        "     | UnaryOp(unaryop op, expr operand)\n"
        "     | Lambda(arguments args, expr body)\n"
        "     | IfExp(expr test, expr body, expr orelse)\n"
        "     | Dict(expr* keys, expr* values)\n"
        "     | Set(expr* elts)\n"
        "     | ListComp(expr elt, comprehension* generators)\n"
        "     | SetComp(expr elt, comprehension* generators)\n"
        "     | DictComp(expr key, expr value, comprehension* generators)\n"
        "     | GeneratorExp(expr elt, comprehension* generators)\n"
        "     | Await(expr value)\n"
        "     | Yield(expr? value)\n"
        "     | YieldFrom(expr value)\n"
        "     | Compare(expr left, cmpop* ops, expr* comparators)\n"
        "     | Call(expr func, expr* args, keyword* keywords)\n"
        "     | FormattedValue(expr value, int conversion, expr? format_spec)\n"
        "     | JoinedStr(expr* values)\n"
        "     | Constant(constant value, string? kind)\n"
        "     | Attribute(expr value, identifier attr, expr_context ctx)\n"
        "     | Subscript(expr value, expr slice, expr_context ctx)\n"
        "     | Starred(expr value, expr_context ctx)\n"
        "     | Name(identifier id, expr_context ctx)\n"
        "     | List(expr* elts, expr_context ctx)\n"
        "     | Tuple(expr* elts, expr_context ctx)\n"
        "     | Slice(expr? lower, expr? upper, expr? step)");
    if (!state->expr_type) return -1;
    if (add_attributes(state, state->expr_type, expr_attributes, 4) < 0) return
        -1;
    if (PyObject_SetAttr(state->expr_type, state->end_lineno, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->expr_type, state->end_col_offset, Py_None) ==
        -1)
        return -1;
    state->BoolOp_type = make_type(state, "BoolOp", state->expr_type,
                                   BoolOp_fields, 2,
        "BoolOp(boolop op, expr* values)");
    if (!state->BoolOp_type) return -1;
    state->NamedExpr_type = make_type(state, "NamedExpr", state->expr_type,
                                      NamedExpr_fields, 2,
        "NamedExpr(expr target, expr value)");
    if (!state->NamedExpr_type) return -1;
    state->BinOp_type = make_type(state, "BinOp", state->expr_type,
                                  BinOp_fields, 3,
        "BinOp(expr left, operator op, expr right)");
    if (!state->BinOp_type) return -1;
    state->UnaryOp_type = make_type(state, "UnaryOp", state->expr_type,
                                    UnaryOp_fields, 2,
        "UnaryOp(unaryop op, expr operand)");
    if (!state->UnaryOp_type) return -1;
    state->Lambda_type = make_type(state, "Lambda", state->expr_type,
                                   Lambda_fields, 2,
        "Lambda(arguments args, expr body)");
    if (!state->Lambda_type) return -1;
    state->IfExp_type = make_type(state, "IfExp", state->expr_type,
                                  IfExp_fields, 3,
        "IfExp(expr test, expr body, expr orelse)");
    if (!state->IfExp_type) return -1;
    state->Dict_type = make_type(state, "Dict", state->expr_type, Dict_fields,
                                 2,
        "Dict(expr* keys, expr* values)");
    if (!state->Dict_type) return -1;
    state->Set_type = make_type(state, "Set", state->expr_type, Set_fields, 1,
        "Set(expr* elts)");
    if (!state->Set_type) return -1;
    state->ListComp_type = make_type(state, "ListComp", state->expr_type,
                                     ListComp_fields, 2,
        "ListComp(expr elt, comprehension* generators)");
    if (!state->ListComp_type) return -1;
    state->SetComp_type = make_type(state, "SetComp", state->expr_type,
                                    SetComp_fields, 2,
        "SetComp(expr elt, comprehension* generators)");
    if (!state->SetComp_type) return -1;
    state->DictComp_type = make_type(state, "DictComp", state->expr_type,
                                     DictComp_fields, 3,
        "DictComp(expr key, expr value, comprehension* generators)");
    if (!state->DictComp_type) return -1;
    state->GeneratorExp_type = make_type(state, "GeneratorExp",
                                         state->expr_type, GeneratorExp_fields,
                                         2,
        "GeneratorExp(expr elt, comprehension* generators)");
    if (!state->GeneratorExp_type) return -1;
    state->Await_type = make_type(state, "Await", state->expr_type,
                                  Await_fields, 1,
        "Await(expr value)");
    if (!state->Await_type) return -1;
    state->Yield_type = make_type(state, "Yield", state->expr_type,
                                  Yield_fields, 1,
        "Yield(expr? value)");
    if (!state->Yield_type) return -1;
    if (PyObject_SetAttr(state->Yield_type, state->value, Py_None) == -1)
        return -1;
    state->YieldFrom_type = make_type(state, "YieldFrom", state->expr_type,
                                      YieldFrom_fields, 1,
        "YieldFrom(expr value)");
    if (!state->YieldFrom_type) return -1;
    state->Compare_type = make_type(state, "Compare", state->expr_type,
                                    Compare_fields, 3,
        "Compare(expr left, cmpop* ops, expr* comparators)");
    if (!state->Compare_type) return -1;
    state->Call_type = make_type(state, "Call", state->expr_type, Call_fields,
                                 3,
        "Call(expr func, expr* args, keyword* keywords)");
    if (!state->Call_type) return -1;
    state->FormattedValue_type = make_type(state, "FormattedValue",
                                           state->expr_type,
                                           FormattedValue_fields, 3,
        "FormattedValue(expr value, int conversion, expr? format_spec)");
    if (!state->FormattedValue_type) return -1;
    if (PyObject_SetAttr(state->FormattedValue_type, state->format_spec,
        Py_None) == -1)
        return -1;
    state->JoinedStr_type = make_type(state, "JoinedStr", state->expr_type,
                                      JoinedStr_fields, 1,
        "JoinedStr(expr* values)");
    if (!state->JoinedStr_type) return -1;
    state->Constant_type = make_type(state, "Constant", state->expr_type,
                                     Constant_fields, 2,
        "Constant(constant value, string? kind)");
    if (!state->Constant_type) return -1;
    if (PyObject_SetAttr(state->Constant_type, state->kind, Py_None) == -1)
        return -1;
    state->Attribute_type = make_type(state, "Attribute", state->expr_type,
                                      Attribute_fields, 3,
        "Attribute(expr value, identifier attr, expr_context ctx)");
    if (!state->Attribute_type) return -1;
    state->Subscript_type = make_type(state, "Subscript", state->expr_type,
                                      Subscript_fields, 3,
        "Subscript(expr value, expr slice, expr_context ctx)");
    if (!state->Subscript_type) return -1;
    state->Starred_type = make_type(state, "Starred", state->expr_type,
                                    Starred_fields, 2,
        "Starred(expr value, expr_context ctx)");
    if (!state->Starred_type) return -1;
    state->Name_type = make_type(state, "Name", state->expr_type, Name_fields,
                                 2,
        "Name(identifier id, expr_context ctx)");
    if (!state->Name_type) return -1;
    state->List_type = make_type(state, "List", state->expr_type, List_fields,
                                 2,
        "List(expr* elts, expr_context ctx)");
    if (!state->List_type) return -1;
    state->Tuple_type = make_type(state, "Tuple", state->expr_type,
                                  Tuple_fields, 2,
        "Tuple(expr* elts, expr_context ctx)");
    if (!state->Tuple_type) return -1;
    state->Slice_type = make_type(state, "Slice", state->expr_type,
                                  Slice_fields, 3,
        "Slice(expr? lower, expr? upper, expr? step)");
    if (!state->Slice_type) return -1;
    if (PyObject_SetAttr(state->Slice_type, state->lower, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->Slice_type, state->upper, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->Slice_type, state->step, Py_None) == -1)
        return -1;
    state->expr_context_type = make_type(state, "expr_context",
                                         state->AST_type, NULL, 0,
        "expr_context = Load | Store | Del");
    if (!state->expr_context_type) return -1;
    if (add_attributes(state, state->expr_context_type, NULL, 0) < 0) return -1;
    state->Load_type = make_type(state, "Load", state->expr_context_type, NULL,
                                 0,
        "Load");
    if (!state->Load_type) return -1;
    state->Load_singleton = PyType_GenericNew((PyTypeObject *)state->Load_type,
                                              NULL, NULL);
    if (!state->Load_singleton) return -1;
    state->Store_type = make_type(state, "Store", state->expr_context_type,
                                  NULL, 0,
        "Store");
    if (!state->Store_type) return -1;
    state->Store_singleton = PyType_GenericNew((PyTypeObject
                                               *)state->Store_type, NULL, NULL);
    if (!state->Store_singleton) return -1;
    state->Del_type = make_type(state, "Del", state->expr_context_type, NULL, 0,
        "Del");
    if (!state->Del_type) return -1;
    state->Del_singleton = PyType_GenericNew((PyTypeObject *)state->Del_type,
                                             NULL, NULL);
    if (!state->Del_singleton) return -1;
    state->boolop_type = make_type(state, "boolop", state->AST_type, NULL, 0,
        "boolop = And | Or");
    if (!state->boolop_type) return -1;
    if (add_attributes(state, state->boolop_type, NULL, 0) < 0) return -1;
    state->And_type = make_type(state, "And", state->boolop_type, NULL, 0,
        "And");
    if (!state->And_type) return -1;
    state->And_singleton = PyType_GenericNew((PyTypeObject *)state->And_type,
                                             NULL, NULL);
    if (!state->And_singleton) return -1;
    state->Or_type = make_type(state, "Or", state->boolop_type, NULL, 0,
        "Or");
    if (!state->Or_type) return -1;
    state->Or_singleton = PyType_GenericNew((PyTypeObject *)state->Or_type,
                                            NULL, NULL);
    if (!state->Or_singleton) return -1;
    state->operator_type = make_type(state, "operator", state->AST_type, NULL,
                                     0,
        "operator = Add | Sub | Mult | MatMult | Div | Mod | Pow | LShift | RShift | BitOr | BitXor | BitAnd | FloorDiv");
    if (!state->operator_type) return -1;
    if (add_attributes(state, state->operator_type, NULL, 0) < 0) return -1;
    state->Add_type = make_type(state, "Add", state->operator_type, NULL, 0,
        "Add");
    if (!state->Add_type) return -1;
    state->Add_singleton = PyType_GenericNew((PyTypeObject *)state->Add_type,
                                             NULL, NULL);
    if (!state->Add_singleton) return -1;
    state->Sub_type = make_type(state, "Sub", state->operator_type, NULL, 0,
        "Sub");
    if (!state->Sub_type) return -1;
    state->Sub_singleton = PyType_GenericNew((PyTypeObject *)state->Sub_type,
                                             NULL, NULL);
    if (!state->Sub_singleton) return -1;
    state->Mult_type = make_type(state, "Mult", state->operator_type, NULL, 0,
        "Mult");
    if (!state->Mult_type) return -1;
    state->Mult_singleton = PyType_GenericNew((PyTypeObject *)state->Mult_type,
                                              NULL, NULL);
    if (!state->Mult_singleton) return -1;
    state->MatMult_type = make_type(state, "MatMult", state->operator_type,
                                    NULL, 0,
        "MatMult");
    if (!state->MatMult_type) return -1;
    state->MatMult_singleton = PyType_GenericNew((PyTypeObject
                                                 *)state->MatMult_type, NULL,
                                                 NULL);
    if (!state->MatMult_singleton) return -1;
    state->Div_type = make_type(state, "Div", state->operator_type, NULL, 0,
        "Div");
    if (!state->Div_type) return -1;
    state->Div_singleton = PyType_GenericNew((PyTypeObject *)state->Div_type,
                                             NULL, NULL);
    if (!state->Div_singleton) return -1;
    state->Mod_type = make_type(state, "Mod", state->operator_type, NULL, 0,
        "Mod");
    if (!state->Mod_type) return -1;
    state->Mod_singleton = PyType_GenericNew((PyTypeObject *)state->Mod_type,
                                             NULL, NULL);
    if (!state->Mod_singleton) return -1;
    state->Pow_type = make_type(state, "Pow", state->operator_type, NULL, 0,
        "Pow");
    if (!state->Pow_type) return -1;
    state->Pow_singleton = PyType_GenericNew((PyTypeObject *)state->Pow_type,
                                             NULL, NULL);
    if (!state->Pow_singleton) return -1;
    state->LShift_type = make_type(state, "LShift", state->operator_type, NULL,
                                   0,
        "LShift");
    if (!state->LShift_type) return -1;
    state->LShift_singleton = PyType_GenericNew((PyTypeObject
                                                *)state->LShift_type, NULL,
                                                NULL);
    if (!state->LShift_singleton) return -1;
    state->RShift_type = make_type(state, "RShift", state->operator_type, NULL,
                                   0,
        "RShift");
    if (!state->RShift_type) return -1;
    state->RShift_singleton = PyType_GenericNew((PyTypeObject
                                                *)state->RShift_type, NULL,
                                                NULL);
    if (!state->RShift_singleton) return -1;
    state->BitOr_type = make_type(state, "BitOr", state->operator_type, NULL, 0,
        "BitOr");
    if (!state->BitOr_type) return -1;
    state->BitOr_singleton = PyType_GenericNew((PyTypeObject
                                               *)state->BitOr_type, NULL, NULL);
    if (!state->BitOr_singleton) return -1;
    state->BitXor_type = make_type(state, "BitXor", state->operator_type, NULL,
                                   0,
        "BitXor");
    if (!state->BitXor_type) return -1;
    state->BitXor_singleton = PyType_GenericNew((PyTypeObject
                                                *)state->BitXor_type, NULL,
                                                NULL);
    if (!state->BitXor_singleton) return -1;
    state->BitAnd_type = make_type(state, "BitAnd", state->operator_type, NULL,
                                   0,
        "BitAnd");
    if (!state->BitAnd_type) return -1;
    state->BitAnd_singleton = PyType_GenericNew((PyTypeObject
                                                *)state->BitAnd_type, NULL,
                                                NULL);
    if (!state->BitAnd_singleton) return -1;
    state->FloorDiv_type = make_type(state, "FloorDiv", state->operator_type,
                                     NULL, 0,
        "FloorDiv");
    if (!state->FloorDiv_type) return -1;
    state->FloorDiv_singleton = PyType_GenericNew((PyTypeObject
                                                  *)state->FloorDiv_type, NULL,
                                                  NULL);
    if (!state->FloorDiv_singleton) return -1;
    state->unaryop_type = make_type(state, "unaryop", state->AST_type, NULL, 0,
        "unaryop = Invert | Not | UAdd | USub");
    if (!state->unaryop_type) return -1;
    if (add_attributes(state, state->unaryop_type, NULL, 0) < 0) return -1;
    state->Invert_type = make_type(state, "Invert", state->unaryop_type, NULL,
                                   0,
        "Invert");
    if (!state->Invert_type) return -1;
    state->Invert_singleton = PyType_GenericNew((PyTypeObject
                                                *)state->Invert_type, NULL,
                                                NULL);
    if (!state->Invert_singleton) return -1;
    state->Not_type = make_type(state, "Not", state->unaryop_type, NULL, 0,
        "Not");
    if (!state->Not_type) return -1;
    state->Not_singleton = PyType_GenericNew((PyTypeObject *)state->Not_type,
                                             NULL, NULL);
    if (!state->Not_singleton) return -1;
    state->UAdd_type = make_type(state, "UAdd", state->unaryop_type, NULL, 0,
        "UAdd");
    if (!state->UAdd_type) return -1;
    state->UAdd_singleton = PyType_GenericNew((PyTypeObject *)state->UAdd_type,
                                              NULL, NULL);
    if (!state->UAdd_singleton) return -1;
    state->USub_type = make_type(state, "USub", state->unaryop_type, NULL, 0,
        "USub");
    if (!state->USub_type) return -1;
    state->USub_singleton = PyType_GenericNew((PyTypeObject *)state->USub_type,
                                              NULL, NULL);
    if (!state->USub_singleton) return -1;
    state->cmpop_type = make_type(state, "cmpop", state->AST_type, NULL, 0,
        "cmpop = Eq | NotEq | Lt | LtE | Gt | GtE | Is | IsNot | In | NotIn");
    if (!state->cmpop_type) return -1;
    if (add_attributes(state, state->cmpop_type, NULL, 0) < 0) return -1;
    state->Eq_type = make_type(state, "Eq", state->cmpop_type, NULL, 0,
        "Eq");
    if (!state->Eq_type) return -1;
    state->Eq_singleton = PyType_GenericNew((PyTypeObject *)state->Eq_type,
                                            NULL, NULL);
    if (!state->Eq_singleton) return -1;
    state->NotEq_type = make_type(state, "NotEq", state->cmpop_type, NULL, 0,
        "NotEq");
    if (!state->NotEq_type) return -1;
    state->NotEq_singleton = PyType_GenericNew((PyTypeObject
                                               *)state->NotEq_type, NULL, NULL);
    if (!state->NotEq_singleton) return -1;
    state->Lt_type = make_type(state, "Lt", state->cmpop_type, NULL, 0,
        "Lt");
    if (!state->Lt_type) return -1;
    state->Lt_singleton = PyType_GenericNew((PyTypeObject *)state->Lt_type,
                                            NULL, NULL);
    if (!state->Lt_singleton) return -1;
    state->LtE_type = make_type(state, "LtE", state->cmpop_type, NULL, 0,
        "LtE");
    if (!state->LtE_type) return -1;
    state->LtE_singleton = PyType_GenericNew((PyTypeObject *)state->LtE_type,
                                             NULL, NULL);
    if (!state->LtE_singleton) return -1;
    state->Gt_type = make_type(state, "Gt", state->cmpop_type, NULL, 0,
        "Gt");
    if (!state->Gt_type) return -1;
    state->Gt_singleton = PyType_GenericNew((PyTypeObject *)state->Gt_type,
                                            NULL, NULL);
    if (!state->Gt_singleton) return -1;
    state->GtE_type = make_type(state, "GtE", state->cmpop_type, NULL, 0,
        "GtE");
    if (!state->GtE_type) return -1;
    state->GtE_singleton = PyType_GenericNew((PyTypeObject *)state->GtE_type,
                                             NULL, NULL);
    if (!state->GtE_singleton) return -1;
    state->Is_type = make_type(state, "Is", state->cmpop_type, NULL, 0,
        "Is");
    if (!state->Is_type) return -1;
    state->Is_singleton = PyType_GenericNew((PyTypeObject *)state->Is_type,
                                            NULL, NULL);
    if (!state->Is_singleton) return -1;
    state->IsNot_type = make_type(state, "IsNot", state->cmpop_type, NULL, 0,
        "IsNot");
    if (!state->IsNot_type) return -1;
    state->IsNot_singleton = PyType_GenericNew((PyTypeObject
                                               *)state->IsNot_type, NULL, NULL);
    if (!state->IsNot_singleton) return -1;
    state->In_type = make_type(state, "In", state->cmpop_type, NULL, 0,
        "In");
    if (!state->In_type) return -1;
    state->In_singleton = PyType_GenericNew((PyTypeObject *)state->In_type,
                                            NULL, NULL);
    if (!state->In_singleton) return -1;
    state->NotIn_type = make_type(state, "NotIn", state->cmpop_type, NULL, 0,
        "NotIn");
    if (!state->NotIn_type) return -1;
    state->NotIn_singleton = PyType_GenericNew((PyTypeObject
                                               *)state->NotIn_type, NULL, NULL);
    if (!state->NotIn_singleton) return -1;
    state->comprehension_type = make_type(state, "comprehension",
                                          state->AST_type,
                                          comprehension_fields, 4,
        "comprehension(expr target, expr iter, expr* ifs, int is_async)");
    if (!state->comprehension_type) return -1;
    if (add_attributes(state, state->comprehension_type, NULL, 0) < 0) return
        -1;
    state->excepthandler_type = make_type(state, "excepthandler",
                                          state->AST_type, NULL, 0,
        "excepthandler = ExceptHandler(expr? type, identifier? name, stmt* body)");
    if (!state->excepthandler_type) return -1;
    if (add_attributes(state, state->excepthandler_type,
        excepthandler_attributes, 4) < 0) return -1;
    if (PyObject_SetAttr(state->excepthandler_type, state->end_lineno, Py_None)
        == -1)
        return -1;
    if (PyObject_SetAttr(state->excepthandler_type, state->end_col_offset,
        Py_None) == -1)
        return -1;
    state->ExceptHandler_type = make_type(state, "ExceptHandler",
                                          state->excepthandler_type,
                                          ExceptHandler_fields, 3,
        "ExceptHandler(expr? type, identifier? name, stmt* body)");
    if (!state->ExceptHandler_type) return -1;
    if (PyObject_SetAttr(state->ExceptHandler_type, state->type, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->ExceptHandler_type, state->name, Py_None) == -1)
        return -1;
    state->arguments_type = make_type(state, "arguments", state->AST_type,
                                      arguments_fields, 7,
        "arguments(arg* posonlyargs, arg* args, arg? vararg, arg* kwonlyargs, expr* kw_defaults, arg? kwarg, expr* defaults)");
    if (!state->arguments_type) return -1;
    if (add_attributes(state, state->arguments_type, NULL, 0) < 0) return -1;
    if (PyObject_SetAttr(state->arguments_type, state->vararg, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->arguments_type, state->kwarg, Py_None) == -1)
        return -1;
    state->arg_type = make_type(state, "arg", state->AST_type, arg_fields, 3,
        "arg(identifier arg, expr? annotation, string? type_comment)");
    if (!state->arg_type) return -1;
    if (add_attributes(state, state->arg_type, arg_attributes, 4) < 0) return
        -1;
    if (PyObject_SetAttr(state->arg_type, state->annotation, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->arg_type, state->type_comment, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->arg_type, state->end_lineno, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->arg_type, state->end_col_offset, Py_None) == -1)
        return -1;
    state->keyword_type = make_type(state, "keyword", state->AST_type,
                                    keyword_fields, 2,
        "keyword(identifier? arg, expr value)");
    if (!state->keyword_type) return -1;
    if (add_attributes(state, state->keyword_type, keyword_attributes, 4) < 0)
        return -1;
    if (PyObject_SetAttr(state->keyword_type, state->arg, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->keyword_type, state->end_lineno, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->keyword_type, state->end_col_offset, Py_None)
        == -1)
        return -1;
    state->alias_type = make_type(state, "alias", state->AST_type,
                                  alias_fields, 2,
        "alias(identifier name, identifier? asname)");
    if (!state->alias_type) return -1;
    if (add_attributes(state, state->alias_type, alias_attributes, 4) < 0)
        return -1;
    if (PyObject_SetAttr(state->alias_type, state->asname, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->alias_type, state->end_lineno, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->alias_type, state->end_col_offset, Py_None) ==
        -1)
        return -1;
    state->withitem_type = make_type(state, "withitem", state->AST_type,
                                     withitem_fields, 2,
        "withitem(expr context_expr, expr? optional_vars)");
    if (!state->withitem_type) return -1;
    if (add_attributes(state, state->withitem_type, NULL, 0) < 0) return -1;
    if (PyObject_SetAttr(state->withitem_type, state->optional_vars, Py_None)
        == -1)
        return -1;
    state->match_case_type = make_type(state, "match_case", state->AST_type,
                                       match_case_fields, 3,
        "match_case(pattern pattern, expr? guard, stmt* body)");
    if (!state->match_case_type) return -1;
    if (add_attributes(state, state->match_case_type, NULL, 0) < 0) return -1;
    if (PyObject_SetAttr(state->match_case_type, state->guard, Py_None) == -1)
        return -1;
    state->pattern_type = make_type(state, "pattern", state->AST_type, NULL, 0,
        "pattern = MatchValue(expr value)\n"
        "        | MatchSingleton(constant value)\n"
        "        | MatchSequence(pattern* patterns)\n"
        "        | MatchMapping(expr* keys, pattern* patterns, identifier? rest)\n"
        "        | MatchClass(expr cls, pattern* patterns, identifier* kwd_attrs, pattern* kwd_patterns)\n"
        "        | MatchStar(identifier? name)\n"
        "        | MatchAs(pattern? pattern, identifier? name)\n"
        "        | MatchOr(pattern* patterns)");
    if (!state->pattern_type) return -1;
    if (add_attributes(state, state->pattern_type, pattern_attributes, 4) < 0)
        return -1;
    state->MatchValue_type = make_type(state, "MatchValue",
                                       state->pattern_type, MatchValue_fields,
                                       1,
        "MatchValue(expr value)");
    if (!state->MatchValue_type) return -1;
    state->MatchSingleton_type = make_type(state, "MatchSingleton",
                                           state->pattern_type,
                                           MatchSingleton_fields, 1,
        "MatchSingleton(constant value)");
    if (!state->MatchSingleton_type) return -1;
    state->MatchSequence_type = make_type(state, "MatchSequence",
                                          state->pattern_type,
                                          MatchSequence_fields, 1,
        "MatchSequence(pattern* patterns)");
    if (!state->MatchSequence_type) return -1;
    state->MatchMapping_type = make_type(state, "MatchMapping",
                                         state->pattern_type,
                                         MatchMapping_fields, 3,
        "MatchMapping(expr* keys, pattern* patterns, identifier? rest)");
    if (!state->MatchMapping_type) return -1;
    if (PyObject_SetAttr(state->MatchMapping_type, state->rest, Py_None) == -1)
        return -1;
    state->MatchClass_type = make_type(state, "MatchClass",
                                       state->pattern_type, MatchClass_fields,
                                       4,
        "MatchClass(expr cls, pattern* patterns, identifier* kwd_attrs, pattern* kwd_patterns)");
    if (!state->MatchClass_type) return -1;
    state->MatchStar_type = make_type(state, "MatchStar", state->pattern_type,
                                      MatchStar_fields, 1,
        "MatchStar(identifier? name)");
    if (!state->MatchStar_type) return -1;
    if (PyObject_SetAttr(state->MatchStar_type, state->name, Py_None) == -1)
        return -1;
    state->MatchAs_type = make_type(state, "MatchAs", state->pattern_type,
                                    MatchAs_fields, 2,
        "MatchAs(pattern? pattern, identifier? name)");
    if (!state->MatchAs_type) return -1;
    if (PyObject_SetAttr(state->MatchAs_type, state->pattern, Py_None) == -1)
        return -1;
    if (PyObject_SetAttr(state->MatchAs_type, state->name, Py_None) == -1)
        return -1;
    state->MatchOr_type = make_type(state, "MatchOr", state->pattern_type,
                                    MatchOr_fields, 1,
        "MatchOr(pattern* patterns)");
    if (!state->MatchOr_type) return -1;
    state->type_ignore_type = make_type(state, "type_ignore", state->AST_type,
                                        NULL, 0,
        "type_ignore = TypeIgnore(int lineno, string tag)");
    if (!state->type_ignore_type) return -1;
    if (add_attributes(state, state->type_ignore_type, NULL, 0) < 0) return -1;
    state->TypeIgnore_type = make_type(state, "TypeIgnore",
                                       state->type_ignore_type,
                                       TypeIgnore_fields, 2,
        "TypeIgnore(int lineno, string tag)");
    if (!state->TypeIgnore_type) return -1;
    state->type_param_type = make_type(state, "type_param", state->AST_type,
                                       NULL, 0,
        "type_param = TypeVar(identifier name, expr? bound)\n"
        "           | ParamSpec(identifier name)\n"
        "           | TypeVarTuple(identifier name)");
    if (!state->type_param_type) return -1;
    if (add_attributes(state, state->type_param_type, type_param_attributes, 4)
        < 0) return -1;
    state->TypeVar_type = make_type(state, "TypeVar", state->type_param_type,
                                    TypeVar_fields, 2,
        "TypeVar(identifier name, expr? bound)");
    if (!state->TypeVar_type) return -1;
    if (PyObject_SetAttr(state->TypeVar_type, state->bound, Py_None) == -1)
        return -1;
    state->ParamSpec_type = make_type(state, "ParamSpec",
                                      state->type_param_type, ParamSpec_fields,
                                      1,
        "ParamSpec(identifier name)");
    if (!state->ParamSpec_type) return -1;
    state->TypeVarTuple_type = make_type(state, "TypeVarTuple",
                                         state->type_param_type,
                                         TypeVarTuple_fields, 1,
        "TypeVarTuple(identifier name)");
    if (!state->TypeVarTuple_type) return -1;

    return 0;
}

static int obj2ast_mod(struct ast_state *state, PyObject* obj, mod_ty* out,
                       PyArena* arena);
static int obj2ast_stmt(struct ast_state *state, PyObject* obj, stmt_ty* out,
                        PyArena* arena);
static int obj2ast_expr(struct ast_state *state, PyObject* obj, expr_ty* out,
                        PyArena* arena);
static int obj2ast_expr_context(struct ast_state *state, PyObject* obj,
                                expr_context_ty* out, PyArena* arena);
static int obj2ast_boolop(struct ast_state *state, PyObject* obj, boolop_ty*
                          out, PyArena* arena);
static int obj2ast_operator(struct ast_state *state, PyObject* obj,
                            operator_ty* out, PyArena* arena);
static int obj2ast_unaryop(struct ast_state *state, PyObject* obj, unaryop_ty*
                           out, PyArena* arena);
static int obj2ast_cmpop(struct ast_state *state, PyObject* obj, cmpop_ty* out,
                         PyArena* arena);
static int obj2ast_comprehension(struct ast_state *state, PyObject* obj,
                                 comprehension_ty* out, PyArena* arena);
static int obj2ast_excepthandler(struct ast_state *state, PyObject* obj,
                                 excepthandler_ty* out, PyArena* arena);
static int obj2ast_arguments(struct ast_state *state, PyObject* obj,
                             arguments_ty* out, PyArena* arena);
static int obj2ast_arg(struct ast_state *state, PyObject* obj, arg_ty* out,
                       PyArena* arena);
static int obj2ast_keyword(struct ast_state *state, PyObject* obj, keyword_ty*
                           out, PyArena* arena);
static int obj2ast_alias(struct ast_state *state, PyObject* obj, alias_ty* out,
                         PyArena* arena);
static int obj2ast_withitem(struct ast_state *state, PyObject* obj,
                            withitem_ty* out, PyArena* arena);
static int obj2ast_match_case(struct ast_state *state, PyObject* obj,
                              match_case_ty* out, PyArena* arena);
static int obj2ast_pattern(struct ast_state *state, PyObject* obj, pattern_ty*
                           out, PyArena* arena);
static int obj2ast_type_ignore(struct ast_state *state, PyObject* obj,
                               type_ignore_ty* out, PyArena* arena);
static int obj2ast_type_param(struct ast_state *state, PyObject* obj,
                              type_param_ty* out, PyArena* arena);

mod_ty
_PyAST_Module(asdl_stmt_seq * body, asdl_type_ignore_seq * type_ignores,
              PyArena *arena)
{
    mod_ty p;
    p = (mod_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Module_kind;
    p->v.Module.body = body;
    p->v.Module.type_ignores = type_ignores;
    return p;
}

mod_ty
_PyAST_Interactive(asdl_stmt_seq * body, PyArena *arena)
{
    mod_ty p;
    p = (mod_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Interactive_kind;
    p->v.Interactive.body = body;
    return p;
}

mod_ty
_PyAST_Expression(expr_ty body, PyArena *arena)
{
    mod_ty p;
    if (!body) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'body' is required for Expression");
        return NULL;
    }
    p = (mod_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Expression_kind;
    p->v.Expression.body = body;
    return p;
}

mod_ty
_PyAST_FunctionType(asdl_expr_seq * argtypes, expr_ty returns, PyArena *arena)
{
    mod_ty p;
    if (!returns) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'returns' is required for FunctionType");
        return NULL;
    }
    p = (mod_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = FunctionType_kind;
    p->v.FunctionType.argtypes = argtypes;
    p->v.FunctionType.returns = returns;
    return p;
}

stmt_ty
_PyAST_FunctionDef(identifier name, arguments_ty args, asdl_stmt_seq * body,
                   asdl_expr_seq * decorator_list, expr_ty returns, string
                   type_comment, asdl_type_param_seq * type_params, int lineno,
                   int col_offset, int end_lineno, int end_col_offset, PyArena
                   *arena)
{
    stmt_ty p;
    if (!name) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'name' is required for FunctionDef");
        return NULL;
    }
    if (!args) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'args' is required for FunctionDef");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = FunctionDef_kind;
    p->v.FunctionDef.name = name;
    p->v.FunctionDef.args = args;
    p->v.FunctionDef.body = body;
    p->v.FunctionDef.decorator_list = decorator_list;
    p->v.FunctionDef.returns = returns;
    p->v.FunctionDef.type_comment = type_comment;
    p->v.FunctionDef.type_params = type_params;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_AsyncFunctionDef(identifier name, arguments_ty args, asdl_stmt_seq *
                        body, asdl_expr_seq * decorator_list, expr_ty returns,
                        string type_comment, asdl_type_param_seq * type_params,
                        int lineno, int col_offset, int end_lineno, int
                        end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!name) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'name' is required for AsyncFunctionDef");
        return NULL;
    }
    if (!args) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'args' is required for AsyncFunctionDef");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = AsyncFunctionDef_kind;
    p->v.AsyncFunctionDef.name = name;
    p->v.AsyncFunctionDef.args = args;
    p->v.AsyncFunctionDef.body = body;
    p->v.AsyncFunctionDef.decorator_list = decorator_list;
    p->v.AsyncFunctionDef.returns = returns;
    p->v.AsyncFunctionDef.type_comment = type_comment;
    p->v.AsyncFunctionDef.type_params = type_params;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_ClassDef(identifier name, asdl_expr_seq * bases, asdl_keyword_seq *
                keywords, asdl_stmt_seq * body, asdl_expr_seq * decorator_list,
                asdl_type_param_seq * type_params, int lineno, int col_offset,
                int end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!name) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'name' is required for ClassDef");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = ClassDef_kind;
    p->v.ClassDef.name = name;
    p->v.ClassDef.bases = bases;
    p->v.ClassDef.keywords = keywords;
    p->v.ClassDef.body = body;
    p->v.ClassDef.decorator_list = decorator_list;
    p->v.ClassDef.type_params = type_params;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Return(expr_ty value, int lineno, int col_offset, int end_lineno, int
              end_col_offset, PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Return_kind;
    p->v.Return.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Delete(asdl_expr_seq * targets, int lineno, int col_offset, int
              end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Delete_kind;
    p->v.Delete.targets = targets;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Assign(asdl_expr_seq * targets, expr_ty value, string type_comment, int
              lineno, int col_offset, int end_lineno, int end_col_offset,
              PyArena *arena)
{
    stmt_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for Assign");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Assign_kind;
    p->v.Assign.targets = targets;
    p->v.Assign.value = value;
    p->v.Assign.type_comment = type_comment;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_TypeAlias(expr_ty name, asdl_type_param_seq * type_params, expr_ty
                 value, int lineno, int col_offset, int end_lineno, int
                 end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!name) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'name' is required for TypeAlias");
        return NULL;
    }
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for TypeAlias");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = TypeAlias_kind;
    p->v.TypeAlias.name = name;
    p->v.TypeAlias.type_params = type_params;
    p->v.TypeAlias.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_AugAssign(expr_ty target, operator_ty op, expr_ty value, int lineno, int
                 col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!target) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'target' is required for AugAssign");
        return NULL;
    }
    if (!op) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'op' is required for AugAssign");
        return NULL;
    }
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for AugAssign");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = AugAssign_kind;
    p->v.AugAssign.target = target;
    p->v.AugAssign.op = op;
    p->v.AugAssign.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_AnnAssign(expr_ty target, expr_ty annotation, expr_ty value, int simple,
                 int lineno, int col_offset, int end_lineno, int
                 end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!target) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'target' is required for AnnAssign");
        return NULL;
    }
    if (!annotation) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'annotation' is required for AnnAssign");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = AnnAssign_kind;
    p->v.AnnAssign.target = target;
    p->v.AnnAssign.annotation = annotation;
    p->v.AnnAssign.value = value;
    p->v.AnnAssign.simple = simple;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_For(expr_ty target, expr_ty iter, asdl_stmt_seq * body, asdl_stmt_seq *
           orelse, string type_comment, int lineno, int col_offset, int
           end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!target) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'target' is required for For");
        return NULL;
    }
    if (!iter) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'iter' is required for For");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = For_kind;
    p->v.For.target = target;
    p->v.For.iter = iter;
    p->v.For.body = body;
    p->v.For.orelse = orelse;
    p->v.For.type_comment = type_comment;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_AsyncFor(expr_ty target, expr_ty iter, asdl_stmt_seq * body,
                asdl_stmt_seq * orelse, string type_comment, int lineno, int
                col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!target) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'target' is required for AsyncFor");
        return NULL;
    }
    if (!iter) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'iter' is required for AsyncFor");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = AsyncFor_kind;
    p->v.AsyncFor.target = target;
    p->v.AsyncFor.iter = iter;
    p->v.AsyncFor.body = body;
    p->v.AsyncFor.orelse = orelse;
    p->v.AsyncFor.type_comment = type_comment;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_While(expr_ty test, asdl_stmt_seq * body, asdl_stmt_seq * orelse, int
             lineno, int col_offset, int end_lineno, int end_col_offset,
             PyArena *arena)
{
    stmt_ty p;
    if (!test) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'test' is required for While");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = While_kind;
    p->v.While.test = test;
    p->v.While.body = body;
    p->v.While.orelse = orelse;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_If(expr_ty test, asdl_stmt_seq * body, asdl_stmt_seq * orelse, int
          lineno, int col_offset, int end_lineno, int end_col_offset, PyArena
          *arena)
{
    stmt_ty p;
    if (!test) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'test' is required for If");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = If_kind;
    p->v.If.test = test;
    p->v.If.body = body;
    p->v.If.orelse = orelse;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_With(asdl_withitem_seq * items, asdl_stmt_seq * body, string
            type_comment, int lineno, int col_offset, int end_lineno, int
            end_col_offset, PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = With_kind;
    p->v.With.items = items;
    p->v.With.body = body;
    p->v.With.type_comment = type_comment;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_AsyncWith(asdl_withitem_seq * items, asdl_stmt_seq * body, string
                 type_comment, int lineno, int col_offset, int end_lineno, int
                 end_col_offset, PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = AsyncWith_kind;
    p->v.AsyncWith.items = items;
    p->v.AsyncWith.body = body;
    p->v.AsyncWith.type_comment = type_comment;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Match(expr_ty subject, asdl_match_case_seq * cases, int lineno, int
             col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!subject) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'subject' is required for Match");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Match_kind;
    p->v.Match.subject = subject;
    p->v.Match.cases = cases;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Raise(expr_ty exc, expr_ty cause, int lineno, int col_offset, int
             end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Raise_kind;
    p->v.Raise.exc = exc;
    p->v.Raise.cause = cause;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Try(asdl_stmt_seq * body, asdl_excepthandler_seq * handlers,
           asdl_stmt_seq * orelse, asdl_stmt_seq * finalbody, int lineno, int
           col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Try_kind;
    p->v.Try.body = body;
    p->v.Try.handlers = handlers;
    p->v.Try.orelse = orelse;
    p->v.Try.finalbody = finalbody;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_TryStar(asdl_stmt_seq * body, asdl_excepthandler_seq * handlers,
               asdl_stmt_seq * orelse, asdl_stmt_seq * finalbody, int lineno,
               int col_offset, int end_lineno, int end_col_offset, PyArena
               *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = TryStar_kind;
    p->v.TryStar.body = body;
    p->v.TryStar.handlers = handlers;
    p->v.TryStar.orelse = orelse;
    p->v.TryStar.finalbody = finalbody;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Assert(expr_ty test, expr_ty msg, int lineno, int col_offset, int
              end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!test) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'test' is required for Assert");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Assert_kind;
    p->v.Assert.test = test;
    p->v.Assert.msg = msg;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Import(asdl_alias_seq * names, int lineno, int col_offset, int
              end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Import_kind;
    p->v.Import.names = names;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_ImportFrom(identifier module, asdl_alias_seq * names, int level, int
                  lineno, int col_offset, int end_lineno, int end_col_offset,
                  PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = ImportFrom_kind;
    p->v.ImportFrom.module = module;
    p->v.ImportFrom.names = names;
    p->v.ImportFrom.level = level;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Global(asdl_identifier_seq * names, int lineno, int col_offset, int
              end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Global_kind;
    p->v.Global.names = names;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Nonlocal(asdl_identifier_seq * names, int lineno, int col_offset, int
                end_lineno, int end_col_offset, PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Nonlocal_kind;
    p->v.Nonlocal.names = names;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Expr(expr_ty value, int lineno, int col_offset, int end_lineno, int
            end_col_offset, PyArena *arena)
{
    stmt_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for Expr");
        return NULL;
    }
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Expr_kind;
    p->v.Expr.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Pass(int lineno, int col_offset, int end_lineno, int end_col_offset,
            PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Pass_kind;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Break(int lineno, int col_offset, int end_lineno, int end_col_offset,
             PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Break_kind;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

stmt_ty
_PyAST_Continue(int lineno, int col_offset, int end_lineno, int end_col_offset,
                PyArena *arena)
{
    stmt_ty p;
    p = (stmt_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Continue_kind;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_BoolOp(boolop_ty op, asdl_expr_seq * values, int lineno, int col_offset,
              int end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!op) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'op' is required for BoolOp");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = BoolOp_kind;
    p->v.BoolOp.op = op;
    p->v.BoolOp.values = values;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_NamedExpr(expr_ty target, expr_ty value, int lineno, int col_offset, int
                 end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!target) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'target' is required for NamedExpr");
        return NULL;
    }
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for NamedExpr");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = NamedExpr_kind;
    p->v.NamedExpr.target = target;
    p->v.NamedExpr.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_BinOp(expr_ty left, operator_ty op, expr_ty right, int lineno, int
             col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!left) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'left' is required for BinOp");
        return NULL;
    }
    if (!op) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'op' is required for BinOp");
        return NULL;
    }
    if (!right) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'right' is required for BinOp");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = BinOp_kind;
    p->v.BinOp.left = left;
    p->v.BinOp.op = op;
    p->v.BinOp.right = right;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_UnaryOp(unaryop_ty op, expr_ty operand, int lineno, int col_offset, int
               end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!op) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'op' is required for UnaryOp");
        return NULL;
    }
    if (!operand) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'operand' is required for UnaryOp");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = UnaryOp_kind;
    p->v.UnaryOp.op = op;
    p->v.UnaryOp.operand = operand;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Lambda(arguments_ty args, expr_ty body, int lineno, int col_offset, int
              end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!args) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'args' is required for Lambda");
        return NULL;
    }
    if (!body) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'body' is required for Lambda");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Lambda_kind;
    p->v.Lambda.args = args;
    p->v.Lambda.body = body;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_IfExp(expr_ty test, expr_ty body, expr_ty orelse, int lineno, int
             col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!test) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'test' is required for IfExp");
        return NULL;
    }
    if (!body) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'body' is required for IfExp");
        return NULL;
    }
    if (!orelse) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'orelse' is required for IfExp");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = IfExp_kind;
    p->v.IfExp.test = test;
    p->v.IfExp.body = body;
    p->v.IfExp.orelse = orelse;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Dict(asdl_expr_seq * keys, asdl_expr_seq * values, int lineno, int
            col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Dict_kind;
    p->v.Dict.keys = keys;
    p->v.Dict.values = values;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Set(asdl_expr_seq * elts, int lineno, int col_offset, int end_lineno,
           int end_col_offset, PyArena *arena)
{
    expr_ty p;
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Set_kind;
    p->v.Set.elts = elts;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_ListComp(expr_ty elt, asdl_comprehension_seq * generators, int lineno,
                int col_offset, int end_lineno, int end_col_offset, PyArena
                *arena)
{
    expr_ty p;
    if (!elt) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'elt' is required for ListComp");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = ListComp_kind;
    p->v.ListComp.elt = elt;
    p->v.ListComp.generators = generators;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_SetComp(expr_ty elt, asdl_comprehension_seq * generators, int lineno,
               int col_offset, int end_lineno, int end_col_offset, PyArena
               *arena)
{
    expr_ty p;
    if (!elt) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'elt' is required for SetComp");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = SetComp_kind;
    p->v.SetComp.elt = elt;
    p->v.SetComp.generators = generators;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_DictComp(expr_ty key, expr_ty value, asdl_comprehension_seq *
                generators, int lineno, int col_offset, int end_lineno, int
                end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!key) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'key' is required for DictComp");
        return NULL;
    }
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for DictComp");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = DictComp_kind;
    p->v.DictComp.key = key;
    p->v.DictComp.value = value;
    p->v.DictComp.generators = generators;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_GeneratorExp(expr_ty elt, asdl_comprehension_seq * generators, int
                    lineno, int col_offset, int end_lineno, int end_col_offset,
                    PyArena *arena)
{
    expr_ty p;
    if (!elt) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'elt' is required for GeneratorExp");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = GeneratorExp_kind;
    p->v.GeneratorExp.elt = elt;
    p->v.GeneratorExp.generators = generators;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Await(expr_ty value, int lineno, int col_offset, int end_lineno, int
             end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for Await");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Await_kind;
    p->v.Await.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Yield(expr_ty value, int lineno, int col_offset, int end_lineno, int
             end_col_offset, PyArena *arena)
{
    expr_ty p;
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Yield_kind;
    p->v.Yield.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_YieldFrom(expr_ty value, int lineno, int col_offset, int end_lineno, int
                 end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for YieldFrom");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = YieldFrom_kind;
    p->v.YieldFrom.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Compare(expr_ty left, asdl_int_seq * ops, asdl_expr_seq * comparators,
               int lineno, int col_offset, int end_lineno, int end_col_offset,
               PyArena *arena)
{
    expr_ty p;
    if (!left) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'left' is required for Compare");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Compare_kind;
    p->v.Compare.left = left;
    p->v.Compare.ops = ops;
    p->v.Compare.comparators = comparators;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Call(expr_ty func, asdl_expr_seq * args, asdl_keyword_seq * keywords,
            int lineno, int col_offset, int end_lineno, int end_col_offset,
            PyArena *arena)
{
    expr_ty p;
    if (!func) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'func' is required for Call");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Call_kind;
    p->v.Call.func = func;
    p->v.Call.args = args;
    p->v.Call.keywords = keywords;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_FormattedValue(expr_ty value, int conversion, expr_ty format_spec, int
                      lineno, int col_offset, int end_lineno, int
                      end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for FormattedValue");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = FormattedValue_kind;
    p->v.FormattedValue.value = value;
    p->v.FormattedValue.conversion = conversion;
    p->v.FormattedValue.format_spec = format_spec;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_JoinedStr(asdl_expr_seq * values, int lineno, int col_offset, int
                 end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = JoinedStr_kind;
    p->v.JoinedStr.values = values;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Constant(constant value, string kind, int lineno, int col_offset, int
                end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for Constant");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Constant_kind;
    p->v.Constant.value = value;
    p->v.Constant.kind = kind;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Attribute(expr_ty value, identifier attr, expr_context_ty ctx, int
                 lineno, int col_offset, int end_lineno, int end_col_offset,
                 PyArena *arena)
{
    expr_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for Attribute");
        return NULL;
    }
    if (!attr) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'attr' is required for Attribute");
        return NULL;
    }
    if (!ctx) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'ctx' is required for Attribute");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Attribute_kind;
    p->v.Attribute.value = value;
    p->v.Attribute.attr = attr;
    p->v.Attribute.ctx = ctx;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Subscript(expr_ty value, expr_ty slice, expr_context_ty ctx, int lineno,
                 int col_offset, int end_lineno, int end_col_offset, PyArena
                 *arena)
{
    expr_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for Subscript");
        return NULL;
    }
    if (!slice) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'slice' is required for Subscript");
        return NULL;
    }
    if (!ctx) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'ctx' is required for Subscript");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Subscript_kind;
    p->v.Subscript.value = value;
    p->v.Subscript.slice = slice;
    p->v.Subscript.ctx = ctx;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Starred(expr_ty value, expr_context_ty ctx, int lineno, int col_offset,
               int end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for Starred");
        return NULL;
    }
    if (!ctx) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'ctx' is required for Starred");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Starred_kind;
    p->v.Starred.value = value;
    p->v.Starred.ctx = ctx;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Name(identifier id, expr_context_ty ctx, int lineno, int col_offset, int
            end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!id) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'id' is required for Name");
        return NULL;
    }
    if (!ctx) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'ctx' is required for Name");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Name_kind;
    p->v.Name.id = id;
    p->v.Name.ctx = ctx;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_List(asdl_expr_seq * elts, expr_context_ty ctx, int lineno, int
            col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!ctx) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'ctx' is required for List");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = List_kind;
    p->v.List.elts = elts;
    p->v.List.ctx = ctx;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Tuple(asdl_expr_seq * elts, expr_context_ty ctx, int lineno, int
             col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    if (!ctx) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'ctx' is required for Tuple");
        return NULL;
    }
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Tuple_kind;
    p->v.Tuple.elts = elts;
    p->v.Tuple.ctx = ctx;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

expr_ty
_PyAST_Slice(expr_ty lower, expr_ty upper, expr_ty step, int lineno, int
             col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    expr_ty p;
    p = (expr_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = Slice_kind;
    p->v.Slice.lower = lower;
    p->v.Slice.upper = upper;
    p->v.Slice.step = step;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

comprehension_ty
_PyAST_comprehension(expr_ty target, expr_ty iter, asdl_expr_seq * ifs, int
                     is_async, PyArena *arena)
{
    comprehension_ty p;
    if (!target) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'target' is required for comprehension");
        return NULL;
    }
    if (!iter) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'iter' is required for comprehension");
        return NULL;
    }
    p = (comprehension_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->target = target;
    p->iter = iter;
    p->ifs = ifs;
    p->is_async = is_async;
    return p;
}

excepthandler_ty
_PyAST_ExceptHandler(expr_ty type, identifier name, asdl_stmt_seq * body, int
                     lineno, int col_offset, int end_lineno, int
                     end_col_offset, PyArena *arena)
{
    excepthandler_ty p;
    p = (excepthandler_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = ExceptHandler_kind;
    p->v.ExceptHandler.type = type;
    p->v.ExceptHandler.name = name;
    p->v.ExceptHandler.body = body;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

arguments_ty
_PyAST_arguments(asdl_arg_seq * posonlyargs, asdl_arg_seq * args, arg_ty
                 vararg, asdl_arg_seq * kwonlyargs, asdl_expr_seq *
                 kw_defaults, arg_ty kwarg, asdl_expr_seq * defaults, PyArena
                 *arena)
{
    arguments_ty p;
    p = (arguments_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->posonlyargs = posonlyargs;
    p->args = args;
    p->vararg = vararg;
    p->kwonlyargs = kwonlyargs;
    p->kw_defaults = kw_defaults;
    p->kwarg = kwarg;
    p->defaults = defaults;
    return p;
}

arg_ty
_PyAST_arg(identifier arg, expr_ty annotation, string type_comment, int lineno,
           int col_offset, int end_lineno, int end_col_offset, PyArena *arena)
{
    arg_ty p;
    if (!arg) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'arg' is required for arg");
        return NULL;
    }
    p = (arg_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->arg = arg;
    p->annotation = annotation;
    p->type_comment = type_comment;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

keyword_ty
_PyAST_keyword(identifier arg, expr_ty value, int lineno, int col_offset, int
               end_lineno, int end_col_offset, PyArena *arena)
{
    keyword_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for keyword");
        return NULL;
    }
    p = (keyword_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->arg = arg;
    p->value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

alias_ty
_PyAST_alias(identifier name, identifier asname, int lineno, int col_offset,
             int end_lineno, int end_col_offset, PyArena *arena)
{
    alias_ty p;
    if (!name) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'name' is required for alias");
        return NULL;
    }
    p = (alias_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->name = name;
    p->asname = asname;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

withitem_ty
_PyAST_withitem(expr_ty context_expr, expr_ty optional_vars, PyArena *arena)
{
    withitem_ty p;
    if (!context_expr) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'context_expr' is required for withitem");
        return NULL;
    }
    p = (withitem_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->context_expr = context_expr;
    p->optional_vars = optional_vars;
    return p;
}

match_case_ty
_PyAST_match_case(pattern_ty pattern, expr_ty guard, asdl_stmt_seq * body,
                  PyArena *arena)
{
    match_case_ty p;
    if (!pattern) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'pattern' is required for match_case");
        return NULL;
    }
    p = (match_case_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->pattern = pattern;
    p->guard = guard;
    p->body = body;
    return p;
}

pattern_ty
_PyAST_MatchValue(expr_ty value, int lineno, int col_offset, int end_lineno,
                  int end_col_offset, PyArena *arena)
{
    pattern_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for MatchValue");
        return NULL;
    }
    p = (pattern_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = MatchValue_kind;
    p->v.MatchValue.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

pattern_ty
_PyAST_MatchSingleton(constant value, int lineno, int col_offset, int
                      end_lineno, int end_col_offset, PyArena *arena)
{
    pattern_ty p;
    if (!value) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'value' is required for MatchSingleton");
        return NULL;
    }
    p = (pattern_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = MatchSingleton_kind;
    p->v.MatchSingleton.value = value;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

pattern_ty
_PyAST_MatchSequence(asdl_pattern_seq * patterns, int lineno, int col_offset,
                     int end_lineno, int end_col_offset, PyArena *arena)
{
    pattern_ty p;
    p = (pattern_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = MatchSequence_kind;
    p->v.MatchSequence.patterns = patterns;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

pattern_ty
_PyAST_MatchMapping(asdl_expr_seq * keys, asdl_pattern_seq * patterns,
                    identifier rest, int lineno, int col_offset, int
                    end_lineno, int end_col_offset, PyArena *arena)
{
    pattern_ty p;
    p = (pattern_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = MatchMapping_kind;
    p->v.MatchMapping.keys = keys;
    p->v.MatchMapping.patterns = patterns;
    p->v.MatchMapping.rest = rest;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

pattern_ty
_PyAST_MatchClass(expr_ty cls, asdl_pattern_seq * patterns, asdl_identifier_seq
                  * kwd_attrs, asdl_pattern_seq * kwd_patterns, int lineno, int
                  col_offset, int end_lineno, int end_col_offset, PyArena
                  *arena)
{
    pattern_ty p;
    if (!cls) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'cls' is required for MatchClass");
        return NULL;
    }
    p = (pattern_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = MatchClass_kind;
    p->v.MatchClass.cls = cls;
    p->v.MatchClass.patterns = patterns;
    p->v.MatchClass.kwd_attrs = kwd_attrs;
    p->v.MatchClass.kwd_patterns = kwd_patterns;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

pattern_ty
_PyAST_MatchStar(identifier name, int lineno, int col_offset, int end_lineno,
                 int end_col_offset, PyArena *arena)
{
    pattern_ty p;
    p = (pattern_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = MatchStar_kind;
    p->v.MatchStar.name = name;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

pattern_ty
_PyAST_MatchAs(pattern_ty pattern, identifier name, int lineno, int col_offset,
               int end_lineno, int end_col_offset, PyArena *arena)
{
    pattern_ty p;
    p = (pattern_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = MatchAs_kind;
    p->v.MatchAs.pattern = pattern;
    p->v.MatchAs.name = name;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

pattern_ty
_PyAST_MatchOr(asdl_pattern_seq * patterns, int lineno, int col_offset, int
               end_lineno, int end_col_offset, PyArena *arena)
{
    pattern_ty p;
    p = (pattern_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = MatchOr_kind;
    p->v.MatchOr.patterns = patterns;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

type_ignore_ty
_PyAST_TypeIgnore(int lineno, string tag, PyArena *arena)
{
    type_ignore_ty p;
    if (!tag) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'tag' is required for TypeIgnore");
        return NULL;
    }
    p = (type_ignore_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = TypeIgnore_kind;
    p->v.TypeIgnore.lineno = lineno;
    p->v.TypeIgnore.tag = tag;
    return p;
}

type_param_ty
_PyAST_TypeVar(identifier name, expr_ty bound, int lineno, int col_offset, int
               end_lineno, int end_col_offset, PyArena *arena)
{
    type_param_ty p;
    if (!name) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'name' is required for TypeVar");
        return NULL;
    }
    p = (type_param_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = TypeVar_kind;
    p->v.TypeVar.name = name;
    p->v.TypeVar.bound = bound;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

type_param_ty
_PyAST_ParamSpec(identifier name, int lineno, int col_offset, int end_lineno,
                 int end_col_offset, PyArena *arena)
{
    type_param_ty p;
    if (!name) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'name' is required for ParamSpec");
        return NULL;
    }
    p = (type_param_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = ParamSpec_kind;
    p->v.ParamSpec.name = name;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}

type_param_ty
_PyAST_TypeVarTuple(identifier name, int lineno, int col_offset, int
                    end_lineno, int end_col_offset, PyArena *arena)
{
    type_param_ty p;
    if (!name) {
        PyErr_SetString(PyExc_ValueError,
                        "field 'name' is required for TypeVarTuple");
        return NULL;
    }
    p = (type_param_ty)_PyArena_Malloc(arena, sizeof(*p));
    if (!p)
        return NULL;
    p->kind = TypeVarTuple_kind;
    p->v.TypeVarTuple.name = name;
    p->lineno = lineno;
    p->col_offset = col_offset;
    p->end_lineno = end_lineno;
    p->end_col_offset = end_col_offset;
    return p;
}


PyObject*
ast2obj_mod(struct ast_state *state, struct validator *vstate, void* _o)
{
    mod_ty o = (mod_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    switch (o->kind) {
    case Module_kind:
        tp = (PyTypeObject *)state->Module_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Module.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.Module.type_ignores,
                             ast2obj_type_ignore);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_ignores, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Interactive_kind:
        tp = (PyTypeObject *)state->Interactive_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Interactive.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Expression_kind:
        tp = (PyTypeObject *)state->Expression_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Expression.body);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case FunctionType_kind:
        tp = (PyTypeObject *)state->FunctionType_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.FunctionType.argtypes,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->argtypes, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.FunctionType.returns);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->returns, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    }
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_stmt(struct ast_state *state, struct validator *vstate, void* _o)
{
    stmt_ty o = (stmt_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    switch (o->kind) {
    case FunctionDef_kind:
        tp = (PyTypeObject *)state->FunctionDef_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_identifier(state, vstate, o->v.FunctionDef.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_arguments(state, vstate, o->v.FunctionDef.args);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->args, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.FunctionDef.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.FunctionDef.decorator_list,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->decorator_list, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.FunctionDef.returns);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->returns, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_string(state, vstate, o->v.FunctionDef.type_comment);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_comment, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.FunctionDef.type_params,
                             ast2obj_type_param);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_params, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case AsyncFunctionDef_kind:
        tp = (PyTypeObject *)state->AsyncFunctionDef_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_identifier(state, vstate, o->v.AsyncFunctionDef.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_arguments(state, vstate, o->v.AsyncFunctionDef.args);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->args, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.AsyncFunctionDef.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.AsyncFunctionDef.decorator_list,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->decorator_list, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.AsyncFunctionDef.returns);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->returns, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_string(state, vstate, o->v.AsyncFunctionDef.type_comment);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_comment, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.AsyncFunctionDef.type_params,
                             ast2obj_type_param);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_params, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case ClassDef_kind:
        tp = (PyTypeObject *)state->ClassDef_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_identifier(state, vstate, o->v.ClassDef.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.ClassDef.bases,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->bases, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.ClassDef.keywords,
                             ast2obj_keyword);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->keywords, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.ClassDef.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.ClassDef.decorator_list,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->decorator_list, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.ClassDef.type_params,
                             ast2obj_type_param);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_params, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Return_kind:
        tp = (PyTypeObject *)state->Return_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Return.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Delete_kind:
        tp = (PyTypeObject *)state->Delete_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Delete.targets,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->targets, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Assign_kind:
        tp = (PyTypeObject *)state->Assign_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Assign.targets,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->targets, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.Assign.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_string(state, vstate, o->v.Assign.type_comment);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_comment, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case TypeAlias_kind:
        tp = (PyTypeObject *)state->TypeAlias_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.TypeAlias.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.TypeAlias.type_params,
                             ast2obj_type_param);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_params, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.TypeAlias.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case AugAssign_kind:
        tp = (PyTypeObject *)state->AugAssign_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.AugAssign.target);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->target, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_operator(state, vstate, o->v.AugAssign.op);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->op, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.AugAssign.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case AnnAssign_kind:
        tp = (PyTypeObject *)state->AnnAssign_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.AnnAssign.target);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->target, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.AnnAssign.annotation);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->annotation, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.AnnAssign.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_int(state, vstate, o->v.AnnAssign.simple);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->simple, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case For_kind:
        tp = (PyTypeObject *)state->For_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.For.target);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->target, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.For.iter);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->iter, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.For.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.For.orelse,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->orelse, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_string(state, vstate, o->v.For.type_comment);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_comment, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case AsyncFor_kind:
        tp = (PyTypeObject *)state->AsyncFor_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.AsyncFor.target);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->target, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.AsyncFor.iter);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->iter, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.AsyncFor.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.AsyncFor.orelse,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->orelse, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_string(state, vstate, o->v.AsyncFor.type_comment);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_comment, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case While_kind:
        tp = (PyTypeObject *)state->While_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.While.test);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->test, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.While.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.While.orelse,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->orelse, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case If_kind:
        tp = (PyTypeObject *)state->If_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.If.test);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->test, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.If.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.If.orelse,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->orelse, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case With_kind:
        tp = (PyTypeObject *)state->With_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.With.items,
                             ast2obj_withitem);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->items, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.With.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_string(state, vstate, o->v.With.type_comment);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_comment, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case AsyncWith_kind:
        tp = (PyTypeObject *)state->AsyncWith_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.AsyncWith.items,
                             ast2obj_withitem);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->items, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.AsyncWith.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_string(state, vstate, o->v.AsyncWith.type_comment);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type_comment, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Match_kind:
        tp = (PyTypeObject *)state->Match_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Match.subject);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->subject, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Match.cases,
                             ast2obj_match_case);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->cases, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Raise_kind:
        tp = (PyTypeObject *)state->Raise_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Raise.exc);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->exc, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.Raise.cause);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->cause, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Try_kind:
        tp = (PyTypeObject *)state->Try_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Try.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Try.handlers,
                             ast2obj_excepthandler);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->handlers, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Try.orelse,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->orelse, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Try.finalbody,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->finalbody, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case TryStar_kind:
        tp = (PyTypeObject *)state->TryStar_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.TryStar.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.TryStar.handlers,
                             ast2obj_excepthandler);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->handlers, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.TryStar.orelse,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->orelse, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.TryStar.finalbody,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->finalbody, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Assert_kind:
        tp = (PyTypeObject *)state->Assert_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Assert.test);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->test, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.Assert.msg);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->msg, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Import_kind:
        tp = (PyTypeObject *)state->Import_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Import.names,
                             ast2obj_alias);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->names, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case ImportFrom_kind:
        tp = (PyTypeObject *)state->ImportFrom_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_identifier(state, vstate, o->v.ImportFrom.module);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->module, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.ImportFrom.names,
                             ast2obj_alias);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->names, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_int(state, vstate, o->v.ImportFrom.level);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->level, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Global_kind:
        tp = (PyTypeObject *)state->Global_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Global.names,
                             ast2obj_identifier);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->names, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Nonlocal_kind:
        tp = (PyTypeObject *)state->Nonlocal_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Nonlocal.names,
                             ast2obj_identifier);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->names, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Expr_kind:
        tp = (PyTypeObject *)state->Expr_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Expr.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Pass_kind:
        tp = (PyTypeObject *)state->Pass_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        break;
    case Break_kind:
        tp = (PyTypeObject *)state->Break_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        break;
    case Continue_kind:
        tp = (PyTypeObject *)state->Continue_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        break;
    }
    value = ast2obj_int(state, vstate, o->lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_expr(struct ast_state *state, struct validator *vstate, void* _o)
{
    expr_ty o = (expr_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    switch (o->kind) {
    case BoolOp_kind:
        tp = (PyTypeObject *)state->BoolOp_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_boolop(state, vstate, o->v.BoolOp.op);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->op, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.BoolOp.values,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->values, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case NamedExpr_kind:
        tp = (PyTypeObject *)state->NamedExpr_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.NamedExpr.target);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->target, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.NamedExpr.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case BinOp_kind:
        tp = (PyTypeObject *)state->BinOp_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.BinOp.left);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->left, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_operator(state, vstate, o->v.BinOp.op);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->op, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.BinOp.right);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->right, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case UnaryOp_kind:
        tp = (PyTypeObject *)state->UnaryOp_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_unaryop(state, vstate, o->v.UnaryOp.op);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->op, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.UnaryOp.operand);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->operand, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Lambda_kind:
        tp = (PyTypeObject *)state->Lambda_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_arguments(state, vstate, o->v.Lambda.args);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->args, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.Lambda.body);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case IfExp_kind:
        tp = (PyTypeObject *)state->IfExp_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.IfExp.test);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->test, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.IfExp.body);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.IfExp.orelse);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->orelse, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Dict_kind:
        tp = (PyTypeObject *)state->Dict_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Dict.keys,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->keys, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Dict.values,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->values, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Set_kind:
        tp = (PyTypeObject *)state->Set_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Set.elts,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->elts, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case ListComp_kind:
        tp = (PyTypeObject *)state->ListComp_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.ListComp.elt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->elt, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.ListComp.generators,
                             ast2obj_comprehension);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->generators, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case SetComp_kind:
        tp = (PyTypeObject *)state->SetComp_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.SetComp.elt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->elt, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.SetComp.generators,
                             ast2obj_comprehension);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->generators, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case DictComp_kind:
        tp = (PyTypeObject *)state->DictComp_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.DictComp.key);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->key, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.DictComp.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.DictComp.generators,
                             ast2obj_comprehension);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->generators, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case GeneratorExp_kind:
        tp = (PyTypeObject *)state->GeneratorExp_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.GeneratorExp.elt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->elt, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.GeneratorExp.generators,
                             ast2obj_comprehension);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->generators, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Await_kind:
        tp = (PyTypeObject *)state->Await_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Await.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Yield_kind:
        tp = (PyTypeObject *)state->Yield_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Yield.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case YieldFrom_kind:
        tp = (PyTypeObject *)state->YieldFrom_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.YieldFrom.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Compare_kind:
        tp = (PyTypeObject *)state->Compare_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Compare.left);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->left, value) == -1)
            goto failed;
        Py_DECREF(value);
        {
            Py_ssize_t i, n = asdl_seq_LEN(o->v.Compare.ops);
            value = PyList_New(n);
            if (!value) goto failed;
            for(i = 0; i < n; i++)
                PyList_SET_ITEM(value, i, ast2obj_cmpop(state, vstate, (cmpop_ty)asdl_seq_GET(o->v.Compare.ops, i)));
        }
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->ops, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.Compare.comparators, ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->comparators, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Call_kind:
        tp = (PyTypeObject *)state->Call_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Call.func);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->func, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Call.args,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->args, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Call.keywords,
                             ast2obj_keyword);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->keywords, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case FormattedValue_kind:
        tp = (PyTypeObject *)state->FormattedValue_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.FormattedValue.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_int(state, vstate, o->v.FormattedValue.conversion);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->conversion, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.FormattedValue.format_spec);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->format_spec, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case JoinedStr_kind:
        tp = (PyTypeObject *)state->JoinedStr_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.JoinedStr.values,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->values, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Constant_kind:
        tp = (PyTypeObject *)state->Constant_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_constant(state, vstate, o->v.Constant.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_string(state, vstate, o->v.Constant.kind);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->kind, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Attribute_kind:
        tp = (PyTypeObject *)state->Attribute_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Attribute.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_identifier(state, vstate, o->v.Attribute.attr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->attr, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr_context(state, vstate, o->v.Attribute.ctx);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->ctx, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Subscript_kind:
        tp = (PyTypeObject *)state->Subscript_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Subscript.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.Subscript.slice);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->slice, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr_context(state, vstate, o->v.Subscript.ctx);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->ctx, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Starred_kind:
        tp = (PyTypeObject *)state->Starred_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Starred.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr_context(state, vstate, o->v.Starred.ctx);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->ctx, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Name_kind:
        tp = (PyTypeObject *)state->Name_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_identifier(state, vstate, o->v.Name.id);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->id, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr_context(state, vstate, o->v.Name.ctx);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->ctx, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case List_kind:
        tp = (PyTypeObject *)state->List_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.List.elts,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->elts, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr_context(state, vstate, o->v.List.ctx);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->ctx, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Tuple_kind:
        tp = (PyTypeObject *)state->Tuple_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.Tuple.elts,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->elts, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr_context(state, vstate, o->v.Tuple.ctx);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->ctx, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case Slice_kind:
        tp = (PyTypeObject *)state->Slice_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.Slice.lower);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->lower, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.Slice.upper);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->upper, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.Slice.step);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->step, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    }
    value = ast2obj_int(state, vstate, o->lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject* ast2obj_expr_context(struct ast_state *state, struct validator
                               *vstate, expr_context_ty o)
{
    switch(o) {
        case Load:
            return Py_NewRef(state->Load_singleton);
        case Store:
            return Py_NewRef(state->Store_singleton);
        case Del:
            return Py_NewRef(state->Del_singleton);
    }
    Py_UNREACHABLE();
}
PyObject* ast2obj_boolop(struct ast_state *state, struct validator *vstate,
                         boolop_ty o)
{
    switch(o) {
        case And:
            return Py_NewRef(state->And_singleton);
        case Or:
            return Py_NewRef(state->Or_singleton);
    }
    Py_UNREACHABLE();
}
PyObject* ast2obj_operator(struct ast_state *state, struct validator *vstate,
                           operator_ty o)
{
    switch(o) {
        case Add:
            return Py_NewRef(state->Add_singleton);
        case Sub:
            return Py_NewRef(state->Sub_singleton);
        case Mult:
            return Py_NewRef(state->Mult_singleton);
        case MatMult:
            return Py_NewRef(state->MatMult_singleton);
        case Div:
            return Py_NewRef(state->Div_singleton);
        case Mod:
            return Py_NewRef(state->Mod_singleton);
        case Pow:
            return Py_NewRef(state->Pow_singleton);
        case LShift:
            return Py_NewRef(state->LShift_singleton);
        case RShift:
            return Py_NewRef(state->RShift_singleton);
        case BitOr:
            return Py_NewRef(state->BitOr_singleton);
        case BitXor:
            return Py_NewRef(state->BitXor_singleton);
        case BitAnd:
            return Py_NewRef(state->BitAnd_singleton);
        case FloorDiv:
            return Py_NewRef(state->FloorDiv_singleton);
    }
    Py_UNREACHABLE();
}
PyObject* ast2obj_unaryop(struct ast_state *state, struct validator *vstate,
                          unaryop_ty o)
{
    switch(o) {
        case Invert:
            return Py_NewRef(state->Invert_singleton);
        case Not:
            return Py_NewRef(state->Not_singleton);
        case UAdd:
            return Py_NewRef(state->UAdd_singleton);
        case USub:
            return Py_NewRef(state->USub_singleton);
    }
    Py_UNREACHABLE();
}
PyObject* ast2obj_cmpop(struct ast_state *state, struct validator *vstate,
                        cmpop_ty o)
{
    switch(o) {
        case Eq:
            return Py_NewRef(state->Eq_singleton);
        case NotEq:
            return Py_NewRef(state->NotEq_singleton);
        case Lt:
            return Py_NewRef(state->Lt_singleton);
        case LtE:
            return Py_NewRef(state->LtE_singleton);
        case Gt:
            return Py_NewRef(state->Gt_singleton);
        case GtE:
            return Py_NewRef(state->GtE_singleton);
        case Is:
            return Py_NewRef(state->Is_singleton);
        case IsNot:
            return Py_NewRef(state->IsNot_singleton);
        case In:
            return Py_NewRef(state->In_singleton);
        case NotIn:
            return Py_NewRef(state->NotIn_singleton);
    }
    Py_UNREACHABLE();
}
PyObject*
ast2obj_comprehension(struct ast_state *state, struct validator *vstate, void*
                      _o)
{
    comprehension_ty o = (comprehension_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    tp = (PyTypeObject *)state->comprehension_type;
    result = PyType_GenericNew(tp, NULL, NULL);
    if (!result) return NULL;
    value = ast2obj_expr(state, vstate, o->target);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->target, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_expr(state, vstate, o->iter);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->iter, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_list(state, vstate, (asdl_seq*)o->ifs, ast2obj_expr);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->ifs, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->is_async);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->is_async, value) == -1)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_excepthandler(struct ast_state *state, struct validator *vstate, void*
                      _o)
{
    excepthandler_ty o = (excepthandler_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    switch (o->kind) {
    case ExceptHandler_kind:
        tp = (PyTypeObject *)state->ExceptHandler_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.ExceptHandler.type);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->type, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_identifier(state, vstate, o->v.ExceptHandler.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.ExceptHandler.body,
                             ast2obj_stmt);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->body, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    }
    value = ast2obj_int(state, vstate, o->lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_arguments(struct ast_state *state, struct validator *vstate, void* _o)
{
    arguments_ty o = (arguments_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    tp = (PyTypeObject *)state->arguments_type;
    result = PyType_GenericNew(tp, NULL, NULL);
    if (!result) return NULL;
    value = ast2obj_list(state, vstate, (asdl_seq*)o->posonlyargs, ast2obj_arg);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->posonlyargs, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_list(state, vstate, (asdl_seq*)o->args, ast2obj_arg);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->args, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_arg(state, vstate, o->vararg);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->vararg, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_list(state, vstate, (asdl_seq*)o->kwonlyargs, ast2obj_arg);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->kwonlyargs, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_list(state, vstate, (asdl_seq*)o->kw_defaults,
                         ast2obj_expr);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->kw_defaults, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_arg(state, vstate, o->kwarg);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->kwarg, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_list(state, vstate, (asdl_seq*)o->defaults, ast2obj_expr);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->defaults, value) == -1)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_arg(struct ast_state *state, struct validator *vstate, void* _o)
{
    arg_ty o = (arg_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    tp = (PyTypeObject *)state->arg_type;
    result = PyType_GenericNew(tp, NULL, NULL);
    if (!result) return NULL;
    value = ast2obj_identifier(state, vstate, o->arg);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->arg, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_expr(state, vstate, o->annotation);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->annotation, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_string(state, vstate, o->type_comment);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->type_comment, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_keyword(struct ast_state *state, struct validator *vstate, void* _o)
{
    keyword_ty o = (keyword_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    tp = (PyTypeObject *)state->keyword_type;
    result = PyType_GenericNew(tp, NULL, NULL);
    if (!result) return NULL;
    value = ast2obj_identifier(state, vstate, o->arg);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->arg, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_expr(state, vstate, o->value);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->value, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_alias(struct ast_state *state, struct validator *vstate, void* _o)
{
    alias_ty o = (alias_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    tp = (PyTypeObject *)state->alias_type;
    result = PyType_GenericNew(tp, NULL, NULL);
    if (!result) return NULL;
    value = ast2obj_identifier(state, vstate, o->name);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->name, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_identifier(state, vstate, o->asname);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->asname, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_withitem(struct ast_state *state, struct validator *vstate, void* _o)
{
    withitem_ty o = (withitem_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    tp = (PyTypeObject *)state->withitem_type;
    result = PyType_GenericNew(tp, NULL, NULL);
    if (!result) return NULL;
    value = ast2obj_expr(state, vstate, o->context_expr);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->context_expr, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_expr(state, vstate, o->optional_vars);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->optional_vars, value) == -1)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_match_case(struct ast_state *state, struct validator *vstate, void* _o)
{
    match_case_ty o = (match_case_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    tp = (PyTypeObject *)state->match_case_type;
    result = PyType_GenericNew(tp, NULL, NULL);
    if (!result) return NULL;
    value = ast2obj_pattern(state, vstate, o->pattern);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->pattern, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_expr(state, vstate, o->guard);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->guard, value) == -1)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_list(state, vstate, (asdl_seq*)o->body, ast2obj_stmt);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->body, value) == -1)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_pattern(struct ast_state *state, struct validator *vstate, void* _o)
{
    pattern_ty o = (pattern_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    switch (o->kind) {
    case MatchValue_kind:
        tp = (PyTypeObject *)state->MatchValue_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.MatchValue.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case MatchSingleton_kind:
        tp = (PyTypeObject *)state->MatchSingleton_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_constant(state, vstate, o->v.MatchSingleton.value);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->value, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case MatchSequence_kind:
        tp = (PyTypeObject *)state->MatchSequence_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.MatchSequence.patterns,
                             ast2obj_pattern);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->patterns, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case MatchMapping_kind:
        tp = (PyTypeObject *)state->MatchMapping_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.MatchMapping.keys,
                             ast2obj_expr);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->keys, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.MatchMapping.patterns,
                             ast2obj_pattern);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->patterns, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_identifier(state, vstate, o->v.MatchMapping.rest);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->rest, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case MatchClass_kind:
        tp = (PyTypeObject *)state->MatchClass_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_expr(state, vstate, o->v.MatchClass.cls);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->cls, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.MatchClass.patterns,
                             ast2obj_pattern);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->patterns, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.MatchClass.kwd_attrs,
                             ast2obj_identifier);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->kwd_attrs, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_list(state, vstate,
                             (asdl_seq*)o->v.MatchClass.kwd_patterns,
                             ast2obj_pattern);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->kwd_patterns, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case MatchStar_kind:
        tp = (PyTypeObject *)state->MatchStar_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_identifier(state, vstate, o->v.MatchStar.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case MatchAs_kind:
        tp = (PyTypeObject *)state->MatchAs_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_pattern(state, vstate, o->v.MatchAs.pattern);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->pattern, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_identifier(state, vstate, o->v.MatchAs.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case MatchOr_kind:
        tp = (PyTypeObject *)state->MatchOr_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_list(state, vstate, (asdl_seq*)o->v.MatchOr.patterns,
                             ast2obj_pattern);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->patterns, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    }
    value = ast2obj_int(state, vstate, o->lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_type_ignore(struct ast_state *state, struct validator *vstate, void* _o)
{
    type_ignore_ty o = (type_ignore_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    switch (o->kind) {
    case TypeIgnore_kind:
        tp = (PyTypeObject *)state->TypeIgnore_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_int(state, vstate, o->v.TypeIgnore.lineno);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->lineno, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_string(state, vstate, o->v.TypeIgnore.tag);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->tag, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    }
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}

PyObject*
ast2obj_type_param(struct ast_state *state, struct validator *vstate, void* _o)
{
    type_param_ty o = (type_param_ty)_o;
    PyObject *result = NULL, *value = NULL;
    PyTypeObject *tp;
    if (!o) {
        Py_RETURN_NONE;
    }
    if (++vstate->recursion_depth > vstate->recursion_limit) {
        PyErr_SetString(PyExc_RecursionError,
            "maximum recursion depth exceeded during ast construction");
        return NULL;
    }
    switch (o->kind) {
    case TypeVar_kind:
        tp = (PyTypeObject *)state->TypeVar_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_identifier(state, vstate, o->v.TypeVar.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        value = ast2obj_expr(state, vstate, o->v.TypeVar.bound);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->bound, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case ParamSpec_kind:
        tp = (PyTypeObject *)state->ParamSpec_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_identifier(state, vstate, o->v.ParamSpec.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    case TypeVarTuple_kind:
        tp = (PyTypeObject *)state->TypeVarTuple_type;
        result = PyType_GenericNew(tp, NULL, NULL);
        if (!result) goto failed;
        value = ast2obj_identifier(state, vstate, o->v.TypeVarTuple.name);
        if (!value) goto failed;
        if (PyObject_SetAttr(result, state->name, value) == -1)
            goto failed;
        Py_DECREF(value);
        break;
    }
    value = ast2obj_int(state, vstate, o->lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_lineno);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_lineno, value) < 0)
        goto failed;
    Py_DECREF(value);
    value = ast2obj_int(state, vstate, o->end_col_offset);
    if (!value) goto failed;
    if (PyObject_SetAttr(result, state->end_col_offset, value) < 0)
        goto failed;
    Py_DECREF(value);
    vstate->recursion_depth--;
    return result;
failed:
    vstate->recursion_depth--;
    Py_XDECREF(value);
    Py_XDECREF(result);
    return NULL;
}


int
obj2ast_mod(struct ast_state *state, PyObject* obj, mod_ty* out, PyArena* arena)
{
    int isinstance;

    PyObject *tmp = NULL;
    PyObject *tp;

    if (obj == Py_None) {
        *out = NULL;
        return 0;
    }
    tp = state->Module_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_stmt_seq* body;
        asdl_type_ignore_seq* type_ignores;

        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Module field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Module' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Module field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_ignores, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Module field \"type_ignores\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            type_ignores = _Py_asdl_type_ignore_seq_new(len, arena);
            if (type_ignores == NULL) goto failed;
            for (i = 0; i < len; i++) {
                type_ignore_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Module' node")) {
                    goto failed;
                }
                res = obj2ast_type_ignore(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Module field \"type_ignores\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(type_ignores, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Module(body, type_ignores, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Interactive_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_stmt_seq* body;

        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Interactive field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Interactive' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Interactive field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Interactive(body, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Expression_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty body;

        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"body\" missing from Expression");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Expression' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &body, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Expression(body, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->FunctionType_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_expr_seq* argtypes;
        expr_ty returns;

        if (PyObject_GetOptionalAttr(obj, state->argtypes, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "FunctionType field \"argtypes\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            argtypes = _Py_asdl_expr_seq_new(len, arena);
            if (argtypes == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'FunctionType' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "FunctionType field \"argtypes\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(argtypes, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->returns, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"returns\" missing from FunctionType");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'FunctionType' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &returns, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_FunctionType(argtypes, returns, arena);
        if (*out == NULL) goto failed;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of mod, but got %R", obj);
    failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_stmt(struct ast_state *state, PyObject* obj, stmt_ty* out, PyArena*
             arena)
{
    int isinstance;

    PyObject *tmp = NULL;
    PyObject *tp;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;

    if (obj == Py_None) {
        *out = NULL;
        return 0;
    }
    if (PyObject_GetOptionalAttr(obj, state->lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"lineno\" missing from stmt");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'stmt' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"col_offset\" missing from stmt");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'stmt' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_lineno = lineno;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'stmt' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_col_offset = col_offset;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'stmt' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    tp = state->FunctionDef_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        identifier name;
        arguments_ty args;
        asdl_stmt_seq* body;
        asdl_expr_seq* decorator_list;
        expr_ty returns;
        string type_comment;
        asdl_type_param_seq* type_params;

        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"name\" missing from FunctionDef");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'FunctionDef' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->args, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"args\" missing from FunctionDef");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'FunctionDef' node")) {
                goto failed;
            }
            res = obj2ast_arguments(state, tmp, &args, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "FunctionDef field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'FunctionDef' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "FunctionDef field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->decorator_list, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "FunctionDef field \"decorator_list\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            decorator_list = _Py_asdl_expr_seq_new(len, arena);
            if (decorator_list == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'FunctionDef' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "FunctionDef field \"decorator_list\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(decorator_list, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->returns, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            returns = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'FunctionDef' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &returns, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_comment, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            type_comment = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'FunctionDef' node")) {
                goto failed;
            }
            res = obj2ast_string(state, tmp, &type_comment, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_params, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "FunctionDef field \"type_params\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            type_params = _Py_asdl_type_param_seq_new(len, arena);
            if (type_params == NULL) goto failed;
            for (i = 0; i < len; i++) {
                type_param_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'FunctionDef' node")) {
                    goto failed;
                }
                res = obj2ast_type_param(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "FunctionDef field \"type_params\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(type_params, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_FunctionDef(name, args, body, decorator_list, returns,
                                  type_comment, type_params, lineno,
                                  col_offset, end_lineno, end_col_offset,
                                  arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->AsyncFunctionDef_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        identifier name;
        arguments_ty args;
        asdl_stmt_seq* body;
        asdl_expr_seq* decorator_list;
        expr_ty returns;
        string type_comment;
        asdl_type_param_seq* type_params;

        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"name\" missing from AsyncFunctionDef");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AsyncFunctionDef' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->args, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"args\" missing from AsyncFunctionDef");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AsyncFunctionDef' node")) {
                goto failed;
            }
            res = obj2ast_arguments(state, tmp, &args, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "AsyncFunctionDef field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'AsyncFunctionDef' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "AsyncFunctionDef field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->decorator_list, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "AsyncFunctionDef field \"decorator_list\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            decorator_list = _Py_asdl_expr_seq_new(len, arena);
            if (decorator_list == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'AsyncFunctionDef' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "AsyncFunctionDef field \"decorator_list\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(decorator_list, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->returns, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            returns = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AsyncFunctionDef' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &returns, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_comment, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            type_comment = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AsyncFunctionDef' node")) {
                goto failed;
            }
            res = obj2ast_string(state, tmp, &type_comment, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_params, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "AsyncFunctionDef field \"type_params\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            type_params = _Py_asdl_type_param_seq_new(len, arena);
            if (type_params == NULL) goto failed;
            for (i = 0; i < len; i++) {
                type_param_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'AsyncFunctionDef' node")) {
                    goto failed;
                }
                res = obj2ast_type_param(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "AsyncFunctionDef field \"type_params\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(type_params, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_AsyncFunctionDef(name, args, body, decorator_list,
                                       returns, type_comment, type_params,
                                       lineno, col_offset, end_lineno,
                                       end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->ClassDef_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        identifier name;
        asdl_expr_seq* bases;
        asdl_keyword_seq* keywords;
        asdl_stmt_seq* body;
        asdl_expr_seq* decorator_list;
        asdl_type_param_seq* type_params;

        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"name\" missing from ClassDef");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'ClassDef' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->bases, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "ClassDef field \"bases\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            bases = _Py_asdl_expr_seq_new(len, arena);
            if (bases == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'ClassDef' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "ClassDef field \"bases\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(bases, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->keywords, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "ClassDef field \"keywords\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            keywords = _Py_asdl_keyword_seq_new(len, arena);
            if (keywords == NULL) goto failed;
            for (i = 0; i < len; i++) {
                keyword_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'ClassDef' node")) {
                    goto failed;
                }
                res = obj2ast_keyword(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "ClassDef field \"keywords\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(keywords, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "ClassDef field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'ClassDef' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "ClassDef field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->decorator_list, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "ClassDef field \"decorator_list\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            decorator_list = _Py_asdl_expr_seq_new(len, arena);
            if (decorator_list == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'ClassDef' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "ClassDef field \"decorator_list\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(decorator_list, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_params, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "ClassDef field \"type_params\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            type_params = _Py_asdl_type_param_seq_new(len, arena);
            if (type_params == NULL) goto failed;
            for (i = 0; i < len; i++) {
                type_param_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'ClassDef' node")) {
                    goto failed;
                }
                res = obj2ast_type_param(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "ClassDef field \"type_params\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(type_params, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_ClassDef(name, bases, keywords, body, decorator_list,
                               type_params, lineno, col_offset, end_lineno,
                               end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Return_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            value = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Return' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Return(value, lineno, col_offset, end_lineno,
                             end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Delete_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_expr_seq* targets;

        if (PyObject_GetOptionalAttr(obj, state->targets, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Delete field \"targets\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            targets = _Py_asdl_expr_seq_new(len, arena);
            if (targets == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Delete' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Delete field \"targets\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(targets, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Delete(targets, lineno, col_offset, end_lineno,
                             end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Assign_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_expr_seq* targets;
        expr_ty value;
        string type_comment;

        if (PyObject_GetOptionalAttr(obj, state->targets, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Assign field \"targets\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            targets = _Py_asdl_expr_seq_new(len, arena);
            if (targets == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Assign' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Assign field \"targets\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(targets, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from Assign");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Assign' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_comment, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            type_comment = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Assign' node")) {
                goto failed;
            }
            res = obj2ast_string(state, tmp, &type_comment, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Assign(targets, value, type_comment, lineno, col_offset,
                             end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->TypeAlias_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty name;
        asdl_type_param_seq* type_params;
        expr_ty value;

        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"name\" missing from TypeAlias");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'TypeAlias' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_params, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "TypeAlias field \"type_params\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            type_params = _Py_asdl_type_param_seq_new(len, arena);
            if (type_params == NULL) goto failed;
            for (i = 0; i < len; i++) {
                type_param_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'TypeAlias' node")) {
                    goto failed;
                }
                res = obj2ast_type_param(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "TypeAlias field \"type_params\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(type_params, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from TypeAlias");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'TypeAlias' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_TypeAlias(name, type_params, value, lineno, col_offset,
                                end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->AugAssign_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty target;
        operator_ty op;
        expr_ty value;

        if (PyObject_GetOptionalAttr(obj, state->target, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"target\" missing from AugAssign");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AugAssign' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &target, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->op, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"op\" missing from AugAssign");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AugAssign' node")) {
                goto failed;
            }
            res = obj2ast_operator(state, tmp, &op, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from AugAssign");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AugAssign' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_AugAssign(target, op, value, lineno, col_offset,
                                end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->AnnAssign_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty target;
        expr_ty annotation;
        expr_ty value;
        int simple;

        if (PyObject_GetOptionalAttr(obj, state->target, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"target\" missing from AnnAssign");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AnnAssign' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &target, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->annotation, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"annotation\" missing from AnnAssign");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AnnAssign' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &annotation, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            value = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AnnAssign' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->simple, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"simple\" missing from AnnAssign");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AnnAssign' node")) {
                goto failed;
            }
            res = obj2ast_int(state, tmp, &simple, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_AnnAssign(target, annotation, value, simple, lineno,
                                col_offset, end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->For_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty target;
        expr_ty iter;
        asdl_stmt_seq* body;
        asdl_stmt_seq* orelse;
        string type_comment;

        if (PyObject_GetOptionalAttr(obj, state->target, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"target\" missing from For");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'For' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &target, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->iter, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"iter\" missing from For");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'For' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &iter, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "For field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'For' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "For field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->orelse, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "For field \"orelse\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            orelse = _Py_asdl_stmt_seq_new(len, arena);
            if (orelse == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'For' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "For field \"orelse\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(orelse, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_comment, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            type_comment = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'For' node")) {
                goto failed;
            }
            res = obj2ast_string(state, tmp, &type_comment, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_For(target, iter, body, orelse, type_comment, lineno,
                          col_offset, end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->AsyncFor_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty target;
        expr_ty iter;
        asdl_stmt_seq* body;
        asdl_stmt_seq* orelse;
        string type_comment;

        if (PyObject_GetOptionalAttr(obj, state->target, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"target\" missing from AsyncFor");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AsyncFor' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &target, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->iter, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"iter\" missing from AsyncFor");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AsyncFor' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &iter, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "AsyncFor field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'AsyncFor' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "AsyncFor field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->orelse, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "AsyncFor field \"orelse\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            orelse = _Py_asdl_stmt_seq_new(len, arena);
            if (orelse == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'AsyncFor' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "AsyncFor field \"orelse\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(orelse, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_comment, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            type_comment = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AsyncFor' node")) {
                goto failed;
            }
            res = obj2ast_string(state, tmp, &type_comment, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_AsyncFor(target, iter, body, orelse, type_comment,
                               lineno, col_offset, end_lineno, end_col_offset,
                               arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->While_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty test;
        asdl_stmt_seq* body;
        asdl_stmt_seq* orelse;

        if (PyObject_GetOptionalAttr(obj, state->test, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"test\" missing from While");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'While' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &test, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "While field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'While' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "While field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->orelse, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "While field \"orelse\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            orelse = _Py_asdl_stmt_seq_new(len, arena);
            if (orelse == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'While' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "While field \"orelse\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(orelse, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_While(test, body, orelse, lineno, col_offset, end_lineno,
                            end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->If_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty test;
        asdl_stmt_seq* body;
        asdl_stmt_seq* orelse;

        if (PyObject_GetOptionalAttr(obj, state->test, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"test\" missing from If");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'If' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &test, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "If field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'If' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "If field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->orelse, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "If field \"orelse\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            orelse = _Py_asdl_stmt_seq_new(len, arena);
            if (orelse == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'If' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "If field \"orelse\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(orelse, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_If(test, body, orelse, lineno, col_offset, end_lineno,
                         end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->With_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_withitem_seq* items;
        asdl_stmt_seq* body;
        string type_comment;

        if (PyObject_GetOptionalAttr(obj, state->items, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "With field \"items\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            items = _Py_asdl_withitem_seq_new(len, arena);
            if (items == NULL) goto failed;
            for (i = 0; i < len; i++) {
                withitem_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'With' node")) {
                    goto failed;
                }
                res = obj2ast_withitem(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "With field \"items\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(items, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "With field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'With' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "With field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_comment, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            type_comment = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'With' node")) {
                goto failed;
            }
            res = obj2ast_string(state, tmp, &type_comment, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_With(items, body, type_comment, lineno, col_offset,
                           end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->AsyncWith_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_withitem_seq* items;
        asdl_stmt_seq* body;
        string type_comment;

        if (PyObject_GetOptionalAttr(obj, state->items, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "AsyncWith field \"items\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            items = _Py_asdl_withitem_seq_new(len, arena);
            if (items == NULL) goto failed;
            for (i = 0; i < len; i++) {
                withitem_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'AsyncWith' node")) {
                    goto failed;
                }
                res = obj2ast_withitem(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "AsyncWith field \"items\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(items, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "AsyncWith field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'AsyncWith' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "AsyncWith field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->type_comment, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            type_comment = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'AsyncWith' node")) {
                goto failed;
            }
            res = obj2ast_string(state, tmp, &type_comment, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_AsyncWith(items, body, type_comment, lineno, col_offset,
                                end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Match_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty subject;
        asdl_match_case_seq* cases;

        if (PyObject_GetOptionalAttr(obj, state->subject, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"subject\" missing from Match");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Match' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &subject, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->cases, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Match field \"cases\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            cases = _Py_asdl_match_case_seq_new(len, arena);
            if (cases == NULL) goto failed;
            for (i = 0; i < len; i++) {
                match_case_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Match' node")) {
                    goto failed;
                }
                res = obj2ast_match_case(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Match field \"cases\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(cases, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Match(subject, cases, lineno, col_offset, end_lineno,
                            end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Raise_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty exc;
        expr_ty cause;

        if (PyObject_GetOptionalAttr(obj, state->exc, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            exc = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Raise' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &exc, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->cause, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            cause = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Raise' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &cause, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Raise(exc, cause, lineno, col_offset, end_lineno,
                            end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Try_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_stmt_seq* body;
        asdl_excepthandler_seq* handlers;
        asdl_stmt_seq* orelse;
        asdl_stmt_seq* finalbody;

        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Try field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Try' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Try field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->handlers, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Try field \"handlers\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            handlers = _Py_asdl_excepthandler_seq_new(len, arena);
            if (handlers == NULL) goto failed;
            for (i = 0; i < len; i++) {
                excepthandler_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Try' node")) {
                    goto failed;
                }
                res = obj2ast_excepthandler(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Try field \"handlers\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(handlers, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->orelse, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Try field \"orelse\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            orelse = _Py_asdl_stmt_seq_new(len, arena);
            if (orelse == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Try' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Try field \"orelse\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(orelse, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->finalbody, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Try field \"finalbody\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            finalbody = _Py_asdl_stmt_seq_new(len, arena);
            if (finalbody == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Try' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Try field \"finalbody\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(finalbody, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Try(body, handlers, orelse, finalbody, lineno,
                          col_offset, end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->TryStar_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_stmt_seq* body;
        asdl_excepthandler_seq* handlers;
        asdl_stmt_seq* orelse;
        asdl_stmt_seq* finalbody;

        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "TryStar field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'TryStar' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "TryStar field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->handlers, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "TryStar field \"handlers\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            handlers = _Py_asdl_excepthandler_seq_new(len, arena);
            if (handlers == NULL) goto failed;
            for (i = 0; i < len; i++) {
                excepthandler_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'TryStar' node")) {
                    goto failed;
                }
                res = obj2ast_excepthandler(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "TryStar field \"handlers\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(handlers, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->orelse, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "TryStar field \"orelse\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            orelse = _Py_asdl_stmt_seq_new(len, arena);
            if (orelse == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'TryStar' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "TryStar field \"orelse\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(orelse, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->finalbody, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "TryStar field \"finalbody\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            finalbody = _Py_asdl_stmt_seq_new(len, arena);
            if (finalbody == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'TryStar' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "TryStar field \"finalbody\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(finalbody, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_TryStar(body, handlers, orelse, finalbody, lineno,
                              col_offset, end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Assert_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty test;
        expr_ty msg;

        if (PyObject_GetOptionalAttr(obj, state->test, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"test\" missing from Assert");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Assert' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &test, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->msg, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            msg = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Assert' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &msg, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Assert(test, msg, lineno, col_offset, end_lineno,
                             end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Import_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_alias_seq* names;

        if (PyObject_GetOptionalAttr(obj, state->names, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Import field \"names\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            names = _Py_asdl_alias_seq_new(len, arena);
            if (names == NULL) goto failed;
            for (i = 0; i < len; i++) {
                alias_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Import' node")) {
                    goto failed;
                }
                res = obj2ast_alias(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Import field \"names\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(names, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Import(names, lineno, col_offset, end_lineno,
                             end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->ImportFrom_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        identifier module;
        asdl_alias_seq* names;
        int level;

        if (PyObject_GetOptionalAttr(obj, state->module, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            module = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'ImportFrom' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &module, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->names, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "ImportFrom field \"names\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            names = _Py_asdl_alias_seq_new(len, arena);
            if (names == NULL) goto failed;
            for (i = 0; i < len; i++) {
                alias_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'ImportFrom' node")) {
                    goto failed;
                }
                res = obj2ast_alias(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "ImportFrom field \"names\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(names, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->level, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            level = 0;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'ImportFrom' node")) {
                goto failed;
            }
            res = obj2ast_int(state, tmp, &level, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_ImportFrom(module, names, level, lineno, col_offset,
                                 end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Global_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_identifier_seq* names;

        if (PyObject_GetOptionalAttr(obj, state->names, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Global field \"names\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            names = _Py_asdl_identifier_seq_new(len, arena);
            if (names == NULL) goto failed;
            for (i = 0; i < len; i++) {
                identifier val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Global' node")) {
                    goto failed;
                }
                res = obj2ast_identifier(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Global field \"names\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(names, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Global(names, lineno, col_offset, end_lineno,
                             end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Nonlocal_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_identifier_seq* names;

        if (PyObject_GetOptionalAttr(obj, state->names, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Nonlocal field \"names\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            names = _Py_asdl_identifier_seq_new(len, arena);
            if (names == NULL) goto failed;
            for (i = 0; i < len; i++) {
                identifier val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Nonlocal' node")) {
                    goto failed;
                }
                res = obj2ast_identifier(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Nonlocal field \"names\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(names, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Nonlocal(names, lineno, col_offset, end_lineno,
                               end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Expr_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from Expr");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Expr' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Expr(value, lineno, col_offset, end_lineno,
                           end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Pass_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {

        *out = _PyAST_Pass(lineno, col_offset, end_lineno, end_col_offset,
                           arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Break_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {

        *out = _PyAST_Break(lineno, col_offset, end_lineno, end_col_offset,
                            arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Continue_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {

        *out = _PyAST_Continue(lineno, col_offset, end_lineno, end_col_offset,
                               arena);
        if (*out == NULL) goto failed;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of stmt, but got %R", obj);
    failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_expr(struct ast_state *state, PyObject* obj, expr_ty* out, PyArena*
             arena)
{
    int isinstance;

    PyObject *tmp = NULL;
    PyObject *tp;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;

    if (obj == Py_None) {
        *out = NULL;
        return 0;
    }
    if (PyObject_GetOptionalAttr(obj, state->lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"lineno\" missing from expr");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'expr' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"col_offset\" missing from expr");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'expr' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_lineno = lineno;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'expr' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_col_offset = col_offset;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'expr' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    tp = state->BoolOp_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        boolop_ty op;
        asdl_expr_seq* values;

        if (PyObject_GetOptionalAttr(obj, state->op, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"op\" missing from BoolOp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'BoolOp' node")) {
                goto failed;
            }
            res = obj2ast_boolop(state, tmp, &op, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->values, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "BoolOp field \"values\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            values = _Py_asdl_expr_seq_new(len, arena);
            if (values == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'BoolOp' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "BoolOp field \"values\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(values, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_BoolOp(op, values, lineno, col_offset, end_lineno,
                             end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->NamedExpr_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty target;
        expr_ty value;

        if (PyObject_GetOptionalAttr(obj, state->target, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"target\" missing from NamedExpr");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'NamedExpr' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &target, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from NamedExpr");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'NamedExpr' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_NamedExpr(target, value, lineno, col_offset, end_lineno,
                                end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->BinOp_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty left;
        operator_ty op;
        expr_ty right;

        if (PyObject_GetOptionalAttr(obj, state->left, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"left\" missing from BinOp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'BinOp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &left, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->op, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"op\" missing from BinOp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'BinOp' node")) {
                goto failed;
            }
            res = obj2ast_operator(state, tmp, &op, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->right, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"right\" missing from BinOp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'BinOp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &right, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_BinOp(left, op, right, lineno, col_offset, end_lineno,
                            end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->UnaryOp_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        unaryop_ty op;
        expr_ty operand;

        if (PyObject_GetOptionalAttr(obj, state->op, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"op\" missing from UnaryOp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'UnaryOp' node")) {
                goto failed;
            }
            res = obj2ast_unaryop(state, tmp, &op, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->operand, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"operand\" missing from UnaryOp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'UnaryOp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &operand, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_UnaryOp(op, operand, lineno, col_offset, end_lineno,
                              end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Lambda_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        arguments_ty args;
        expr_ty body;

        if (PyObject_GetOptionalAttr(obj, state->args, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"args\" missing from Lambda");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Lambda' node")) {
                goto failed;
            }
            res = obj2ast_arguments(state, tmp, &args, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"body\" missing from Lambda");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Lambda' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &body, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Lambda(args, body, lineno, col_offset, end_lineno,
                             end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->IfExp_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty test;
        expr_ty body;
        expr_ty orelse;

        if (PyObject_GetOptionalAttr(obj, state->test, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"test\" missing from IfExp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'IfExp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &test, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"body\" missing from IfExp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'IfExp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &body, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->orelse, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"orelse\" missing from IfExp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'IfExp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &orelse, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_IfExp(test, body, orelse, lineno, col_offset, end_lineno,
                            end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Dict_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_expr_seq* keys;
        asdl_expr_seq* values;

        if (PyObject_GetOptionalAttr(obj, state->keys, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Dict field \"keys\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            keys = _Py_asdl_expr_seq_new(len, arena);
            if (keys == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Dict' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Dict field \"keys\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(keys, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->values, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Dict field \"values\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            values = _Py_asdl_expr_seq_new(len, arena);
            if (values == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Dict' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Dict field \"values\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(values, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Dict(keys, values, lineno, col_offset, end_lineno,
                           end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Set_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_expr_seq* elts;

        if (PyObject_GetOptionalAttr(obj, state->elts, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Set field \"elts\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            elts = _Py_asdl_expr_seq_new(len, arena);
            if (elts == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Set' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Set field \"elts\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(elts, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Set(elts, lineno, col_offset, end_lineno, end_col_offset,
                          arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->ListComp_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty elt;
        asdl_comprehension_seq* generators;

        if (PyObject_GetOptionalAttr(obj, state->elt, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"elt\" missing from ListComp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'ListComp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &elt, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->generators, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "ListComp field \"generators\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            generators = _Py_asdl_comprehension_seq_new(len, arena);
            if (generators == NULL) goto failed;
            for (i = 0; i < len; i++) {
                comprehension_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'ListComp' node")) {
                    goto failed;
                }
                res = obj2ast_comprehension(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "ListComp field \"generators\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(generators, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_ListComp(elt, generators, lineno, col_offset, end_lineno,
                               end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->SetComp_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty elt;
        asdl_comprehension_seq* generators;

        if (PyObject_GetOptionalAttr(obj, state->elt, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"elt\" missing from SetComp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'SetComp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &elt, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->generators, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "SetComp field \"generators\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            generators = _Py_asdl_comprehension_seq_new(len, arena);
            if (generators == NULL) goto failed;
            for (i = 0; i < len; i++) {
                comprehension_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'SetComp' node")) {
                    goto failed;
                }
                res = obj2ast_comprehension(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "SetComp field \"generators\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(generators, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_SetComp(elt, generators, lineno, col_offset, end_lineno,
                              end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->DictComp_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty key;
        expr_ty value;
        asdl_comprehension_seq* generators;

        if (PyObject_GetOptionalAttr(obj, state->key, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"key\" missing from DictComp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'DictComp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &key, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from DictComp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'DictComp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->generators, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "DictComp field \"generators\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            generators = _Py_asdl_comprehension_seq_new(len, arena);
            if (generators == NULL) goto failed;
            for (i = 0; i < len; i++) {
                comprehension_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'DictComp' node")) {
                    goto failed;
                }
                res = obj2ast_comprehension(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "DictComp field \"generators\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(generators, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_DictComp(key, value, generators, lineno, col_offset,
                               end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->GeneratorExp_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty elt;
        asdl_comprehension_seq* generators;

        if (PyObject_GetOptionalAttr(obj, state->elt, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"elt\" missing from GeneratorExp");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'GeneratorExp' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &elt, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->generators, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "GeneratorExp field \"generators\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            generators = _Py_asdl_comprehension_seq_new(len, arena);
            if (generators == NULL) goto failed;
            for (i = 0; i < len; i++) {
                comprehension_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'GeneratorExp' node")) {
                    goto failed;
                }
                res = obj2ast_comprehension(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "GeneratorExp field \"generators\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(generators, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_GeneratorExp(elt, generators, lineno, col_offset,
                                   end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Await_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from Await");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Await' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Await(value, lineno, col_offset, end_lineno,
                            end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Yield_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            value = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Yield' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Yield(value, lineno, col_offset, end_lineno,
                            end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->YieldFrom_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from YieldFrom");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'YieldFrom' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_YieldFrom(value, lineno, col_offset, end_lineno,
                                end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Compare_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty left;
        asdl_int_seq* ops;
        asdl_expr_seq* comparators;

        if (PyObject_GetOptionalAttr(obj, state->left, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"left\" missing from Compare");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Compare' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &left, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->ops, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Compare field \"ops\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            ops = _Py_asdl_int_seq_new(len, arena);
            if (ops == NULL) goto failed;
            for (i = 0; i < len; i++) {
                cmpop_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Compare' node")) {
                    goto failed;
                }
                res = obj2ast_cmpop(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Compare field \"ops\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(ops, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->comparators, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Compare field \"comparators\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            comparators = _Py_asdl_expr_seq_new(len, arena);
            if (comparators == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Compare' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Compare field \"comparators\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(comparators, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Compare(left, ops, comparators, lineno, col_offset,
                              end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Call_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty func;
        asdl_expr_seq* args;
        asdl_keyword_seq* keywords;

        if (PyObject_GetOptionalAttr(obj, state->func, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"func\" missing from Call");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Call' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &func, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->args, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Call field \"args\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            args = _Py_asdl_expr_seq_new(len, arena);
            if (args == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Call' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Call field \"args\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(args, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->keywords, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Call field \"keywords\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            keywords = _Py_asdl_keyword_seq_new(len, arena);
            if (keywords == NULL) goto failed;
            for (i = 0; i < len; i++) {
                keyword_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Call' node")) {
                    goto failed;
                }
                res = obj2ast_keyword(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Call field \"keywords\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(keywords, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Call(func, args, keywords, lineno, col_offset,
                           end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->FormattedValue_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;
        int conversion;
        expr_ty format_spec;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from FormattedValue");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'FormattedValue' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->conversion, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"conversion\" missing from FormattedValue");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'FormattedValue' node")) {
                goto failed;
            }
            res = obj2ast_int(state, tmp, &conversion, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->format_spec, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            format_spec = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'FormattedValue' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &format_spec, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_FormattedValue(value, conversion, format_spec, lineno,
                                     col_offset, end_lineno, end_col_offset,
                                     arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->JoinedStr_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_expr_seq* values;

        if (PyObject_GetOptionalAttr(obj, state->values, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "JoinedStr field \"values\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            values = _Py_asdl_expr_seq_new(len, arena);
            if (values == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'JoinedStr' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "JoinedStr field \"values\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(values, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_JoinedStr(values, lineno, col_offset, end_lineno,
                                end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Constant_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        constant value;
        string kind;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from Constant");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Constant' node")) {
                goto failed;
            }
            res = obj2ast_constant(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->kind, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            kind = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Constant' node")) {
                goto failed;
            }
            res = obj2ast_string(state, tmp, &kind, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Constant(value, kind, lineno, col_offset, end_lineno,
                               end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Attribute_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;
        identifier attr;
        expr_context_ty ctx;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from Attribute");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Attribute' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->attr, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"attr\" missing from Attribute");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Attribute' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &attr, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->ctx, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"ctx\" missing from Attribute");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Attribute' node")) {
                goto failed;
            }
            res = obj2ast_expr_context(state, tmp, &ctx, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Attribute(value, attr, ctx, lineno, col_offset,
                                end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Subscript_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;
        expr_ty slice;
        expr_context_ty ctx;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from Subscript");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Subscript' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->slice, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"slice\" missing from Subscript");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Subscript' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &slice, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->ctx, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"ctx\" missing from Subscript");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Subscript' node")) {
                goto failed;
            }
            res = obj2ast_expr_context(state, tmp, &ctx, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Subscript(value, slice, ctx, lineno, col_offset,
                                end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Starred_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;
        expr_context_ty ctx;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from Starred");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Starred' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->ctx, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"ctx\" missing from Starred");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Starred' node")) {
                goto failed;
            }
            res = obj2ast_expr_context(state, tmp, &ctx, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Starred(value, ctx, lineno, col_offset, end_lineno,
                              end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Name_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        identifier id;
        expr_context_ty ctx;

        if (PyObject_GetOptionalAttr(obj, state->id, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"id\" missing from Name");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Name' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &id, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->ctx, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"ctx\" missing from Name");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Name' node")) {
                goto failed;
            }
            res = obj2ast_expr_context(state, tmp, &ctx, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Name(id, ctx, lineno, col_offset, end_lineno,
                           end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->List_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_expr_seq* elts;
        expr_context_ty ctx;

        if (PyObject_GetOptionalAttr(obj, state->elts, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "List field \"elts\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            elts = _Py_asdl_expr_seq_new(len, arena);
            if (elts == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'List' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "List field \"elts\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(elts, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->ctx, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"ctx\" missing from List");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'List' node")) {
                goto failed;
            }
            res = obj2ast_expr_context(state, tmp, &ctx, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_List(elts, ctx, lineno, col_offset, end_lineno,
                           end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Tuple_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_expr_seq* elts;
        expr_context_ty ctx;

        if (PyObject_GetOptionalAttr(obj, state->elts, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "Tuple field \"elts\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            elts = _Py_asdl_expr_seq_new(len, arena);
            if (elts == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'Tuple' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "Tuple field \"elts\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(elts, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->ctx, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"ctx\" missing from Tuple");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Tuple' node")) {
                goto failed;
            }
            res = obj2ast_expr_context(state, tmp, &ctx, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Tuple(elts, ctx, lineno, col_offset, end_lineno,
                            end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->Slice_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty lower;
        expr_ty upper;
        expr_ty step;

        if (PyObject_GetOptionalAttr(obj, state->lower, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            lower = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Slice' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &lower, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->upper, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            upper = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Slice' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &upper, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->step, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            step = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'Slice' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &step, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_Slice(lower, upper, step, lineno, col_offset, end_lineno,
                            end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of expr, but got %R", obj);
    failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_expr_context(struct ast_state *state, PyObject* obj, expr_context_ty*
                     out, PyArena* arena)
{
    int isinstance;

    isinstance = PyObject_IsInstance(obj, state->Load_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Load;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Store_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Store;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Del_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Del;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of expr_context, but got %R", obj);
    return -1;
}

int
obj2ast_boolop(struct ast_state *state, PyObject* obj, boolop_ty* out, PyArena*
               arena)
{
    int isinstance;

    isinstance = PyObject_IsInstance(obj, state->And_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = And;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Or_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Or;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of boolop, but got %R", obj);
    return -1;
}

int
obj2ast_operator(struct ast_state *state, PyObject* obj, operator_ty* out,
                 PyArena* arena)
{
    int isinstance;

    isinstance = PyObject_IsInstance(obj, state->Add_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Add;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Sub_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Sub;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Mult_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Mult;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->MatMult_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = MatMult;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Div_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Div;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Mod_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Mod;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Pow_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Pow;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->LShift_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = LShift;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->RShift_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = RShift;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->BitOr_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = BitOr;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->BitXor_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = BitXor;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->BitAnd_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = BitAnd;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->FloorDiv_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = FloorDiv;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of operator, but got %R", obj);
    return -1;
}

int
obj2ast_unaryop(struct ast_state *state, PyObject* obj, unaryop_ty* out,
                PyArena* arena)
{
    int isinstance;

    isinstance = PyObject_IsInstance(obj, state->Invert_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Invert;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Not_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Not;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->UAdd_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = UAdd;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->USub_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = USub;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of unaryop, but got %R", obj);
    return -1;
}

int
obj2ast_cmpop(struct ast_state *state, PyObject* obj, cmpop_ty* out, PyArena*
              arena)
{
    int isinstance;

    isinstance = PyObject_IsInstance(obj, state->Eq_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Eq;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->NotEq_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = NotEq;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Lt_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Lt;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->LtE_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = LtE;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Gt_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Gt;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->GtE_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = GtE;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->Is_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = Is;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->IsNot_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = IsNot;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->In_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = In;
        return 0;
    }
    isinstance = PyObject_IsInstance(obj, state->NotIn_type);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        *out = NotIn;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of cmpop, but got %R", obj);
    return -1;
}

int
obj2ast_comprehension(struct ast_state *state, PyObject* obj, comprehension_ty*
                      out, PyArena* arena)
{
    PyObject* tmp = NULL;
    expr_ty target;
    expr_ty iter;
    asdl_expr_seq* ifs;
    int is_async;

    if (PyObject_GetOptionalAttr(obj, state->target, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"target\" missing from comprehension");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'comprehension' node")) {
            goto failed;
        }
        res = obj2ast_expr(state, tmp, &target, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->iter, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"iter\" missing from comprehension");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'comprehension' node")) {
            goto failed;
        }
        res = obj2ast_expr(state, tmp, &iter, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->ifs, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        tmp = PyList_New(0);
        if (tmp == NULL) {
            return -1;
        }
    }
    {
        int res;
        Py_ssize_t len;
        Py_ssize_t i;
        if (!PyList_Check(tmp)) {
            PyErr_Format(PyExc_TypeError, "comprehension field \"ifs\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
            goto failed;
        }
        len = PyList_GET_SIZE(tmp);
        ifs = _Py_asdl_expr_seq_new(len, arena);
        if (ifs == NULL) goto failed;
        for (i = 0; i < len; i++) {
            expr_ty val;
            PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
            if (_Py_EnterRecursiveCall(" while traversing 'comprehension' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp2, &val, arena);
            _Py_LeaveRecursiveCall();
            Py_DECREF(tmp2);
            if (res != 0) goto failed;
            if (len != PyList_GET_SIZE(tmp)) {
                PyErr_SetString(PyExc_RuntimeError, "comprehension field \"ifs\" changed size during iteration");
                goto failed;
            }
            asdl_seq_SET(ifs, i, val);
        }
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->is_async, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"is_async\" missing from comprehension");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'comprehension' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &is_async, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    *out = _PyAST_comprehension(target, iter, ifs, is_async, arena);
    if (*out == NULL) goto failed;
    return 0;
failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_excepthandler(struct ast_state *state, PyObject* obj, excepthandler_ty*
                      out, PyArena* arena)
{
    int isinstance;

    PyObject *tmp = NULL;
    PyObject *tp;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;

    if (obj == Py_None) {
        *out = NULL;
        return 0;
    }
    if (PyObject_GetOptionalAttr(obj, state->lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"lineno\" missing from excepthandler");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'excepthandler' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"col_offset\" missing from excepthandler");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'excepthandler' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_lineno = lineno;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'excepthandler' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_col_offset = col_offset;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'excepthandler' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    tp = state->ExceptHandler_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty type;
        identifier name;
        asdl_stmt_seq* body;

        if (PyObject_GetOptionalAttr(obj, state->type, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            type = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'ExceptHandler' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &type, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            name = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'ExceptHandler' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "ExceptHandler field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            body = _Py_asdl_stmt_seq_new(len, arena);
            if (body == NULL) goto failed;
            for (i = 0; i < len; i++) {
                stmt_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'ExceptHandler' node")) {
                    goto failed;
                }
                res = obj2ast_stmt(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "ExceptHandler field \"body\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(body, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_ExceptHandler(type, name, body, lineno, col_offset,
                                    end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of excepthandler, but got %R", obj);
    failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_arguments(struct ast_state *state, PyObject* obj, arguments_ty* out,
                  PyArena* arena)
{
    PyObject* tmp = NULL;
    asdl_arg_seq* posonlyargs;
    asdl_arg_seq* args;
    arg_ty vararg;
    asdl_arg_seq* kwonlyargs;
    asdl_expr_seq* kw_defaults;
    arg_ty kwarg;
    asdl_expr_seq* defaults;

    if (PyObject_GetOptionalAttr(obj, state->posonlyargs, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        tmp = PyList_New(0);
        if (tmp == NULL) {
            return -1;
        }
    }
    {
        int res;
        Py_ssize_t len;
        Py_ssize_t i;
        if (!PyList_Check(tmp)) {
            PyErr_Format(PyExc_TypeError, "arguments field \"posonlyargs\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
            goto failed;
        }
        len = PyList_GET_SIZE(tmp);
        posonlyargs = _Py_asdl_arg_seq_new(len, arena);
        if (posonlyargs == NULL) goto failed;
        for (i = 0; i < len; i++) {
            arg_ty val;
            PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
            if (_Py_EnterRecursiveCall(" while traversing 'arguments' node")) {
                goto failed;
            }
            res = obj2ast_arg(state, tmp2, &val, arena);
            _Py_LeaveRecursiveCall();
            Py_DECREF(tmp2);
            if (res != 0) goto failed;
            if (len != PyList_GET_SIZE(tmp)) {
                PyErr_SetString(PyExc_RuntimeError, "arguments field \"posonlyargs\" changed size during iteration");
                goto failed;
            }
            asdl_seq_SET(posonlyargs, i, val);
        }
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->args, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        tmp = PyList_New(0);
        if (tmp == NULL) {
            return -1;
        }
    }
    {
        int res;
        Py_ssize_t len;
        Py_ssize_t i;
        if (!PyList_Check(tmp)) {
            PyErr_Format(PyExc_TypeError, "arguments field \"args\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
            goto failed;
        }
        len = PyList_GET_SIZE(tmp);
        args = _Py_asdl_arg_seq_new(len, arena);
        if (args == NULL) goto failed;
        for (i = 0; i < len; i++) {
            arg_ty val;
            PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
            if (_Py_EnterRecursiveCall(" while traversing 'arguments' node")) {
                goto failed;
            }
            res = obj2ast_arg(state, tmp2, &val, arena);
            _Py_LeaveRecursiveCall();
            Py_DECREF(tmp2);
            if (res != 0) goto failed;
            if (len != PyList_GET_SIZE(tmp)) {
                PyErr_SetString(PyExc_RuntimeError, "arguments field \"args\" changed size during iteration");
                goto failed;
            }
            asdl_seq_SET(args, i, val);
        }
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->vararg, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        vararg = NULL;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'arguments' node")) {
            goto failed;
        }
        res = obj2ast_arg(state, tmp, &vararg, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->kwonlyargs, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        tmp = PyList_New(0);
        if (tmp == NULL) {
            return -1;
        }
    }
    {
        int res;
        Py_ssize_t len;
        Py_ssize_t i;
        if (!PyList_Check(tmp)) {
            PyErr_Format(PyExc_TypeError, "arguments field \"kwonlyargs\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
            goto failed;
        }
        len = PyList_GET_SIZE(tmp);
        kwonlyargs = _Py_asdl_arg_seq_new(len, arena);
        if (kwonlyargs == NULL) goto failed;
        for (i = 0; i < len; i++) {
            arg_ty val;
            PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
            if (_Py_EnterRecursiveCall(" while traversing 'arguments' node")) {
                goto failed;
            }
            res = obj2ast_arg(state, tmp2, &val, arena);
            _Py_LeaveRecursiveCall();
            Py_DECREF(tmp2);
            if (res != 0) goto failed;
            if (len != PyList_GET_SIZE(tmp)) {
                PyErr_SetString(PyExc_RuntimeError, "arguments field \"kwonlyargs\" changed size during iteration");
                goto failed;
            }
            asdl_seq_SET(kwonlyargs, i, val);
        }
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->kw_defaults, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        tmp = PyList_New(0);
        if (tmp == NULL) {
            return -1;
        }
    }
    {
        int res;
        Py_ssize_t len;
        Py_ssize_t i;
        if (!PyList_Check(tmp)) {
            PyErr_Format(PyExc_TypeError, "arguments field \"kw_defaults\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
            goto failed;
        }
        len = PyList_GET_SIZE(tmp);
        kw_defaults = _Py_asdl_expr_seq_new(len, arena);
        if (kw_defaults == NULL) goto failed;
        for (i = 0; i < len; i++) {
            expr_ty val;
            PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
            if (_Py_EnterRecursiveCall(" while traversing 'arguments' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp2, &val, arena);
            _Py_LeaveRecursiveCall();
            Py_DECREF(tmp2);
            if (res != 0) goto failed;
            if (len != PyList_GET_SIZE(tmp)) {
                PyErr_SetString(PyExc_RuntimeError, "arguments field \"kw_defaults\" changed size during iteration");
                goto failed;
            }
            asdl_seq_SET(kw_defaults, i, val);
        }
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->kwarg, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        kwarg = NULL;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'arguments' node")) {
            goto failed;
        }
        res = obj2ast_arg(state, tmp, &kwarg, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->defaults, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        tmp = PyList_New(0);
        if (tmp == NULL) {
            return -1;
        }
    }
    {
        int res;
        Py_ssize_t len;
        Py_ssize_t i;
        if (!PyList_Check(tmp)) {
            PyErr_Format(PyExc_TypeError, "arguments field \"defaults\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
            goto failed;
        }
        len = PyList_GET_SIZE(tmp);
        defaults = _Py_asdl_expr_seq_new(len, arena);
        if (defaults == NULL) goto failed;
        for (i = 0; i < len; i++) {
            expr_ty val;
            PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
            if (_Py_EnterRecursiveCall(" while traversing 'arguments' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp2, &val, arena);
            _Py_LeaveRecursiveCall();
            Py_DECREF(tmp2);
            if (res != 0) goto failed;
            if (len != PyList_GET_SIZE(tmp)) {
                PyErr_SetString(PyExc_RuntimeError, "arguments field \"defaults\" changed size during iteration");
                goto failed;
            }
            asdl_seq_SET(defaults, i, val);
        }
        Py_CLEAR(tmp);
    }
    *out = _PyAST_arguments(posonlyargs, args, vararg, kwonlyargs, kw_defaults,
                            kwarg, defaults, arena);
    if (*out == NULL) goto failed;
    return 0;
failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_arg(struct ast_state *state, PyObject* obj, arg_ty* out, PyArena* arena)
{
    PyObject* tmp = NULL;
    identifier arg;
    expr_ty annotation;
    string type_comment;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;

    if (PyObject_GetOptionalAttr(obj, state->arg, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"arg\" missing from arg");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'arg' node")) {
            goto failed;
        }
        res = obj2ast_identifier(state, tmp, &arg, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->annotation, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        annotation = NULL;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'arg' node")) {
            goto failed;
        }
        res = obj2ast_expr(state, tmp, &annotation, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->type_comment, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        type_comment = NULL;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'arg' node")) {
            goto failed;
        }
        res = obj2ast_string(state, tmp, &type_comment, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"lineno\" missing from arg");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'arg' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"col_offset\" missing from arg");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'arg' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_lineno = lineno;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'arg' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_col_offset = col_offset;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'arg' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    *out = _PyAST_arg(arg, annotation, type_comment, lineno, col_offset,
                      end_lineno, end_col_offset, arena);
    if (*out == NULL) goto failed;
    return 0;
failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_keyword(struct ast_state *state, PyObject* obj, keyword_ty* out,
                PyArena* arena)
{
    PyObject* tmp = NULL;
    identifier arg;
    expr_ty value;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;

    if (PyObject_GetOptionalAttr(obj, state->arg, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        arg = NULL;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'keyword' node")) {
            goto failed;
        }
        res = obj2ast_identifier(state, tmp, &arg, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from keyword");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'keyword' node")) {
            goto failed;
        }
        res = obj2ast_expr(state, tmp, &value, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"lineno\" missing from keyword");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'keyword' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"col_offset\" missing from keyword");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'keyword' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_lineno = lineno;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'keyword' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_col_offset = col_offset;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'keyword' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    *out = _PyAST_keyword(arg, value, lineno, col_offset, end_lineno,
                          end_col_offset, arena);
    if (*out == NULL) goto failed;
    return 0;
failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_alias(struct ast_state *state, PyObject* obj, alias_ty* out, PyArena*
              arena)
{
    PyObject* tmp = NULL;
    identifier name;
    identifier asname;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;

    if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"name\" missing from alias");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'alias' node")) {
            goto failed;
        }
        res = obj2ast_identifier(state, tmp, &name, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->asname, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        asname = NULL;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'alias' node")) {
            goto failed;
        }
        res = obj2ast_identifier(state, tmp, &asname, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"lineno\" missing from alias");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'alias' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"col_offset\" missing from alias");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'alias' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_lineno = lineno;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'alias' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        end_col_offset = col_offset;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'alias' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    *out = _PyAST_alias(name, asname, lineno, col_offset, end_lineno,
                        end_col_offset, arena);
    if (*out == NULL) goto failed;
    return 0;
failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_withitem(struct ast_state *state, PyObject* obj, withitem_ty* out,
                 PyArena* arena)
{
    PyObject* tmp = NULL;
    expr_ty context_expr;
    expr_ty optional_vars;

    if (PyObject_GetOptionalAttr(obj, state->context_expr, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"context_expr\" missing from withitem");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'withitem' node")) {
            goto failed;
        }
        res = obj2ast_expr(state, tmp, &context_expr, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->optional_vars, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        optional_vars = NULL;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'withitem' node")) {
            goto failed;
        }
        res = obj2ast_expr(state, tmp, &optional_vars, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    *out = _PyAST_withitem(context_expr, optional_vars, arena);
    if (*out == NULL) goto failed;
    return 0;
failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_match_case(struct ast_state *state, PyObject* obj, match_case_ty* out,
                   PyArena* arena)
{
    PyObject* tmp = NULL;
    pattern_ty pattern;
    expr_ty guard;
    asdl_stmt_seq* body;

    if (PyObject_GetOptionalAttr(obj, state->pattern, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"pattern\" missing from match_case");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'match_case' node")) {
            goto failed;
        }
        res = obj2ast_pattern(state, tmp, &pattern, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->guard, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL || tmp == Py_None) {
        Py_CLEAR(tmp);
        guard = NULL;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'match_case' node")) {
            goto failed;
        }
        res = obj2ast_expr(state, tmp, &guard, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->body, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        tmp = PyList_New(0);
        if (tmp == NULL) {
            return -1;
        }
    }
    {
        int res;
        Py_ssize_t len;
        Py_ssize_t i;
        if (!PyList_Check(tmp)) {
            PyErr_Format(PyExc_TypeError, "match_case field \"body\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
            goto failed;
        }
        len = PyList_GET_SIZE(tmp);
        body = _Py_asdl_stmt_seq_new(len, arena);
        if (body == NULL) goto failed;
        for (i = 0; i < len; i++) {
            stmt_ty val;
            PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
            if (_Py_EnterRecursiveCall(" while traversing 'match_case' node")) {
                goto failed;
            }
            res = obj2ast_stmt(state, tmp2, &val, arena);
            _Py_LeaveRecursiveCall();
            Py_DECREF(tmp2);
            if (res != 0) goto failed;
            if (len != PyList_GET_SIZE(tmp)) {
                PyErr_SetString(PyExc_RuntimeError, "match_case field \"body\" changed size during iteration");
                goto failed;
            }
            asdl_seq_SET(body, i, val);
        }
        Py_CLEAR(tmp);
    }
    *out = _PyAST_match_case(pattern, guard, body, arena);
    if (*out == NULL) goto failed;
    return 0;
failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_pattern(struct ast_state *state, PyObject* obj, pattern_ty* out,
                PyArena* arena)
{
    int isinstance;

    PyObject *tmp = NULL;
    PyObject *tp;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;

    if (obj == Py_None) {
        *out = NULL;
        return 0;
    }
    if (PyObject_GetOptionalAttr(obj, state->lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"lineno\" missing from pattern");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'pattern' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"col_offset\" missing from pattern");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'pattern' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"end_lineno\" missing from pattern");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'pattern' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"end_col_offset\" missing from pattern");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'pattern' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    tp = state->MatchValue_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty value;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from MatchValue");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'MatchValue' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_MatchValue(value, lineno, col_offset, end_lineno,
                                 end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->MatchSingleton_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        constant value;

        if (PyObject_GetOptionalAttr(obj, state->value, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"value\" missing from MatchSingleton");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'MatchSingleton' node")) {
                goto failed;
            }
            res = obj2ast_constant(state, tmp, &value, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_MatchSingleton(value, lineno, col_offset, end_lineno,
                                     end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->MatchSequence_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_pattern_seq* patterns;

        if (PyObject_GetOptionalAttr(obj, state->patterns, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "MatchSequence field \"patterns\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            patterns = _Py_asdl_pattern_seq_new(len, arena);
            if (patterns == NULL) goto failed;
            for (i = 0; i < len; i++) {
                pattern_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'MatchSequence' node")) {
                    goto failed;
                }
                res = obj2ast_pattern(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "MatchSequence field \"patterns\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(patterns, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_MatchSequence(patterns, lineno, col_offset, end_lineno,
                                    end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->MatchMapping_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_expr_seq* keys;
        asdl_pattern_seq* patterns;
        identifier rest;

        if (PyObject_GetOptionalAttr(obj, state->keys, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "MatchMapping field \"keys\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            keys = _Py_asdl_expr_seq_new(len, arena);
            if (keys == NULL) goto failed;
            for (i = 0; i < len; i++) {
                expr_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'MatchMapping' node")) {
                    goto failed;
                }
                res = obj2ast_expr(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "MatchMapping field \"keys\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(keys, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->patterns, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "MatchMapping field \"patterns\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            patterns = _Py_asdl_pattern_seq_new(len, arena);
            if (patterns == NULL) goto failed;
            for (i = 0; i < len; i++) {
                pattern_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'MatchMapping' node")) {
                    goto failed;
                }
                res = obj2ast_pattern(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "MatchMapping field \"patterns\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(patterns, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->rest, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            rest = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'MatchMapping' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &rest, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_MatchMapping(keys, patterns, rest, lineno, col_offset,
                                   end_lineno, end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->MatchClass_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        expr_ty cls;
        asdl_pattern_seq* patterns;
        asdl_identifier_seq* kwd_attrs;
        asdl_pattern_seq* kwd_patterns;

        if (PyObject_GetOptionalAttr(obj, state->cls, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"cls\" missing from MatchClass");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'MatchClass' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &cls, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->patterns, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "MatchClass field \"patterns\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            patterns = _Py_asdl_pattern_seq_new(len, arena);
            if (patterns == NULL) goto failed;
            for (i = 0; i < len; i++) {
                pattern_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'MatchClass' node")) {
                    goto failed;
                }
                res = obj2ast_pattern(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "MatchClass field \"patterns\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(patterns, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->kwd_attrs, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "MatchClass field \"kwd_attrs\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            kwd_attrs = _Py_asdl_identifier_seq_new(len, arena);
            if (kwd_attrs == NULL) goto failed;
            for (i = 0; i < len; i++) {
                identifier val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'MatchClass' node")) {
                    goto failed;
                }
                res = obj2ast_identifier(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "MatchClass field \"kwd_attrs\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(kwd_attrs, i, val);
            }
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->kwd_patterns, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "MatchClass field \"kwd_patterns\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            kwd_patterns = _Py_asdl_pattern_seq_new(len, arena);
            if (kwd_patterns == NULL) goto failed;
            for (i = 0; i < len; i++) {
                pattern_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'MatchClass' node")) {
                    goto failed;
                }
                res = obj2ast_pattern(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "MatchClass field \"kwd_patterns\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(kwd_patterns, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_MatchClass(cls, patterns, kwd_attrs, kwd_patterns,
                                 lineno, col_offset, end_lineno,
                                 end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->MatchStar_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        identifier name;

        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            name = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'MatchStar' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_MatchStar(name, lineno, col_offset, end_lineno,
                                end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->MatchAs_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        pattern_ty pattern;
        identifier name;

        if (PyObject_GetOptionalAttr(obj, state->pattern, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            pattern = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'MatchAs' node")) {
                goto failed;
            }
            res = obj2ast_pattern(state, tmp, &pattern, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            name = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'MatchAs' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_MatchAs(pattern, name, lineno, col_offset, end_lineno,
                              end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->MatchOr_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        asdl_pattern_seq* patterns;

        if (PyObject_GetOptionalAttr(obj, state->patterns, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            tmp = PyList_New(0);
            if (tmp == NULL) {
                return -1;
            }
        }
        {
            int res;
            Py_ssize_t len;
            Py_ssize_t i;
            if (!PyList_Check(tmp)) {
                PyErr_Format(PyExc_TypeError, "MatchOr field \"patterns\" must be a list, not a %.200s", _PyType_Name(Py_TYPE(tmp)));
                goto failed;
            }
            len = PyList_GET_SIZE(tmp);
            patterns = _Py_asdl_pattern_seq_new(len, arena);
            if (patterns == NULL) goto failed;
            for (i = 0; i < len; i++) {
                pattern_ty val;
                PyObject *tmp2 = Py_NewRef(PyList_GET_ITEM(tmp, i));
                if (_Py_EnterRecursiveCall(" while traversing 'MatchOr' node")) {
                    goto failed;
                }
                res = obj2ast_pattern(state, tmp2, &val, arena);
                _Py_LeaveRecursiveCall();
                Py_DECREF(tmp2);
                if (res != 0) goto failed;
                if (len != PyList_GET_SIZE(tmp)) {
                    PyErr_SetString(PyExc_RuntimeError, "MatchOr field \"patterns\" changed size during iteration");
                    goto failed;
                }
                asdl_seq_SET(patterns, i, val);
            }
            Py_CLEAR(tmp);
        }
        *out = _PyAST_MatchOr(patterns, lineno, col_offset, end_lineno,
                              end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of pattern, but got %R", obj);
    failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_type_ignore(struct ast_state *state, PyObject* obj, type_ignore_ty*
                    out, PyArena* arena)
{
    int isinstance;

    PyObject *tmp = NULL;
    PyObject *tp;

    if (obj == Py_None) {
        *out = NULL;
        return 0;
    }
    tp = state->TypeIgnore_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        int lineno;
        string tag;

        if (PyObject_GetOptionalAttr(obj, state->lineno, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"lineno\" missing from TypeIgnore");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'TypeIgnore' node")) {
                goto failed;
            }
            res = obj2ast_int(state, tmp, &lineno, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->tag, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"tag\" missing from TypeIgnore");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'TypeIgnore' node")) {
                goto failed;
            }
            res = obj2ast_string(state, tmp, &tag, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_TypeIgnore(lineno, tag, arena);
        if (*out == NULL) goto failed;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of type_ignore, but got %R", obj);
    failed:
    Py_XDECREF(tmp);
    return -1;
}

int
obj2ast_type_param(struct ast_state *state, PyObject* obj, type_param_ty* out,
                   PyArena* arena)
{
    int isinstance;

    PyObject *tmp = NULL;
    PyObject *tp;
    int lineno;
    int col_offset;
    int end_lineno;
    int end_col_offset;

    if (obj == Py_None) {
        *out = NULL;
        return 0;
    }
    if (PyObject_GetOptionalAttr(obj, state->lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"lineno\" missing from type_param");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'type_param' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"col_offset\" missing from type_param");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'type_param' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_lineno, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"end_lineno\" missing from type_param");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'type_param' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_lineno, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    if (PyObject_GetOptionalAttr(obj, state->end_col_offset, &tmp) < 0) {
        return -1;
    }
    if (tmp == NULL) {
        PyErr_SetString(PyExc_TypeError, "required field \"end_col_offset\" missing from type_param");
        return -1;
    }
    else {
        int res;
        if (_Py_EnterRecursiveCall(" while traversing 'type_param' node")) {
            goto failed;
        }
        res = obj2ast_int(state, tmp, &end_col_offset, arena);
        _Py_LeaveRecursiveCall();
        if (res != 0) goto failed;
        Py_CLEAR(tmp);
    }
    tp = state->TypeVar_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        identifier name;
        expr_ty bound;

        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"name\" missing from TypeVar");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'TypeVar' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        if (PyObject_GetOptionalAttr(obj, state->bound, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL || tmp == Py_None) {
            Py_CLEAR(tmp);
            bound = NULL;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'TypeVar' node")) {
                goto failed;
            }
            res = obj2ast_expr(state, tmp, &bound, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_TypeVar(name, bound, lineno, col_offset, end_lineno,
                              end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->ParamSpec_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        identifier name;

        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"name\" missing from ParamSpec");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'ParamSpec' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_ParamSpec(name, lineno, col_offset, end_lineno,
                                end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }
    tp = state->TypeVarTuple_type;
    isinstance = PyObject_IsInstance(obj, tp);
    if (isinstance == -1) {
        return -1;
    }
    if (isinstance) {
        identifier name;

        if (PyObject_GetOptionalAttr(obj, state->name, &tmp) < 0) {
            return -1;
        }
        if (tmp == NULL) {
            PyErr_SetString(PyExc_TypeError, "required field \"name\" missing from TypeVarTuple");
            return -1;
        }
        else {
            int res;
            if (_Py_EnterRecursiveCall(" while traversing 'TypeVarTuple' node")) {
                goto failed;
            }
            res = obj2ast_identifier(state, tmp, &name, arena);
            _Py_LeaveRecursiveCall();
            if (res != 0) goto failed;
            Py_CLEAR(tmp);
        }
        *out = _PyAST_TypeVarTuple(name, lineno, col_offset, end_lineno,
                                   end_col_offset, arena);
        if (*out == NULL) goto failed;
        return 0;
    }

    PyErr_Format(PyExc_TypeError, "expected some sort of type_param, but got %R", obj);
    failed:
    Py_XDECREF(tmp);
    return -1;
}


static int
astmodule_exec(PyObject *m)
{
    struct ast_state *state = get_ast_state();
    if (state == NULL) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "AST", state->AST_type) < 0) {
        return -1;
    }
    if (PyModule_AddIntMacro(m, PyCF_ALLOW_TOP_LEVEL_AWAIT) < 0) {
        return -1;
    }
    if (PyModule_AddIntMacro(m, PyCF_ONLY_AST) < 0) {
        return -1;
    }
    if (PyModule_AddIntMacro(m, PyCF_TYPE_COMMENTS) < 0) {
        return -1;
    }
    if (PyModule_AddIntMacro(m, PyCF_OPTIMIZED_AST) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "mod", state->mod_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Module", state->Module_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Interactive", state->Interactive_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Expression", state->Expression_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "FunctionType", state->FunctionType_type) < 0)
        {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "stmt", state->stmt_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "FunctionDef", state->FunctionDef_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "AsyncFunctionDef",
        state->AsyncFunctionDef_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "ClassDef", state->ClassDef_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Return", state->Return_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Delete", state->Delete_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Assign", state->Assign_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "TypeAlias", state->TypeAlias_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "AugAssign", state->AugAssign_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "AnnAssign", state->AnnAssign_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "For", state->For_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "AsyncFor", state->AsyncFor_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "While", state->While_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "If", state->If_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "With", state->With_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "AsyncWith", state->AsyncWith_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Match", state->Match_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Raise", state->Raise_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Try", state->Try_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "TryStar", state->TryStar_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Assert", state->Assert_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Import", state->Import_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "ImportFrom", state->ImportFrom_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Global", state->Global_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Nonlocal", state->Nonlocal_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Expr", state->Expr_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Pass", state->Pass_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Break", state->Break_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Continue", state->Continue_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "expr", state->expr_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "BoolOp", state->BoolOp_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "NamedExpr", state->NamedExpr_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "BinOp", state->BinOp_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "UnaryOp", state->UnaryOp_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Lambda", state->Lambda_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "IfExp", state->IfExp_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Dict", state->Dict_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Set", state->Set_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "ListComp", state->ListComp_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "SetComp", state->SetComp_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "DictComp", state->DictComp_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "GeneratorExp", state->GeneratorExp_type) < 0)
        {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Await", state->Await_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Yield", state->Yield_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "YieldFrom", state->YieldFrom_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Compare", state->Compare_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Call", state->Call_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "FormattedValue", state->FormattedValue_type)
        < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "JoinedStr", state->JoinedStr_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Constant", state->Constant_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Attribute", state->Attribute_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Subscript", state->Subscript_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Starred", state->Starred_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Name", state->Name_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "List", state->List_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Tuple", state->Tuple_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Slice", state->Slice_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "expr_context", state->expr_context_type) < 0)
        {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Load", state->Load_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Store", state->Store_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Del", state->Del_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "boolop", state->boolop_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "And", state->And_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Or", state->Or_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "operator", state->operator_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Add", state->Add_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Sub", state->Sub_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Mult", state->Mult_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "MatMult", state->MatMult_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Div", state->Div_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Mod", state->Mod_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Pow", state->Pow_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "LShift", state->LShift_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "RShift", state->RShift_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "BitOr", state->BitOr_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "BitXor", state->BitXor_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "BitAnd", state->BitAnd_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "FloorDiv", state->FloorDiv_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "unaryop", state->unaryop_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Invert", state->Invert_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Not", state->Not_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "UAdd", state->UAdd_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "USub", state->USub_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "cmpop", state->cmpop_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Eq", state->Eq_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "NotEq", state->NotEq_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Lt", state->Lt_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "LtE", state->LtE_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Gt", state->Gt_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "GtE", state->GtE_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "Is", state->Is_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "IsNot", state->IsNot_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "In", state->In_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "NotIn", state->NotIn_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "comprehension", state->comprehension_type) <
        0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "excepthandler", state->excepthandler_type) <
        0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "ExceptHandler", state->ExceptHandler_type) <
        0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "arguments", state->arguments_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "arg", state->arg_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "keyword", state->keyword_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "alias", state->alias_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "withitem", state->withitem_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "match_case", state->match_case_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "pattern", state->pattern_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "MatchValue", state->MatchValue_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "MatchSingleton", state->MatchSingleton_type)
        < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "MatchSequence", state->MatchSequence_type) <
        0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "MatchMapping", state->MatchMapping_type) < 0)
        {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "MatchClass", state->MatchClass_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "MatchStar", state->MatchStar_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "MatchAs", state->MatchAs_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "MatchOr", state->MatchOr_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "type_ignore", state->type_ignore_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "TypeIgnore", state->TypeIgnore_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "type_param", state->type_param_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "TypeVar", state->TypeVar_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "ParamSpec", state->ParamSpec_type) < 0) {
        return -1;
    }
    if (PyModule_AddObjectRef(m, "TypeVarTuple", state->TypeVarTuple_type) < 0)
        {
        return -1;
    }
    return 0;
}

static PyModuleDef_Slot astmodule_slots[] = {
    {Py_mod_exec, astmodule_exec},
    {Py_mod_multiple_interpreters, Py_MOD_PER_INTERPRETER_GIL_SUPPORTED},
    {0, NULL}
};

static struct PyModuleDef _astmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "_ast",
    // The _ast module uses a per-interpreter state (PyInterpreterState.ast)
    .m_size = 0,
    .m_slots = astmodule_slots,
};

PyMODINIT_FUNC
PyInit__ast(void)
{
    return PyModuleDef_Init(&_astmodule);
}


PyObject* PyAST_mod2obj(mod_ty t)
{
    struct ast_state *state = get_ast_state();
    if (state == NULL) {
        return NULL;
    }

    int starting_recursion_depth;
    /* Be careful here to prevent overflow. */
    PyThreadState *tstate = _PyThreadState_GET();
    if (!tstate) {
        return NULL;
    }
    struct validator vstate;
    vstate.recursion_limit = Py_C_RECURSION_LIMIT;
    int recursion_depth = Py_C_RECURSION_LIMIT - tstate->c_recursion_remaining;
    starting_recursion_depth = recursion_depth;
    vstate.recursion_depth = starting_recursion_depth;

    PyObject *result = ast2obj_mod(state, &vstate, t);

    /* Check that the recursion depth counting balanced correctly */
    if (result && vstate.recursion_depth != starting_recursion_depth) {
        PyErr_Format(PyExc_SystemError,
            "AST constructor recursion depth mismatch (before=%d, after=%d)",
            starting_recursion_depth, vstate.recursion_depth);
        return NULL;
    }
    return result;
}

/* mode is 0 for "exec", 1 for "eval" and 2 for "single" input */
mod_ty PyAST_obj2mod(PyObject* ast, PyArena* arena, int mode)
{
    const char * const req_name[] = {"Module", "Expression", "Interactive"};
    int isinstance;

    if (PySys_Audit("compile", "OO", ast, Py_None) < 0) {
        return NULL;
    }

    struct ast_state *state = get_ast_state();
    if (state == NULL) {
        return NULL;
    }

    PyObject *req_type[3];
    req_type[0] = state->Module_type;
    req_type[1] = state->Expression_type;
    req_type[2] = state->Interactive_type;

    assert(0 <= mode && mode <= 2);

    isinstance = PyObject_IsInstance(ast, req_type[mode]);
    if (isinstance == -1)
        return NULL;
    if (!isinstance) {
        PyErr_Format(PyExc_TypeError, "expected %s node, got %.400s",
                     req_name[mode], _PyType_Name(Py_TYPE(ast)));
        return NULL;
    }

    mod_ty res = NULL;
    if (obj2ast_mod(state, ast, &res, arena) != 0)
        return NULL;
    else
        return res;
}

int PyAST_Check(PyObject* obj)
{
    struct ast_state *state = get_ast_state();
    if (state == NULL) {
        return -1;
    }
    return PyObject_IsInstance(obj, state->AST_type);
}

