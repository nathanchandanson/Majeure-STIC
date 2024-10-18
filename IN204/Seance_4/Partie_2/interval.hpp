#include <cstddef>
#include <stdexcept>

class interval_iterator;

/* Interval class */
class interval
{
private:
	int minValue;
	int maxValue;
    friend class interval_iterator;
 
public:
	typedef int value_type;
	typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef interval_iterator iterator;
    typedef const interval_iterator const_iterator;
    typedef int& reference;
    typedef const int& const_reference;
 
	interval(int theMinValue, int theMaxValue) : 
		minValue(theMinValue), maxValue(theMaxValue) 
	{}

	interval(const interval& anotherInterval):
		minValue(anotherInterval.minValue), 			 		  
                maxValue(anotherInterval.maxValue)
	{}

	interval& operator = (const interval& anotherInterval)
	{
		minValue = anotherInterval.minValue;
		maxValue = anotherInterval.maxValue;
		return *this;
	}

	size_type size() const
	{
		return (size_type)(maxValue - minValue);
	}

	int operator[](size_type anIndex) const
	{
		if (anIndex > size())
			throw std::out_of_range("Index out of range");
		return minValue + (int)anIndex;
	}

	bool operator == (const interval& anotherInterval) const
	{
		return anotherInterval.maxValue == maxValue &&
			anotherInterval.minValue == minValue;
	}

	bool operator != (const interval& anotherInterval) const
	{
		return anotherInterval.maxValue != maxValue ||
			anotherInterval.minValue != minValue;
	}

    inline iterator begin();

    inline iterator end();
};



/* Iterator for interval */
class interval_iterator
	: public std::iterator<std::forward_iterator_tag, int>
{
private:
	friend class interval;      // Donner un accès (aux champs de interval_iterator) de niveau membre à interval
	const interval* mInterval;  // Référence à l'interval.
	int mCurrent;               // la valeur courante dont on fait référence.
 
	interval_iterator(const interval& anInterval, int aCurrentValue) : 
		mInterval(&anInterval), mCurrent(aCurrentValue) {}
 
public:
    typedef interval_iterator iterator;
    typedef const interval_iterator const_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

	interval_iterator(const interval_iterator& anotherIterator):
		mInterval(anotherIterator.mInterval),
		mCurrent(anotherIterator.mCurrent) {}
 
	interval_iterator& operator = (interval_iterator& anotherIterator)
	{
		mInterval = anotherIterator.mInterval;
		mCurrent = anotherIterator.mCurrent;
		return *this;
	}
 
	reference operator*() const 
    {
        return (int&)mCurrent;
    }

	// reference operator->() const 
    // {
    //     return &mCurrent;
    // }

	iterator& operator++()
    {
        // Passe à la valeur suivant si nous ne sommes pas
        // déjà à la fin de l'interval.
        if(mCurrent <= mInterval->maxValue)
            mCurrent ++;
        return *this;
    }

    iterator operator++(int)
    {
        interval_iterator it(*this); // Crée une copie de l'itérateur.
        ++(*this);          // Incrément l'itérateur courant en appellant
                            // l'opérateur iterator& operator()
        return it;          // Retourne la copie de l'itérateur (avant modification).
    }

	bool operator ==(const interval_iterator& anotherIterator) const
    {
        return mCurrent == anotherIterator.mCurrent && 
          *mInterval == *anotherIterator.mInterval;
    }

    bool operator !=(const interval_iterator& anotherIterator) const
    {
        return mCurrent != anotherIterator.mCurrent || 
          *mInterval != *anotherIterator.mInterval;
    }
 
};

inline interval::iterator interval::begin() 
{
    return interval_iterator(*this, minValue);
}

inline interval::iterator interval::end() 
{
    return interval_iterator(*this, maxValue+1);
}