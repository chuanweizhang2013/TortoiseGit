
// TortoiseGit - a Windows shell extension for easy version control

// Copyright (C) 2009-2015 - TortoiseGit

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
#include "stdafx.h"
#include "gittype.h"
#include "Git.h"
#include "GitRevRefBrowser.h"

GitRevRefBrowser::GitRevRefBrowser()
{
	GitRev();
}

void GitRevRefBrowser::Clear()
{
	GitRev::Clear();
	m_Description.Empty();
	m_UpstreamRef.Empty();
}

int GitRevRefBrowser::GetGitRevRefMap(MAP_REF_GITREVREFBROWSER& map, CString& err, std::function<bool(const CString& refName)> filterCallback)
{
	err.Empty();
	MAP_STRING_STRING descriptions;
	g_Git.GetBranchDescriptions(descriptions);

	CString allRefs;
	if (g_Git.Run(L"git.exe for-each-ref --format=\"%(refname)%04 %(objectname)%04 %(upstream)%04 %(subject)%04 %(authorname)%04%(authordate:raw)%03\"", &allRefs, &err, CP_UTF8))
		return -1;

	int linePos = 0;
	CString singleRef;
	while (!(singleRef = allRefs.Tokenize(L"\03", linePos)).IsEmpty())
	{
		singleRef.TrimLeft(L"\r\n");
		int valuePos = 0;
		CString refName = singleRef.Tokenize(L"\04", valuePos);

		if (refName.IsEmpty() || (filterCallback && !filterCallback(refName)))
			continue;

		GitRevRefBrowser ref;
		ref.m_CommitHash = singleRef.Tokenize(L"\04", valuePos).Trim(); if (valuePos < 0) continue;
		ref.m_UpstreamRef = singleRef.Tokenize(L"\04", valuePos).Trim(); if (valuePos < 0) continue;
		ref.m_Subject = singleRef.Tokenize(L"\04", valuePos).Trim(); if (valuePos < 0) continue;
		ref.m_AuthorName = singleRef.Tokenize(L"\04", valuePos).Trim(); if (valuePos < 0) continue;
		CString date = singleRef.Tokenize(L"\04", valuePos).Trim();
		ref.m_AuthorDate = StrToInt(date);

		if (wcsncmp(refName, L"refs/heads/", 11) == 0)
			ref.m_Description = descriptions[refName.Mid(11)];

		map.insert(std::make_pair(refName, ref));
	}

	return 0;
}
