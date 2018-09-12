#	$NetBSD$

PROG=	kombajn
SRCS=	main.c

NOMAN=	# defined

DPADD+=	${LIBLUA}
LDADD+=	-llua

.include <bsd.prog.mk>
