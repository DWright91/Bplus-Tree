using namespace std;
/********************************************
constructor that maximizes the fields
********************************************/
FixedLengthBuffer :: FixedLengthBuffer (int recordSize)
// construct with a maximum of maxFields
: IOBuffer (recordSize)
{ Init (recordSize);}
/********************************************
the clear method for Fixed Length Buffer
********************************************/
void FixedLengthBuffer :: Clear ()
// clear fields from buffer
{
    IOBuffer::Clear ();
    Buffer [0] =0;
    Packing= true;
}
/********************************************
the read method for Fixed Length Buffer
********************************************/
int FixedLengthBuffer :: Read (istream & stream)
// write the number of bytes in the buffer field definitions
{
    int recaddr =stream. tellg (); stream.clear();
    Clear ();
    Packing= false;
    stream. read (Buffer, BufferSize);
    if (! stream. good ()){stream.clear(); return recaddr;}
    return recaddr;
}

/********************************************
the write method for Fixed Length Buffer
********************************************/
int FixedLengthBuffer::Write(ostream& stream) const
{
    int recaddr = stream.tellp();
    stream.write(Buffer,BufferSize);
    if(!stream.good()) return -1;
    return recaddr;
}

static const char* headerStr1 = "Fixed";
static const int headerStrSize = strlen(headerStr1);
/********************************************
the read header method for Fixed Length Buffer
********************************************/
int FixedLengthBuffer::ReadHeader(istream& stream)
{
    char str[headerStrSize+1];
    int recordSize;
    int result;
    result = IOBuffer::ReadHeader(stream);
    if(result < 0) return -1;
    stream.read(str, headerStrSize);
    if(!stream.good()) return -1;
    if(strncmp(str, headerStr1, headerStrSize) != 0) return -1;
    stream.read((char*)&recordSize, sizeof(recordSize));
    if(Initialized)
    {
        if(recordSize != BufferSize) return -1;
    }
    ChangeRecordSize (recordSize);
    return stream.tellg();
}
/********************************************
the write header method for Fixed Length Buffer
********************************************/
int FixedLengthBuffer::WriteHeader(ostream& stream) const
{
    int result;
    if(!Initialized) return -1;
    result = IOBuffer::WriteHeader(stream);
    if(!result) return -1;
    stream.write(headerStr1, headerStrSize);
    if(!stream.good()) return -1;
    stream.write((char*)&BufferSize, sizeof(BufferSize));
    if(!stream.good()) return -1;
    return stream.tellp();
}
/********************************************
the print method for Fixed Length Buffer
********************************************/
void FixedLengthBuffer::Print(ostream& stream) const
{
    IOBuffer::Print(stream);
    stream << "Fixed ";
}
/********************************************
the initialization method for Fixed Length Buffer
********************************************/
int FixedLengthBuffer::Init(int recordSize)
{
    Clear();
    BufferSize = recordSize;
    return 1;
}
/********************************************
the change record size method for Fixed Length Buffer
********************************************/
int FixedLengthBuffer::ChangeRecordSize(int recordSize)
{
    BufferSize = recordSize;
    return 1;
}
