using namespace std;
#include <stdio.h>
#include<string.h>
/********************************************
IOBuffer default constructor
********************************************/
IOBuffer::IOBuffer (int maxBytes)
// construct with a maximum of maxFields
{Init (maxBytes);}
IOBuffer& IOBuffer::operator = (const IOBuffer& buffer)
{
    if (MaxBytes < buffer.BufferSize) return *this; // fails
    Initialized = buffer.Initialized;
    BufferSize =buffer.BufferSize;
    memcpy(Buffer, buffer.Buffer, buffer.BufferSize);
    NextByte = buffer.NextByte;
    Packing = Packing;
    return *this;
}
/********************************************
IOBuffer clear method
********************************************/
void IOBuffer::Clear ()
// clear field values from buffer
{ NextByte = 0; Packing= true;}

void IOBuffer::Print (ostream & stream) const
{ stream << "MaxBytes "<< MaxBytes <<" BufferSize "<<BufferSize;}
/********************************************
IOBuffer initialization
********************************************/
int IOBuffer::Init (int maxBytes)
{
    Initialized= false;
    if (maxBytes < 0) maxBytes = 0;
    MaxBytes = maxBytes;
    Buffer= new char[MaxBytes];
    BufferSize = 0;
    Clear();
    return 1;
}
/********************************************
IOBuffer data reading method of the record
********************************************/
int IOBuffer::DRead (istream & stream, int recref)
// read specified record
{
    stream.seekg (recref, ios::beg);
    if (stream.tellg () != recref) return -1;
    return Read (stream);
}
/********************************************
IOBuffer data writing method for the record
********************************************/
int IOBuffer::DWrite (ostream & stream, int recref) const
//write specified record
{
    stream.seekp(recref, ios::beg);
    if (stream.tellp () != recref) return -1;
    return Write (stream);
}

static const char* headerStr = "IOBuffer";
static const int headerSize = strlen (headerStr);
/********************************************
IOBuffer Read header data method
********************************************/
int IOBuffer::ReadHeader (istream & stream)
{
    char str[9];
    stream.seekg (0, ios::beg);
    stream.read (str, headerSize);
    if (! stream.good()) return -1;
    if (strncmp (str, headerStr, headerSize)==0) return headerSize;
    else return -1;
}
/********************************************
IOBuffer write header data method
********************************************/
int IOBuffer::WriteHeader (ostream & stream) const
{
    stream.seekp (0, ios::beg);
    stream. write (headerStr, headerSize);
    if (!stream.good ()) return -1;
    return headerSize;
}

