//
// Generated file, do not edit! Created by nedtool 4.6 from R_PDU.msg.
//

#ifndef _R_PDU_M_H_
#define _R_PDU_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include <map>
#include<utility>
#include <omnetpp.h>
	using namespace std;
	typedef map<int,pair<int,pair<int,cGate*>>> table;		
// }}

/**
 * Class generated from <tt>R_PDU.msg:27</tt> by nedtool.
 * <pre>
 * packet R_PDU
 * {
 *     table m;
 *     int cost;
 * }
 * </pre>
 */
class R_PDU : public ::cPacket
{
  protected:
    table m_var;
    int cost_var;

  private:
    void copy(const R_PDU& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const R_PDU&);

  public:
    R_PDU(const char *name=NULL, int kind=0);
    R_PDU(const R_PDU& other);
    virtual ~R_PDU();
    R_PDU& operator=(const R_PDU& other);
    virtual R_PDU *dup() const {return new R_PDU(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual table& getM();
    virtual const table& getM() const {return const_cast<R_PDU*>(this)->getM();}
    virtual void setM(const table& m);
    virtual int getCost() const;
    virtual void setCost(int cost);
};

inline void doPacking(cCommBuffer *b, R_PDU& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, R_PDU& obj) {obj.parsimUnpack(b);}


#endif // ifndef _R_PDU_M_H_

