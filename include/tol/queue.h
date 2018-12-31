#pragma once

#ifdef _QUEUE_HAS_ASSERT
#include <assert.h>
#define $Q_assert(x) assert(x)
#else
#define $Q_assert(x)
#endif

#ifndef _QUEUE_NODE
#ifndef _QUEUE_NODE_STRUCT
#define _QUEUE_NODE_STRUCT queue_node
#endif
struct _QUEUE_NODE_STRUCT
{
	struct _QUEUE_NODE_STRUCT *next;
#ifdef _QUEUE_CONTENTS
	_QUEUE_CONTENTS;
#endif
};
#define _QUEUE_NODE		struct _QUEUE_NODE_STRUCT
#endif

#ifndef _QUEUE_HEAD
#ifndef _QUEUE_HEAD_STRUCT
#define _QUEUE_HEAD_STRUCT queue_head
#endif
struct _QUEUE_HEAD_STRUCT
{
	_QUEUE_NODE *head, *last;
#ifdef _QUEUE_HEAD_CONTENTS
	_QUEUE_HEAD_CONTENTS;
#endif
};
#define _QUEUE_HEAD		struct _QUEUE_HEAD_STRUCT
#endif

#ifndef _QUEUE_PREF
#define _QUEUE_PREF		queue_
#endif

#ifndef _Q_PREF
#define _Q_PREF
#endif

#define $Q____METCATPRF(pref, x) pref##x
#define $Q___METCATPRF(pref, x) $Q____METCATPRF(pref, x)
#define $Q__METCATPRF(pref, x) $Q___METCATPRF(pref, x)
#define $Q_METCATPRF(pref, x) $Q__METCATPRF(pref, x)
#define $Q(x)	$Q_METCATPRF(_Q_PREF, x)
#define $QME(x)	$Q_METCATPRF(_QUEUE_PREF, x)


static _QUEUE_NODE *$QME(pop)(_QUEUE_HEAD *q)
{
	_QUEUE_NODE *n = q->$Q(head);
	q->$Q(head) = n->$Q(next);
	if (!q->$Q(head))
		q->$Q(last) = q->$Q(head) = 0;
	return n;
}

static int $QME(append)(_QUEUE_HEAD *q, _QUEUE_NODE *n)
{
	if (!q->$Q(head)) {
		$Q_assert(!q->$Q(last));
		q->$Q(head) = n;
		q->$Q(last) = 0;
		n->$Q(next) = 0;
		return 0;
	}
	if (!q->$Q(last)) {
		q->$Q(head)->$Q(next) = n;
		q->$Q(last) = n;
	}

	q->$Q(last)->$Q(next) = n;
	n->$Q(next) = q->$Q(last);
	return 1;
}

static int $QME(empty)(_QUEUE_HEAD *q)
{
	if (!q->$Q(head)) {
		$Q_assert(!q->$Q(last));
		return 1;
	}
	return 0;
}

#undef $Q
#undef $QME
#undef $Q_METCATPRF
#undef _QUEUE_HAS_ASSERT
#undef _QUEUE_NODE
#undef _QUEUE_NODE_STRUCT
#undef _QUEUE_HEAD
#undef _QUEUE_HEAD_STRUCT
#undef _QUEUE_PREF
#undef _Q_PREF
