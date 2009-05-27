/***************************************************************************
                          simplemanagemeasureprogremote_c.h  - managing of remote
                                                   process data object
                             -------------------
    begin                : Fri Apr 07 2000
    copyright            : (C) 2000 - 2009 by Dipl.-Inform. Achim Spangler
    email                : a.spangler@osb-ag:de
    type                 : Header
    $LastChangedDate$
    $LastChangedRevision$
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
 * Copyright (C) 2000 - 2009 Dipl.-Inform. Achim Spangler                  *
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
#ifndef SIMPLE_MANAGE_MEASUREPROG_REMOTE_H
#define SIMPLE_MANAGE_MEASUREPROG_REMOTE_H

/* *************************************** */
/* ********** include headers ************ */
/* *************************************** */
#include "../../../impl/processelementbase_c.h"

// Begin Namespace IsoAgLib
namespace __IsoAgLib {
// ***************************************************************************************
// ************************* SimpleManageMeasureProgRemote_c **************************
// ***************************************************************************************


/**
  simple management of a Measure Prog value
  without flexible measurement programs
  (only with one shot value requests).
  */
class SimpleManageMeasureProgRemote_c : public ProcessElementBase_c
{
 public:
  /** allow SimpleManageSetpointRemote_c access to private elements */
  friend class SimpleManageSetpointRemote_c;
  friend class ProcDataRemoteSimpleSetpointSimpleMeasure_c;
  friend class ProcDataRemoteSimpleMeasure_c;
  /**
    constructor which initialse both pointers if given
    @param apc_processData optional pointer to containing ProcessData instance
  */
  SimpleManageMeasureProgRemote_c( ProcDataBase_c *const apc_processData = NULL )
  : ProcessElementBase_c( apc_processData )
  { init( apc_processData );};
  /**
    initialise this SimpleManageMeasureProgRemote_c instance to a well defined initial state
    @param apc_processData optional pointer to containing ProcessData instance
  */
  void init( ProcDataBase_c *const apc_processData = NULL );
  /** copy constructor */
  SimpleManageMeasureProgRemote_c( const SimpleManageMeasureProgRemote_c& acrc_src );
  /** assignment operator */
  const SimpleManageMeasureProgRemote_c& operator=( const SimpleManageMeasureProgRemote_c& acrc_src );


  /**
    deliver actual measurement value as long
    @param ab_sendRequest true -> request for new value is sent (optional, default false)
  */
  int32_t masterMeasurementVal(bool ab_sendRequest = false);
  /**
    send reset cmd for the measurement value
  */
  void resetMasterVal();
 private:
  /** process a measure prog message for remote process data */
  void processProg();

  int32_t mi32_masterVal;
};

}
#endif
