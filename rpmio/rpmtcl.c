#include "system.h"

#ifdef	WITH_TCL
#define _RPMTCL_INTERNAL
#include "rpmtcl.h"

#include "debug.h"

/*@unchecked@*/
int _rpmtcl_debug = 0;

static void rpmtclFini(void * _tcl)
        /*@globals fileSystem @*/
        /*@modifies *_tcl, fileSystem @*/
{
    rpmtcl tcl = _tcl;

    tcl->fn = _free(tcl->fn);
    tcl->flags = 0;
#if defined(WITH_TCL)
    Tcl_DeleteInterp(tcl->I);
#endif
    tcl->I = NULL;
    (void)rpmiobFree(tcl->iob);
    tcl->iob = NULL;
}

/*@unchecked@*/ /*@only@*/ /*@null@*/
rpmioPool _rpmtclPool;

static rpmtcl rpmtclGetPool(/*@null@*/ rpmioPool pool)
        /*@globals _rpmtclPool, fileSystem @*/
        /*@modifies pool, _rpmtclPool, fileSystem @*/
{
    rpmtcl tcl;

    if (_rpmtclPool == NULL) {
        _rpmtclPool = rpmioNewPool("tcl", sizeof(*tcl), -1, _rpmtcl_debug,
                        NULL, NULL, rpmtclFini);
        pool = _rpmtclPool;
    }
    return (rpmtcl) rpmioGetPool(pool, sizeof(*tcl));
}

#if defined(WITH_TCL)
static int rpmtclIOclose(ClientData CD, Tcl_Interp *I)
	/*@*/
{
if (_rpmtcl_debug)
fprintf(stderr, "==> %s(%p, %p)\n", __FUNCTION__, CD, I);
    return 0;
}

static int rpmtclIOread(ClientData CD, char *b, int nb, int *errnop)
	/*@*/
{
if (_rpmtcl_debug)
fprintf(stderr, "==> %s(%p, %p[%d], %p)\n", __FUNCTION__, CD, b, nb, errnop);
    *errnop = EINVAL;
    return -1;
}

static int rpmtclIOwrite(ClientData CD, const char *b, int nb, int *errnop)
	/*@*/
{
    rpmtcl tcl = (rpmtcl) CD;
if (_rpmtcl_debug)
fprintf(stderr, "==> %s(%p, %p[%d], %p)\n", __FUNCTION__, CD, b, nb, errnop);
    (void) rpmiobAppend(tcl->iob, b, (size_t)nb);
    return nb;
}

static int rpmtclIOseek(ClientData CD, long off, int mode, int *errnop)
	/*@*/
{
if (_rpmtcl_debug)
fprintf(stderr, "==> %s(%p, %ld, %d, %p)\n", __FUNCTION__, CD, off, mode, errnop);
    *errnop = EINVAL;
    return -1;
}

static Tcl_ChannelType rpmtclIO = {
    "rpmtclIO",			/* Type name */
    TCL_CHANNEL_VERSION_2,	/* Tcl_ChannelTypeVersion */
    rpmtclIOclose,		/* Tcl_DriverCloseProc */
    rpmtclIOread,		/* Tcl_DriverInputProc */
    rpmtclIOwrite,		/* Tcl_DriverOutputProc */
    rpmtclIOseek,		/* Tcl_DriverSeekProc */
    NULL,			/* Tcl_DriverSetOptionProc */
    NULL,			/* Tcl_DriverGetOptionProc */
    NULL,			/* Tcl_DriverWatchProc */
    NULL,			/* Tcl_DriverGetHandleProc */
    NULL,			/* Tcl_DriverClose2Proc */
    NULL,			/* Tcl_DriverBlockModeProc */
    NULL,			/* Tcl_DriverFlushProc */
    NULL,			/* Tcl_DriverHandlerProc */
    NULL,			/* Tcl_DriverWideSeekProc */
    NULL,			/* Tcl_DriverThreadActionProc */
    NULL,			/* Tcl_DriverTruncateProc */
};
#endif

rpmtcl rpmtclNew(const char * fn, int flags)
{
    rpmtcl tcl = rpmtclGetPool(_rpmtclPool);

    if (fn)
	tcl->fn = xstrdup(fn);
    tcl->flags = flags;

#if defined(WITH_TCL)
    tcl->I = Tcl_CreateInterp();
    tcl->tclout = Tcl_GetStdChannel(TCL_STDOUT);
    Tcl_SetChannelOption(tcl->I, tcl->tclout, "-translation", "auto");
    Tcl_StackChannel(tcl->I, &rpmtclIO, tcl, TCL_WRITABLE, tcl->tclout);
#endif
    tcl->iob = rpmiobNew(0);

    return rpmtclLink(tcl);
}

rpmRC rpmtclRunFile(rpmtcl tcl, const char * fn, const char ** resultp)
{
    rpmRC rc = RPMRC_FAIL;

if (_rpmtcl_debug)
fprintf(stderr, "==> %s(%p,%s)\n", __FUNCTION__, tcl, fn);

#if defined(WITH_TCL)
    if (fn != NULL && Tcl_EvalFile(tcl->I, fn) == TCL_OK) {
	rc = RPMRC_OK;
	if (resultp)
	    *resultp = rpmiobStr(tcl->iob);
    }
#endif
    return rc;
}

rpmRC rpmtclRun(rpmtcl tcl, const char * str, const char ** resultp)
{
    rpmRC rc = RPMRC_FAIL;

if (_rpmtcl_debug)
fprintf(stderr, "==> %s(%p,%s)\n", __FUNCTION__, tcl, str);

#if defined(WITH_TCL)
    if (str != NULL && Tcl_Eval(tcl->I, str) == TCL_OK) {
	rc = RPMRC_OK;
	if (resultp)
	    *resultp = rpmiobStr(tcl->iob);
    }
#endif
    return rc;
}
#endif	/* WITH_TCL */