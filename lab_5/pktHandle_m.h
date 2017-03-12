//
// Generated file, do not edit! Created by nedtool 4.6 from pktHandle.msg.
//

#ifndef _PKTHANDLE_M_H_
#define _PKTHANDLE_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>pktHandle.msg:15</tt> by nedtool.
 * <pre>
 * //
 * // This program is free software: you can redistribute it and/or modify
 * // it under the terms of the GNU Lesser General Public License as published by
 * // the Free Software Foundation, either version 3 of the License, or
 * // (at your option) any later version.
 * // 
 * // This program is distributed in the hope that it will be useful,
 * // but WITHOUT ANY WARRANTY; without even the implied warranty of
 * // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * // GNU Lesser General Public License for more details.
 * // 
 * // You should have received a copy of the GNU Lesser General Public License
 * // along with this program.  If not, see http://www.gnu.org/licenses/.
 * //
 * packet PktHandle
 * {
 *     int id;
 * }
 * </pre>
 */
class PktHandle : public ::cPacket
{
  protected:
    int id_var;

  private:
    void copy(const PktHandle& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PktHandle&);

  public:
    PktHandle(const char *name=NULL, int kind=0);
    PktHandle(const PktHandle& other);
    virtual ~PktHandle();
    PktHandle& operator=(const PktHandle& other);
    virtual PktHandle *dup() const {return new PktHandle(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getId() const;
    virtual void setId(int id);
};

inline void doPacking(cCommBuffer *b, PktHandle& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, PktHandle& obj) {obj.parsimUnpack(b);}


#endif // ifndef _PKTHANDLE_M_H_
