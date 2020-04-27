//--------------------------------------------------------------------
//
//  Laboratory 4                                         ordlist.cpp
//
//  Array implementation of the Ordered List ADT
//
//--------------------------------------------------------------------

#ifndef ORDEREDLIST_CPP
#define ORDEREDLIST_CPP

using namespace std;

#include "OrderedList.h"

//--------------------------------------------------------------------
template < typename DataType, typename KeyType >
OrderedList<DataType,KeyType>:: OrderedList ( int maxNumber )

// Creates an empty list by calling the List ADT constructor.

  : List<DataType>(maxNumber)

{}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void OrderedList<DataType,KeyType>:: insert ( const DataType &newDataItem ) throw ( logic_error )

// Inserts newDataItem in its appropriate location within an ordered
// list. If a data item with the same key as newData already
// exists in the list, then updates that data item's data with
// newData's data. Moves the cursor to newData.

{
    // Requires that list is not full
    if ( size >= maxSize )  
       throw logic_error("list is full");

	if (binarySearch(newDataItem.getKey(), cursor))
	{
		dataItems[cursor] = newDataItem;
	}
	else
	{
		for (int j = size - 1; j > cursor; j--)
		{
			dataItems[j + 1] = dataItems[j];
		}
		dataItems[++cursor] = newDataItem;
		size++;
	}

    
       // Or, plan B
       // List<DataType>::insert(newDataItem);
    
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool OrderedList<DataType,KeyType>:: retrieve ( const KeyType& searchKey, DataType &searchDataItem )

// Searches a list for the data item with key searchKey. If the
// data item is found, then moves the cursor to the data item,
// copies the data item to searchDataItem, and returns true.
// Otherwise, returns false without moving the cursor and with
// searchDataItems undefined.

{
	int prev_cursor = cursor;
	bool result = false;

	if (binarySearch(searchKey, cursor))
	{
		searchDataItem = dataItems[cursor];
		result = true;
	}
	else
	{
		cursor = prev_cursor;
		result = false;
	}
	return result;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void OrderedList<DataType,KeyType>:: replace ( const DataType &newDataItem )
    throw ( logic_error )

// Replaces the data item marked by the cursor with newData and
// moves the cursor to newData.

{
    // Requires that list is not empty
    if ( size == 0)  
        throw logic_error("list is empty");

	if (newDataItem.getKey() == dataItems[cursor].getKey())
	{
		dataItems[cursor] = newDataItem;
	}
	else
	{
		insert(newDataItem);
	}
    
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void OrderedList<DataType,KeyType>:: showStructure () const

// Outputs the keys of the data items in a list. If the list is
// empty, outputs "Empty list". This operation is intended for
// testing and debugging purposes only.

{
    if ( size == 0 )
       cout << "Empty list" << endl;
    else
    {
       cout << "size = " << size
            <<  "   cursor = " << cursor << endl;
       for ( int j = 0 ; j < maxSize ; ++j )
           cout << j << "\t";
       cout << endl;
       for ( int j = 0 ; j < size ; ++j ) {
	   if( j == cursor ) {
               cout << "[" << dataItems[j].getKey() << "]\t";
	   } else {
               cout << dataItems[j].getKey() << "\t";
	   }
       }
       cout << endl;
    }
}

//--------------------------------------------------------------------
//
//  Facilitator function
//

template < typename DataType, typename KeyType >
bool OrderedList<DataType, KeyType>::binarySearch(KeyType searchKey, int& index)

// Binary search routine. Searches a list for the data item with
// key searchKey. If the data item is found, then returns true with
// index returning the array index of the entry containing searchKey.
// Otherwise, returns false with index returning the array index of the
// entry containing the largest key that is smaller than searchKey
// (or -1 if there is no such key).

{
	int lower_half = 0;
	int upper_half = size - 1;
	bool result = false;

	while (lower_half <= upper_half)
	{
		index = (lower_half + upper_half) / 2;
		if (searchKey < dataItems[index].getKey())
		{

			upper_half = index - 1;
		}
		else if (searchKey > dataItems[index].getKey())
		{
			lower_half = index + 1;
		}
	}

	if (lower_half <= upper_half)
	{
	
	result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

//--------------------------------------------------------------------
//
//                        In-lab operations
//
//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void OrderedList<DataType, KeyType>::merge(const OrderedList<DataType, KeyType>& fromL) throw (logic_error)

// Merges the data items in list fromL into a list. Assumes that
// none of the data items in fromL occur in L already. The merge
// is done in a single pass through both lists.

{
	int temp = 0;
	int i = fromL.size - 1; 
	int j = size + i;  
	temp = size - 1; 

	while (i >= 0 && j >= 0)
	{
		if (fromL.dataItems[j].getKey() == dataItems[i].getKey())
		{
			throw logic_error("Common items found in lists");
		}

		else if (fromL.dataItems[j].getKey() > dataItems[i].getKey())
		{
			dataItems[temp--] = fromL.dataItems[j--];
		}

		else
		{
			dataItems[temp--] = dataItems[i--];
		}
	}
	for (temp = j; temp >= 0; temp--)
	{
	
	dataItems[temp] = fromL.dataItems[temp];
	size += fromL.size;
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool OrderedList<DataType,KeyType>:: isSubset ( const OrderedList<DataType,KeyType> &subList )

// Returns true if every key in list subList also occurs in a list --
// that is, if the keys in subList are a subset of the keys in the list.
// Otherwise, returns false.

{
	int x = 0;
	int y = 0; 
	bool result = false; // Initialize to false so the function continues

	while ((x < size) && (y < subList.size))
	{
		if (dataItems[x].getKey() < subList.dataItems[y].getKey())
		{
			x++;
		}
			else if (dataItems[x].getKey() == subList.dataItems[y].getKey())
			{
				x++;
				y++;
			}
				else
				{
					result = false;
				}
	}
	if (y == subList.size)
	{
		result = true;
	}
		else
		{
			result = false;
		}

			return result;
}

#endif // #IFNDEF ORDEREDLIST_CPP
