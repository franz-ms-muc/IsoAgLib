/* *************************************************************************
                          2_7_RemoteReadDataStdIso.cpp - tutorial for pure ISO address claim
                             -------------------
    begin                : Sun Jul 18 17:00:00 CEST 2004

    copyright            : (C) 2000 - 2004 by Dipl.-Inform. Achim Spangler
    email                : a.spangler@osb-ag:de
 ***************************************************************************/

/* *************************************************************************
 * This example main application is published NOT as GPL`ed Open Source,   *
 * so that you can include this source file in propietary closed projects. *
 * Everybody is encouraged to use the examples in the IsoAgLib_Examples    *
 * directory for a quick and easy start of development for IsoAgLib        *
 * applications.                                                           *
 *                                                                         *
 * So nobody is bound to publish changes of the example source files.      *
 * But every changed example, which could help learning the use of the     *
 * GPLed "IsoAgLib", is invited to be sent to the original author, so      *
 * that it can be published with the other examples.                       *
 ***************************************************************************/

/* *************************************************************************
 *                                                                         *
 * This is an example of "IsoAgLib", an object oriented program library    *
 * to serve as a software layer between application specific program and   *
 * communication protocol details. By providing simple function calls for  *
 * jobs like starting a measuring program for a process data value on a    *
 * remote ECU, the main program has not to deal with single CAN telegram   *
 * formatting. This way communication problems between ECU's which use     *
 * this library should be prevented.                                       *
 * Everybody and every company is invited to use this library to make a    *
 * working plug and play standard out of the printed protocol standard.    *
 *                                                                         *
 * Copyright (C) 1999 - 2004 Dipl.-Inform. Achim Spangler                  *
 *                                                                         *
 * The "IsoAgLib" is free software; you can redistribute it and/or         *
 * modify it under the terms of the GNU Lesser General Public License as   *
 * published by the Free Software Foundation; either version 2 of the      *
 * License, or (at your option) any later version.                         *
 *                                                                         *
 * The "IsoAgLib" is distributed in the hope that it will be useful, but   *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       *
 * General Public License for more details.                                *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with IsoAgLib; if not, write to the Free Software Foundation,     *
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111_1307  USA           *
 ***************************************************************************/

/* *********************************************************************** */
/** \example 2_7_RemoteReadDataStdIso.cpp
 * This tutorial shall provide a simple base program, which creates some
 * remote process data, for which a measurement program is started for
 * automatic periodic value update.
 * Demonstrate optional usage of handler class with a method which is automatically
 * called on each measurement value receive.
 *
 * <H1>What is demonstrated</H1>
 * <ol>
 * <li>Create some remote standard process data and request measurement data from remote device
 * <ul>
 *	<li>Standard remote process data class IsoAgLib::iProcDataRemote_c
 *	<li>Use constructor IsoAgLib::iProcDataRemote_c::iProcDataRemote_c to create variable with defined property
 *	<li>Use IsoAgLib::iProcDataRemote_c::init to define process data properties independent from instantiation ( needed especially for arrays of process data )
 *	<li>Use IsoAgLib::iProcDataRemote_c::prog() to retrive measurement program information as class IsoAgLib::iMeasureProgRemote_c
 *	<li>USe IsoAgLib::iProcDataRemote_c::masterVal to access current measurement value
 *	<li>Use IsoAgLib::iMeasureProgRemote_c::addSubprog , IsoAgLib::iMeasureProgRemote_c::start and IsoAgLib::iMeasureProgRemote_c::stop to control programs
 *	<li>Use IsoAgLib::iMeasureProgRemote_c::lastMeasurementReceive to check for last receive time
 * </ul>
 * <li>Trigger periodic activities of ISO<i><sub>AgLib</sub></i>
 * 	<ul>
 *	<li>Core class IsoAgLib::iScheduler_c for scheduling of all periodic activities
 *	<li>Method IsoAgLib::iScheduler_c::timeEvent() which can<ul>
 *		<li>Perform activities until defined rl_endTime is reached, which is important
 *			for scheduling purposes of whole system - call by IsoAgLib::iScheduler_c::timeEvent( rl_endTime )
 *		<li>Process all received CAN messages until all receive buffers are empty
 *			-> simple call, but can lead to deadlock on to high CAN load
 *		</ul>
 *	</ul>
 * <li>Create local identity, for which the ISO<i><sub>AgLib</sub></i> performs an address claim,
 *		so that the ECU can access the <b><i>ISO11783</i></b> BUS with IsoAgLib::iIdentItem_c
 *		and its constructor IsoAgLib::iIdentItem_c::iIdentItem_c
 * </ol>
 * <H1>Where to look for further information</H1>
 * <ol>
 * <li>Overview on process data at \ref ProcDataPage
 * <li>Overview information on Scheduling at \ref SchedulerPage
 * <li>Overview on global communication functions at \ref CommOverPage
 * </ol>
 *
 * <H1>Howto compile this example</H1>
 * <ol>
 * <li>Call the script update_makefile.sh with the spec file
 *     conf_2_7_RemoteReadDataStdIso from the directory where the spec file
 *     and the script are located<br>
 *     <i>#> update_makefile.sh conf_2_7_RemoteReadDataStdIso</i>
 * <li><b>Only Linux:</b><ul>
 *     <li><i>#>cd 2_7_RemoteReadDataStdIso</i> to go to the subdirectory 2_7_RemoteReadDataStdIso
 *     <li><i>#> make</i><br>
 *     <li>GNU make will then use the fresh created Makefile to create the executable 2_7_RemoteReadDataStdIso in this directory
 *     </ul>
 * <li><b>Other Development Environments:</b><ul>
 *     <li>import the file list in filelist-2_7_RemoteReadDataStdIso.txt into the IDE of your choice
 *     <li>set <i>-DPRJ_USE_AUTOGEN_CONFIG=config_2_7_RemoteReadDataStdIso</i> as global project parameter
 *     <li>add target specific headers, sources or libraries to the project
 *     <li>let your IDE build the project
 *   </ul>
 * </ol>
 *
 * <H1>Needed Project Specification</H1>
 * The project specification, which is needed as input for
 * the generation script update_makefile.sh is described in
 * \ref PrjSpec2_7_RemoteReadDataStdIso__pc_linux__simulating__simulating .
 *
 * The adopted project specifications for different setups:
 * <ul>
 * <li>Configuration Setups for Linux on PC:
 * <ul>
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_linux__rte__rte
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_linux__rte__simulating
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_linux__rte__sys
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_linux__simulating__rte
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_linux__simulating__simulating
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_linux__simulating__sys
 *	</ul>
 * <li>Configuration Setups for Win32 on PC:
 * <ul>
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_win32__vector_canlib__simulating
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_win32__vector_xl_drv_lib__simulating
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_win32__vector_canlib__sys
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_win32__vector_xl_drv_lib__sys
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_win32__simulating__simulating
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pc_win32__simulating__sys
 * 	</ul>
 * <li>Configuration Setupts for some embedded targets:
 * <ul>
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__esx__sys__sys
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__imi__sys__sys
 *		<li> \ref PrjSpec2_7_RemoteReadDataStdIso__pm167__sys__sys
 *	</ul>
 * </ul>
 *
 * <H1>Resulting Project File List</H1>
 * See \ref FileLists2_7_RemoteReadDataStdIso__pc_linux__simulating__simulating for needed files
 * ( filelist-2_7_RemoteReadDataStdIso-doxygen_import.txt ),
 *  with \ref SrcList2_7_RemoteReadDataStdIso__pc_linux__simulating__simulating containing the needed sources
 *  and with \ref HdrList2_7_RemoteReadDataStdIso__pc_linux__simulating__simulating containing the needed headers.
 *
 * The resulting file lists for different setups:
 * <ul>
 * <li>Configuration Setups for Linux on PC:
 * <ul>
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_linux__rte__rte
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_linux__rte__simulating
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_linux__rte__sys
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_linux__simulating__rte
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_linux__simulating__simulating
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_linux__simulating__sys
 *	</ul>
 * <li>Configuration Setups for Win32 on PC:
 * <ul>
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_win32__vector_canlib__simulating
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_win32__vector_xl_drv_lib__simulating
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_win32__vector_canlib__sys
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_win32__vector_xl_drv_lib__sys
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_win32__simulating__simulating
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pc_win32__simulating__sys
 * 	</ul>
 * <li>Configuration Setupts for some embedded targets:
 * <ul>
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__esx__sys__sys
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__imi__sys__sys
 *		<li> \ref FileLists2_7_RemoteReadDataStdIso__pm167__sys__sys
 *	</ul>
 * </ul>
 *
 * <H1>Resulting Project Configuration Header</H1>
 * This header is automatically included by xgpl_src/Application_Config/isoaglib_config.h
 * if the #define PRJ_USE_AUTOGEN_CONFIG is set to
 * config_2_7_RemoteReadDataStdIso ( see also at \ref PrjConfig2_7_RemoteReadDataStdIso ).
 *                                                                         */
/* *************************************************************************/

/** the define PRJ_USE_AUTOGEN_CONFIG is used by xgpl_src/Application_Config/isoaglib_config.h
    to include project specific configuration settings.
		Set this define in the project file or Makefile of the whole
		project, so that each source file is compiled with this setting
	*/
#ifndef PRJ_USE_AUTOGEN_CONFIG
	#define PRJ_USE_AUTOGEN_CONFIG config_2_7_RemoteReadDataStdIso.h
#endif

// include the central interface header for the hardware adaption layer part
// of the "IsoAgLib"

/* include some needed util headers */
//#include <IsoAgLib/util/config.h>
#include <IsoAgLib/util/igetypos_c.h>

/* include headers for the needed drivers */
#include <IsoAgLib/driver/system/isystem_c.h>
#include <IsoAgLib/driver/can/icanio_c.h>

/* include the central interface header for the communication layer part
   of the "IsoAgLib" */
#include <IsoAgLib/comm/Scheduler/ischeduler_c.h>
#include <IsoAgLib/comm/SystemMgmt/iidentitem_c.h>
#include <IsoAgLib/comm/SystemMgmt/isystemmgmt_c.h>
#include <IsoAgLib/comm/Process/proc_c.h>
#include <IsoAgLib/comm/Process/Remote/Std/iprocdataremote_c.h>

// if following define is active, the version with HANDLER usage is compiled
// the handler allows immediate reaction on each received value - no polling is needed
#define USE_PROC_HANDLER

#ifdef USE_PROC_HANDLER
	#include <IsoAgLib/comm/Process/processdatachangehandler_c.h>
#endif

#if defined(WIN32) || defined(SYSTEM_PC)
	#define LOG_INFO std::cout
	#include <iostream>
#else
	#define LOG_INFO getIrs232Instance()
#endif


// the interface objects of the IsoAgLib are placed in the IsoAgLibAll namespace
// -> include all elements of this area for easy access
// with this command the text part "IsoAgLib::" can be avoided, which
// is needed for the documentation generator
using namespace IsoAgLib;

/** define channel to write:
 - access data from tutorial examples 2_0_xy to 2_6_nm which listen to requests on channel 0
    -> select here the corresponding channel in your configuration
			 ( e.g. select channel 1 for a 2-channel CAN-Hardware )
	- simply write on channel 0, when no connection needed, or the connection is
	  realized with another external connection
*/
static const int32_t cui32_canChannel = 0;


/** dummy function to use the information of the remote device work state */
void handleRemoteWorkState( bool rb_isWorking )
{ // do something
	LOG_INFO << "Received New Working State: " << rb_isWorking << "\r\n";
}
/** dummy function to use the information of the remote device application rate */
void handleRemoteApplicationRate( uint32_t rui32_applicationRate )
{ // do something
	LOG_INFO << "Received New Application Rate: " << rui32_applicationRate << "\r\n";
}

#ifdef USE_PROC_HANDLER

const uint8_t cui8_indexWorkState = 0;
const uint8_t cui8_indexApplicationRate = 1;
IsoAgLib::iProcDataRemote_c arr_procData[2];

class MyProcDataHandler_c : public IsoAgLib::ProcessDataChangeHandler_c
{
	public:
		/** react on new received measurement update for remote process data
			* (remote system which manages the process data sent new value on request or
			*  during active measurement programm)
			* @param rc_src general event source class, which provides conversion functions to get needed event source class
			* @param ri32_val new value, which caused the event (for immediate access)
			* @param rc_callerGetyPos GetyPos of calling device - i.e. which sent new setpoint
			* @return true -> handler class reacted on change event
			*/
		virtual bool processMeasurementUpdate( EventSource_c rc_src, int32_t ri32_val, iGetyPos_c rc_callerGetyPos, bool rb_change );
};

bool MyProcDataHandler_c::processMeasurementUpdate( EventSource_c rc_src, int32_t ri32_val, iGetyPos_c /* rc_callerGetyPos */, bool rb_change )
{

   printf("measure value: %d\n", ri32_val);

   if (ri32_val > 0xa0) {
		arr_procData[cui8_indexWorkState].prog().stop();
    printf("measurement stopped\n");
  }
   
	if ( ! rb_change )
	{ // don't handle values which don't contain new value - maybe still relevant for other applications
		return false; // indicate that this information is not again handled - just ignored
	}

	// use helper function to get automatically casted pointer to used process data type
	uint16_t ui16_index = rc_src.makeIProcDataRemote() - arr_procData;
	switch ( ui16_index )
	{
		case cui8_indexWorkState:
			handleRemoteWorkState( ri32_val );
			break;
		case cui8_indexApplicationRate:
			handleRemoteApplicationRate( ri32_val );
			break;
	}
	// answer to IsoAgLib that this new setpoint is handled
	return true;
}

// create one class instance for the handler
MyProcDataHandler_c c_myMeasurementHandler;
#endif


int main()
{ // init CAN channel with 250kBaud at needed channel ( count starts with 0 )
  getIcanInstance().init( cui32_canChannel, 250 );
  // variable for GETY_POS
  // default with primary cultivation mounted back
  IsoAgLib::iGetyPos_c c_myGtp( 2, 0 );

  // start address claim of the local member "IMI"
  // if GETY_POS conflicts forces change of POS, the
  // IsoAgLib can cahnge the c_myGtp val through the pointer to c_myGtp
  bool b_selfConf = true;
  uint8_t ui8_indGroup = 2,
      b_func = 25,
      b_wantedSa = 128,
      b_funcInst = 0,
      b_ecuInst = 0;
  uint16_t ui16_manufCode = 0x7FF;
  uint32_t ui32_serNo = 27;

	// start address claim of the local member "IMI"
  // if GETY_POS conflicts forces change of POS, the
  // IsoAgLib can change the c_myGtp val through the pointer to c_myGtp
  IsoAgLib::iIdentItem_c c_myIdent( &c_myGtp,
      b_selfConf, ui8_indGroup, b_func, ui16_manufCode,
      ui32_serNo, b_wantedSa, 0xFFFF, b_funcInst, b_ecuInst);

	// device type of remote ECU
	IsoAgLib::iGetyPos_c c_remoteDeviceType( 0x5, 0 );


	#ifdef USE_PROC_HANDLER
  // DIN:
  // workstate of MiniVegN (LIS=0, GETY=2, WERT=1, INST=0)
  //arr_procData[cui8_indexWorkState].init(0, c_remoteDeviceType, 0x1, 0x0, 0xFF, 2, c_remoteDeviceType, &c_myGtp, &c_myMeasurementHandler);
  // WERT == 5 -> device specific material flow information (mostly 5/0 -> distributed/harvested amount per area )
  //arr_procData[cui8_indexApplicationRate].init(0, c_remoteDeviceType, 0x5, 0x0, 0xFF, 2, c_remoteDeviceType, &c_myGtp, &c_myMeasurementHandler);
  
  // ISO:
  // DDI 2, element 2
  arr_procData[cui8_indexWorkState].init(2, 2, c_remoteDeviceType, 2, c_remoteDeviceType, &c_myGtp, &c_myMeasurementHandler);
  // DDI 1, element 1
  arr_procData[cui8_indexApplicationRate].init(1, 1, c_remoteDeviceType, 2, c_remoteDeviceType, &c_myGtp, &c_myMeasurementHandler);
  #else
  // workstate of MiniVegN (LIS=0, GETY=2, WERT=1, INST=0)
	// of device with device type/subtype=5/0
	IsoAgLib::iProcDataRemote_c c_workState(0, c_remoteDeviceType, 0x1, 0x0, 0xFF, 2, c_remoteDeviceType, &c_myGtp);
	int32_t i32_lastWorkStateReceive = 0;
  // WERT == 5 -> device specific material flow information (mostly 5/0 -> distributed/harvested amount per area )
	// of device with device type/subtype=5/0
  IsoAgLib::iProcDataRemote_c c_applicationRate(0, c_remoteDeviceType, 0x5, 0x0, 0xFF, 2, c_remoteDeviceType, &c_myGtp);
	int32_t i32_lastApplicationRateReceive = 0;
	#endif

	// variable to control if programs are running at the moment
	bool b_runningPrograms = false;

  /** IMPORTANT:
	  - The following loop could be replaced of any repeating call of
			IsoAgLib::getISchedulerInstance().timeEvent();
			which is needed to perform all internal activities of the IsoAgLib.
		- Define the time intervall for IsoAgLib::getISchedulerInstance().timeEvent()
			in a way, that allows IsoAgLib to trigger all reactions on BUS
			in the ISO 11783 defined time resolution - especially the address
			claim process has some tight time restrictions, that suggest
			a trigger rate of at least 100msec ( you could call the function
			only during address claim, mask updload and other special
			circumstances in a high repetition rate )
		- The main loop is running until iSystem_c::canEn() is returning false.
			This function can be configured by the #define CONFIG_BUFFER_SHORT_CAN_EN_LOSS_MSEC
			in isoaglib_config.h to ignore short CAN_EN loss.
		- This explicit control of power state without automatic powerdown on CanEn loss
			can be controled with the central config define
			#define CONFIG_DEFAULT_POWERDOWN_STRATEGY IsoAgLib::PowerdownByExplcitCall
			or
			#define CONFIG_DEFAULT_POWERDOWN_STRATEGY IsoAgLib::PowerdownOnCanEnLoss
			in the header xgpl_src/Application_Config/isoaglib_config.h
		- This can be also controlled during runtime with the function call:
			getIsystemInstance().setPowerdownStrategy( IsoAgLib::PowerdownByExplcitCall )
			or
			getIsystemInstance().setPowerdownStrategy( IsoAgLib::PowerdownOnCanEnLoss )
	*/
	while ( iSystem_c::canEn() )
	{ // run main loop
		// IMPORTANT: call main timeEvent function for
    
    usleep(50000);
    
		// all time controlled actions of IsoAgLib    
		IsoAgLib::getISchedulerInstance().timeEvent();

		if ( ! getISystemMgmtInstance().existMemberGtp(c_myGtp, true) ) continue;
		if ( ( ! b_runningPrograms ) && ( getISystemMgmtInstance().existMemberGtp(c_remoteDeviceType, true) ) )
		{ // remote device is active and no program is running
			b_runningPrograms = true;
			LOG_INFO << "\r\nRemote ECU found - try to start measurement programs" << "\r\n";
			#ifdef USE_PROC_HANDLER
			arr_procData[cui8_indexWorkState].prog().addSubprog(Proc_c::TimeProp, 4000);
			arr_procData[cui8_indexWorkState].prog().start(Proc_c::Target, Proc_c::TimeProp, Proc_c::DoVal);
			//arr_procData[cui8_indexApplicationRate].prog().addSubprog(Proc_c::TimeProp, 1000);
			//arr_procData[cui8_indexApplicationRate].prog().start(Proc_c::Target, Proc_c::TimeProp, Proc_c::DoVal);
			#else
			c_workState.prog().addSubprog(Proc_c::TimeProp, 1000);
			c_workState.prog().start(Proc_c::Target, Proc_c::TimeProp, Proc_c::DoVal);
			c_applicationRate.prog().addSubprog(Proc_c::TimeProp, 1000);
			c_applicationRate.prog().start(Proc_c::Target, Proc_c::TimeProp, Proc_c::DoVal);
			#endif
		}
		else if ( ! getISystemMgmtInstance().existMemberGtp(c_remoteDeviceType, true) )
		{ // no more active -> stop
			b_runningPrograms = false;
			#ifdef USE_PROC_HANDLER
			arr_procData[cui8_indexWorkState].prog().stop();
			//arr_procData[cui8_indexApplicationRate].prog().stop();
			#else
			c_workState.prog().stop();
			c_applicationRate.prog().stop();
			#endif
		}
		#ifndef USE_PROC_HANDLER
		// poll for current measurement val -> check for receive time
		if ( c_workState.prog().lastMeasurementReceive() > i32_lastWorkStateReceive )
		{ // new measurement received
			i32_lastWorkStateReceive = c_workState.prog().lastMeasurementReceive();
			handleRemoteWorkState( c_workState.masterVal() );
		}
		if ( c_applicationRate.prog().lastMeasurementReceive() > i32_lastApplicationRateReceive )
		{ // new measurement received
			i32_lastApplicationRateReceive = c_applicationRate.prog().lastMeasurementReceive();
			handleRemoteApplicationRate( c_applicationRate.masterVal() );
		}
		#endif
	}
  return 1;
}
