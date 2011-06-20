/* 
**  mod_servertime.c -- Apache sample servertime module
**  [Autogenerated via ``apxs -n servertime -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_servertime.c
**
**  Then activate it in Apache's httpd.conf file for instance
**  for the URL /servertime in as follows:
**
**    #   httpd.conf
**    LoadModule servertime_module modules/mod_servertime.so
**    <Location /servertime>
**    SetHandler servertime
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /servertime and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/servertime 
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**  
**    The sample page from mod_servertime.c
*/ 

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

#include <inttypes.h>

/* The sample content handler */
static int servertime_handler(request_rec *r)
{
    if (strcmp(r->handler, "servertime")) {
        return DECLINED;
    }
    r->content_type = "text/plain";

    if (r->header_only)
        return OK;

    struct timeval t;
    gettimeofday(&t, NULL);
    uint64_t restime = 0;

    restime = t.tv_sec * 1000;
    restime += t.tv_usec / 1000;

    ap_rprintf(r, "%"PRIu64"\n", restime);

    return OK;
}

static void servertime_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(servertime_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA servertime_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    servertime_register_hooks  /* register hooks                      */
};

