#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

//Precondition: none
//Postcondition: Allocate space for a string object that represents the empty
// string. The string will have capacity 7 and size 0 by default. A copy of
// the address of the opaque object will be returned on success and NULL on
// failure.
MY_STRING my_string_init_default(void)
{
  My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
  if(pMy_string != NULL)
    {
      pMy_string->size = 0;
      pMy_string->capacity = 7;
      pMy_string->data = (char*)malloc(sizeof(char) * pMy_string->capacity);
      if(pMy_string->data == NULL)
	{
	  free(pMy_string);
	  pMy_string = NULL;
	}
    }
  return (MY_STRING)pMy_string;
  
}

//Precondition: c_string is a valid null terminated c-string.
//Postcondition: Allocate space for a string object that represents a string with
// the same value as the given c-string. The capacity of the string object will
// be set to be one greater than is required to hold the string. As an example,
// the string "the" would set capacity to 4 instead of 3. A copy of the address
// of the opaque object will be returned on success and NULL on failure.
MY_STRING my_string_init_c_string(const char* c_string)
{
  int i;
  My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
  if(pMy_string != NULL)
    {
      for(i = 0; c_string[i] != '\0'; i++);
      pMy_string->size = i;
      pMy_string->capacity = i + 1;
      pMy_string->data = (char*)malloc(sizeof(char) * pMy_string->capacity);
      if(pMy_string->data == NULL)
	{
	  free(pMy_string);
	  pMy_string = NULL;
	}
      for(i = 0; c_string[i] != '\0'; i++)
	{
	  pMy_string->data[i] = c_string[i];
	}
    }
  return (MY_STRING)pMy_string;
}

//Precondition:hMy_string is the handle of a valid My_string object.
//Postcondition: Returns a copy of the integer value of the object's capacity.
int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;
  return pMy_string->capacity;
}

//Precondition:hMy_string is the handle of a valid My_string object.
//Postcondition: Returns a copy of the integer value of the object's size.
int my_string_get_size(MY_STRING hMy_string)
{
   My_string* pMy_string = (My_string*)hMy_string;
   return pMy_string->size;
}


//Precondition: hLeft_string and hRight_string are valid My_string objects.
//Postcondition: returns an integer less than zero if the string is represented
// by hLeft_string is lexicographically smaller than hRight_string. If one string
// is a prefix of the other string then the shorter string is considered to be the
// smaller one (ie. app is less than apple). Returns 0 of the strings are the same
// and returns a number greater than zero if the string represented by
// hLeft_string is bigger than hRight_string.
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  int i = 0;
  if(hLeft_string == NULL || hRight_string == NULL){
	  return 0;
  }
  My_string* pLeft_string = (My_string*)hLeft_string;
  My_string* pRight_string = (My_string*)hRight_string;
  Boolean mismatched = FALSE;
  for(i = 0; i < pLeft_string->size && i < pRight_string->size; i++){
	  if(pLeft_string->data[i] != pRight_string->data[i]){
		  mismatched = TRUE;
		  break;
	  }
  }
  if(mismatched){
	  return pLeft_string->data[i] - pRight_string->data[i];
  }
  else{
	  if(pLeft_string->size == pRight_string->size){
		  return 0;
	  }
	  else{
		  if(pLeft_string->size > pRight_string->size){
			  return 1;
		  }
		  else{
			  // if(pLeft_string->size < pRight_string->size)
				  return -1;
		  }
	  }
  }
}

//Precondition: hMy_string is the handle to a valid My_String object.
//Postcondition: hMy_string will be the handle of a string object that contains
// the next string from the file stream fp according to the following rules.
// 1) Leading whitespace will be ignored
// 2) All characters (after the first non-whitespace  character is obtained and
// included) will be added to the string until a stopping condition is met. The
// capacity of the string will continue to grow as needed until all characters
// are stored.
// 3) A stopping condition is met if we read a whitespace character after we have
// read at least one non-whitespace character or if we reach the end of the file.
// Function will return SUCCESS if a non-empty string is read successfully, and
// failure otherwise. Remember that the incoming string may already contain some
// data and this function should replace the data but not necessarily resize the
// array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
if(hMy_string == NULL || fp == NULL)
    {
      return FAILURE;
    }
  else
    {
      Status return_status = FAILURE;
      int c = fgetc(fp);
      My_string* pMy_string = (My_string*)hMy_string;
      char* temp;
      int i;
      pMy_string->size = 0;
      // printf("hi\n");
      //stop reading if reach end of file
      while(c != EOF)
	{
      // printf("%c\n", c);
	  //leading whitespace is ignored
	  if(isspace(c))
	    {
	      continue;
	    }
	  return_status = SUCCESS;
	  //add the character to the string and increment string size
	  pMy_string->data[pMy_string->size++] = c;
	  //string capacity is lengthened with addition of characters
	  if(pMy_string->size >= pMy_string->capacity)
	    {
	      temp = (char*)malloc(sizeof(char) * 2 * pMy_string->capacity);
	      if(temp == NULL)
		{
		  return_status = FAILURE;
		}
	      for(i = 0; i < pMy_string->size; i++)
		{
		  temp[i] = pMy_string->data[i];
		}
	      //temp[i] = ' ';
	      free(pMy_string->data);
	      pMy_string->data = temp;
	      pMy_string->capacity *= 2;
	    }
	  //get next character
	  c = fgetc(fp);
	  //stop if next character is space and space should be readable
	  // by next file operation
	  if(isspace(c))
	    {
	      ungetc(c, fp);
	      break;
	    }
	}
      return return_status;
    }
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Writes the characters contained in the string object indicated
// by the handle hMy_string to the file stream fp. Function will return SUCCESS
// if it successfully writes the string and FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  if(hMy_string == NULL || fp == NULL)
    {
      return FAILURE;
    }
  else
    {
      int i;
      Status return_status;
      My_string* pMy_string = (My_string*)hMy_string;
      for(i = 0; i < pMy_string->size; i++)
	{
	  if(fputc(pMy_string->data[i], fp) == EOF)
	    {
	      return_status = FAILURE;
	    }
	}
      return_status = SUCCESS;
      return return_status;
    }
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: If successful, places the character item at the end of the
// string and returns SUCCESS. If the string does not have enough room and
// cannot resize to accomodate the new character then the operation fails and
// FAILURE is returned. The resize operation will attempt to amortize the
// cost of a resize by making the string capacity somewhat larger than it was
// before (up to two times bigger)
Status my_string_push_back(MY_STRING hMy_string, char item)
{
  if(hMy_string == NULL)
    {
      return FAILURE;
    }
  else
    {
      int i;
      char* temp;
      My_string* pMy_string = (My_string*)hMy_string;
      if(pMy_string->size >= pMy_string->capacity)
	{
	  temp = (char*)malloc(sizeof(char) * 2 * pMy_string->capacity);
	  if(temp == NULL)
	    {
	      return FAILURE;
	    }
	  for(i = 0; i < pMy_string->size; i++)
	    {
	      temp[i] = pMy_string->data[i];
	    }
	  free(pMy_string->data);
	  pMy_string->data = temp;
	  pMy_string->capacity *= 2;
	}
      pMy_string->data[pMy_string->size++] = item;
      return SUCCESS;
    }
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Removes the last character of a string in constant time.
// Guaranteed to not cause a resize operation of the internal data. Returns
// SUCCESS on success and FAILURE if the string is empty.
Status my_string_pop_back(MY_STRING hMy_string)
{
  if(hMy_string == NULL)
    {
      return FAILURE;
    }
  else
    {
      My_string* pMy_string = (My_string*)hMy_string;
      if(pMy_string->size == 0)
	{
	  return FAILURE;
	}
      pMy_string->size--;
      return SUCCESS;
    }
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns the address of the character located at the given
// index if the index is in bounds but otherwise returns NULL. This address
// is not usable as a c-string since the data is not NULL terminated and is
// intended to just provide access to the element at that index.
char* my_string_at(MY_STRING hMy_string, int index)
{
  if(hMy_string == NULL)
    {
      return NULL;
    }
  else
    {
      My_string* pMy_string = (My_string*)hMy_string;
      if(index >= pMy_string->size)
	{
	  return NULL;
	}
      return &(pMy_string->data[index]);
    }
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: This function will basically add a NULL terminator to the
// memory representation of the string and then return the address of the
// first character in the string. The function will resize the string if needed
// to make room for the NULL terminator but will typically not double the string's
// size and will just add enough room for the NULL. The NULL character is not
// considered to be part of the string object and will actually exist outside of
// the current size of the string. For example, if the string is "the" then the
// size will still be 3 but this function will make sure that the character after
// the 'e' is NULL in the internal character array.
char* my_string_c_str(MY_STRING hMy_string)
{
  if(hMy_string == NULL)
    {
      return NULL;
    }
  else
    {
      int i;
      char* temp;
      My_string* pMy_string = (My_string*)hMy_string;
      if(pMy_string->size >= pMy_string->capacity)
	{
	  temp = (char*)malloc(sizeof(char) * (pMy_string->capacity + 1));
	  if(temp == NULL)
	    {
	      return NULL;
	    }
	  for(i = 0; i < pMy_string->size; i++)
	    {
	      temp[i] = pMy_string->data[i];
	    }
	  free(pMy_string->data);
	  pMy_string->data = temp;
	  pMy_string->capacity += 1;
	}
      pMy_string->data[pMy_string->size] = '\0';
      return pMy_string->data;
    }
}

//Precondition: hResult and hAppend are handles to valid My_string objects.
//Postcondition: hResult is the handle of a string that contains the original
// hResult object followed by the hAppend object concatenated together. This
// function should guarantee no change to the hAppend object and return
// SUCCESS if the operation is successful and FAILURE if the hResult object
// is unable to accomodate the characters in the hAppend string, perhaps because
// of a failed resize operation. On FAILURE, no change to either string
// should be made.
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  int i;
  char* temp;
  if(hResult == NULL || hAppend == NULL){
	  return FAILURE;
  }
  My_string* pResult = (My_string*)hResult;
  My_string* pAppend = (My_string*)hAppend;
  if(pResult->capacity < (pResult->size + pAppend->size))
    {
      temp = (char*)malloc(sizeof(char) * (pResult->size + pAppend->size));
      if(temp == NULL)
	{
	  return FAILURE;
	}
      for(i = 0; i < pResult->size; i++)
	{
	  temp[i] = pResult->data[i];
	}
      free(pResult->data);
      pResult->data = temp;
      pResult->capacity = (pResult->size + pAppend->size);
    }
  for(i = 0; i < pAppend->size; i++)
    {
      pResult->data[pResult->size + i] = pAppend->data[i];
    }
  pResult->size = pResult->size + pAppend->size;
  return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns an enumerated type with value TRUE if the string is
// empty and FALSE otherwise.
Boolean my_string_empty(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;
  return (Boolean)(pMy_string->size == 0);
}

//Precondition: pLeft is the address of a MY_STRING handle containing a valid
// MY_STRING object address OR NULL. The value of Right must be the handle of
// a valid MY_STRING object.
//Postcondition: On success, pLeft will contain the address of a handle to a 
// valid MY_STRING object that is a deep copy of the object indicated by Right.
// If the value of the handle at the address indicated by pLeft is originally 
// NULL then the function will attempt to initialize a new object that is a 
// deep copy of the object indicated by Right, otherwise the object indicated by
// the handle at the address pLeft will attempt to resize to hold the data in Right.
// On failure, pLeft will be left as NULL and any memory that may have been used 
// by a potential object indicated by pLeft will be returned to the freestore.
Status my_string_assignment(Item* pLeft, Item Right)
{
	//int i;
	//char* temp;
	My_string* left = NULL;
	My_string* right = (My_string*) Right;
	//check Right is handle of a valid MY_STRING object
	if(Right == NULL){
		return FAILURE;
	}
	//if pLeft is not NULL, but a the handle of a valid MY_STRING object
	if(*pLeft != NULL){
		//empty pLeft
		my_string_destroy(*pLeft);
	}
	//if pLeft is NULL
	if(*pLeft == NULL){
		//initialize new object that is copy of Right
		left = my_string_init_c_string(my_string_c_str(right));
		*pLeft = left;
		//if failure, return memory and set pLeft to NULL
		if(*pLeft == NULL){
			my_string_destroy(*pLeft);
			return FAILURE;
		}
	}
	return SUCCESS;
}


//Precondition: phMy_string holds the address of a valid handle to a MY_STRING
// object.
//Postcondition: The memory used for the MY_STRING object has to be reclaimed
// by the system and the handle referred to by the pointer phMy_string has been
// set to NULL.
void my_string_destroy(Item* pItem)
{
  if(pItem != NULL)
    {
       My_string* pMy_string = (My_string*) *pItem;
       free(pMy_string->data);
       free(pMy_string);
       *pItem = NULL;
       pItem = NULL;
    }
}