// TortoiseGit - a Windows shell extension for easy version control

// Copyright (C) 2009-2013 - TortoiseGit

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#pragma once

#include "SettingsPropPage.h"
#include "RegexEdit.h"
// CSettingsBugtraqConfig dialog

class CSettingsBugtraqConfig : public ISettingsPropPage
{
	DECLARE_DYNAMIC(CSettingsBugtraqConfig)

public:
	CSettingsBugtraqConfig(CString cmdPath);
	virtual ~CSettingsBugtraqConfig();

// Dialog Data
	enum { IDD = IDD_SETTINGSBUGTRAQ_CONFIG };
	UINT GetIconID() {return IDI_BUGTRAQ;}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnChange();

	CRegexEdit	m_BugtraqRegex1;

	CString	m_URL;
	BOOL	m_bNWarningifnoissue;
	CString	m_Message;
	BOOL	m_bNAppend;
	CString	m_Label;
	BOOL	m_bNNumber;
	CString	m_Logregex;
};
