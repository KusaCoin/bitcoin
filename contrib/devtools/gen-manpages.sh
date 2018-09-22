#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

KUSACOIND=${KUSACOIND:-$SRCDIR/kusacoind}
KUSACOINCLI=${KUSACOINCLI:-$SRCDIR/kusacoin-cli}
KUSACOINTX=${KUSACOINTX:-$SRCDIR/kusacoin-tx}
KUSACOINQT=${KUSATCOINQT:-$SRCDIR/qt/kusacoin-qt}

[ ! -x $KUSACOIND ] && echo "$KUSACOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
KUSAVER=($($KUSACOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for kusacoind if --version-string is not set,
# but has different outcomes for kusacoin-qt and kusacoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$KUSACOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $KUSACOIND $KUSACOINCLI $KUSACOINTX $KUSACOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${KUSAVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${KUSAVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
