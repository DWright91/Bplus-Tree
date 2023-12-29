/********************************************
FixLength.h header file
Fixed Length Buffer Header
********************************************/
using namespace std;
class FixedLengthBuffer: public IOBuffer
// Abstract class designed to support fixed length records
{
public:
    FixedLengthBuffer (int recordSize = 1000);
    FixedLengthBuffer (const FixedLengthBuffer & buffer);
    // copy constructor
    void Clear(); // clear values from buffer
    int Read (istream &) ;
    int Write (ostream &) const;
    int ReadHeader (istream &); // read the header
    int WriteHeader (ostream &) const; // write the header
    void Print (ostream &) const;
    int SizeOfBuffer () const; // return size of buffer
    protected:
    int Init (int recordSize);
    int ChangeRecordSize (int recordSize);
};

#include"FixLength.cpp"

inline FixedLengthBuffer::FixedLengthBuffer(const FixedLengthBuffer & buffer) : IOBuffer (buffer)
{
    Init(buffer.BufferSize);
}
