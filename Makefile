# seturgent - set an applications urgency hint (or not)
# See LICENSE file for copyright and license details.

include config.mk

SRC = seturgent.c
OBJ = ${SRC:.c=.o}

all: options seturgent

options:
	@echo seturgent build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

seturgent: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

readme:
	@echo creating README
	@groff -T utf8 -man < seturgent.1 | col -bx | \
		sed "s@VERSION@${VERSION}@g" > README

clean:
	@echo cleaning
	@rm -f seturgent ${OBJ} seturgent-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p seturgent-${VERSION}
	@cp -R LICENSE Makefile config.mk \
		seturgent.1 ${SRC} seturgent-${VERSION}
	@tar -cf seturgent-${VERSION}.tar seturgent-${VERSION}
	@gzip seturgent-${VERSION}.tar
	@rm -rf seturgent-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f seturgent ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/seturgent
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < seturgent.1 > ${DESTDIR}${MANPREFIX}/man1/seturgent.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/seturgent.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/seturgent
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/seturgent.1

.PHONY: all readme options clean dist install uninstall
