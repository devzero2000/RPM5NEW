/** \ingroup js_c
 * \file js/rpmfi-js.c
 */

#include "system.h"

#include "rpmfi-js.h"
#include "rpmhdr-js.h"
#include "rpmjs-debug.h"

#include <argv.h>
#include <mire.h>

#include <rpmdb.h>

#include <rpmfi.h>

#include "debug.h"

/*@unchecked@*/
static int _debug = 0;

/* --- helpers */

/* --- Object methods */

static JSFunctionSpec rpmfi_funcs[] = {
    JS_FS_END
};

/* --- Object properties */
enum rpmfi_tinyid {
    _DEBUG	= -2,
    _LENGTH     = -3,
    _FC		= -4,
    _FX		= -5,
    _DC		= -6,
    _DX		= -7,
    _BN		= -8,
    _DN		= -9,
    _FN		= -10,
    _VFLAGS	= -11,
    _FFLAGS	= -12,
    _FMODE	= -13,
    _FSTATE	= -14,
    _FDIGEST	= -15,
    _FLINK	= -16,
    _FSIZE	= -17,
    _FRDEV	= -18,
    _FMTIME	= -19,
    _FUSER	= -20,
    _FGROUP	= -21,
    _FCOLOR	= -22,
    _FCLASS	= -23,
};

static JSPropertySpec rpmfi_props[] = {
    {"debug",	_DEBUG,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"length",	_LENGTH,	JSPROP_ENUMERATE,	NULL,	NULL},
    {"fc",	_FC,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"fx",	_FX,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"dc",	_DC,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"dx",	_DX,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"bn",	_BN,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"dn",	_DN,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"fn",	_FN,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"vflags",	_VFLAGS,	JSPROP_ENUMERATE,	NULL,	NULL},
    {"fflags",	_FFLAGS,	JSPROP_ENUMERATE,	NULL,	NULL},
    {"fmode",	_FMODE,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"fstate",	_FSTATE,	JSPROP_ENUMERATE,	NULL,	NULL},
    {"fdigest",	_FDIGEST,	JSPROP_ENUMERATE,	NULL,	NULL},
    {"flink",	_FLINK,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"fsize",	_FSIZE,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"frdev",	_FRDEV,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"fmtime",	_FMTIME,	JSPROP_ENUMERATE,	NULL,	NULL},
    {"fuser",	_FUSER,		JSPROP_ENUMERATE,	NULL,	NULL},
    {"fgroup",	_FGROUP,	JSPROP_ENUMERATE,	NULL,	NULL},
    {"fcolor",	_FCOLOR,	JSPROP_ENUMERATE,	NULL,	NULL},
    {"fclass",	_FCLASS,	JSPROP_ENUMERATE,	NULL,	NULL},
    {NULL, 0, 0, NULL, NULL}
};

static JSBool
rpmfi_addprop(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmfiClass, NULL);
_PROP_DEBUG_ENTRY(_debug < 0);
    return JS_TRUE;
}

static JSBool
rpmfi_delprop(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmfiClass, NULL);
_PROP_DEBUG_ENTRY(_debug < 0);
    return JS_TRUE;
}
static JSBool
rpmfi_getprop(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmfiClass, NULL);
    rpmfi fi = ptr;
    jsint tiny = JSVAL_TO_INT(id);
    /* XXX the class has ptr == NULL, instances have ptr != NULL. */
    JSBool ok = (ptr ? JS_FALSE : JS_TRUE);
    int ix;

    switch (tiny) {
    case _DEBUG:
	*vp = INT_TO_JSVAL(_debug);
	ok = JS_TRUE;
	break;
    case _LENGTH:
    case _FC:
	*vp = INT_TO_JSVAL(rpmfiFC(fi));
	ok = JS_TRUE;
	break;
    case _FX:
	*vp = INT_TO_JSVAL(rpmfiFX(fi));
	ok = JS_TRUE;
	break;
    case _DC:
	*vp = INT_TO_JSVAL(rpmfiDC(fi));
	ok = JS_TRUE;
	break;
    case _DX:
	*vp = INT_TO_JSVAL(rpmfiDX(fi));
	ok = JS_TRUE;
	break;
    case _BN:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, rpmfiBN(fi)));
	ok = JS_TRUE;
	break;
    case _DN:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, rpmfiDN(fi)));
	ok = JS_TRUE;
	break;
    case _FN:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, rpmfiFN(fi)));
	ok = JS_TRUE;
	break;
    case _VFLAGS:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = INT_TO_JSVAL(rpmfiVFlags(fi));
	ok = JS_TRUE;
	break;
    case _FFLAGS:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = INT_TO_JSVAL(rpmfiFFlags(fi));
	ok = JS_TRUE;
	break;
    case _FMODE:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = INT_TO_JSVAL(rpmfiFMode(fi));
	ok = JS_TRUE;
	break;
    case _FSTATE:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = INT_TO_JSVAL(rpmfiFState(fi));
	ok = JS_TRUE;
	break;
    case _FDIGEST:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
      {	int dalgo = 0;
	size_t dlen = 0;
	const unsigned char * digest = rpmfiDigest(fi, &dalgo, &dlen);
	const unsigned char * s = digest;
	size_t nb = 2 * dlen;
	char * fdigest = memset(alloca(nb+1), 0, nb+1);
	char *t = fdigest;
	int i;

	for (i = 0, s = digest, t = fdigest; i < (int)dlen; i++, s++, t+= 2) {
	    static const char hex[] = "0123456789abcdef";
	    t[0] = hex[(s[0] >> 4) & 0xf];
	    t[1] = hex[(s[0]     ) & 0xf];
	}
	*t = '\0';
	*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, fdigest));
	ok = JS_TRUE;
      }	break;
    case _FLINK:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, rpmfiFLink(fi)));
	ok = JS_TRUE;
	break;
    case _FSIZE:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = INT_TO_JSVAL(rpmfiFSize(fi));
	ok = JS_TRUE;
	break;
    case _FRDEV:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = INT_TO_JSVAL(rpmfiFRdev(fi));
	ok = JS_TRUE;
	break;
    case _FMTIME:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = INT_TO_JSVAL(rpmfiFMtime(fi));
	ok = JS_TRUE;
	break;
    case _FUSER:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, rpmfiFUser(fi)));
	ok = JS_TRUE;
	break;
    case _FGROUP:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, rpmfiFGroup(fi)));
	ok = JS_TRUE;
	break;
    case _FCOLOR:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
	*vp = INT_TO_JSVAL(rpmfiFColor(fi));
	ok = JS_TRUE;
	break;
    case _FCLASS:
	if ((ix = rpmfiFX(fi)) < 0 || ix >= rpmfiFC(fi)) break;
      {	const char * FClass = rpmfiFClass(fi);
	char * t;
	if (FClass == NULL) FClass = "";
	/* XXX spot fix for known embedded single quotes. */
	t = xstrdup(FClass);
	if (!strncmp(t, "symbolic link to `", sizeof("symbolic link to `")-1))
	   t[sizeof("symbolic link")-1] = '\0';
	*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, t));
	t = _free(t);
	ok = JS_TRUE;
      }	break;
    default:
	if (tiny < 0 || tiny >= rpmfiFC(fi)) break;
	ok = JS_TRUE;
	break;
    }

    if (!ok) {
_PROP_DEBUG_EXIT(_debug);
    }
ok = JS_TRUE;  /* XXX avoid immediate interp exit by always succeeding. */
    return ok;
}

static JSBool
rpmfi_setprop(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmfiClass, NULL);
    rpmfi fi = (rpmfi)ptr;
    jsint tiny = JSVAL_TO_INT(id);
    /* XXX the class has ptr == NULL, instances have ptr != NULL. */
    JSBool ok = (ptr ? JS_FALSE : JS_TRUE);
    int myint;

    switch (tiny) {
    case _DEBUG:
	if (JS_ValueToInt32(cx, *vp, &_debug))
	    ok = JS_TRUE;
	break;
    case _FX:
	if (!JS_ValueToInt32(cx, *vp, &myint))
	    break;
	if (myint != rpmfiFX(fi)) {
	    (void) rpmfiSetFX(fi, myint-1);
	    /* XXX flush and recreate {BN,DN,FN} with a rpmfiNext() step */
	    (void) rpmfiNext(fi);
	}
	ok = JS_TRUE;
	break;
    case _DX:
	if (!JS_ValueToInt32(cx, *vp, &myint))
	    break;
	if (myint != rpmfiDX(fi)) {
	    (void) rpmfiSetDX(fi, myint-1);
	    /* XXX flush and recreate {BN,DN,FN} with a rpmfiNextD() step */
	    (void) rpmfiNextD(fi);
	}
	ok = JS_TRUE;
	break;
    default:
	break;
    }

    if (!ok) {
_PROP_DEBUG_EXIT(_debug);
    }
ok = JS_TRUE;  /* XXX avoid immediate interp exit by always succeeding. */
    return ok;
}

static JSBool
rpmfi_resolve(JSContext *cx, JSObject *obj, jsval id, uintN flags,
	JSObject **objp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmfiClass, NULL);
    rpmfi fi = ptr;
    JSBool ok = JS_FALSE;
    int ix;

_RESOLVE_DEBUG_ENTRY(_debug);

    if ((flags & JSRESOLVE_ASSIGNING)
     || (fi == NULL)) { /* don't resolve to parent prototypes objects. */
	*objp = NULL;
	ok = JS_TRUE;
	goto exit;
    }

    if (JSVAL_IS_INT(id)
     && (ix = JSVAL_TO_INT(id)) >= 0 && ix < rpmfiFC(fi))
    {
	JSObject * arr = JS_NewArrayObject(cx, 1, NULL);
	JSString *valstr;

	if (ix != rpmfiFX(fi)) {
if (_debug < 0)
fprintf(stderr, "\trpmfiSetFX(%p, %d)\n", fi, ix);
	    (void) rpmfiSetFX(fi, ix-1);
	    (void) rpmfiNext(fi);
	}

	if (!JS_DefineElement(cx, obj, ix, OBJECT_TO_JSVAL(arr),
			NULL, NULL, JSPROP_ENUMERATE))
	    goto exit;
	if ((valstr = JS_NewStringCopyZ(cx, rpmfiFN(fi))) == NULL
	 || !JS_DefineElement(cx, arr, 0, STRING_TO_JSVAL(valstr),
			NULL, NULL, JSPROP_ENUMERATE))
	    goto exit;
	*objp = obj;
    } else
	*objp = NULL;

    ok = JS_TRUE;
exit:
    return ok;
}

static JSBool
rpmfi_enumerate(JSContext *cx, JSObject *obj, JSIterateOp op,
		  jsval *statep, jsid *idp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmfiClass, NULL);
    rpmfi fi = ptr;
    JSBool ok = JS_FALSE;
    int ix;

_ENUMERATE_DEBUG_ENTRY(_debug);

    switch (op) {
    case JSENUMERATE_INIT:
	*statep = JSVAL_VOID;
	(void) rpmfiInit(fi, 0);
	if (idp)
	    *idp = JSVAL_ZERO;
	break;
    case JSENUMERATE_NEXT:
	*statep = JSVAL_VOID;
	if ((ix = rpmfiNext(fi)) >= 0) {
	    JS_ValueToId(cx, INT_TO_JSVAL(ix), idp);
	} else
	    *idp = JSVAL_VOID;
	if (*idp != JSVAL_VOID)
	    break;
	/*@fallthrough@*/
    case JSENUMERATE_DESTROY:
	*statep = JSVAL_NULL;
	break;
    }
    ok = JS_TRUE;
    return ok;
}

static JSBool
rpmfi_convert(JSContext *cx, JSObject *obj, JSType type, jsval *vp)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmfiClass, NULL);
_CONVERT_DEBUG_ENTRY(_debug);
    return JS_TRUE;
}

/* --- Object ctors/dtors */
static rpmfi
rpmfi_init(JSContext *cx, JSObject *obj, rpmts ts, Header h, int _tagN)
{
    rpmfi fi;
    int flags = 0;

    if ((fi = rpmfiNew(ts, h, _tagN, flags)) == NULL)
	return NULL;
    if (!JS_SetPrivate(cx, obj, (void *)fi)) {
	/* XXX error msg */
	(void) rpmfiFree(fi);
	return NULL;
    }
    return fi;
}

static void
rpmfi_dtor(JSContext *cx, JSObject *obj)
{
    void * ptr = JS_GetInstancePrivate(cx, obj, &rpmfiClass, NULL);
    rpmfi fi = ptr;

if (_debug)
fprintf(stderr, "==> %s(%p,%p) ptr %p\n", __FUNCTION__, cx, obj, ptr);

    (void) rpmfiFree(fi);
}

static JSBool
rpmfi_ctor(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    JSBool ok = JS_FALSE;
    rpmts ts = NULL;	/* XXX FIXME: should be a ts method? */
    JSObject *hdro = NULL;
    int tagN = RPMTAG_BASENAMES;

if (_debug)
fprintf(stderr, "==> %s(%p,%p,%p[%u],%p)\n", __FUNCTION__, cx, obj, argv, (unsigned)argc, rval);

    if (!(ok = JS_ConvertArguments(cx, argc, argv, "o/i", &hdro, &tagN)))
	goto exit;

    if (cx->fp->flags & JSFRAME_CONSTRUCTING) {
	Header h = JS_GetInstancePrivate(cx, hdro, &rpmhdrClass, NULL);
	if (rpmfi_init(cx, obj, ts, h, tagN) == NULL)
	    goto exit;
    } else {
	if ((obj = JS_NewObject(cx, &rpmfiClass, NULL, NULL)) == NULL)
	    goto exit;
	*rval = OBJECT_TO_JSVAL(obj);
    }
    ok = JS_TRUE;

exit:
    return ok;
}

/* --- Class initialization */
JSClass rpmfiClass = {
    "Fi", JSCLASS_NEW_RESOLVE | JSCLASS_NEW_ENUMERATE | JSCLASS_HAS_PRIVATE,
    rpmfi_addprop, rpmfi_delprop, rpmfi_getprop, rpmfi_setprop,
    (JSEnumerateOp)rpmfi_enumerate, (JSResolveOp)rpmfi_resolve,
    rpmfi_convert,	rpmfi_dtor,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

JSObject *
rpmjs_InitFiClass(JSContext *cx, JSObject* obj)
{
    JSObject * o;

if (_debug)
fprintf(stderr, "==> %s(%p,%p)\n", __FUNCTION__, cx, obj);

    o = JS_InitClass(cx, obj, NULL, &rpmfiClass, rpmfi_ctor, 1,
		rpmfi_props, rpmfi_funcs, NULL, NULL);
assert(o != NULL);
    return o;
}

JSObject *
rpmjs_NewFiObject(JSContext *cx, void * _h, int _tagN)
{
    JSObject *obj;
    rpmts ts = NULL;	/* XXX FIXME: should be a ts method? */
    rpmfi fi;

    if ((obj = JS_NewObject(cx, &rpmfiClass, NULL, NULL)) == NULL) {
	/* XXX error msg */
	return NULL;
    }
    if ((fi = rpmfi_init(cx, obj, ts, _h, _tagN)) == NULL) {
	/* XXX error msg */
	return NULL;
    }
    return obj;
}