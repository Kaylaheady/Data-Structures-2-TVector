#ifndef TVECTOR_HPP
#define TVECTOR_HPP
#include "TVector.h"
#include <iostream>
using namespace std;

template <class T>
        class TVectorIterator;

template <class T>
        class TVector;

template <class T>
        TVector<T>::TVector(){
            array = nullptr;
            size=0;
            capacity=0;
        }

template <class T>
     	TVector<T>::TVector(const TVector &rhs): capacity(rhs.capacity),size(rhs.size), array(nullptr){

             array = new T [size];
                 for(int i=0; i<size; ++i){
                      array[i]=rhs.array[i];
                    }
                } // end of copy constructor

template <class T>
         TVector<T>::TVector(TVector &&rhs): array(rhs.array), size(rhs.size), capacity(rhs.capacity){
                    rhs.array = nullptr;
                    rhs.capacity = 0;
                    rhs. size = 0;
        } // move constructor


template <class T>
          TVector<T>::TVector(T val, int num){
           size=num;
           array = new T[num];
             for(int i = 0; i<size; i++){
                  array[i]=val;
                    }
                } 



template <class T>
          TVector<T>::~TVector(){}

                        /*template <class T>
                                T& TVector<T>::operator[](int index){
                    return array[index];
                }*/
                        /*
template <typename T>
                        const T& TVector<T>::operator[](const int index) const {
                            return array[index];
                        }*/
template <class T>
       	  TVector<T>& TVector<T>::operator = (const TVector<T> &rhs){

          TVector copy = rhs;
                swap( *this, copy );
                  return *this;

          } //end assignment operator
                                
template <class T>
          TVector<T>& TVector<T>::operator = ( TVector<T> &&rhs){
                 swap( size, rhs.size );
                 swap( capacity, rhs.capacity );
                 swap( array, rhs.array);

                          return *this;
                 }

template <class T>
          int TVector<T>::GetSize() const{
                  return size;
                                                }



template <typename T> //Is it empty
          bool TVector<T>::IsEmpty() const{
                  if(size==0){
                      return true;
                       }
                  else{
                      return false;
                       }
                   }
                                                

template <typename T>
           void TVector<T>::Clear(){
                                                    
 	   size = 0;
                                                }
                                                
template <typename T>
                                               
	   void TVector<T>::InsertBack(const T &val){
                  if (size < capacity) {
                      array[size] = val;
                          ++size;
                      } 
		  else {

			SetCapacity(capacity + SPARECAPACITY);
                            array[size] = val;
                             ++size;
				}
                                              }
template <class T>
            void TVector<T>::RemoveBack( ){

                      --size;
}


template <class T>
            void TVector<T>::Print(std::ostream& os, char delim ) const{
                 if (size == 0) {
                   cout<<" The Vector is empty" <<endl;
}


                 os << array[0];
		 for (int i = 1; i < size; ++i) {
                     os << delim << array[i];
}
}

template <class T>
           T& TVector<T>::GetFirst() const {
             	if (size > 0) {
                   return array[0];
} 
	 	else {
			throw std::out_of_range("Vector is empty. Cannot get the first element.");
}
}
template <class T>
           T& TVector<T>::GetLast() const {
                if (size > 0) {
                    return array[size - 1];
} 
		else {
			throw std::out_of_range("Vector is empty. Cannot get the last element.");
}
}
template <class T>
           TVectorIterator<T> TVector<T>::GetIterator() const {
           TVectorIterator<T> iterator;
           iterator.index = 0;
           iterator.ptr = &array[0];
           iterator.vsize = size;
           return iterator;
 }

template <class T>
           TVectorIterator<T> TVector<T>::GetIteratorEnd() const {
           TVectorIterator<T> iterator;
           iterator.index = size - 1;
           iterator.ptr = &array[iterator.index];
           iterator.vsize = size;
           return iterator;
}

template <class T>
          void TVector<T>::SetCapacity(unsigned int c) {
             if (c > capacity) {
            	T* newArray = new T[c];
		for (unsigned int i = 0; i < size; ++i) {
			newArray[i] = std::move(array[i]);
                }

                delete[] array;
		array = newArray;
                capacity = c;
		}

	}

template <typename T>
         TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d) {
             if (pos.index <= size) {
	       if (size == capacity) {
                 SetCapacity(capacity + SPARECAPACITY);
		   pos.ptr = &array[pos.index];
                 }
		for (unsigned int i = size; i > pos.index; --i) {
                     array[i] = std::move(array[i - 1]);
           	}
		 array[pos.index] = d;
                 ++size;
		 return pos;
              } 
	     else {
		throw std::out_of_range("Invalid position for insertion.");
}
}

template <class T>
            TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos) {
               if (pos.index < size) {
		for (unsigned int i = pos.index; i < size - 1; ++i) {
                    array[i] = std::move(array[i + 1]);
		}
		--size;
		return pos;
               } else {
			throw std::out_of_range("Invalid position for removal.");
                                                                                                                    
		}
               }

template <class T>
             TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2) {
                 if (pos1.index <= pos2.index && pos2.index <= size) {
                           unsigned int shift = pos2.index - pos1.index;
                           for (unsigned int i = pos1.index; i < size - shift; ++i) {
                           array[i] = std::move(array[i + shift]);
                          }


// Update the size
   			size -= shift;
			return pos1;
                 } else {
                        throw std::out_of_range("Invalid range for removal.");
}
}
template <typename T>
	    TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2) {
            TVector<T> result;
	    result.SetCapacity(t1.GetSize() + t2.GetSize());
	    for (unsigned int i = 0; i < t1.GetSize(); ++i) {
             result.InsertBack(i);
              }
	    for (unsigned int i = 0; i < t2.GetSize(); ++i) {
             result.InsertBack(i);
             }
 	     return result;
}
template <typename T>
          TVectorIterator<T>::TVectorIterator() : index(0), ptr(nullptr), vsize(0) {
           // Constructor implementation
           }


template <typename T>
         bool TVectorIterator<T>::HasNext() const {
            return index < vsize;
            }


template <typename T>
         bool TVectorIterator<T>::HasPrevious() const {
         return index > 0; // Returns true if there is a previous item (index is greater than 0)
 }

template <typename T>
         TVectorIterator<T> TVectorIterator<T>::Next() {
           if (index < vsize) {
              ++index;  
              ++ptr;   
		 }
	  return *this; // Return the updated iterator
      }

template <typename T>
          TVectorIterator<T> TVectorIterator<T>::Previous() {
            if (index > 0) {
                --index;  
                --ptr;   
 		}

           return *this; // Return the updated iterator
}

template <typename T>
          T& TVectorIterator<T>::GetData() const {
           if (index < vsize) {
              return *ptr; // Return a reference to the current data element
             } else {
		return TVector<T>::dummy;
                    }
             }




#endif