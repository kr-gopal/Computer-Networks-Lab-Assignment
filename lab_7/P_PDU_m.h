//
// Generated file, do not edit! Created by nedtool 4.6 from P_PDU.msg.
//

#ifndef _P_PDU_M_H_
#define _P_PDU_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>P_PDU.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet P_PDU
 * {
 *     int id;
 *     char type;
 * }
 * </pre>
 */
class P_PDU : public ::cPacket
{
  protected:
    int id_var;
    char type_var;

  private:
    void copy(const P_PDU& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const P_PDU&);

  public:
    P_PDU(const char *name=NULL, int kind=0);
    P_PDU(const P_PDU& other);
    virtual ~P_PDU();
    P_PDU& operator=(const P_PDU& other);
    virtual P_PDU *dup() const {return new P_PDU(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getId() const;
    virtual void setId(int id);
    virtual char getType() const;
    virtual void setType(char type);
};

inline void doPacking(cCommBuffer *b, P_PDU& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, P_PDU& obj) {obj.parsimUnpack(b);}


#endif // ifndef _P_PDU_M_H_
