/******************************************************************************
 *	Copyright 2008-2013 by Aerospike.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy 
 *	of this software and associated documentation files (the "Software"), to 
 *	deal in the Software without restriction, including without limitation the 
 *	rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 *	sell copies of the Software, and to permit persons to whom the Software is 
 *	furnished to do so, subject to the following conditions:
 * 
 *	The above copyright notice and this permission notice shall be included in 
 *	all copies or substantial portions of the Software.
 * 
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 *	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *	IN THE SOFTWARE.
 *****************************************************************************/

#include <aerospike/as_iterator.h>
#include <aerospike/as_linkedlist.h>
#include <aerospike/as_linkedlist_iterator.h>

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 *	EXTERNS
 ******************************************************************************/

extern const as_iterator_hooks as_linkedlist_iterator_hooks;

/******************************************************************************
 *	FUNCTIONS
 *****************************************************************************/

as_linkedlist_iterator * as_linkedlist_iterator_init(as_linkedlist_iterator * iterator, const as_linkedlist * l)
{
	if ( !iterator ) return iterator;
	
	as_iterator_init((as_iterator *) iterator, false, NULL, &as_linkedlist_iterator_hooks);
	iterator->list = l;
	return iterator;
}

as_linkedlist_iterator * as_linkedlist_iterator_new(const as_linkedlist * l) 
{
	as_linkedlist_iterator * iterator = (as_linkedlist_iterator *) malloc(sizeof(as_linkedlist_iterator));
	if ( !iterator ) return iterator;

	as_iterator_init((as_iterator *) iterator, true, NULL, &as_linkedlist_iterator_hooks);
	iterator->list = l;
	return iterator;
}

bool as_linkedlist_iterator_release(as_linkedlist_iterator * iterator) 
{
	iterator->list = NULL;
	return true;
}

void as_linkedlist_iterator_destroy(as_linkedlist_iterator * iterator) 
{
	as_iterator_destroy((as_iterator *) iterator);
}

bool as_linkedlist_iterator_has_next(const as_linkedlist_iterator * iterator) 
{
	return iterator && iterator->list && iterator->list->head;
}

const as_val * as_linkedlist_iterator_next(as_linkedlist_iterator * iterator) 
{
	as_val * head = NULL;
	if ( iterator->list ) {
		head = iterator->list->head;
		if ( iterator->list->tail ) {
			iterator->list = iterator->list->tail;
		}
		else {
			iterator->list = 0;
		}
	}
	return head;
}
