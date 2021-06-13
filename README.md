[![CI](https://github.com/lpenz/xseturgent/actions/workflows/ci.yml/badge.svg)](https://github.com/lpenz/xseturgent/actions/workflows/ci.yml)
[![coveralls](https://coveralls.io/repos/github/lpenz/xseturgent/badge.svg?branch=main)](https://coveralls.io/github/lpenz/xseturgent?branch=main)
[![packagecloud](https://img.shields.io/badge/deb-packagecloud.io-844fec.svg)](https://packagecloud.io/app/lpenz/debian/search?q=xseturgent)

xseturgent
==========

xseturgent is a tool that sets/clears the urgency hint of a window in X11


## Usage

~~~[.sh]
xseturgent -h
xseturgent -V
xseturgent [-i <windowid>] [-t <set/reset/toggle>]
~~~

### Options

**-h** Help.

**-V** Version information.

**-v** Verbose, show files changed.

**-i windowid** The window ID, in decimal or hex. If not provided, use
   the WINDOWID environment variable by default; fails if that doesn't
   exist.

**-t <set/reset/toggle>** What to do with the urgency hint.

