# xseturgent - set an applications urgency hint (or not)
# See LICENSE file for copyright and license details.

include config.mk

SRC = xseturgent.c
OBJ = ${SRC:.c=.o}

all: options xseturgent

options:
	@echo xseturgent build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

xseturgent: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f xseturgent ${OBJ} xseturgent-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p xseturgent-${VERSION}
	@cp -R LICENSE Makefile config.mk \
		xseturgent.1 ${SRC} xseturgent-${VERSION}
	@tar -cf xseturgent-${VERSION}.tar xseturgent-${VERSION}
	@gzip xseturgent-${VERSION}.tar
	@rm -rf xseturgent-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f xseturgent ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/xseturgent
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < xseturgent.1 > ${DESTDIR}${MANPREFIX}/man1/xseturgent.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/xseturgent.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/xseturgent
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/xseturgent.1

.PHONY: all options clean dist install uninstall
