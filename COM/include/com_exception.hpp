//
//  Copyright@2013, Illinois Rocstar LLC. All rights reserved.
//        
//  See LICENSE file included with this source or
//  (opensource.org/licenses/NCSA) for license information. 
//

#ifndef __COM_EXCEPTION_H__
#define __COM_EXCEPTION_H__

#include "com_basic.h"
#include <string>

COM_BEGIN_NAME_SPACE

/** Error codes */
enum Error_code { 
  COM_WARN_DUP_WINDOW = 100, COM_WARN_DUP_DATAITEM,
  COM_WARN_DUP_FUNCTION, COM_WARN_DUP_FUNC, COM_WARN_EMPTY_MESH,
  COM_WARN_MODULE_LOADED, COM_ERR_MODULE_NOTLOADED=1000, 
  COM_ERR_COULD_OPENLIB, COM_ERR_COULD_FINDSYM,
  COM_ERR_WAS_INITIALIZED, COM_ERR_WASNOT_INITIALIZED,
  COM_ERR_WINDOW_NOTEXIST, COM_ERR_PANE_NOTEXIST, 
  COM_ERR_DATAITEM_NOTEXIST, COM_ERR_FUNCTION_NOTEXIST, 
  COM_ERR_UNKNOWN_KEYWORD, COM_ERR_UNKNOWN_DATATYPE, 
  COM_ERR_INVALID_DATAITEM_NAME, COM_ERR_DATAITEM_INITIALIZED, 
  COM_ERR_DATAITEM_ALLOCATED, COM_ERR_DATAITEM_NOT_ALLOCATED, 
  COM_ERR_DATAITEM_CONST, COM_ERR_ALLOC_STRUCTURED, 
  COM_ERR_INVALID_DIMENSION, COM_ERR_INVALID_SIZE, 
  COM_ERR_INVALID_CAPACITY, COM_ERR_INVALID_STRIDE,  COM_ERR_INVALID_ADDR, 
  COM_ERR_F90FUNC, COM_ERR_UNKNOWN_INTENT,  
  COM_ERR_TOO_MANY_ARGS, COM_ERR_TOO_FEW_ARGS, 
  COM_ERR_INVALID_FUNCTION_HANDLE, COM_ERR_INVALID_DATAITEM_HANDLE,
  COM_ERR_INVALID_WINDOW_HANDLE, COM_ERR_INIT_DONE_PANEMAP,
  COM_ERR_INCOMPATIBLE_DATAITEMS,  COM_ERR_INCOMPATIBLE_TYPES, 
  COM_ERR_NOT_A_WINDOW_DATAITEM, COM_ERR_NOT_A_POINTER, COM_ERR_IMMUTABLE, 
  COM_ERR_NULL_POINTER, COM_ERR_OUT_OF_MEMORY, COM_ERR_INDEX_OUT_OF_BOUNDS, 
  COM_ERR_PARENT_SMALLER, COM_ERR_CHANGE_INHERITED, COM_ERR_RESIZE, 
  COM_ERR_INHERIT_MESH_LATE, COM_ERR_INHERIT_ST_NG, 
  COM_ERR_MIXED_GHOST, COM_ERR_GHOST_NODES, COM_ERR_GHOST_ELEMS, 
  COM_ERR_GHOST_LAYERS, COM_ERR_APPEND_ARRAY, COM_UNKNOWN_ERROR};

/** Encapsulates the states of an exception.  */
struct COM_exception {
  /// Constructor from an error code and optionally an error message.
  COM_exception( Error_code i, const std::string &m=std::string())
    : ierr(i), msg(m) {}
  /// Copy constructor.
  COM_exception( const COM_exception &e)
    : ierr(e.ierr), msg(e.msg) {}

  Error_code    ierr;   ///< Error code
  std::string   msg;    ///< Error message
};

/// Print out a given exception.
std::ostream &operator<<( std::ostream& os, const COM_exception &ex);

/// Append the information about the given frame to the string s.
std::string append_frame_info( const std::string &s, const char *frame,
			       const char *file, int line);

/// Macro for appending the information about the given frame to the string s.
#define append_frame( s, frame) \
   append_frame_info( s, #frame, __FILE__, __LINE__)

/// Macro for catching an exception and append the information 
/// to the current frame.
#define CATCHEXP_APPEND(frame) \
  catch ( COM_exception e) \
  { throw COM_exception( e.ierr, append_frame( e.msg, frame)); }

/// Macro for catching an deallocation exception and append the information 
/// to the current frame.
#define CATCHBADALLOC_APPEND(frame) \
  catch ( std::bad_alloc xa) \
  { throw COM_exception( COM_ERR_OUT_OF_MEMORY, append_frame( "", frame)); }

/// Macro for catching an unknown exception and append the information 
/// to the current frame.
#define CATCHREST_APPEND(frame) \
  catch (...) \
  { throw COM_exception( COM_UNKNOWN_ERROR, append_frame( "", frame)); }

COM_END_NAME_SPACE

#endif



