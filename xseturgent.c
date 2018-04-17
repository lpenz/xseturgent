/****************************************************************************/
/**
 * \file
 * \brief xseturgent is a tool that sets/clears the urgency hint of a
 * window in X11
 *
 * See LICENSE file for copyright and license details.
 */
/****************************************************************************/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROGRAM_NAME "xseturgent"
#define PROGRAM_VERSION "2.0"

enum op {
    URGENT_SET,
    URGENT_RESET,
    URGENT_TOGGLE,
};

static int xseturgent_window(bool verbose, Display *dpy, Window winid,
                             enum op op) {
    int ret = 0;
    XWMHints *hints = XGetWMHints(dpy, winid);
    if (!hints) {
        fprintf(stderr, "Unable to get window manager hints.\n");
        return 20;
    }
    if (verbose)
        printf("Window 0x%08lx has hint->flags 0x%08lx\n", winid, hints->flags);
    switch (op) {
        case URGENT_SET:
            hints->flags |= XUrgencyHint;
            break;
        case URGENT_RESET:
            hints->flags &= ~XUrgencyHint;
            break;
        case URGENT_TOGGLE:
            if (hints->flags | XUrgencyHint) {
                hints->flags |= XUrgencyHint;
            } else {
                hints->flags &= ~XUrgencyHint;
            }
            break;
    }
    if (verbose)
        printf("Window 0x%08lx setting hint->flags 0x%08lx\n", winid,
               hints->flags);
    if (!XSetWMHints(dpy, winid, hints)) {
        fprintf(stderr, "Unable to set urgency hint.\n");
        ret = 30;
    }
    if (verbose) printf("Freeing hints\n");
    XFree(hints);

    return ret;
}

static int error_handler(Display *d, XErrorEvent *e) {
    char msg[80];
    XGetErrorText(d, e->error_code, msg, sizeof(msg));
    fprintf(stderr, "Error %d (%s) on request %d.%d\n", e->error_code, msg,
            e->request_code, e->minor_code);
    return 0;
}

static int xseturgent(bool verbose, Window windowid, int urgent) {
    Display *dpy;
    int ret = 0;

    if (verbose) printf("Setting error handler\n");
    XSetErrorHandler(error_handler);

    if (verbose) printf("Opening display\n");
    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "Unable to open display.\n");
        return 10;
    }

    ret = xseturgent_window(verbose, dpy, windowid, urgent);

    if (verbose) printf("Closing display\n");
    XCloseDisplay(dpy);

    return ret;
}

/****************************************************************************/

const char USAGE[] =
    "Usage: " PROGRAM_NAME
    " [-V] [-v] [-h] [-i windowid] [-t operation]\n"
    "Change urgent hint of a window in X\n"
    "    -h             This help.\n"
    "    -V             Version information.\n"
    "    -v             Verbose mode.\n"
    "    -i <windowid>  Specify the window;"
    " default is WINDOWID environment variable\n"
    "    -t <operation> Operation is set, reset or toggle; default is set\n";

/****************************************************************************/

int main(int argc, char *argv[]) {
    bool verbose = false;
    Window windowid = LONG_MAX;
    enum op op = URGENT_SET;

    const char *windowidEnv = getenv("WINDOWID");
    if (windowidEnv) {
        windowid = strtol(windowidEnv, NULL, 0);
    }

    const char options[] = "i:t:hvV";
    int opt;
    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
            case 'i':
                windowid = strtol(optarg, NULL, 0);
                break;
            case 't':
                if (strcmp(optarg, "set") == 0) {
                    op = URGENT_SET;
                } else if (strcmp(optarg, "reset") == 0) {
                    op = URGENT_RESET;
                } else if (strcmp(optarg, "toggle") == 0) {
                    op = URGENT_TOGGLE;
                } else {
                    fprintf(stderr, "Invalid operation type %s.\n%s", optarg,
                            USAGE);
                    return 1;
                }
                break;
            case 'h':
                printf("%s", USAGE);
                return 0;
            case 'v':
                verbose = true;
                break;
            case 'V':
                printf("%s %s\n", PROGRAM_NAME, PROGRAM_VERSION);
                return 0;
            case '?':
                fprintf(stderr, "Unknown option/command.\n%s", USAGE);
                return 1;
            default:
                fprintf(stderr, "Error: option/command not found!\n%s", USAGE);
                return 1;
        }
    }

    if (argc - optind != 0) {
        fprintf(stderr, "Invalid number of arguments.\n%s", USAGE);
        return 1;
    }

    if (windowid == LONG_MAX) {
        fprintf(stderr,
                "Window id discovery failed, please specify one with -i\n%s",
                USAGE);
        return 2;
    }
    return xseturgent(verbose, windowid, op);
}
