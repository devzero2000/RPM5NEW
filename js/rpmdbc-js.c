/** \ingroup js_c
 * \file js/rpmdbc-js.c
 */

#include "system.h"

#include "rpmdbc-js.h"
#include "rpmjs-debug.h"

#include <argv.h>

#include <db.h>

#include "debug.h"

/*@unchecked@*/
static int _debug = -1;

/* Required JSClass vectors */
#define	rpmdbc_addprop		JS_PropertyStub
#define	rpmdbc_delprop		JS_PropertyStub
#define	rpmdbc_convert		JS_ConvertStub

/* Optional JSClass vectors */
#define	rpmdbc_getobjectops	NULL
#define	rpmdbc_checkaccess	NULL
#define	rpmdbc_call		rpmdbc_call
#define	rpmdbc_construct		rpmdbc_ctor
#define	rpmdbc_xdrobject		NULL
#define	rpmdbc_hasinstance	NULL
#define	rpmdbc_mark		NULL
#define	rpmdbc_reserveslots	NULL

/* Extended JSClass vectors */
#define rpmdbc_equality		NULL
#define rpmdbc_outerobject	NULL
#define rpmdbc_innerobject	NULL
#define rpmdbc_iteratorobject	NULL
#define rpmdbc_wrappedobject	NULL

/* --- helpers */

/* --- Object methods */

#define	_zalloca(_p)	memset(alloca(sizeof(*_p)), 0, sizeof(*_p))

static JSBool
rpmdbc_Close(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    JSBool ok = JS_FALSE;

_METHOD_DEBUG_ENTRY(_debug);

    *rval = JSVAL_TRUE;

    if (dbc) {
	int ret = dbc->close(dbc);
	dbc = ptr = NULL;
	(void) JS_SetPrivate(cx, obj, ptr);
    }

    ok = JS_TRUE;
exit:
    return ok;
}

static JSBool
rpmdbc_Cmp(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    JSBool ok = JS_FALSE;

_METHOD_DEBUG_ENTRY(_debug);

    *rval = JSVAL_TRUE;

    if (dbc) {
	DBC * _otherdbc = NULL;
	int _result = 0;
	uint32_t _flags = 0;
	int ret = dbc->cmp(dbc, _otherdbc, &_result, _flags);
    }

    ok = JS_TRUE;

    return ok;
}

static JSBool
rpmdbc_Count(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    JSBool ok = JS_FALSE;

_METHOD_DEBUG_ENTRY(_debug);

    *rval = JSVAL_TRUE;

    if (dbc) {
	db_recno_t _count = 0;
	uint32_t _flags = 0;
	int ret = dbc->count(dbc, &_count, _flags);
    }

    ok = JS_TRUE;

    return ok;
}

static JSBool
rpmdbc_Del(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    JSBool ok = JS_FALSE;

_METHOD_DEBUG_ENTRY(_debug);

    *rval = JSVAL_TRUE;

    if (dbc) {
	uint32_t _flags = 0;
	int ret = dbc->del(dbc, _flags);
    }

    ok = JS_TRUE;

    return ok;
}

static JSBool
rpmdbc_Dup(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    JSBool ok = JS_FALSE;

_METHOD_DEBUG_ENTRY(_debug);

    *rval = JSVAL_TRUE;

    if (dbc) {
	DBC * _cursor = NULL;
	uint32_t _flags = 0;
	int ret = dbc->dup(dbc, &_cursor, _flags);
    }

    ok = JS_TRUE;

    return ok;
}

static JSBool
rpmdbc_Get(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    JSBool ok = JS_FALSE;

_METHOD_DEBUG_ENTRY(_debug);

    *rval = JSVAL_TRUE;

    if (dbc) {
	DBT * _key = _zalloca(_key);
	DBT * _data = _zalloca(_key);
	uint32_t _flags = 0;
	int ret = dbc->get(dbc, _key, _data, _flags);
    }

    ok = JS_TRUE;

    return ok;
}

static JSBool
rpmdbc_Pget(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    JSBool ok = JS_FALSE;

_METHOD_DEBUG_ENTRY(_debug);

    *rval = JSVAL_TRUE;

    if (dbc) {
	DBT * _key = _zalloca(_key);
	DBT * _pkey = _zalloca(_pkey);
	DBT * _data = _zalloca(_key);
	uint32_t _flags = 0;
	int ret = dbc->pget(dbc, _key, _pkey, _data, _flags);
    }

    ok = JS_TRUE;

    return ok;
}

static JSBool
rpmdbc_Put(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    JSBool ok = JS_FALSE;

_METHOD_DEBUG_ENTRY(_debug);

    *rval = JSVAL_TRUE;

    if (dbc) {
	DBT * _key = _zalloca(_key);
	DBT * _data = _zalloca(_key);
	uint32_t _flags = 0;
	int ret = dbc->put(dbc, _key, _data, _flags);
    }

    ok = JS_TRUE;

    return ok;
}

static JSFunctionSpec rpmdbc_funcs[] = {
    JS_FS("close",	rpmdbc_Close,		0,0,0),
    JS_FS("cmp",	rpmdbc_Cmp,		0,0,0),
    JS_FS("count",	rpmdbc_Count,		0,0,0),
    JS_FS("del",	rpmdbc_Del,		0,0,0),
    JS_FS("dup",	rpmdbc_Dup,		0,0,0),
    JS_FS("get",	rpmdbc_Get,		0,0,0),
    JS_FS("pget",	rpmdbc_Pget,		0,0,0),
    JS_FS("put",	rpmdbc_Put,		0,0,0),
    JS_FS_END
};

/* --- Object properties */

#define	_TABLE(_v)	#_v, _##_v, JSPROP_ENUMERATE, NULL, NULL

enum rpmdbc_tinyid {
    _DEBUG	= -2,
    _PRIORITY	= -3,
};

static JSPropertySpec rpmdbc_props[] = {
    {"debug",	_DEBUG,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"priority",_PRIORITY,	JSPROP_ENUMERATE,	NULL,	NULL},

    {NULL, 0, 0, NULL, NULL}
};

#define	_RET_B(_bool)	((_bool) > 0 ? JSVAL_TRUE: JSVAL_FALSE)
#define	_RET_S(_str)	\
    ((_str) ? STRING_TO_JSVAL(JS_NewStringCopyZ(cx, (_str))) : JSVAL_NULL)
#define	_GET_S(_test)	((_test) ? _RET_S(_s) : JSVAL_VOID)
#define	_GET_U(_test)	((_test) ? INT_TO_JSVAL(_u) : JSVAL_VOID)
#define	_GET_I(_test)	((_test) ? INT_TO_JSVAL(_i) : JSVAL_VOID)
#define	_GET_B(_test)	((_test) ? _RET_B(_i) : JSVAL_VOID)
#define	_GET_L(_test)	((_test) ? DOUBLE_TO_JSVAL((double)_l) : JSVAL_VOID)

static JSBool
rpmdbc_getprop(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    uint32_t _u = 0;
    jsint tiny = JSVAL_TO_INT(id);

    /* XXX the class has ptr == NULL, instances have ptr != NULL. */
    if (ptr == NULL)
	return JS_TRUE;

    switch (tiny) {
    case _DEBUG:
	*vp = INT_TO_JSVAL(_debug);
	break;
    case _PRIORITY:	*vp = _GET_U(!dbc->get_priority(dbc, (DB_CACHE_PRIORITY *)&_u)); break;

    default:
	break;
    }

    return JS_TRUE;
}

#define	_PUT_S(_put)	(JSVAL_IS_STRING(*vp) && !(_put) \
	? JSVAL_TRUE : JSVAL_FALSE)
#define	_PUT_U(_put)	(JSVAL_IS_INT(*vp) && !(_put) \
	? JSVAL_TRUE : JSVAL_FALSE)
#define	_PUT_I(_put)	(JSVAL_IS_INT(*vp) && !(_put) \
	? JSVAL_TRUE : JSVAL_FALSE)
#define	_PUT_L(_put)	(JSVAL_IS_INT(*vp) && !(_put) \
	? JSVAL_TRUE : JSVAL_FALSE)

static JSBool
rpmdbc_setprop(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
    DBC * dbc = ptr;
    uint32_t _u = 0;
    jsint tiny = JSVAL_TO_INT(id);

    /* XXX the class has ptr == NULL, instances have ptr != NULL. */
    if (ptr == NULL)
	return JS_TRUE;

    if (JSVAL_IS_INT(*vp))
	_u = JSVAL_TO_INT(*vp);

    switch (tiny) {
    case _DEBUG:
	if (!JS_ValueToInt32(cx, *vp, &_debug))
	    break;
	break;
    case _PRIORITY:	*vp = _PUT_U(dbc->set_priority(dbc, (DB_CACHE_PRIORITY)_u));		break;

    default:
	break;
    }

    return JS_TRUE;
}

static JSBool
rpmdbc_resolve(JSContext *cx, JSObject *obj, jsval id, uintN flags,
	JSObject **objp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);

_RESOLVE_DEBUG_ENTRY(_debug < 0);

    if ((flags & JSRESOLVE_ASSIGNING)
     || (ptr == NULL)) { /* don't resolve to parent prototypes objects. */
	*objp = NULL;
	goto exit;
    }

    *objp = obj;	/* XXX always resolve in this object. */

exit:
    return JS_TRUE;
}

static JSBool
rpmdbc_enumerate(JSContext *cx, JSObject *obj, JSIterateOp op,
		  jsval *statep, jsid *idp)
{

_ENUMERATE_DEBUG_ENTRY(_debug < 0);

    switch (op) {
    case JSENUMERATE_INIT:
	*statep = JSVAL_VOID;
        if (idp)
            *idp = JSVAL_ZERO;
        break;
    case JSENUMERATE_NEXT:
	*statep = JSVAL_VOID;
        if (*idp != JSVAL_VOID)
            break;
        /*@fallthrough@*/
    case JSENUMERATE_DESTROY:
	*statep = JSVAL_NULL;
        break;
    }
    return JS_TRUE;
}

/* --- Object ctors/dtors */
static DBC *
rpmdbc_init(JSContext *cx, JSObject *obj)
{
    DBC * dbc = NULL;
#ifdef	NOTYET
    uint32_t _flags = 0;

    if (rpmdbc_env_create(&db, _flags) || dbc == NULL
     || !JS_SetPrivate(cx, obj, (void *)dbc))
#else
    if (!JS_SetPrivate(cx, obj, (void *)dbc))
#endif
    {
#ifdef	NOTYET
	if (dbc)
	    (void) dbc->close(dbc, _flags);
#endif

	/* XXX error msg */
	dbc = NULL;
    }

if (_debug)
fprintf(stderr, "<== %s(%p,%p) dbc %p\n", __FUNCTION__, cx, obj, dbc);

    return dbc;
}

static void
rpmdbc_dtor(JSContext *cx, JSObject *obj)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmdbcClass, NULL);
#ifdef	NOTYET
    DBC * dbc = ptr;
    uint32_t _flags = 0;
#endif

if (_debug)
fprintf(stderr, "==> %s(%p,%p) ptr %p\n", __FUNCTION__, cx, obj, ptr);
#ifdef	NOTYET
    if (db) {
	(void) db->close(db, _flags);
    }
#endif
}

static JSBool
rpmdbc_ctor(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    JSBool ok = JS_FALSE;

if (_debug)
fprintf(stderr, "==> %s(%p,%p,%p[%u],%p)%s\n", __FUNCTION__, cx, obj, argv, (unsigned)argc, rval, ((cx->fp->flags & JSFRAME_CONSTRUCTING) ? " constructing" : ""));

    if (cx->fp->flags & JSFRAME_CONSTRUCTING) {
	(void) rpmdbc_init(cx, obj);
    } else {
	if ((obj = JS_NewObject(cx, &rpmdbcClass, NULL, NULL)) == NULL)
	    goto exit;
	*rval = OBJECT_TO_JSVAL(obj);
    }
    ok = JS_TRUE;

exit:
    return ok;
}

static JSBool
rpmdbc_call(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    /* XXX obj is the global object so lookup "this" object. */
    JSObject * o = JSVAL_TO_OBJECT(argv[-2]);
    void * ptr = JS_GetInstancePrivate(cx, o, &rpmdbcClass, NULL);
#ifdef	NOTYET
    DBC * dbc = ptr;
    const char *_fn = NULL;
    const char * _con = NULL;
#endif
    JSBool ok = JS_FALSE;

#ifdef	NOTYET
    if (!(ok = JS_ConvertArguments(cx, argc, argv, "s", &_fn)))
        goto exit;

    *rval = (dbc && _fn && (_con = rpmdbcLgetfilecon(dbc, _fn)) != NULL)
	? STRING_TO_JSVAL(JS_NewStringCopyZ(cx, _con)) : JSVAL_VOID;
    _con = _free(_con);

    ok = JS_TRUE;

exit:
#endif

if (_debug)
fprintf(stderr, "<== %s(%p,%p,%p[%u],%p) o %p ptr %p\n", __FUNCTION__, cx, obj, argv, (unsigned)argc, rval, o, ptr);

    return ok;
}

/* --- Class initialization */
JSClass rpmdbcClass = {
    "Dbc", JSCLASS_NEW_RESOLVE | JSCLASS_NEW_ENUMERATE | JSCLASS_HAS_PRIVATE,
    rpmdbc_addprop,   rpmdbc_delprop, rpmdbc_getprop, rpmdbc_setprop,
    (JSEnumerateOp)rpmdbc_enumerate, (JSResolveOp)rpmdbc_resolve,
    rpmdbc_convert,	rpmdbc_dtor,

    rpmdbc_getobjectops,	rpmdbc_checkaccess,
    rpmdbc_call,		rpmdbc_construct,
    rpmdbc_xdrobject,	rpmdbc_hasinstance,
    rpmdbc_mark,		rpmdbc_reserveslots,
};

JSObject *
rpmjs_InitDbcClass(JSContext *cx, JSObject* obj)
{
    JSObject *proto;

if (_debug)
fprintf(stderr, "==> %s(%p,%p)\n", __FUNCTION__, cx, obj);

    proto = JS_InitClass(cx, obj, NULL, &rpmdbcClass, rpmdbc_ctor, 1,
		rpmdbc_props, rpmdbc_funcs, NULL, NULL);
assert(proto != NULL);
    return proto;
}

JSObject *
rpmjs_NewDbcObject(JSContext *cx)
{
    JSObject *obj;
    DBC * dbc;

    if ((obj = JS_NewObject(cx, &rpmdbcClass, NULL, NULL)) == NULL) {
	/* XXX error msg */
	return NULL;
    }
    if ((dbc = rpmdbc_init(cx, obj)) == NULL) {
	/* XXX error msg */
	return NULL;
    }
    return obj;
}