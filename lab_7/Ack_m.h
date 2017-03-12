//
// Generated file, do not edit! Created by nedtool 4.6 from Ack.msg.
//

#ifndef _ACK_M_H_
#define _ACK_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>Ack.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet Ack
 * {
 *     int id;
 *     char type;
 * }
 * </pre>
 */
class Ack : public ::cPacket
{
  protected:
    int id_var;
    char type_var;

  private:
    void copy(const Ack& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ack&);

  public:
    Ack(const char *name=NULL, int kind=0);
    Ack(const Ack& other);
    virtual ~Ack();
    Ack& operator=(const Ack& other);
    virtual Ack *dup() const {return new Ack(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getId() const;
    virtual void setId(int id);
    virtual char getType() const;
    virtual void setType(char type);
};

inline void doPacking(cCommBuffer *b, Ack& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ack& obj) {obj.parsimUnpack(b);}


#endif // ifndef _ACK_M_H_

