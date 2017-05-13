/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

static void
die(const char *s) {
	fputs(s, stderr);
	exit(EXIT_FAILURE);
}

static int
seturgency(Display *dpy, Window winid, Bool set) {
	int ret = EXIT_SUCCESS;
	XWMHints *hints = XGetWMHints(dpy, winid);
	if(!hints) {
		fputs("seturgent: unable to get window manager hints.\n", stderr);
		return EXIT_FAILURE;
	}
	if(set)
		hints->flags |= XUrgencyHint;
	else
		hints->flags &= ~XUrgencyHint;
	if(!XSetWMHints(dpy, winid, hints)) {
		fputs("seturgent: unable to set urgency hint.\n", stderr);
		ret = EXIT_FAILURE;
	}
	XFree(hints);
	return ret;
}

int
main(int argc, char **argv) {
	Display *dpy;
	int ret = EXIT_SUCCESS;

	if(argc < 2 || !strcmp(argv[1], "-h")) /* help / usage */
		die("Usage: seturgent <winid> [0|1]\n");
	if(argc == 2 && !strcmp(argv[1], "-v")) /* version */
		die("seturgent-"VERSION" © 2010-2017 seturgent engineer, see " \
		    "LICENSE file for details.\n");
	if(!(dpy = XOpenDisplay(NULL)))
		die("seturgent: unable to open display.\n");
	/* set the urgency hint (or not), if not specified its True. */
	ret = seturgency(dpy, (Window)strtol(argv[1], NULL, 0),
	           !((argc > 2) && !atol(argv[2])));
	XSync(dpy, False);
	XCloseDisplay(dpy);
	return ret;
}
