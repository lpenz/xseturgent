[![Build Status](https://travis-ci.org/lpenz/xseturgent.png?branch=master)](https://travis-ci.org/lpenz/xseturgent) 

xseturgent
==========

# About

xseturgent is a tool that sets/clears the urgency hint of a window in X11


# Usage

~~~[.sh]
xseturgent <windowid> [0|1]
~~~

## Options

**windowid** The window ID, in decimal or hex.

**0|1** 1 to set (default) or 0 to clear.

