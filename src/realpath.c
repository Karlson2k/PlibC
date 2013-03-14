/*
     This file is part of PlibC.
     (C) 2005 Nils Durner (and other contributing authors)

	   This library is free software; you can redistribute it and/or
	   modify it under the terms of the GNU Lesser General Public
	   License as published by the Free Software Foundation; either
	   version 2.1 of the License, or (at your option) any later version.
	
	   This library is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	   Lesser General Public License for more details.
	
	   You should have received a copy of the GNU Lesser General Public
	   License along with this library; if not, write to the Free Software
	   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 * @file src/realpath.c
 * @brief realpath()
 */

#include "plibc_private.h"

char *realpath(const char *file_name, char *resolved_name, size_t resolv_buffer_length)
{
  long lRet;
  wchar_t szFile[_MAX_PATH + 1];
  wchar_t szRet[_MAX_PATH + 1];
  wchar_t *wresult;
  char *result = NULL;

  if (_plibc_utf8_mode == 1)
  {
    lRet = plibc_conv_to_win_pathwconv(file_name, szFile, _MAX_PATH );
    if (lRet != ERROR_SUCCESS)
    {
      SetErrnoFromWinError(lRet);
      return NULL;
    }
    wresult = _wfullpath(szRet, szFile, MAX_PATH);
    SetErrnoFromWinError(GetLastError());
    if (wresult)
      wchartostr (szRet, &result, CP_UTF8);
    return result;
  }
  else
  {
    lRet = plibc_conv_to_win_path(file_name, (char *) szFile, _MAX_PATH );
    if (lRet != ERROR_SUCCESS)
    {
      SetErrnoFromWinError(lRet);
      return NULL;
    }
    result = _fullpath(resolved_name, (char *) szFile, resolv_buffer_length);
    SetErrnoFromWinError(GetLastError());
    return result;
  }
}

/* end of realpath.c */
