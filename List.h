#pragma once
template <typename T>
class List
{
	struct ListNode
	{
		ListNode()
		{
		}
		T mData;
		ListNode* mPrev;
		ListNode* mNext;
	};
	int mSize;
	ListNode* mHead;
	ListNode* mTail;
	T mUndefined;


public:
	List()
	{
		mHead = new ListNode;
		mTail = new ListNode;
		mHead->mNext = mTail;
		mHead->mPrev = nullptr;
		mTail->mPrev = mHead;
		mTail->mNext = nullptr;
		mSize = 0;
	}
	//Copy Constructor
	List( const List& tOther ) : List()
	{
		*this = tOther;
	}
	List& operator = ( const List& tRHS )
	{
		if ( mSize > 0 ) Clear();

		if ( tRHS.mHead->mNext == mTail ) return *this;

		for ( List<T>::Iterator tIter = tRHS.Begin(); tIter != tRHS.End(); tIter++ ) {
			PushBack( tIter.GetData() );
		}

		return *this;
	}
	//Destructor
	~List()
	{
		Clear();
		delete mHead;
		delete mTail;
	}

	void PushFront(const T& tWhat)
	{
		ListNode* tTempNode = new ListNode();
		tTempNode->mData = tWhat;
		tTempNode->mPrev = mHead;
		tTempNode->mNext = mHead->mNext;
		mHead->mNext->mPrev = tTempNode;
		mHead->mNext = tTempNode;
		mSize++;
	}
	void PopFront()
	{
		if ( mHead->mNext == mTail ) 
		{//Nothing to pop!
			return;
		}
		ListNode* tTempPtr = mHead->mNext;
		mHead->mNext = mHead->mNext->mNext;
		mHead->mNext->mPrev = mHead;
		delete tTempPtr;
		mSize--;
	}
	T& Front()
	{
		if ( mHead->mNext == mTail ) 
		{//No data
			return mUndefined;
		}
		else return mHead->mNext->mData;
	}

	void PushBack( const T& tWhat )
	{
		ListNode* tTempNode = new ListNode();
		tTempNode->mData = tWhat;
		tTempNode->mNext = mTail;
		tTempNode->mPrev = mTail->mPrev;
		mTail->mPrev->mNext = tTempNode;
		mTail->mPrev = tTempNode;
		mSize++;
	}
	void PopBack()
	{
		if ( mTail->mPrev == mHead ) 
		{//Nothing to pop!
			return;
		}
		ListNode* tTempPtr = mTail->mPrev;
		mTail->mPrev = mTail->mPrev->mPrev;
		mTail->mPrev->mNext = mTail;
		mSize--;
	}
	T& Back()
	{
		if ( mTail->mPrev == mHead ) 
		{//No data
			return mUndefined;
		}
		else return mTail->mPrev->mData;
	}

	int Size() const
	{
		return mSize;
	}
	void Clear()
	{
		if ( mHead->mNext == mTail )return;
		for ( int i = 0; i < mSize; ) 
		{
			PopBack();
		}
	}

	T& At( int tWhere )
	{
		if ( tWhere > mSize || tWhere < 0 ) return mUndefined;

		ListNode* tTempPtr = mHead->mNext;
		for ( int i = 0; i < tWhere; i++ ) 
		{
			tTempPtr = tTempPtr->mNext;
		}
		return tTempPtr->mData;
	}


	///////////////////////////////////////////////////////////////////
	// Iterators
	class Iterator
	{
		ListNode* mCurrent;
		T mUndefined;
		friend class List;

	public:
		Iterator() 
		{
			mCurent = nullptr;
		}
		Iterator( ListNode* tStart )
		{
			mCurrent = tStart;
		}
		T& GetData()
		{
			if ( mCurrent->mPrev == nullptr || mCurrent->mNext == nullptr )
				return mUndefined;
			else
				return mCurrent->mData;
		}
		void Next()// As in "Move to the next item please"
		{
			if ( mCurrent->mNext != nullptr ) 
			{
				mCurrent = mCurrent->mNext;
			}
		}
		void Back() {
			if ( mCurrent->mPrev != nullptr ) 
			{
				mCurrent = mCurrent->mPrev;
			}
		}
		bool IsEqual( const Iterator& tRHS )
		{
			if ( mCurrent == tRHS.mCurrent )
				return true;
			else
				return false;
		}
		bool operator == ( const Iterator& tRHS ) 
		{
			return IsEqual( tRHS );
		}
		bool operator != ( const Iterator& tRHS ) 
		{
			return !( IsEqual( tRHS ) );
		}
		Iterator operator ++ () 
		{
			Next();
			return *this;
		}
		Iterator operator ++ ( int ) 
		{
			Next();
			return *this;
		}
		Iterator operator -- () 
		{
			Back();
			return *this;
		}
		Iterator operator -- ( int ) 
		{
			Back();
			return *this;
		}
	};

	Iterator Insert( Iterator& tWhere, const T& tWhat )
	{
		if (	tWhere.mCurrent->mPrev == nullptr 
			 || tWhere.mCurrent->mNext == nullptr 
			 || tWhere.mCurrent == nullptr ) return Iterator( nullptr );

		ListNode* tTempPtr = new ListNode();
		tTempPtr->mData = tWhat;
		tTempPtr->mNext = tWhere.mCurrent;
		tTempPtr->mPrev = tWhere.mCurrent->mPrev;
		tWhere.mCurrent->mPrev->mNext = tTempPtr;
		tWhere.mCurrent->mPrev = tTempPtr;
		tWhere.mCurrent = tWhere.mCurrent->mPrev;
		mSize++;
		return tWhere;
	}

	Iterator Erase( Iterator& tWhere )
	{
		if (	tWhere.mCurrent->mPrev == nullptr 
			||  tWhere.mCurrent->mNext == nullptr 
			||  tWhere.mCurrent == nullptr) return Iterator( nullptr );
		tWhere.mCurrent->mPrev->mNext = tWhere.mCurrent->mNext;
		tWhere.mCurrent->mNext->mPrev = tWhere.mCurrent->mPrev;
		ListNode* tTempPtr = tWhere.mCurrent;
		tWhere.mCurrent = tWhere.mCurrent->mNext;
		mSize--;
		delete tTempPtr;
		return tWhere;
	}

	Iterator Begin() const
	{
		return Iterator( mHead->mNext );

	}

	Iterator End() const
	{
		return Iterator( mTail );
	}
};