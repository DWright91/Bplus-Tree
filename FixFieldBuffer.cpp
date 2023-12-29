/********************************************
Fixed Field Buffer Implementation File
********************************************/
FixedFieldBuffer::FixedFieldBuffer(int maxFields,int maxBytes)
// construct with a maximum of maxFields
: FixedLengthBuffer(maxBytes)

{ Init(maxFields);}

/********************************************
Fixed Field Buffer summation of field sizes
********************************************/
static int SumFieldSizes(int numFields, int* fieldSize)
{
    int sum = 0;
    for(int i = 0; i < numFields; i++)
        sum += fieldSize[i];
    return sum;
}
/********************************************
Fixed Field Buffer overloaded = operator
********************************************/
FixedFieldBuffer & FixedFieldBuffer::operator = (const FixedFieldBuffer & buffer)
{
    //
    if(NumFields != buffer.NumFields) return *this;
    for(int i = 0; i < NumFields; i++)
        if(FieldSize[i] != buffer.FieldSize[i]) return *this;
    NextField = buffer.NextField;
    FixedLengthBuffer::operator=(buffer);
    return *this;
}
/********************************************
Fixed Field Buffer initialization
********************************************/
FixedFieldBuffer::FixedFieldBuffer(int numFields, int* fieldSize)
: FixedLengthBuffer(SumFieldSizes(numFields, fieldSize))
{
    Init (numFields, fieldSize);
}
/********************************************
Fixed Field Buffer method for getting
the total number of fields
********************************************/
int FixedFieldBuffer::NumberOfFields () const
{
    return NumFields;
}
/********************************************
clears the buffer for Field Buffer
********************************************/
void FixedFieldBuffer::Clear()
{
    FixedLengthBuffer::Clear();
    NextField=0;
    Buffer[0]=0;
    Packing = true;
}
/********************************************
adds a field to the buffer for Field Buffer
********************************************/
int FixedFieldBuffer::AddField(int fieldSize)
{
    Initialized = true;
    if(NumFields == MaxFields) return false;
    if(BufferSize + fieldSize > MaxBytes) return false;
    FieldSize[NumFields] = fieldSize;
    NumFields++;
    BufferSize += fieldSize;
    return true;
}

//static const char* headerStr = "Field";
//static const int headerStrSize = strlen (headerStr);
/********************************************
reads the header data for Field Buffer
********************************************/
int FixedFieldBuffer :: ReadHeader (istream & stream)
// read the header and check for consistency
// see WriteHeader for header record structure
{
    char* str = new char[headerStrSize+1];
    int numFields, *fieldSize;
    int result;
    // read the FixedLengthBufferheader
    result = FixedLengthBuffer::ReadHeader (stream);
    if (result< 0) return -1;
    // read the header string
    stream.read (str, headerStrSize);
    if (!stream.good()) return -1;
    if (strncmp (str, headerStr, headerStrSize) != 0) return -1;
    //read the record description
    stream. read ((char*)&numFields, sizeof(numFields));
    if (!stream) return -1; // failed to read numFields
    fieldSize = new int[numFields];
    for (int i = 0; i < numFields; i ++)
    stream.read ((char*)&fieldSize[i], sizeof(fieldSize [i]));

    if (Initialized) // check header for consistency
    {
    if (numFields != NumFields) return -1;
    for (int j = 0; j < numFields; j ++)
        if (fieldSize[j] != FieldSize[j]) return -1;
    return stream.tellg ();//II everything matches
    }
    //
    Init(numFields, fieldSize);
    return stream.tellg();
}
/********************************************
writes the header data for Field Buffer
********************************************/
int FixedFieldBuffer :: WriteHeader (ostream & stream) const
// write a buffer header to the beginning of the stream
// A header consists of the
// FixedLengthBufferheader
// FIXED5 bytes
//Variable sized record of length fields
// that describes the file records
// Header record size 2 bytes
// number of fields 4 bytes
// field sizes 4 bytes per field
{
    int result;
    if (!Initialized) return -1; // cannot write unitialized buffer
    // write the parent (FixedLengthBuffer} header
    result = FixedLengthBuffer::WriteHeader (stream);
    if (!result) return -1;
    //write the header string
    stream. write (headerStr, headerStrSize);
    if (!stream.good()) return -1;
    // write the record description
    stream. write ((char*)&NumFields, sizeof(NumFields));
    for (int i=0; i < NumFields; i ++)
    {
        stream.write((char*)&FieldSize[i], sizeof(FieldSize[i]));
    }
    if(!stream) return -1;
    return stream.tellp();
}
/********************************************
pack method for Field Buffer
********************************************/
int FixedFieldBuffer::Pack(const void*field, int size)
{
    if(NextField == NumFields || !Packing)
        return -1;
    int start = NextByte; //
    int packSize = FieldSize[NextField];
    if(size != -1 && packSize != size) return -1;
    memcpy(&Buffer[start], field, packSize);
    NextByte += packSize;
    NextField++;
    if(NextField == NumFields)
    {
        Packing = -1;
        NextField = NextByte;
    }
    return packSize;
}
/********************************************
unpack method for Field Buffer
********************************************/
int FixedFieldBuffer::Unpack(void * field, int maxBytes)
{
    Packing = false;
    if(NextField == NumFields)
        return -1;
    int start = NextByte;
    int packSize = FieldSize[NextField];
    memcpy(field, &Buffer[start], packSize);
    NextByte += packSize;
    NextField ++;
    if(NextField == NumFields) Clear ();//
    return packSize;
}
/********************************************
print method for Field Buffer
********************************************/
void FixedFieldBuffer::Print(ostream& stream) const
{
    FixedLengthBuffer::Print(stream);
    stream << endl;
    stream << "\t max fields " << MaxFields << " and actual " << NumFields << endl;
    for(int i = 0; i < NumFields; i++)
        stream << "\tfield " << i << " size " << FieldSize[i] << endl;
    Buffer[BufferSize]=0;
    stream << "NextByte " << NextByte << endl;
    stream << "Buffer " << Buffer<< " " << endl;
}
/********************************************
the intialization method for Field Buffer
********************************************/
int FixedFieldBuffer::Init(int maxFields)
{
    Clear();
    if(maxFields < 0) maxFields = 0;
    MaxFields = maxFields;
    FieldSize = new int(MaxFields);
    BufferSize = 0;
    NumFields = 0;
    return 1;
}
/********************************************
the second intialization method for Field Buffer
with parameters
********************************************/
int FixedFieldBuffer::Init(int numFields, int* fieldSize)
{
    Initialized = true;
    Init(numFields);

    for(int j= 0; j < numFields; j++)
        AddField(FieldSize[j]);
    return true;
}



