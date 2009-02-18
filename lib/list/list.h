#ifndef _LIST_H
#define _LIST_H

struct list_item {
	struct list_item *prev, *next;
};

struct list {
	struct list_item head;
};

#ifndef container_of
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#define list_for_each(list, pos) \
	for (pos = (list)->head.next; pos != ((list)->head); pos = pos->next)

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_for_each_entry(list, pos, member)				\
	for (pos = list_entry((list)->head.next, typeof(*pos), member);	\
	     &pos->member != &(list)->head; 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

void list_init(struct list *list);
void list_insert_before(struct list_item *next, struct list_item *new);
void list_insert_after(struct list_item *prev, struct list_item *new);
void list_remove(struct list_item *item);

static inline void list_add(struct list *list, struct list_item *new)
{
	list_insert_after(&list->head, new);
}
static inline void list_add_tail(struct list *list, struct list_item *new)
{
	list_insert_before(&list->head, new);
}

#endif /* _LIST_H */