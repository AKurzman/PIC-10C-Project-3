#include <iostream>

// Forward declaration
template <typename ItemType, int MAX_SIZE>
class RingQueue;

template <typename ItemType, int MAX_SIZE>
class RingQueue{
    
    // Nested Forward declaration of RingQueue<ItemType,MAX_SIZE>::iterator
    public: 
        class iterator;
        typedef ItemType* pointer;
        typedef ItemType& reference;

        class iterator{
            private:
                RingQueue* parent;
                int offset;
                //Private constructor
                iterator(RingQueue *_parent, int _offset = 0) 
                    : parent(_parent), offset(_offset){};

            friend class RingQueue<ItemType, MAX_SIZE>;

            public:
                reference operator*() {
                    return parent->buffer[offset];  
                }
                iterator& operator++(){
					          offset++;
                    return *this;
                }
                iterator operator++( int unused ){
					          offset++;
                    return iterator(parent, offset);
                }
                bool operator==( const iterator& rhs ) const {
					return (this->offset == rhs.offset && this->parent == rhs.parent)
                }
                bool operator!=( const iterator& rhs ) const {
					return !(this->offset == rhs.offset || this->parent == rhs.parent)
                }
        };

        /**
        class const_iterator{
            private:
                RingQueue* parent;
                int offset;
            private:
                // Only RingQueue objects can create const_iterators...
                const_iterator() ;
            public:
                // ... however, const_iterators can be 'copied'.
                const_iterator( const const_iterator& ) ;
            friend class RingQueue<ItemType,MAX_SIZE>;
        };
        */

    friend class iterator;
    // friend class const_iterator;  // not implemented... yet.

    private:
        ItemType buffer[MAX_SIZE];  //Array of ItemType with capacity of MAX_SIZE
        int begin_index;
        int ring_size;

        int end_index() const {
            int end = (begin_index + ring_size) % MAX_SIZE;
            return end;
        }

    public: 
        // Constructor
        RingQueue() : begin_index(0), ring_size(0) { }

        // Accessors. Note: 'back()' is not considered part of the array.
        ItemType front() const { 
            if ( ring_size == 0 ){
                std::cerr<< "Warning: Empty ring!\n" ;
                throw;
            }else{
                return buffer[begin_index];
            }
        }
        ItemType back() const {  
            if ( ring_size == 0 ){
                std::cerr<< "Warning: Empty ring!\n" ;
                throw;
            }else{
                return buffer[end_index()];
            }
        }

        // Mutators
        void push_back( const ItemType& value ){
			if (end_index() < (MAX_SIZE - 1)) {
				buffer[end_index() + 1] = value;
				ring_size++;
			}
			else
				buffer[0] = value;
            return;
        }
        void pop_front(){
			if (ring_size > 0) {
				ring_size--;
				if (begin_index < 4)
					begin_index++;
				else
					begin_index = 0;
			}
			else
				std::cout << "Warning: Empty ring!\n";
            return;
        }

        // Functions that return iterators
        iterator begin() { 
            return iterator(this, begin_index); 
        }
        iterator end() {
            return iterator(this, end_index());
        }

        // Miscellaneous functions
        size_t size() const {
            return ring_size;
        }

        // Debugging functions
        void dump_queue() const {
            std::cout << "Raw queue...\n";
            for ( size_t i = 0 ; i < MAX_SIZE ; ++i )
                std::cout << "Val: " << buffer[i] << ", at: " << buffer+i << '\n';
            std::cout << '\n';
            return;
        }

};

int main(){
    RingQueue<int,6> r;
    r.dump_queue();

    for ( int i = 0 ; i < 7 ; ++i )
        r.push_back(i+1);

    r.dump_queue();
    r.pop_front();

    std::cout << "Queue via size: \n";

    // RingQueue<int,7>::iterator iter = r.begin() ; 
    auto iter = r.begin() ; 
    for ( size_t i = 0 ; i < r.size() ; ++i ) {
        std::cout << "Value: " << *iter << ", address: " << &(*iter) << '\n';
        ++iter;
    }
    std::cout << '\n';

    

    // Uncomment the block below only when you have a working 
    // implementation of RingQueue<ItemType,int>::end(). 
    // If the implementation is not correct, it might result in 
    // an infinite loop.
    
    std::cout << "Queue via iterators: \n";
    for ( auto it = r.begin() ; iter != r.end() ; ++iter ) {
        std::cout << "Value: " << *iter << ", address: " << &(*iter) << '\n';
    }
    std::cout << '\n';
    



    r.dump_queue();

    return 0;
}



/** 
    +++++++++++++++++++++++++++++++++++++++++++++++
    The output of your program [once the missing 
    code is added] should look more or less like
    the output below.
    
    Note:
        It is dependent on the device where 
        this driver is executed. However, it
        should be clear that the difference 
        between consecutive memory addresses
        is equal to the number reported by
        'size_of( int )'.
    +++++++++++++++++++++++++++++++++++++++++++++++
        Raw queue...
        Val: 2, at: 0x7ffcdeeaab40
        Val: 0, at: 0x7ffcdeeaab44
        Val: 4198285, at: 0x7ffcdeeaab48
        Val: 0, at: 0x7ffcdeeaab4c
        Val: 0, at: 0x7ffcdeeaab50
        Val: 0, at: 0x7ffcdeeaab54
        Val: 0, at: 0x7ffcdeeaab58
        Raw queue...
        Val: 8, at: 0x7ffcdeeaab40
        Val: 2, at: 0x7ffcdeeaab44
        Val: 3, at: 0x7ffcdeeaab48
        Val: 4, at: 0x7ffcdeeaab4c
        Val: 5, at: 0x7ffcdeeaab50
        Val: 6, at: 0x7ffcdeeaab54
        Val: 7, at: 0x7ffcdeeaab58
        Queue via size: 
        Value: 3, address: 0x7ffcdeeaab48
        Value: 4, address: 0x7ffcdeeaab4c
        Value: 5, address: 0x7ffcdeeaab50
        Value: 6, address: 0x7ffcdeeaab54
        Value: 7, address: 0x7ffcdeeaab58
        Value: 8, address: 0x7ffcdeeaab40
        Queue via iterators: 
        Value: 3, address: 0x7ffcdeeaab48
        Value: 4, address: 0x7ffcdeeaab4c
        Value: 5, address: 0x7ffcdeeaab50
        Value: 6, address: 0x7ffcdeeaab54
        Value: 7, address: 0x7ffcdeeaab58
        Value: 8, address: 0x7ffcdeeaab40
        Raw queue...
        Val: 8, at: 0x7ffcdeeaab40
        Val: 2, at: 0x7ffcdeeaab44
        Val: 3, at: 0x7ffcdeeaab48
        Val: 4, at: 0x7ffcdeeaab4c
        Val: 5, at: 0x7ffcdeeaab50
        Val: 6, at: 0x7ffcdeeaab54
        Val: 7, at: 0x7ffcdeeaab58
 */
