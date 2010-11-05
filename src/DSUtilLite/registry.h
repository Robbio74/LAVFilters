/*
 *      Copyright (C) 2010 Hendrik Leppkes
 *      http://www.1f0.de
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 */

#pragma once

#include <string>

bool CreateRegistryKey(HKEY hKeyRoot, LPCTSTR pszSubKey);

class CRegistry
{
public:
  CRegistry();
  CRegistry(HKEY hkeyRoot, LPCTSTR pszSubKey, HRESULT &hr);
  ~CRegistry();
  
  HRESULT Open(HKEY hkeyRoot, LPCTSTR pszSubKey);

  std::wstring ReadString(LPCTSTR pszKey, HRESULT &hr);
  HRESULT WriteString(LPCTSTR pszKey, LPCTSTR pszValue);

  DWORD ReadDWORD(LPCTSTR pszKey, HRESULT &hr);
  HRESULT WriteDWORD(LPCTSTR pszKey, DWORD dwValue);

  BOOL ReadBOOL(LPCTSTR pszKey, HRESULT &hr);
  HRESULT WriteBOOL(LPCTSTR pszKey, BOOL bValue);

private:
  HKEY *m_key;
};
