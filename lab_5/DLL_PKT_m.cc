//
// Generated file, do not edit! Created by nedtool 4.6 from DLL_PKT.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DLL_PKT_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(DLL_PKT);

DLL_PKT::DLL_PKT(const char *name, int kind) : ::cPacket(name,kind)
{
    this->id_var = 0;
    this->type_var = 0;
    this->initialTime_var = 0;
    this->finalTime_var = 0;
}

DLL_PKT::DLL_PKT(const DLL_PKT& other) : ::cPacket(other)
{
    copy(other);
}

DLL_PKT::~DLL_PKT()
{
}

DLL_PKT& DLL_PKT::operator=(const DLL_PKT& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void DLL_PKT::copy(const DLL_PKT& other)
{
    this->id_var = other.id_var;
    this->type_var = other.type_var;
    this->initialTime_var = other.initialTime_var;
    this->finalTime_var = other.finalTime_var;
}

void DLL_PKT::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->id_var);
    doPacking(b,this->type_var);
    doPacking(b,this->initialTime_var);
    doPacking(b,this->finalTime_var);
}

void DLL_PKT::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->id_var);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->initialTime_var);
    doUnpacking(b,this->finalTime_var);
}

int DLL_PKT::getId() const
{
    return id_var;
}

void DLL_PKT::setId(int id)
{
    this->id_var = id;
}

int DLL_PKT::getType() const
{
    return type_var;
}

void DLL_PKT::setType(int type)
{
    this->type_var = type;
}

double DLL_PKT::getInitialTime() const
{
    return initialTime_var;
}

void DLL_PKT::setInitialTime(double initialTime)
{
    this->initialTime_var = initialTime;
}

double DLL_PKT::getFinalTime() const
{
    return finalTime_var;
}

void DLL_PKT::setFinalTime(double finalTime)
{
    this->finalTime_var = finalTime;
}

class DLL_PKTDescriptor : public cClassDescriptor
{
  public:
    DLL_PKTDescriptor();
    virtual ~DLL_PKTDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(DLL_PKTDescriptor);

DLL_PKTDescriptor::DLL_PKTDescriptor() : cClassDescriptor("DLL_PKT", "cPacket")
{
}

DLL_PKTDescriptor::~DLL_PKTDescriptor()
{
}

bool DLL_PKTDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DLL_PKT *>(obj)!=NULL;
}

const char *DLL_PKTDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DLL_PKTDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int DLL_PKTDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *DLL_PKTDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
        "type",
        "initialTime",
        "finalTime",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int DLL_PKTDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "initialTime")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "finalTime")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DLL_PKTDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "double",
        "double",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *DLL_PKTDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int DLL_PKTDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DLL_PKT *pp = (DLL_PKT *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DLL_PKTDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DLL_PKT *pp = (DLL_PKT *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getId());
        case 1: return long2string(pp->getType());
        case 2: return double2string(pp->getInitialTime());
        case 3: return double2string(pp->getFinalTime());
        default: return "";
    }
}

bool DLL_PKTDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DLL_PKT *pp = (DLL_PKT *)object; (void)pp;
    switch (field) {
        case 0: pp->setId(string2long(value)); return true;
        case 1: pp->setType(string2long(value)); return true;
        case 2: pp->setInitialTime(string2double(value)); return true;
        case 3: pp->setFinalTime(string2double(value)); return true;
        default: return false;
    }
}

const char *DLL_PKTDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *DLL_PKTDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DLL_PKT *pp = (DLL_PKT *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


