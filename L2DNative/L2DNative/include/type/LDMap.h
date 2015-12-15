/**
 *  LDMap.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_LDMAP_H__
#define __LIVE2D_LDMAP_H__


#include "../memory/LDObject.h"
#include "LDString.h"
#include "../util/UtDebug.h"

#define l2d_map		live2d::LDMap

#ifndef NULL
#  define NULL    0
#endif

//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{


#ifndef __SKIP_DOC__

	
	template<class _KeyT , class _ValT> 
	class LDPair  : public live2d::LDObject 
	{
	public:
		LDPair() : first(), second() {}
	
		LDPair( const _KeyT& key) 	: first(key) , second() {}
	
		LDPair( const _KeyT& key , const _ValT &value )
			: first( key ) , second( value ) {}
	
		~LDPair(){} 
	
		_KeyT	 first ;
		_ValT	 second ;
	} ;

#endif // __SKIP_DOC__

	
	
	template<class _KeyT , class _ValT> 
	class LDMap  : public live2d::LDObject 
	{
	public:
		LDMap(MemoryParam* memParam = NULL);
		LDMap(int size , MemoryParam* memParam = NULL);
	
		virtual ~LDMap();
	
	
		void appendKey( _KeyT& key )
		{
			
			prepare_capacity( _size + 1 , false ) ;
			
			
	
			void* addr = &_keyValues[_size] ;
			L2D_PLACEMENT_NEW (addr) LDPair<_KeyT,_ValT>(key) ;//placement new
	
			_size += 1 ;
		}
	
		//-- [] --
		_ValT& operator[](_KeyT key)
		{	
			int found = -1 ;
			for( int i = 0 ; i < _size ; i++ )
			{
				if( _keyValues[i].first == key )
				{
					found = i ;
					break ;
				}
			}
			if( found >= 0 )
			{
				return _keyValues[found].second ;
			}
			else{
				appendKey( key ) ;
				return _keyValues[_size-1].second ;
			}
		}
	
		const _ValT& operator[] (_KeyT key) const {	
			int found = -1 ;
			for( int i = 0 ; i < _size ; i++ )
			{
				if( _keyValues[i].first == key )
				{
					found = i ;
					break ;
				}
			}
			if( found >= 0 )
			{
				return _keyValues[found].second ;
			}
			else{
				
				if( ! DUMMY_VALUE_PTR ) DUMMY_VALUE_PTR = L2D_NEW(memoryGroup)  _ValT() ;
				return *DUMMY_VALUE_PTR ;
			}
		}

		bool isExist(_KeyT key){
			for(int i=0;i< _size ;i++)
			{
				if(_keyValues[i].first == key)
				{
					return true;
				}
			}
			return false;
		}

	
		//-- else --
	//	void push_back( const _T& value ) ;
		void clear() ;
		int size(){	return _size ; }
	
	//	void resize( int size , _T value = _T() ) ;
	
		void prepare_capacity( int newsize , bool fitToSize) ;
	
		class iterator ;
	
	//	void insert( iterator pos, iterator start, iterator end ) ;
	//	void assign( int size , _T value = _T() ) ;
	
		
		class iterator 
		{
			friend class LDMap ;
		public:
			iterator() : _index(0) , _map(NULL){}
			iterator(LDMap<_KeyT , _ValT> *v) : _index(0) , _map(v) {}
			iterator(LDMap<_KeyT , _ValT> *v, int idx) : _index(idx) , _map(v){}
	
			iterator& operator=( const iterator & ite )
			{
				this->_index = ite._index ;
				this->_map = ite._map ;
				return *this ;
			}
			iterator& operator++()
			{
				this->_index ++ ;
				return *this ;
			}
			iterator& operator--()
			{
				this->_index -- ;
				return *this ;
			}
			iterator operator++(int)
			{
			    iterator iteold( this->_map , this->_index++ ) ;
				return iteold ;
			}
			iterator operator--(int)
			{
			    iterator iteold( this->_map , this->_index-- ) ;
				return iteold ;
			}
			LDPair<_KeyT , _ValT>& operator*()const{
				return this->_map->_keyValues[this->_index] ;
			}
			bool operator!=( const iterator & ite )const{
				return (this->_index != ite._index) || (this->_map != ite._map) ;
			}
		private:
			int _index ;
			LDMap<_KeyT , _ValT> *_map ;
		} ;
	
		
		class const_iterator 
		{
			friend class LDMap ;
		public:
			const_iterator() :  _index(0) , _map(NULL){}
			const_iterator(const LDMap<_KeyT , _ValT> *v) : _index(0) , _map(v){}
			const_iterator(const LDMap<_KeyT , _ValT> *v, int idx) : _index(idx) , _map(v){}
	
			const_iterator& operator=( const const_iterator & ite )
			{
				this->_index = ite._index ;
				this->_map = ite._map ;
				return *this ;
			}
			const_iterator& operator++()
			{
				this->_index ++ ;
				return *this ;
			}
			const_iterator& operator--()
			{
				this->_index -- ;
				return *this ;
			}
			const_iterator operator++(int)
			{
			    const_iterator iteold( this->_map , this->_index++ ) ;
				return iteold ;
			}
			const_iterator operator--(int)
			{
			    const_iterator iteold( this->_map , this->_index-- ) ;
				return iteold ;
			}
			LDPair<_KeyT , _ValT>& operator*()const{
				return this->_map->_keyValues[this->_index] ;
			}
			bool operator!=( const const_iterator & ite )const{
				return (this->_index != ite._index) || (this->_map != ite._map) ;
			}
		private:
			int _index ;
			const LDMap<_KeyT , _ValT> *_map ;
		} ;
	
		//--------- iterator method ---------
		const const_iterator begin() const {
			const_iterator ite(this , 0) ;
			return ite ;
		}
	
		const const_iterator end() const {
			const_iterator ite(this , _size) ;
			return ite ;
		}
	
		const iterator erase(const iterator& ite)
		{
			int index = ite._index ;
			if( index < 0 || _size <= index ) return ite ;
	
			
			if( index < _size-1 ) memmove( &(_keyValues[index]) , &(_keyValues[index+1]) , sizeof(LDPair<_KeyT , _ValT>)*(_size-index-1) ) ;
			--_size ;
	
			iterator ite2(this , index) ;
			return ite2 ;
		}
	
		const const_iterator erase(const const_iterator& ite)
		{
			int index = ite._index ;
			if( index < 0 || _size <= index ) return ite ;
	
			
			if( index < _size-1 ) memmove( &(_keyValues[index]) , &(_keyValues[index+1]) , sizeof(LDPair<_KeyT , _ValT>)*(_size-index-1) ) ;
			--_size ;
	
			const_iterator ite2(this , index) ;
			return ite2 ;
		}
	
	
		void dumpAsInt()
		{
			for(int i = 0 ; i < _size ; i++ ) UtDebug::print("%d ," , _keyValues[i] ) ;
			UtDebug::print("\n") ;
		}
	
	
	private:
		static const int DEFAULT_SIZE = 10 ;
	
		LDPair<_KeyT , _ValT> * _keyValues ;
	
		//static _ValT DUMMY_VALUE ;
		_ValT* DUMMY_VALUE_PTR ;
	
	
		int _size ;
		int _capacity ;
	
		
		
		
		
		
		MemoryParam* memoryGroup ;
	};
	
	//======================================================
	//======================================================
	template<class _KeyT , class _ValT> 
	LDMap<_KeyT , _ValT>::LDMap(MemoryParam* memParam)
	: _keyValues(NULL), DUMMY_VALUE_PTR(NULL) , _size(0), _capacity(0) 
	{
		memoryGroup = ( memParam == NULL ) ? L2D_MEM_TMP : memParam ;
	}
	
	//======================================================
	//======================================================
	template<class _KeyT , class _ValT> 
	LDMap<_KeyT , _ValT>::LDMap(int size,MemoryParam* memParam)
		: DUMMY_VALUE_PTR(NULL)
	{
		memoryGroup = ( memParam == NULL ) ? L2D_MEM_TMP : memParam ;
	
		if( size < 1 )
		{
			_keyValues = NULL ;
			_capacity = 0 ;
			_size = 0 ;
		}
		else{
			_keyValues = (LDPair<_KeyT , _ValT> *)L2D_MALLOC( memoryGroup , size * sizeof(LDPair<_KeyT , _ValT>) ) ;
			memset( _keyValues , 0, size * sizeof(LDPair<_KeyT , _ValT>) ) ;
	
			if( _keyValues == NULL )
			{
				//TODO ERROR
				_capacity = 0 ;
				_size = 0 ;
				return ;
			}
			_capacity = size ;
			_size = size ;
		}
	}
	
	//======================================================
	//======================================================
	template<class _KeyT , class _ValT> 
	LDMap<_KeyT , _ValT>::~LDMap()
	{
		clear() ;
	}
	
	
	
	//======================================================
	//push_back
	template<class _KeyT , class _ValT> 
	void LDMap<_KeyT , _ValT>::prepare_capacity( int newsize , bool fitToSize )
	{
	
		if( newsize > _capacity )
		{
			if( _capacity == 0 )
			{
				if( ! fitToSize && newsize < DEFAULT_SIZE ) newsize = DEFAULT_SIZE ;
	
				_keyValues = (LDPair<_KeyT , _ValT> *)L2D_MALLOC( memoryGroup , sizeof(LDPair<_KeyT,_ValT>) * newsize ) ;
				if( _keyValues == NULL )
				{
					//TODO ERROR
					return ;
				}
				_capacity = newsize ;
			}
			else{
				if( ! fitToSize && newsize < _capacity*2 ) newsize = _capacity*2 ;
	
				int tmp_capacity = newsize ;
				LDPair<_KeyT,_ValT>* tmp = (LDPair<_KeyT , _ValT> *)L2D_MALLOC( memoryGroup , sizeof(LDPair<_KeyT,_ValT>) * tmp_capacity ) ;
	
				if( tmp == NULL )
				{
					//TODO ERROR
					return ;
				}
				else{
					
					memcpy( (void*)tmp , (void*)_keyValues , sizeof(LDPair<_KeyT,_ValT>) *_capacity ) ;
					L2D_FREE( _keyValues ) ;
	
					_keyValues = tmp ;
					_capacity = newsize ;
				}
	
			}
		}
	//	_size = newsize ;
	}
	
	
	//======================================================
	//======================================================
	template<class _KeyT , class _ValT> 
	void LDMap<_KeyT , _ValT>::clear()
	{
		if( DUMMY_VALUE_PTR ) L2D_DELETE  DUMMY_VALUE_PTR ;
		for( int i = 0 ; i < _size ; i++ )
		{
			_keyValues[i].~LDPair<_KeyT,_ValT>() ;
		}
	
		L2D_FREE( _keyValues ) ;
	
		_keyValues = NULL ;
	
		_size = 0 ;
		_capacity = 0 ;
	}
} 
//------------------------- LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_LDMAP_H__
