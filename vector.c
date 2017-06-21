#include <stdlib.h>
#include "vector.h"

MY_VECTOR vector_init_default(void)
{
	Vector* pVector = (Vector*) malloc(sizeof(Vector));
	if (pVector != NULL)
	{
		//worked
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (Item*)malloc(sizeof(Item) * pVector->capacity);
		if (pVector->data == NULL)
		{
			//object is half created and we have an error
			free(pVector);
			pVector = NULL;
		}
	}
	return (MY_VECTOR)pVector;
}

Status vector_push_back(MY_VECTOR hVector, Item item)
{
	Vector* pVector = (Vector*) hVector;
	Item* temp;
	int i;

	if (pVector->size >= pVector->capacity) //no room
	{
		temp = (Item*) malloc(sizeof(Item)* pVector->capacity * 2);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pVector->size; i++)
		{
			temp[i] = pVector->data[i];
		}
		free(pVector->data);
		pVector->data = temp;
		pVector->capacity *= 2;
	}
	pVector->data[pVector->size] = item;
	pVector->size++;
	return SUCCESS;
}

int vector_get_size(MY_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->size;
}
int vector_get_capacity(MY_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->capacity;
}

Boolean vector_empty(MY_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;

	return (Boolean) (pVector->size == 0);
}

Item* vector_at(MY_VECTOR hVector, unsigned int index)
{
	Vector* pVector = (Vector*)hVector;

	if (index >= pVector->size) //out of bounds
	{
		return NULL;
	}

	return &(pVector->data[index]);
}

Status vector_pop_back(MY_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;

	if (pVector->size == 0)
	{
		return FAILURE;
	}
	pVector->size--;
	return SUCCESS;
}

void vector_destroy(MY_VECTOR* phVector)
{
	Vector* pVector = (Vector*) *phVector;

	free(pVector->data);
	free(pVector);
	*phVector = NULL;
}