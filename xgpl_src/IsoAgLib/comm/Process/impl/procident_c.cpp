/***************************************************************************
                          procident_c.cpp - identity of a process data instance
                                          for easy search
                             -------------------
    begin                : Fri Apr 07 2000
    copyright            : (C) 2000 - 2004 by Dipl.-Inform. Achim Spangler
    email                : a.spangler@osb-ag:de
    type                 : Source
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 * This file is part of the "IsoAgLib", an object oriented program library *
 * to serve as a software layer between application specific program and   *
 * communication protocol details. By providing simple function calls for  *
 * jobs like starting a measuring program for a process data value on a    *
 * remote ECU, the main program has not to deal with single CAN telegram   *
 * formatting. This way communication problems between ECU's which use     *
 * this library should be prevented.                                       *
 * Everybody and every company is invited to use this library to make a    *
 * working plug and play standard out of the printed protocol standard.    *
 *                                                                         *
 * Copyright (C) 2000 - 2004 Dipl.-Inform. Achim Spangler                  *
 *                                                                         *
 * The IsoAgLib is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published          *
 * by the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This library is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       *
 * General Public License for more details.                                *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with IsoAgLib; if not, write to the Free Software Foundation,     *
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA           *
 *                                                                         *
 * As a special exception, if other files instantiate templates or use     *
 * macros or inline functions from this file, or you compile this file and *
 * link it with other works to produce a work based on this file, this file*
 * does not by itself cause the resulting work to be covered by the GNU    *
 * General Public License. However the source code for this file must still*
 * be made available in accordance with section (3) of the                 *
 * GNU General Public License.                                             *
 *                                                                         *
 * This exception does not invalidate any other reasons why a work based on*
 * this file might be covered by the GNU General Public License.           *
 *                                                                         *
 * Alternative licenses for IsoAgLib may be arranged by contacting         *
 * the main author Achim Spangler by a.spangler@osb-ag:de                  *
 ***************************************************************************/

 /**************************************************************************
 *                                                                         *
 *     ###    !!!    ---    ===    IMPORTANT    ===    ---    !!!    ###   *
 * Each software module, which accesses directly elements of this file,    *
 * is considered to be an extension of IsoAgLib and is thus covered by the *
 * GPL license. Applications must use only the interface definition out-   *
 * side :impl: subdirectories. Never access direct elements of __IsoAgLib  *
 * and __HAL namespaces from applications which shouldnt be affected by    *
 * the license. Only access their interface counterparts in the IsoAgLib   *
 * and HAL namespaces. Contact a.spangler@osb-ag:de in case your applicat- *
 * ion really needs access to a part of an internal namespace, so that the *
 * interface might be extended if your request is accepted.                *
 *                                                                         *
 * Definition of direct access:                                            *
 * - Instantiation of a variable with a datatype from internal namespace   *
 * - Call of a (member-) function                                          *
 * Allowed is:                                                             *
 * - Instatiation of a variable with a datatype from interface namespace,  *
 *   even if this is derived from a base class inside an internal namespace*
 * - Call of member functions which are defined in the interface class     *
 *   definition ( header )                                                 *
 *                                                                         *
 * Pairing of internal and interface classes:                              *
 * - Internal implementation in an :impl: subdirectory                     *
 * - Interface in the parent directory of the corresponding internal class *
 * - Interface class name IsoAgLib::iFoo_c maps to the internal class      *
 *   __IsoAgLib::Foo_c                                                     *
 *                                                                         *
 * AS A RULE: Use only classes with names beginning with small letter :i:  *
 ***************************************************************************/

 /**************************************************************************
 *                                                                         *
 *     ###    !!!    ---    ===    IMPORTANT    ===    ---    !!!    ###   *
 * Each software module, which accesses directly elements of this file,    *
 * is considered to be an extension of IsoAgLib and is thus covered by the *
 * GPL license. Applications must use only the interface definition out-   *
 * side :impl: subdirectories. Never access direct elements of __IsoAgLib  *
 * and __HAL namespaces from applications which shouldnt be affected by    *
 * the license. Only access their interface counterparts in the IsoAgLib   *
 * and HAL namespaces. Contact a.spangler@osb-ag:de in case your applicat- *
 * ion really needs access to a part of an internal namespace, so that the *
 * interface might be extended if your request is accepted.                *
 *                                                                         *
 * Definition of direct access:                                            *
 * - Call of a (member-) function                                          *
 * - Instantiation of a variable in a datatype from internal namespace     *
 * Allowed is:                                                             *
 * - Instatiation of a variable in a datatype from interface namespace,    *
 *   even if this is derived from a base class inside an internal namespace*
 * - Call of member functions which are defined in the interface class     *
 *   definition ( header )                                                 *
 * Pairing of internal and interface classes:                              *
 * - Internal implementation in an :impl: subdirectory                     *
 * - Interface in the parent directory of the corresponding internal class *
 * - Interface class name IsoAgLib::iFoo_c maps to the internal class      *
 *   __IsoAgLib::Foo_c                                                     *
 *                                                                         *
 * AS A RULE: Use only classes with names beginning with small letter :i:  *
 ***************************************************************************/
#include "procident_c.h"
#include "process_c.h"

namespace __IsoAgLib {

#ifdef USE_DIN_9684
/** static instance for all ProcIdent_c objects that is solely used as a temp variable for the function
 * const DevKey_c& devKey() const
 * only in DIN 9684 mode
 */
DevKey_c ProcIdent_c::c_temp;
#endif


ProcIdent_c::_data::_data( const DevKey_c& rrefc_ownerDevKey, const DevKey_c& rrefc_devKey, uint16_t rui8_zaehlnum, uint16_t rui8_wert, uint16_t rui8_inst, uint16_t rui8_lis, uint16_t rui8_pri)
  : c_ownerDevKey(rrefc_ownerDevKey),
    c_devKey(rrefc_devKey),
    ui8_zaehlnum(rui8_zaehlnum),
    ui8_wert(rui8_wert),
    ui8_inst(rui8_inst),
    ui8_lis(rui8_lis),
    ui8_pri(rui8_pri)
    {}

    ProcIdent_c::_data::_data( const _data& rrefc_src)
  : c_ownerDevKey(rrefc_src.c_ownerDevKey),
    c_devKey(rrefc_src.c_devKey),
    ui8_zaehlnum(rrefc_src.ui8_zaehlnum),
    ui8_wert(rrefc_src.ui8_wert),
    ui8_inst(rrefc_src.ui8_inst),
    ui8_lis(rrefc_src.ui8_lis),
    ui8_pri(rrefc_src.ui8_pri)
    {}
/**
  constructor which can optional set all member values
    ISO parameter
    @param ps_elementDDI optional pointer to array of structure IsoAgLib::ElementDDI_s which contains DDI, isSetpoint and ValueGroup
                         (array is terminated by ElementDDI_s.ddi == 0xFFFF)
    @param ui16_element device element number
    DIN parameter
    @param rui8_lis optional LIS code of Process-Data
    @param rui8_wert optional WERT code of Process-Data
    @param rui8_inst optional INST code of Process-Data
    @param rui8_zaehlnum optional ZAEHLNUM  code of Process-Data

    common parameter
    @param rc_devKey optional DEV_KEY code of Process-Data
    @param rui8_pri PRI code of messages with this process data instance (default 2)
    @param rc_ownerDevKey optional DEV_KEY code of owner of Process-Data
           ( important if DEVCLASS and/or DEVCLASSINST differs from identity DEVKEY in rc_devKey; this is the case
             for process data from base data dictionary table (DEVCLASS==0), which is managed/owned by device of
             type DEVCLASS != 0)
    @param rpc_ownerDevKey pointer to the optional DEV_KEY var of the owner (for automatic update as soon
            as corresponding device is registered as having claimed address in monitor table list)
  */
  ProcIdent_c::ProcIdent_c(
#ifdef USE_ISO_11783
                           const IsoAgLib::ElementDDI_s* ps_elementDDI,
                           uint16_t ui16_element,
#endif
#ifdef USE_DIN_9684
                           uint8_t rui8_lis,
                           uint8_t rui8_wert,
                           uint8_t rui8_inst,
                           uint8_t rui8_zaehlnum,
#endif
                           const DevKey_c& rc_devKey,
                           uint8_t rui8_pri,
                           const DevKey_c& rc_ownerDevKey,
                           const DevKey_c *rpc_ownerDevKey,
                           int ri_singletonVecKey)
  : ClientBase( ri_singletonVecKey ),
    pc_ownerDevKey(NULL),
    data(DevKey_c::DevKeyUnspecified,DevKey_c::DevKeyUnspecified,0, 0, 0, 0, 0)
{
  init(
#ifdef USE_ISO_11783
            ps_elementDDI,
            ui16_element,
#endif
#ifdef USE_DIN_9684
            rui8_lis,
            rui8_wert,
            rui8_inst,
            rui8_zaehlnum,
#endif
            rc_devKey,
            rui8_pri,
            rc_ownerDevKey,
            rpc_ownerDevKey);
}

/** copy constructor */
ProcIdent_c::ProcIdent_c( const ProcIdent_c& rrefc_src )
  : ClientBase( rrefc_src ), data( rrefc_src.data)
{
  assignFromSource( rrefc_src );
}

/**
    initialisation which can set this process data instance to a defined intial state
    ISO parameter
    @param ps_elementDDI optional pointer to array of structure IsoAgLib::ElementDDI_s which contains DDI, isSetpoint and ValueGroup
                         (array is terminated by ElementDDI_s.ddi == 0xFFFF)
    @param ui16_element device element number
    DIN parameter
    @param rui8_lis LIS code of Process-Data
    @param rui8_wert WERT code of Process-Data
    @param rui8_inst INST code of Process-Data
    @param rui8_zaehlnum ZAEHLNUM  code of Process-Data

    common parameter
    @param rc_devKey DEV_KEY code of Process-Data
    @param rui8_pri optional PRI code of messages with this process data instance (default 2)
    @param rc_ownerDevKey optional DEV_KEY code of owner of Process-Data
           ( important if DEVCLASS and/or DEVCLASSINST differs from identity DEVKEY in rc_devKey; this is the case
             for process data from base data dictionary table (DEVCLASS==0), which is managed/owned by device of
             type DEVCLASS != 0)
    @param rpc_ownerDevKey pointer to the optional DEV_KEY var of the owner (for automatic update as soon
            as corresponding device is registered as having claimed address in monitor table list)
*/
void ProcIdent_c::init(
#ifdef USE_ISO_11783
            const IsoAgLib::ElementDDI_s* ps_elementDDI,
            uint16_t ui16_element,
#endif
#ifdef USE_DIN_9684
            uint8_t rui8_lis,
            uint8_t rui8_wert,
            uint8_t rui8_inst,
            uint8_t rui8_zaehlnum,
#endif
            const DevKey_c& rc_devKey,
            uint8_t rui8_pri,
            const DevKey_c& rc_ownerDevKey,
            const DevKey_c *rpc_ownerDevKey)
{
#ifdef USE_ISO_11783
  setElementDDI(ps_elementDDI);
  setElementNumber(ui16_element);
#endif
#ifdef USE_DIN_9684
  setLis(rui8_lis);
  setWert(rui8_wert);
  setInst(rui8_inst);
  setZaehlnum(rui8_zaehlnum);
#endif

  data.c_devKey = rc_devKey;
  setPri(rui8_pri);
  pc_ownerDevKey = rpc_ownerDevKey;

  // the DEV_KEY of ident is best defined by pointed value of rpc_ownerDevKey
  if ( rpc_ownerDevKey != 0 ) data.c_ownerDevKey = *rpc_ownerDevKey;
  // second choicer is explicit (not default) setting in rc_ownerDevKey
  else if ( rc_ownerDevKey.isSpecified() ) data.c_ownerDevKey = rc_ownerDevKey;
  // last choice is definition of c_ownerDevKey by process data identiy
  else data.c_ownerDevKey = rc_devKey;
}

/**
  copy constructor for class instance
  @rrrefcSrc source ProcIdent_c instance
  @return reference to source for cmd like "proc1 = proc2 = proc3;"
*/
ProcIdent_c& ProcIdent_c::operator=(const ProcIdent_c& rrefc_src){
  // first assign base class
  ClientBase::operator=(rrefc_src);
  // now assign flags of this class
  assignFromSource( rrefc_src );

  return *this;
}

/** internal base function for copy constructor and assignement */
void ProcIdent_c::assignFromSource( const ProcIdent_c& rrefc_src )
{
  setLis(rrefc_src.lis());
  data.c_devKey = rrefc_src.data.c_devKey;
  data.c_ownerDevKey = rrefc_src.data.c_ownerDevKey;
  pc_ownerDevKey = rrefc_src.pc_ownerDevKey;
#ifdef USE_ISO_11783
  // elementDDI() returns list reference, setElementDDI() expects pointer to list
  setElementDDI(&(rrefc_src.elementDDI()));
#endif
#ifdef USE_DIN_9684
  setWert(rrefc_src.wert());
  setInst(rrefc_src.inst());
  setZaehlnum(rrefc_src.zaehlnum());
#endif
  setPri(rrefc_src.pri());
}

/** default destructor which has nothing to do */
ProcIdent_c::~ProcIdent_c(){
}

/**
  set DEVCLASS and _instance_ of owner by giving pointer to owner DEV_KEY
  @param rpc_val pointer to owner DEV_KEY
*/
void ProcIdent_c::setOwnerDevKey(const DevKey_c* rpc_val)
{
  pc_ownerDevKey = rpc_val;
  data.c_ownerDevKey = *rpc_val;
}


#ifdef USE_ISO_11783
/**
   check if this item has the same identity as defined by the parameters,
   if rui8_devClassInst is 0xFF a lazy match disregarding pos is done
   (important for matching received process data msg);
   if INSTANCE is defined (!= 0xFF) then one of the following conditions must be true:<ul>
   <li>parameter INSTANCE == ident INSTANCE (devClassInst())
   <li>parameter INSTANCE == owner INSTANCE ( ownerDevKey().getDevClassInst() )
   <li>parameter rc_ownerDevKey == ownerDevKey()
   </ul>

   @param rui8_devClassReceiver compared DEVCLASS value

   ISO parameter
   @param rui8_devClassSender compare this parameter with owner devClass (only for remote, local calls: 0xFF)
   @param rui16_DDI compared DDI value
   @param rui16_element compared element value

   @return true -> this instance has same Process-Data identity
*/
bool ProcIdent_c::matchISO(
             uint8_t /*rui8_devClassReceiver*/,
             uint8_t rui8_devClassSender,
             uint16_t rui16_DDI,
             uint16_t rui16_element,
             const DevKey_c& rref_devKeyReceiver,
             const DevKey_c& rref_devKeySender
             ) const
{


  // check wether current element/DDI combination matches one list element in process data element/DDI list
  if (rui16_element != element()) return false;
  std::list<IsoAgLib::ElementDDI_s>::const_iterator iter;
  for (iter = data.l_elementDDI.begin(); iter != data.l_elementDDI.end(); iter++)
    if ( iter->ui16_DDI == rui16_DDI )
      break;

  if (iter == data.l_elementDDI.end())
    return false;

  if (rui8_devClassSender != 0xFF) {
    // check in remote case: check if devClass of ownerDevKey in procident matches devClass of sender
    if (ownerDevKey() != rref_devKeySender) return false;

  } else {
    // check in local case: check if procident devClass matches devClass of empf
    if (ownerDevKey() != rref_devKeyReceiver) return false;
  }

  if (!getProcessInstance4Comm().data().resolveCommandTypeForISO(*iter)) return false;
  // all previous tests are positive -> answer positive match
  return true;
}

/** check if this ProcIdent_c has the given DDI as element */
bool ProcIdent_c::hasDDI( uint16_t rui16_checkDDI ) const
{
  std::list<IsoAgLib::ElementDDI_s>::const_iterator iter;
  for (iter = data.l_elementDDI.begin(); iter != data.l_elementDDI.end(); iter++)
    if (iter->ui16_DDI == rui16_checkDDI)
      break;

  if (iter == data.l_elementDDI.end()) return false;
  else return true;
}

bool ProcIdent_c::hasType(bool rb_isSetpoint, GeneralCommand_c::ValueGroup_t t_ddiType) const
{
  std::list<IsoAgLib::ElementDDI_s>::const_iterator iter;
  for (iter = data.l_elementDDI.begin(); iter != data.l_elementDDI.end(); iter++)
    if ((iter->en_valueGroup == t_ddiType) && (iter->b_isSetpoint == rb_isSetpoint))
      break;

  if (iter == data.l_elementDDI.end()) return false;
  else return true;
}

#endif


#ifdef USE_DIN_9684
/**
   check if this item has the same identity as defined by the parameters,
   if rui8_devClassInst is 0xFF a lazy match disregarding pos is done
   (important for matching received process data msg);
   if INSTANCE is defined (!= 0xFF) then one of the following conditions must be true:<ul>
   <li>parameter INSTANCE == ident INSTANCE (devClassInst())
   <li>parameter INSTANCE == owner INSTANCE ( ownerDevKey().getDevClassInst() )
   <li>parameter rc_ownerDevKey == ownerDevKey()
   </ul>

   @param rui8_devClass compared DEVCLASS value

   DIN parameter
   @param rui8_lis compared LIS value
   @param rui8_wert compared WERT value
   @param rui8_inst compared INST value
   @param rui8_zaehlnum compared ZAEHLNUM value (default 0xFF == complete working width)

   @param rui8_devClassInst optional compared POS
   @param rc_ownerDevKey optional compared DEV_KEY of owner
   @return true -> this instance has same Process-Data identity
*/
bool ProcIdent_c::matchDIN(
             uint8_t rui8_devClass,
             uint8_t rui8_lis,
             uint8_t rui8_wert,
             uint8_t rui8_inst,
             uint8_t rui8_zaehlnum ,
             uint8_t rui8_devClassInst ,
             const DevKey_c& rc_ownerDevKey
             ) const
{

  if (zaehlnum() != rui8_zaehlnum) return false;
  if (lis() != rui8_lis) return false;
  if (wert() != rui8_wert) return false;
  if (inst() != rui8_inst) return false;

  if (devClass() != rui8_devClass) return false;

  // only return false for different pos setting, if rui8_devClassInst != 0xFF -> no lazy match is wanted
  // one of the _instance_ checks must be true to answer positive match
  if ( ( rui8_devClassInst != 0xFF )
    && ( devClassInst() != rui8_devClassInst )
    && (ownerDevKey().getDevClassInst() != rui8_devClassInst)
    && (ownerDevKey() != rc_ownerDevKey)) return false;

  // positive match, so call resolveCommandType
  if (!getProcessInstance4Comm().data().resolveCommandTypeForDIN()) return false;
  // all previous tests are positive -> answer positive match
  return true;
}
#endif


#ifdef USE_ISO_11783
bool ProcIdent_c::check4GroupMatch(uint16_t rui16_DDI, uint16_t rui16_element, const DevKey_c& rc_devKey)
{
  bool b_foundPair = false;
  // first check if DevKey matches
  if (rc_devKey != data.c_devKey) return b_foundPair;

  if (rui16_element != element()) return b_foundPair;

  for (std::list<IsoAgLib::ElementDDI_s>::const_iterator iter = data.l_elementDDI.begin(); iter != data.l_elementDDI.end(); iter++)
  {
    b_foundPair = isPair((*iter).ui16_DDI, rui16_DDI);
    if (b_foundPair) break;
  }
  return b_foundPair;
};

bool ProcIdent_c::check4GroupMatchExisting(uint16_t rui16_DDI, uint16_t rui16_element, const DevKey_c& rc_devKey)
{
  bool b_foundPair = false;
  // first check if DevKey matches
  if (rc_devKey != data.c_devKey) return b_foundPair;

  if (rui16_element != element()) return b_foundPair;

  return hasDDI(rui16_DDI);
};

bool ProcIdent_c::checkProprietary4GroupMatch(uint16_t rui16_element, const DevKey_c& rc_devKey)
{
  bool b_foundPair = false;
  // first check if DevClass is the same like ownerDevKey's DevClass
  if (rc_devKey.getDevClass() != pc_ownerDevKey->getDevClass()) return b_foundPair;

  // if it is not the same device element continue
  if (rui16_element != element()) return b_foundPair;

  std::list<IsoAgLib::ElementDDI_s>::const_iterator iter = data.l_elementDDI.begin();
  if (iter != data.l_elementDDI.end())
  {
    // device element was found
    b_foundPair = true;
  }
  return b_foundPair;
};


bool ProcIdent_c::isPair(uint16_t rui16_ElementDDI, uint16_t rui16_DDI)
{
  if (rui16_ElementDDI == rui16_DDI) return false; // same DDI -> "new DDI should not be added"
  // check if given DDI is proprietary
  if (rui16_ElementDDI > 0xDFFF) return false; // 0xDFFF is Request Default Process Data
  // calculate group membership of both DDIs
  // germane groups are from DDI 1 to 70 grouped to 5 and DDI 71 to 79 grouped to 3 and DDI 142/143
  uint8_t ui8_groupElementDDI1 = (rui16_ElementDDI / 5);
  uint8_t ui8_groupElementDDI2 = ((1 + rui16_ElementDDI) / 3);

  uint8_t ui8_groupDDI1 = (rui16_DDI / 5);
  uint8_t ui8_groupDDI2 = ((1 + rui16_DDI) / 3);

  // check if both are in same DDI group
  if ((ui8_groupElementDDI1 == ui8_groupDDI1) &&
      ((ui8_groupElementDDI1 <= 13) || ((ui8_groupElementDDI1 >= 20) && (ui8_groupElementDDI1 <= 22))))
    return true;
  if ((ui8_groupElementDDI2 == ui8_groupDDI2) && ((ui8_groupElementDDI2 >= 24) && (ui8_groupElementDDI2 <= 26)))
    return true;
  if (((rui16_ElementDDI == 0x8E) && (rui16_DDI == 0x8F)) || ((rui16_ElementDDI == 0x8F) && (rui16_DDI == 0x8E)))
    return true;
  return false;
};


bool ProcIdent_c::add2Group(uint16_t rui16_DDI)
{
  bool b_foundPair = false;

  for (std::list<IsoAgLib::ElementDDI_s>::const_iterator iter = data.l_elementDDI.begin(); iter != data.l_elementDDI.end(); iter++)
  {
    b_foundPair = isPair(iter->ui16_DDI, rui16_DDI);

    if (b_foundPair)
    {
      GeneralCommand_c::ValueGroup_t ddiType;
      bool b_isSetpoint;
      getDDIType(rui16_DDI, ddiType, b_isSetpoint);
      if (ddiType != GeneralCommand_c::noValue)
      {
        IsoAgLib::ElementDDI_s s_DDIToAdd = {rui16_DDI, b_isSetpoint, ddiType};
        data.l_elementDDI.push_back(s_DDIToAdd);
      }
      break;
    }
  }
  return b_foundPair;
};


bool ProcIdent_c::addProprietary2Group(uint16_t rui16_DDI, bool b_isSetpoint, GeneralCommand_c::ValueGroup_t ddiType)
{
  IsoAgLib::ElementDDI_s s_DDIToAdd = {rui16_DDI, b_isSetpoint, ddiType};
  data.l_elementDDI.push_back(s_DDIToAdd);

  return true;
};

void ProcIdent_c::getDDIType(uint16_t rui16_DDI, GeneralCommand_c::ValueGroup_t &ref_ddiType, bool &refb_isSetpoint)
{
  // check if given DDI is proprietary
  if (rui16_DDI > 0xDFFF)
  { // 0xDFFF is Request Default Process Data
    // proprietary DDIs are exact per default
    ref_ddiType = GeneralCommand_c::exactValue;
    refb_isSetpoint = true;
    return;
  }

  if ((rui16_DDI == 0x8E) || (rui16_DDI == 0x8D))
  {
    ref_ddiType = GeneralCommand_c::exactValue;
    refb_isSetpoint = true;
    return;
  }
  if (rui16_DDI == 0x8F)
  {
    ref_ddiType = GeneralCommand_c::exactValue;
    refb_isSetpoint = false;
    return;
  }

  if (((rui16_DDI >=0x1) && (rui16_DDI <= 0x46)) || ((rui16_DDI >=0x65) && (rui16_DDI <= 0x73)))
  {
    uint8_t ui8_groupDDI1 = rui16_DDI % 5;

    switch (ui8_groupDDI1)
    {
      case 0:
        ref_ddiType = GeneralCommand_c::maxValue;
        refb_isSetpoint = false;
        break;
      case 1:
        ref_ddiType = GeneralCommand_c::exactValue;
        refb_isSetpoint = true;
        break;
      case 2:
        ref_ddiType = GeneralCommand_c::exactValue;
        refb_isSetpoint = false;
        break;
      case 3:
        ref_ddiType = GeneralCommand_c::defaultValue;
        refb_isSetpoint = true;
        break;
      case 4:
        ref_ddiType = GeneralCommand_c::minValue;
        refb_isSetpoint = false;
        break;
    }
    return;
  }

  if ((rui16_DDI >=0x47) && (rui16_DDI <= 0x4F))
  {
    uint8_t ui8_groupDDI2 = (1 + rui16_DDI) % 3;

    switch (ui8_groupDDI2)
    {
      case 0:
        ref_ddiType = GeneralCommand_c::exactValue;
        refb_isSetpoint = true;
        break;
      case 1:
        ref_ddiType = GeneralCommand_c::exactValue;
        refb_isSetpoint = false;
        break;
      case 2:
        ref_ddiType = GeneralCommand_c::maxValue;
        refb_isSetpoint = false;
        break;
    }
    return;
  }

  // any other DDI
  ref_ddiType = GeneralCommand_c::exactValue;
  refb_isSetpoint = false;
}


bool ProcIdent_c::hasDDIType (uint16_t rui16_DDI, GeneralCommand_c::ValueGroup_t t_ddiType)
{
  bool b_isSetPoint;
  GeneralCommand_c::ValueGroup_t t_retDDIType;

  getDDIType (rui16_DDI, t_retDDIType, b_isSetPoint);

  return (t_retDDIType == t_ddiType);
}



void ProcIdent_c::setElementDDI(const IsoAgLib::ElementDDI_s* ps_elementDDI)
{
  data.l_elementDDI.clear();
  // check if pointer to strcut (array) is set (constructor call with NULL possible!)
  if (ps_elementDDI) {
    // in last struct element == 0xFFFF
    while (ps_elementDDI->ui16_DDI != 0xFFFF)
      data.l_elementDDI.push_back(*ps_elementDDI++);
  }
}

void ProcIdent_c::setElementDDI(const std::list<IsoAgLib::ElementDDI_s>* pl_elementDDI)
{
  data.l_elementDDI.clear();
  // check if pointer to struct (array) is set (constructor call with NULL possible!)
  if (pl_elementDDI) {
    for (std::list<IsoAgLib::ElementDDI_s>::const_iterator iter = pl_elementDDI->begin();
         iter != pl_elementDDI->end(); iter++)
        data.l_elementDDI.push_back(*iter);
  }
}

#endif

#if 0
/**
  claculates ident value for quick comparison
  @return single comparison value
*/
int32_t ProcIdent_c::calcIdentVal() const {
  int32_t i32_result = (static_cast<int32_t>(devKey().getDevClass()) & 0x7F   );

    #ifdef USE_ISO_11783
    #ifdef USE_DIN_9684
    if ( element() != 0xFFFF )
    #endif
    { // take ISO ident settings for compare
      i32_result |=
      (
        // @todo: find algorithm for handling element/DDI list
        (static_cast<int32_t>(element() & 0x1FF) << 7   ) // len 12 bit -> reduce to 9 Bit
      | (static_cast<int32_t>(DDI())             << 16  )
      );
    }
    #else
      i32_result |=
      (
        (static_cast<int32_t>(devKey().getDevClassInst())    << 8   )
      | (static_cast<int32_t>(lis())             << 12  )
      | (static_cast<int32_t>(inst())            << 16  )
      | (static_cast<int32_t>(wert())            << 20  )
      | (static_cast<int32_t>(zaehlnum())        << 24  )
      );
    #endif
  return i32_result;
};
#endif


} // end of namespace __IsoAgLib

