// huhu.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "sqlite3.h"
#include <string>
using namespace std;

static int kiemtra(string str)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

   // Open database 
	rc = sqlite3_open("C:\\sqlite\\41.db", &db);
	if( rc )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}

	const char * csql = str.c_str();

	 rc= sqlite3_exec(db, csql, 0, 0, &zErrMsg);

	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 0;
	}
	else
	{
		return 1;
	}
	
	sqlite3_close(db);
}

static string bangtam1(string bang)
{
	string sql = " CREATE TABLE " + bang + " (sbd varchar, diemtb" + bang +" double); ";
	return sql;
}

static string bangtam2(string bang)
{
	string sql = " CREATE TABLE " + bang + " (sbd varchar, nvso varchar, manv varchar, diemxt double); ";
	return sql;
}

static string xoabang(string bang)
{
	string sql = " DROP TABLE " + bang + " ; ";
	return sql;
}

static string xuly(string bang, string sonv, string manv, string a, string b, string c, int heso)
{
	string sql = " insert into " + bang + " (sbd,diemtb" + bang + ") SELECT SBD, "\
		" ((" + a + ((heso==2)?"*2 + ":" + ") + b + " + " + c + ")"+ ((heso==2)?"/4 ":"/3") + "  +(KV+DT)/3 + UT) "\
			" from tonghop where " + sonv + " = '" + manv + "' ;";
	return sql;
}

static string xuly1(string bang3, string bang1, string sonv, string manv, int quocte)
{
	string sql = " insert into " + bang3 + " (sbd,nvso,manv,diemxt) SELECT sbd, '"+ sonv +"' as nvso, "\
		"'" + manv + "' as manv, diemtb" + bang1 + " as diemxt from " + bang1 + " where diemxt " + ((quocte==0)?" >= 6.0 ":" >=5.5 ") + " ;";
	return sql;
}

static string xuly2(string bang3, string bang1, string bang2, string sonv, string manv, int quocte)
{
	string sql = " insert into " + bang3 + " (sbd,nvso,manv,diemxt) SELECT " + bang1 + ".sbd, '"+ sonv +"' as nvso, "\
		"'" + manv + "' as manv, case when (diemtb" + bang1 + " >= diemtb" + bang2 + ") then diemtb" + bang1 + \
		" else diemtb" + bang2 + " end as diemxt from " + bang1 + " , " + bang2 + \
		" where " + bang1 + ".sbd=" + bang2 + ".sbd and diemxt " + ((quocte==0)?" >= 6.0 ":" >=5.5 ") + " ;";
	return sql;
}

static string xuly3(string bang3, string bang1, string bang2, string bang4, string sonv, string manv, int quocte)
{
	string sql = " insert into " + bang3 + " (sbd,nvso,manv,diemxt) SELECT " + bang1 + ".sbd, '"+ sonv +"' as nvso, '" + manv + "' as manv, "\
		" case when (diemtb" + bang1 + " >= diemtb" + bang2 + ") and (diemtb" + bang1 + " >= diemtb" + bang4 + ")then diemtb" + bang1 + \
		" when (diemtb" + bang2 + " >= diemtb" + bang1 + ") and (diemtb" + bang2 + " >= diemtb" + bang4 + ")then diemtb" + bang2 + \
		" when (diemtb" + bang4 + " >= diemtb" + bang1 + ") and (diemtb" + bang4 + " >= diemtb" + bang2 + ")then diemtb" + bang4 +\
		" else diemtb" + bang1 + " end as diemxt from " + bang1 + " , " + bang2 + " , " + bang4 + \
		" where " + bang1 + ".sbd=" + bang2 + ".sbd and " + bang2 + ".sbd=" + bang4 + ".sbd and diemxt " + ((quocte==0)?" >= 6.0 ":" >=5.5 ") + " ;";
	return sql;
}

static string xuly4(string bang3, string bang1, string bang2, string bang4, string bang5, string sonv, string manv, int quocte)
{
	string sql = " insert into " + bang3 + " (sbd,nvso,manv,diemxt) SELECT " + bang1 + ".sbd, '"+ sonv +"' as nvso, '" + manv + "' as manv, "\
		"case when (diemtb" + bang1 + " >= diemtb" + bang2 + ") and (diemtb" + bang1 + " >= diemtb" + bang4 + ") and (diemtb" + bang1 + " >= diemtb" + bang5 + ")then diemtb" + bang1 + \
		" when (diemtb" + bang2 + " >= diemtb" + bang1 + ") and (diemtb" + bang2 + " >= diemtb" + bang4 + ") and (diemtb" + bang2 + " >= diemtb" + bang5 + ")then diemtb" + bang2 + \
		" when (diemtb" + bang4 + " >= diemtb" + bang1 + ") and (diemtb" + bang4 + " >= diemtb" + bang2 + ") and (diemtb" + bang4 + " >= diemtb" + bang5 + ")then diemtb" + bang4 + \
		" when (diemtb" + bang5 + " >= diemtb" + bang1 + ") and (diemtb" + bang5 + " >= diemtb" + bang2 + ") and (diemtb" + bang5 + " >= diemtb" + bang4 + ")then diemtb" + bang5 + \
		" else diemtb" + bang1 + " end as diemxt from " + bang1 + " , " + bang2 + " , " + bang4 + " , " + bang5 + \
		" where " + bang1 + ".sbd=" + bang2 + ".sbd and " + bang2 + ".sbd=" + bang4 + ".sbd and " + bang4 + ".sbd=" + bang5 + ".sbd and diemxt " + ((quocte==0)?" >= 6.0 ":" >=5.5 ") + " ;";
	return sql;
}

static string xuly0(string bang3, string bang1, string bang2, string bang4, string bang5, string bang6, string sonv, string manv, int quocte)
{
	string sql = " insert into " + bang3 + " (sbd,nvso,manv,diemxt) SELECT " + bang1 + ".sbd, '"+ sonv +"' as nvso, '" + manv + "' as manv, "\
		" case when (diemtb" + bang1 + " >= diemtb" + bang2 + ") and (diemtb" + bang1 + " >= diemtb" + bang4 + ") and (diemtb" + bang1 + " >= diemtb" + bang5 + ")and (diemtb" + bang1 + " >= diemtb" + bang6 + ")then diemtb" + bang1 + \
		" when (diemtb" + bang2 + " >= diemtb" + bang1 + ") and (diemtb" + bang2 + " >= diemtb" + bang4 + ") and (diemtb" + bang2 + " >= diemtb" + bang5 + ")and (diemtb" + bang2 + " >= diemtb" + bang6 + ")then diemtb" + bang2 + \
		" when (diemtb" + bang4 + " >= diemtb" + bang1 + ") and (diemtb" + bang4 + " >= diemtb" + bang2 + ") and (diemtb" + bang4 + " >= diemtb" + bang5 + ")and (diemtb" + bang4 + " >= diemtb" + bang6 + ")then diemtb" + bang4 + \
		" when (diemtb" + bang5 + " >= diemtb" + bang1 + ") and (diemtb" + bang5 + " >= diemtb" + bang2 + ") and (diemtb" + bang5 + " >= diemtb" + bang4 + ")and (diemtb" + bang5 + " >= diemtb" + bang6 + ")then diemtb" + bang5 + \
		" when (diemtb" + bang6 + " >= diemtb" + bang1 + ") and (diemtb" + bang6 + " >= diemtb" + bang2 + ") and (diemtb" + bang6 + " >= diemtb" + bang4 + ")and (diemtb" + bang6 + " >= diemtb" + bang5 + ")then diemtb" + bang6 + \
		" else diemtb" + bang1 + " end as diemxt from " + bang1 + " , " + bang2 + " , " + bang4 + " , " + bang5 + " , " + bang6 + \
		" where " + bang1 + ".sbd=" + bang2 + ".sbd and " + bang2 + ".sbd=" + bang4 + ".sbd and " + bang4 + ".sbd=" + bang5 + ".sbd and " + bang5 + ".sbd=" + bang6 + ".sbd and diemxt " + ((quocte==0)?" >= 6.0 ":" >=5.5 ") + " ;";
	return sql;
}

static string xuly5(string bang, string sonv, string manv, string chitieu)
{
	string sql = " insert into nvxt(sbd,nvso,manv,diemxt) select " + bang + ".sbd as sbd, '"+ sonv +"' as nvso, "\
		"'" + manv + "' as manv, " + bang + ".diemxt as diemxt from " + bang + \
		" order by " + bang + ".diemxt DESC limit ("+chitieu+"-( select count(sbd) from nvxt where manv ='"+manv+"'));"\

		" insert into diemchuan(nvso,manv,diemxt) select nvso, manv, diemxt from nvxt where "\
		"nvso = '" + sonv + "' and manv = '" + manv + "' order by diemxt ASC limit 1; "\

		" insert into nvxt(sbd,nvso,manv,diemxt) select " + bang + ".sbd as sbd, '"+ sonv +"' as nvso,"\
		"'" + manv + "' as manv, " + bang + ".diemxt as diemxt from " + bang + \
		" where " + bang + ".diemxt =( select diemxt from nvxt order by diemxt ASC limit 1) "\
		" and " + bang +".sbd not in( select sbd from nvxt) ;"\

		" update diemchuan set soluong =( select count(sbd) from nvxt where nvso = '" + sonv + "' and manv = '" + manv + "') "\
		" where nvso = '" + sonv + "' and manv = '" + manv + "';";
	return sql;
}

int main(int argc, char* argv[])
{
	string NV[4]={"NV1","NV2","NV3","NV4"};

	string ma1[9]={"KT11","KT12","KT13","KT14","KT21","KT22","KT23","CN1","CN2"};
	string ct1[9]={"200","750","150","120","1000","450","100","390","540"};

	string ma2[4]={"KT31","KT32","KT33","CN3"};
	string ct2[4]={"720","50","50","180"};

	string ma3[4]={"KT41","KT42","KT51","KT52"};
	string ct3[4]={"150","50","100","60"};

	string ma4[3]={"KQ1","KQ2","KQ3"};
	string ct4[3]={"160","80","100"};

	string ma5[2]={"TA1","TA2"};
	string ct5[2]={"100","100"};

	string ma6[2]={"QT11","QT12"};
	string ct6[2]={"60","60"};

	string ma7[2]={"QT13","QT14"};
	string ct7[2]={"60","120"};

	string ma8="QT21";
	string ct8="60";

	string ma9[3]={"QT31","QT32","QT33"};
	string ct9[3]={"60","60","60"};

	int i,j,a;
	string st="";

	for(j=0; j<4 ;j++)
	{
		printf(" Dang chay NV %d !\n",j+1);
		//toan ly hoa/ toan ly anh/toan hoa anh/toan van anh/toan van phap
		a = kiemtra(" select count(sbd) from nvxt where manv='" + ma8 + "' < " + ct8 + " ;" );
		if(a)
		{
			st += bangtam1("bang1");
			st += xuly("bang1",NV[j],ma8,"Toan","Ly","Hoa",1);
			st += bangtam1("bang2");
			st += xuly("bang2",NV[j],ma8,"Toan","Ly","Anh",1);
			st += bangtam1("bang4");
			st += xuly("bang4",NV[j],ma8,"Toan","Van","Phap",1);
			st += bangtam1("bang5");
			st += xuly("bang5",NV[j],ma8,"Toan","Van","Anh",1);
			st += bangtam1("bang6");
			st += xuly("bang6",NV[j],ma8,"Toan","Hoa","Anh",1);
			st += bangtam2("bang3");
			st += xuly0("bang3","bang1","bang2","bang4","bang5","bang6",NV[j],ma8,0);
			st += xuly5("bang3",NV[j],ma8, ct8);
			st += xoabang("bang1") + xoabang("bang2") + xoabang("bang3") + xoabang("bang4") + xoabang("bang5") + xoabang("bang6");
		}
	
		//toan(hs2)+ly+hoa hoac toan(hs2)+ly+anh
	for(i=0;i<9;i++)
	{
		a = kiemtra(" select count(sbd) from nvxt where manv='" + ma1[i] + "' < " + ct1[i] + " ;" );
		if(a)
		{
			st += bangtam1("bang1");
			st += xuly("bang1",NV[j],ma1[i],"Toan","Ly","Hoa",2);
			st += bangtam1("bang2");
			st += xuly("bang2",NV[j],ma1[i],"Toan","Ly","Anh",2);
			st += bangtam2("bang3");
			st += xuly2("bang3","bang1","bang2",NV[j],ma1[i],0);
			st += xuly5("bang3",NV[j],ma1[i], ct1[i]);
			st += xoabang("bang1") + xoabang("bang2") + xoabang("bang3");
		}
	}
	//toan(hs2)+ly+hoa hoac toan(hs2)+hoa+sinh hoac toan(hs2)+hoa+anh
	for(i=0;i<4;i++)
	{
		a = kiemtra(" select count(sbd) from nvxt where manv='" + ma2[i] + "' < " + ct2[i] + " ;" );
		if(a)
		{
			st += bangtam1("bang1");
			st += xuly("bang1",NV[j],ma2[i],"Toan","Ly","Hoa",2);
			st += bangtam1("bang2");
			st += xuly("bang2",NV[j],ma2[i],"Toan","Hoa","Sinh",2);
			st += bangtam1("bang4");
			st += xuly("bang4",NV[j],ma2[i],"Toan","Hoa","Anh",2);
			st += bangtam2("bang3");
			st += xuly3("bang3","bang1","bang2","bang4",NV[j],ma2[i],0);
			st += xuly5("bang3",NV[j],ma2[i], ct2[i]);
			st += xoabang("bang1") + xoabang("bang2") + xoabang("bang3") + xoabang("bang4");
		}
	}
	//toan+ly+hoa hoac toan+ly+anh
	for(i=0;i<4;i++)
	{
		a = kiemtra(" select count(sbd) from nvxt where manv='" + ma3[i] + "' < " + ct3[i] + " ;" );
		if(a)
		{
			st += bangtam1("bang1");
			st += xuly("bang1",NV[j],ma3[i],"Toan","Ly","Hoa",1);
			st += bangtam1("bang2");
			st += xuly("bang2",NV[j],ma3[i],"Toan","Ly","Anh",1);
			st += bangtam2("bang3");
			st += xuly2("bang3","bang1","bang2",NV[j],ma3[i],0);
			st += xuly5("bang3",NV[j],ma3[i], ct3[i]);
			st += xoabang("bang1") + xoabang("bang2") + xoabang("bang3");
		}
	}
	//toan+ly+hoa hoac toan+ly+anh hoac toan+van+anh
	for(i=0;i<3;i++)
	{
		a = kiemtra(" select count(sbd) from nvxt where manv='" + ma4[i] + "' < " + ct4[i] + " ;" );
		if(a)
		{
			st += bangtam1("bang1");
			st += xuly("bang1",NV[j],ma4[i],"Toan","Ly","Hoa",1);
			st += bangtam1("bang2");
			st += xuly("bang2",NV[j],ma4[i],"Toan","Ly","Anh",1);
			st += bangtam1("bang4");
			st += xuly("bang4",NV[j],ma4[i],"Toan","Van","Anh",1);
			st += bangtam2("bang3");
			st += xuly3("bang3","bang1","bang2","bang4",NV[j],ma4[i],0);
			st += xuly5("bang3",NV[j],ma4[i], ct4[i]);
			st += xoabang("bang1") + xoabang("bang2") + xoabang("bang3") + xoabang("bang4");
		}
	}
	//toan+van+anh(heso2)
	for(i=0;i<2;i++)
	{
		a = kiemtra(" select count(sbd) from nvxt where manv='" + ma5[i] + "' < " + ct5[i] + " ;" );
		if(a)
		{
			st += bangtam1("bang1");
			st += xuly("bang1",NV[j],ma5[i],"Anh","Van","Toan",2);
			st += bangtam2("bang3");
			st += xuly1("bang3","bang1",NV[j],ma5[i],0);
			st += xuly5("bang3",NV[j],ma5[i], ct5[i]);
			st += xoabang("bang1") + xoabang("bang3");
		}
	}
	// toan ly hoa/ toan ly anh/ toan hoa anh
	for(i=0;i<2;i++)
	{
		a = kiemtra(" select count(sbd) from nvxt where manv='" + ma6[i] + "' < " + ct6[i] + " ;" );
		if(a)
		{
			st += bangtam1("bang1");
			st += xuly("bang1",NV[j],ma6[i],"Toan","Ly","Hoa",1);
			st += bangtam1("bang2");
			st += xuly("bang2",NV[j],ma6[i],"Toan","Ly","Anh",1);
			st += bangtam1("bang4");
			st += xuly("bang4",NV[j],ma6[i],"Toan","Hoa","Anh",1);
			st += bangtam2("bang3");
			st += xuly3("bang3","bang1","bang2","bang4",NV[j],ma6[i],0);
			st += xuly5("bang3",NV[j],ma6[i], ct6[i]);
			st += xoabang("bang1") + xoabang("bang2") + xoabang("bang3") + xoabang("bang4");
		}
	}
	//toan ly hoa/ toan ly anh/ toan ly phap/ toan hoa anh
	for(i=0;i<2;i++)
	{
		a = kiemtra(" select count(sbd) from nvxt where manv='" + ma7[i] + "' < " + ct7[i] + " ;" );
		if(a)
		{
			st += bangtam1("bang1");
			st += xuly("bang1",NV[j],ma7[i],"Toan","Ly","Hoa",1);
			st += bangtam1("bang2");
			st += xuly("bang2",NV[j],ma7[i],"Toan","Ly","Anh",1);
			st += bangtam1("bang4");
			st += xuly("bang4",NV[j],ma7[i],"Toan","Ly","Phap",1);
			st += bangtam1("bang5");
			st += xuly("bang5",NV[j],ma7[i],"Toan","Hoa","Anh",1);
			st += bangtam2("bang3");
			st += xuly4("bang3","bang1","bang2","bang4","bang5",NV[j],ma7[i],0);
			st += xuly5("bang3",NV[j],ma7[i], ct7[i]);
			st += xoabang("bang1") + xoabang("bang2") + xoabang("bang3") + xoabang("bang4") + xoabang("bang5");
		}
	}
	

	for(i=0;i<3;i++)
	{
		a = kiemtra(" select count(sbd) from nvxt where manv='" + ma9[i] + "' < " + ct9[i] + " ;" );
		if(a)
		{
			st += bangtam1("bang1");
			st += xuly("bang1",NV[j],ma9[i],"Toan","Ly","Hoa",1);
			st += bangtam1("bang2");
			st += xuly("bang2",NV[j],ma9[i],"Toan","Ly","Anh",1);
			st += bangtam1("bang4");
			st += xuly("bang4",NV[j],ma9[i],"Toan","Van","Phap",1);
			st += bangtam1("bang5");
			st += xuly("bang5",NV[j],ma9[i],"Toan","Van","Anh",1);
			st += bangtam1("bang6");
			st += xuly("bang6",NV[j],ma9[i],"Toan","Hoa","Anh",1);
			st += bangtam2("bang3");
			st += xuly0("bang3","bang1","bang2","bang4","bang5","bang6",NV[j],ma9[i],1);
			st += xuly5("bang3",NV[j],ma9[i], ct9[i]);
			st += xoabang("bang1") + xoabang("bang2") + xoabang("bang3") + xoabang("bang4") + xoabang("bang5") + xoabang("bang6");
		}
	}

	st +=" delete from tonghop where SBD in (select sbd from nvxt);";
	kiemtra(st);
	st="";
	printf(" Chay xong NV %d !\n\n",j+1);
	}
	return 0;
}

