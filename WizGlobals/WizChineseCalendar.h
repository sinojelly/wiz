#pragma once

__declspec( selectany ) UINT WIZ_CHINESECALENDAR_LUNARINFO[] = 
{
	0x04bd8,0x04ae0,0x0a570,0x054d5,0x0d260,0x0d950,0x16554,0x056a0,0x09ad0,0x055d2,
	0x04ae0,0x0a5b6,0x0a4d0,0x0d250,0x1d255,0x0b540,0x0d6a0,0x0ada2,0x095b0,0x14977,
	0x04970,0x0a4b0,0x0b4b5,0x06a50,0x06d40,0x1ab54,0x02b60,0x09570,0x052f2,0x04970,
	0x06566,0x0d4a0,0x0ea50,0x06e95,0x05ad0,0x02b60,0x186e3,0x092e0,0x1c8d7,0x0c950,
	0x0d4a0,0x1d8a6,0x0b550,0x056a0,0x1a5b4,0x025d0,0x092d0,0x0d2b2,0x0a950,0x0b557,
	0x06ca0,0x0b550,0x15355,0x04da0,0x0a5d0,0x14573,0x052d0,0x0a9a8,0x0e950,0x06aa0,
	0x0aea6,0x0ab50,0x04b60,0x0aae4,0x0a570,0x05260,0x0f263,0x0d950,0x05b57,0x056a0,
	0x096d0,0x04dd5,0x04ad0,0x0a4d0,0x0d4d4,0x0d250,0x0d558,0x0b540,0x0b5a0,0x195a6,
	0x095b0,0x049b0,0x0a974,0x0a4b0,0x0b27a,0x06a50,0x06d40,0x0af46,0x0ab60,0x09570,
	0x04af5,0x04970,0x064b0,0x074a3,0x0ea50,0x06b58,0x055c0,0x0ab60,0x096d5,0x092e0,
	0x0c960,0x0d954,0x0d4a0,0x0da50,0x07552,0x056a0,0x0abb7,0x025d0,0x092d0,0x0cab5,
	0x0a950,0x0b4a0,0x0baa4,0x0ad50,0x055d9,0x04ba0,0x0a5b0,0x15176,0x052b0,0x0a930,
	0x07954,0x06aa0,0x0ad50,0x05b52,0x04b60,0x0a6e6,0x0a4e0,0x0d260,0x0ea65,0x0d530,
	0x05aa0,0x076a3,0x096d0,0x04bd7,0x04ad0,0x0a4d0,0x1d0b6,0x0d250,0x0d520,0x0dd45,
	0x0b5a0,0x056d0,0x055b2,0x049b0,0x0a577,0x0a4b0,0x0aa50,0x1b255,0x06d20,0x0ada0
};




__declspec( selectany ) WCHAR WIZ_CHINESECALENDAR_ANIMALS[] = 
{
	L'��',L'ţ',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��'
};

__declspec( selectany ) WCHAR WIZ_CHINESECALENDAR_GAN[] = 
{
	L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��'
};

__declspec( selectany ) WCHAR WIZ_CHINESECALENDAR_ZHI[] = 
{
	L'��',L'��',L'��',L'î',L'��',L'��',L'��',L'δ',L'��',L'��',L'��',L'��'
};

inline CString WizChineseCalendarCyclical(int num)
{
	CString strGan(WIZ_CHINESECALENDAR_GAN[num % 10]);
	CString strZhi(WIZ_CHINESECALENDAR_ZHI[num % 12]);
	return strGan + strZhi;
}



/*
//==== ����ũ�� y�����ĸ��� 1-12 , û�򴫻� 0
*/
inline int WizChineseCalendarGetLeapMonth(int y)
{
	return (WIZ_CHINESECALENDAR_LUNARINFO[y-1900] & 0xf);
}

/*
//==== ����ũ�� y�����µ�����
*/
inline int WizChineseCalendarGetLeapDays(int y) 
{
   if (WizChineseCalendarGetLeapMonth(y)) 
	   return((WIZ_CHINESECALENDAR_LUNARINFO[y - 1900] & 0x10000) ? 30: 29);
   else 
	   return (0);
}

/*
//����ũ�� y���������
*/
inline int WizChineseCalendarGetYearDays(int y) 
{
   int sum = 348;
   for (int i = 0x8000; i > 0x8; i >>= 1) 
	   sum += (WIZ_CHINESECALENDAR_LUNARINFO[y-1900] & i) ? 1: 0;
   //
   return(sum + WizChineseCalendarGetLeapDays(y));
}

/*
//����ũ�� y��m�µ�������
*/
inline int WizChineseCalendarGetMonthDays(int y, int m)
{
	return ( (WIZ_CHINESECALENDAR_LUNARINFO[y - 1900] & (0x10000>>m)) ? 30: 29 );
}

/*
//==== ���ũ��, �����������, ����ũ���������
//     ����������� .year .month .day .isLeap .yearCyl .dayCyl .monCyl
*/
struct WIZCHINESECALENDARDATEDATA
{
	int year;
	int month;
	int day;
	bool isLeap;
	int yearCyl;
	int dayCyl;
	int monCyl;
};

inline WIZCHINESECALENDARDATEDATA WizChineseCalendarGetLunar(const COleDateTime& objDate)
{
	WIZCHINESECALENDARDATEDATA ret;
	ZeroMemory(&ret, sizeof(WIZCHINESECALENDARDATEDATA));
	//
	int i;
	int leap = 0;
	int temp=0;
	//
	COleDateTime baseDate(1900,1,31, 0, 0, 0);
	COleDateTime t(objDate.GetYear(), objDate.GetMonth(), objDate.GetDay(), 0, 0, 0);
	//
	int nDays = (int) COleDateTimeSpan(t - baseDate).GetDays();
	int offset = nDays;

	ret.dayCyl = offset + 40;
	ret.monCyl = 14;

	for(i=1900; i<2050 && offset>0; i++) 
	{
		temp = WizChineseCalendarGetYearDays(i);
		offset -= temp;
		ret.monCyl += 12;
	}
	if(offset<0) 
	{
		offset += temp;
		i--;
		ret.monCyl -= 12;
	}

	ret.year = i;
	ret.yearCyl = i - 1864;

	leap = WizChineseCalendarGetLeapMonth(i); //���ĸ���
	ret.isLeap = false;

	for(i=1; i<13 && offset>0; i++)
	{
		//����
		if(leap>0 && i==(leap+1) && ret.isLeap==false)
		{
			--i; 
			ret.isLeap = true; 
			temp = WizChineseCalendarGetLeapDays(ret.year); 
		}
		else         
		{ 
			temp = WizChineseCalendarGetMonthDays(ret.year, i);
		}


		//�������
		if(ret.isLeap==true && i==(leap+1)) 
			ret.isLeap = false;

		offset -= temp;

		if(ret.isLeap == false) 
			ret.monCyl ++;
	}

	if(offset==0 && leap>0 && i==leap+1)
	{
		if(ret.isLeap)
		{
			ret.isLeap = false; 
		}
		else
		{
			ret.isLeap = true; 
			--i; 
			--ret.monCyl;
		}
	}

	if(offset<0)
	{ 
		offset += temp; 
		--i; 
		--ret.monCyl; 
	}

	ret.month = i;
	ret.day = offset + 1;
	//
	return ret;
}

inline CString WizChineseCalendarGetMonthString(int m)
{
	WCHAR arrayStr1[] = {L'��',L'һ',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'ʮ'};
	//
	CString str;
	if (m > 10)
	{
		str = CString(L'ʮ') + arrayStr1[m - 10];
	}
	else 
	{
		str = arrayStr1[m];
	}
	//
	str += L'��';
	//
	return str;
}


inline CString WizChineseCalendarGetDayString(int d)
{
	WCHAR arrayStr1[] = {L'��',L'һ',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'��',L'ʮ'};
	WCHAR arrayStr2[] = {L'��',L'ʮ',L'إ',L'ئ',L'��'};
	//
	CString str;
	//
	switch (d) 
	{
	  case 10:
		  str += _T("��ʮ");
		  break;
	  case 20:
		  str += _T("��ʮ"); 
		  break;
	  case 30:
		  str += _T("��ʮ");
		  break;
	  default:
		  str += arrayStr2[d / 10];
		  str += arrayStr1[d % 10];
	}
	return str;
}


inline CString WizChineseCalendarGetMonthDayString(int m, int d)
{
	return WizChineseCalendarGetMonthString(m) + WizChineseCalendarGetDayString(d);
}



inline COleDateTimeSpan WizDoubleMilliSecondsToOleDateTimeSpan(double fMilliSeconds)
{
	__int64 nDays = (__int64)(fMilliSeconds / (24 * 60 * 60 * 1000.0));
	fMilliSeconds = fMilliSeconds - (nDays * 24 * 60 * 60 * 1000.0);
	__int64 nHours = (__int64)(fMilliSeconds / (60 * 60 * 1000.0));
	fMilliSeconds = fMilliSeconds - (nHours * 60 * 60 * 1000.0);
	__int64 nMinutes = (__int64)(fMilliSeconds / (60 * 1000.0));
	fMilliSeconds = fMilliSeconds - (nMinutes * 60 * 1000.0);
	__int64 nSeconds = (__int64)(fMilliSeconds / 1000.0);
	//
	return COleDateTimeSpan(int(nDays), int(nHours), int(nMinutes), int(nSeconds));
}


inline CString WizChineseCalendarGetMonthDayStringSimp(const COleDateTime& t)
{
	WIZCHINESECALENDARDATEDATA c = WizChineseCalendarGetLunar(t);
	CString str = WizChineseCalendarGetMonthDayString(c.month, c.day);
	if (c.isLeap)
	{
		str = CString(_T("��")) + str;
	}
	return str;
}

inline CString WizChineseCalendarAutoGetDayStringSimp(const COleDateTime& t)
{
	WIZCHINESECALENDARDATEDATA c = WizChineseCalendarGetLunar(t);
	//
	if (c.day == 1)
	{
		CString str = WizChineseCalendarGetMonthString(c.month);
		if (c.isLeap)
		{
			str = CString(_T("��")) + str;
		}
		return str;
	}
	else
	{
		return WizChineseCalendarGetDayString(c.day);
	}
}

inline CString WizChineseCalendarGetChinese24DaySimp(const COleDateTime& t)
{
	/*
	//���⴦��
	*/
	if (t.GetYear() == 2010 && t.GetMonth() == 8)
	{
		int nDay = t.GetDay();
		if (nDay == 7)
		{
			return CString(_T("����"));
		}
		else if (nDay == 8)
		{
			return CString();
		}
	}
	//
	UINT arrayTermInfo[] = {0,21208,42467,63836,85337,107014,128867,150921,173149,195551,218072,240693,263343,285989,308563,331033,353350,375494,397447,419210,440795,462224,483532,504758};
	LPCTSTR arraySolarTerm[] = {_T("С��"),_T("��"),_T("����"),_T("��ˮ"),_T("����"),_T("����"),_T("����"),_T("����"),_T("����"),_T("С��"),_T("â��"),_T("����"),_T("С��"),_T("����"),_T("����"),_T("����"),_T("��¶"),_T("���"),_T("��¶"),_T("˪��"),_T("����"),_T("Сѩ"),_T("��ѩ"),_T("����")};
	//
	int nInnerMonth = t.GetMonth() - 1;
	//
	double nMisSeconds = 31556925974.7 * (t.GetYear() - 1900) + arrayTermInfo[nInnerMonth * 2 + 1] * 60000.0;
	//
	COleDateTime t1 = COleDateTime(1900, 1, 6, 2, 5, 0) + WizDoubleMilliSecondsToOleDateTimeSpan(nMisSeconds);
	//
	if (t.GetYear() == t1.GetYear()
		&& t.GetMonth() == t1.GetMonth()
		&& t.GetDay() == t1.GetDay())
		return CString(arraySolarTerm[nInnerMonth * 2 + 1]);

	nMisSeconds = 31556925974.7 * (t.GetYear() - 1900) + arrayTermInfo[nInnerMonth * 2] * 60000.0;
	t1 = COleDateTime(1900, 1, 6, 2, 5, 0) + WizDoubleMilliSecondsToOleDateTimeSpan(nMisSeconds);

	if (t.GetYear() == t1.GetYear()
		&& t.GetMonth() == t1.GetMonth()
		&& t.GetDay() == t1.GetDay())
		return CString(arraySolarTerm[nInnerMonth * 2]);
	//
	return CString();
}
inline CString WizChineseCalendarGetChineseHolidaySimp(const COleDateTime& t)
{
	WIZCHINESECALENDARDATEDATA c = WizChineseCalendarGetLunar(t);
	//
	CString str;
	//
	if (c.isLeap)
		return str;
	//
	if (c.month == 1)
	{
		if (c.day == 1)
			return CString(_T("����"));
		if (c.day == 15)
			return CString(_T("Ԫ����"));
	}
	else if (c.month == 5)
	{
		if (c.day == 5)
			return CString(_T("�����"));
	}
	else if (c.month == 7)
	{
		if (c.day == 7)
			return CString(_T("��Ϧ"));
	}
	else if (c.month == 8)
	{
		if (c.day == 15)
			return CString(_T("�����"));
	}
	else if (c.month == 9)
	{
		if (c.day == 9)
			return CString(_T("������"));
	}
	else if (c.month == 12)
	{
		if (c.day == 8)
			return CString(_T("���˽�"));
		//
		WIZCHINESECALENDARDATEDATA c2 = WizChineseCalendarGetLunar(t + COleDateTimeSpan(1, 0, 0, 0));
		if (c2.year == 1 && c2.month == 1)
			return CString(_T("��Ϧ"));
	}
	return str;
}

inline CString WizChineseCalendarGetChineseDaySimp(const COleDateTime& t)
{
	CString str = WizChineseCalendarGetChineseHolidaySimp(t);
	if (!str.IsEmpty())
		return str;
	//
	return WizChineseCalendarGetChinese24DaySimp(t);
}


///////////////////////////////////////////////////////////////////////////////

inline CString WizChineseCalendarSimpStringToTradString(const CString& str)
{
	CString s = str;
	//
	s.Replace(L'��', L'��');
	s.Replace(L'��', L'�R');
	s.Replace(L'��', L'�u');
	s.Replace(L'��', L'�i');
	s.Replace(L'��', L'�c');
	s.Replace(L'��', L'�@');
	s.Replace(L'��', L'�U');
	s.Replace(L'��', L'�M');
	s.Replace(L'��', L'�N');
	s.Replace(L'��', L'̎');
	s.Replace(L'��', L'�D');
	s.Replace(L'��', L'�');
	s.Replace(L'��', L'��');
	//
	return s;
}

inline CString WizChineseCalendarGetMonthDayStringTrad(const COleDateTime& t)
{
	return WizChineseCalendarSimpStringToTradString(WizChineseCalendarGetMonthDayStringSimp(t));
}

inline CString WizChineseCalendarAutoGetDayStringTrad(const COleDateTime& t)
{
	return WizChineseCalendarSimpStringToTradString(WizChineseCalendarAutoGetDayStringSimp(t));
}

inline CString WizChineseCalendarGetChinese24DayTrad(const COleDateTime& t)
{
	return WizChineseCalendarSimpStringToTradString(WizChineseCalendarGetChinese24DaySimp(t));
}
inline CString WizChineseCalendarGetChineseHolidayTrad(const COleDateTime& t)
{
	return WizChineseCalendarSimpStringToTradString(WizChineseCalendarGetChineseHolidaySimp(t));
}

inline CString WizChineseCalendarGetChineseDayTrad(const COleDateTime& t)
{
	return WizChineseCalendarSimpStringToTradString(WizChineseCalendarGetChineseDaySimp(t));
}


inline CString WizChineseCalendarGetMonthDayString(const COleDateTime& t)
{
	if (GetACP() == 936)
		return WizChineseCalendarGetMonthDayStringSimp(t);
	else
		return WizChineseCalendarGetMonthDayStringTrad(t);
}

inline CString WizChineseCalendarAutoGetDayString(const COleDateTime& t)
{
	if (GetACP() == 936)
		return WizChineseCalendarAutoGetDayStringSimp(t);
	else
		return WizChineseCalendarAutoGetDayStringTrad(t);
}

inline CString WizChineseCalendarGetChinese24Day(const COleDateTime& t)
{
	if (GetACP() == 936)
		return WizChineseCalendarGetChinese24DaySimp(t);
	else
		return WizChineseCalendarGetChinese24DayTrad(t);
}
inline CString WizChineseCalendarGetChineseHoliday(const COleDateTime& t)
{
	if (GetACP() == 936)
		return WizChineseCalendarGetChineseHolidaySimp(t);
	else
		return WizChineseCalendarGetChineseHolidayTrad(t);
}

inline CString WizChineseCalendarGetChineseDay(const COleDateTime& t)
{
	if (GetACP() == 936)
		return WizChineseCalendarGetChineseDaySimp(t);
	else
		return WizChineseCalendarGetChineseDayTrad(t);
}



