#include "..\\include\Lib_Clara.h"
#include "log.h"

#ifdef LOG

wchar_t logpath[256];

void GetDateTime(DATETIME *dt)
{
  if(dt) REQUEST_DATEANDTIME_GET(SYNC,dt);
}

void StartLog(wchar_t *path)
{
  wstrcpy(logpath,path);
  int f;
  if (!w_chdir(logpath))
  {
    if ((f=w_fopen(L"lines.txt",WA_Write|WA_Create|WA_Truncate,0x1FF,0))>=0)
    {
      w_fclose(f);
    }
  }
}

void _WriteLog(char *buf)
{
  int f;
  if (!w_chdir(logpath))
  {
    if ((f=w_fopen(L"lines.txt",WA_Write|WA_Append,0x1FF,0))>=0)
    {
      w_fwrite(f,buf,strlen(buf));
      w_fclose(f);
    }
  }
}

void WriteLog(char *buf)
{
  char msg[512];
  DATETIME dt;
  GetDateTime(&dt);
  sprintf(msg, "%02d:%02d:%02d %s\n", dt.time.hour,dt.time.min,dt.time.sec,buf);
  _WriteLog(msg);
}

void WriteLog(wchar_t *buf)
{
  char msg[512];
  DATETIME dt;
  GetDateTime(&dt);
  sprintf(msg, "%02d:%02d:%02d %ls\n", dt.time.hour,dt.time.min,dt.time.sec,buf);
  _WriteLog(msg);
}

void WriteLog(int buf)
{
  char msg[512];
  DATETIME dt;
  GetDateTime(&dt);
  sprintf(msg, "%02d:%02d:%02d %08X\n", dt.time.hour,dt.time.min,dt.time.sec,buf);
  _WriteLog(msg);
}

void WriteLog(char *buf1, char *buf2)
{
  char msg[512];
  DATETIME dt;
  GetDateTime(&dt);
  sprintf(msg, "%02d:%02d:%02d %s %s\n", dt.time.hour,dt.time.min,dt.time.sec,buf1, buf2);
  _WriteLog(msg);
}
#endif
