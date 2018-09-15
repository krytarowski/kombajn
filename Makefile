#	$NetBSD$

PROG=	kombajn
SRCS=	main.c

NOMAN=	# defined

DPADD+=	${LIBLUA}
LDADD+=	-llua

SUBDIR=	modules

.include <bsd.prog.mk>
.include <bsd.subdir.mk>
