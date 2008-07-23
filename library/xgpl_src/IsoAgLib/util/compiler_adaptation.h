/***************************************************************************
                          compiler_adaptation.h  - defines to produce shorter
                                                 symbol names durig compile
                                                 (needed as workaround for buggy compilers)
                             -------------------
    begin                : Fri Apr 11 2003
    modified             : 22.07.2008 16:54:47  (f.muecke@osb-ag:de)
    copyright            : (C) 1999 - 2008 Dipl.-Inform. Achim Spangler
    email                : a.spangler@osb-ag:de
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
 * Copyright (C) 1999 - 2004 Dipl.-Inform. Achim Spangler                  *
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

#include "compiler_adaptation_unicode.h" // defines TCHAR etc.

/* ******************************************** */
/* * as some compilers can't manage long symbol */
/* * names, use some #defines to create shorter */
/* * names during the compile phase. The source */
/* * code can still use the long describing     */
/* * names                                      */
/* ******************************************** */

/* IMPORTANT:
   The current short names are the LONGEST possible
   version for Tasking 7.56.
   The most problematic case is the mangled version of
   the class name for Process_c, which is derived from
   SINGLETON_CLIENT2(Process_c, ProcDataLocalBase_c, ProcIdent_c, ProcDataRemoteBase_c, ProcIdent_c )
   --> the last ProcIdent_c would be cut down to some number which
       can't be resolved for link-recompile-stage
   --> if on any other change of names, the Tasking 7.56 results in link
       errors, the short names must be made shorter
       - it's the most probable reason for irritating
         link problems
 */
#if defined(__TSW_CPP__) && !defined(SHORTEN_SYMBOL_NAMES_DEFINE)
  #define SHORTEN_SYMBOL_NAMES_DEFINE
  #define __IsoAgLib                                   _I_N
  #define Process_c                                    Pr_c
  #define ProcDataLocalBase_c                          PrLB_c
  #define ProcDataRemoteBase_c                         PrRB_c
  #define ProcDataLocalSimpleMeasure_c                 PrLSM_c
  #define ProcDataLocalSimpleSetpoint_c                PrLSS_c
  #define ProcDataLocalSimpleMeasureSimpleSetpoint_c   PrLSMSS_c
  #define ProcDataSimpleMeasureLocal_c                 PrSML_c
  #define Simple_Manage_Setpoint_Local_c               SMSL_c
  #define ProcDataRemoteSimpleMeasure_c                PrRSM_c
  #define ProcDataRemoteSimpleSetpoint_c               PrRSS_c
  #define ProcDataRemoteSimpleMeasureSimpleSetpoint_c  PrRSMSS_c
  #define ProcDataSimpleMeasureRemote_c                PrSMR_c
  #define Simple_Manage_Setpoint_Remote_c              SMSR_c
  #define ProcIdent_c                                  PrId_c
  #define SingletonVec                                 SgV_c
  #define SingletonVecCont1                            SgVC1
  #define SingletonVecCont2                            SgVC2
  #define SingletonVecCont3                            SgVC3
  #define SingletonCont1                               SgC1
  #define SingletonCont2                               SgC2
  #define SingletonCont3                               SgC3
  #define SystemMgmt_c                                 SysMg_c
  #define IdentItem_c                                  IdIt_c
  #define Element_Base_c                               LElBas_c
  #define CAN_Customer_c                               CCus_c
#endif

#if defined(__TSW_CPP__)
  #define DEF_GET_POINTER_ADR_DEBUG_OUTPUT( pointer ) uint32_t( pointer )
#else
  #define DEF_GET_POINTER_ADR_DEBUG_OUTPUT( pointer ) pointer
#endif


#undef CNAMESPACE
#if defined( __TSW_CPP_70__ )
 #define CNAMESPACE
#elif defined( _MSC_VER )
	#if _MSC_VER <= 1200
		#define CNAMESPACE
	#else
	 #define CNAMESPACE std
	#endif
#elif defined( __IAR_SYSTEMS_ICC__ )
	#define CNAMESPACE
#else
 #define CNAMESPACE std
#endif

#ifdef __IAR_SYSTEMS_ICC__
	#define STL_NAMESPACE
#else
	/** usually the STL containers and algorithms are placed in std,
		but compilers like IAR just take the parts from ANSI C++ which they like,
		and change the other ....
	*/
	#define STL_NAMESPACE std
#endif

/** define whether to use SLIST or LIST
 * on win32 systems we'll use the native stl list
 * comparison */
#if !defined(USABLE_SLIST) && !defined(WIN32) && !defined(DO_USE_SLIST)
  #if defined (__GNUC__) || defined(__TSW_CPP__)
    /** both the GCC and Tasking Compiler support slist */
    #define USABLE_SLIST slist
    #define DO_USE_SLIST
  #endif
#endif

/** default: use std::list<T> */
#ifndef USABLE_SLIST
  #define USABLE_SLIST list
#endif


#if defined( __GNUC__ ) || __GNUC__ >= 4
  #define MALLOC_TEMPLATE(PAR) __gnu_cxx::malloc_allocator<PAR>
#else
  #define MALLOC_TEMPLATE(PAR) STL_NAMESPACE::__malloc_alloc_template<0>
#endif


//==============================================================================
// WINCE
// The following section covers Windows CE specific definitions and global
// macros! 
//==============================================================================
#ifdef _WIN32_WCE
  #ifndef WINCE
    #define WINCE
  #endif
  #ifndef WIN32
    #define WIN32
  #endif
#endif

// Windows CE does not support standard abort()!
#if defined(WINCE)
  #define MACRO_ISOAGLIB_ABORT() TerminateProcess(GetCurrentProcess(), 0)
  #define MACRO_ISOAGLIB_PERROR(x) printf("error: %s\n",x)
#else 
  #define MACRO_ISOAGLIB_ABORT() abort()
  #define MACRO_ISOAGLIB_PERROR(x) perror(x)  
#endif

#ifdef WINCE
  #include <winsock2.h>  // needs to be included BEFORE windows.h
  #include <windows.h>

  // sys/stat.h
  // define structure for returning status information
  #ifndef _STAT_DEFINED
  #define _STAT_DEFINED
  struct stat
  {
	//_dev_t st_dev;		// ID of device containing file
	//_ino_t st_ino;		// file serial number 
	//unsigned short st_mode; // mode of file (see below)
	//short st_nlink;		// number of links to the file
	//short st_uid;			// user ID of file
	//short st_gid;			// group ID of file
	//_dev_t st_rdev;		// device ID (if file is character or block special)
	unsigned long st_size;	// file size in bytes (if file is a regular file)
	//time_t st_atime;		// time of last access
	//time_t st_mtime;		// time of last data modification
	//time_t st_ctime;		// time of last status change
  // -- unused: --
  //	blksize_t st_blksize; 	// a filesystem-specific preferred I/O block size for
							// this object.  In some filesystem types, this may
							// vary from file to file
  //	blkcnt_t st_blocks;		// number of blocks allocated for this object
  };

  static __inline int stat( const char* _fileName, struct stat* _stat )
  {
	WIN32_FIND_DATAA wfd;
	_stat->st_size = wfd.nFileSizeLow;
	HANDLE h = FindFirstFileA( _fileName, &wfd );
	if ( h != INVALID_HANDLE_VALUE)
	{
		CloseHandle(h);
		return 0; // success!
	}
	//TODO: set errno
	return -1;	// failure!
  }

  static __inline int stat( const wchar_t* _fileName, struct stat* _stat )
  {
	WIN32_FIND_DATAW wfd;
	HANDLE h = FindFirstFileW( _fileName, &wfd );
	if ( h != INVALID_HANDLE_VALUE)
	{
		_stat->st_size = wfd.nFileSizeLow;
		CloseHandle(h);
		return 0; // success!
	}
	_stat->st_size = 0;
	//TODO: set errno
	return -1;	// failure!
  }
#endif // _STAT_DEFINED
#endif	//WINCE
