// A standalone program or a batch of private guest tasks. Compiler errors must
// not look like a successful expected Til panic; report the exception and status.
U0 GuestPutChars(U64 ch)
{
  OutU8(0xE9,ch);
  PutChars(ch);
}
#define PutChars GuestPutChars

U0 GuestReport(U8 *text)
{
  while (*text)
    OutU8(0xE9,*text++);
}

Bool guest_input_ready=FALSE;
U0 GuestInputReady()
{
  if (!guest_input_ready) {
    guest_input_ready=TRUE;
    GuestReport("TILTEST:INPUT\n");
  }
}

U0 GuestSaveDiagnostics()
{
  I64 size;
  U8 *body=DocSave(DocPut,&size);
  U8 *padded=CAlloc((size+BLK_SIZE-1)/BLK_SIZE*BLK_SIZE);
  MemCpy(padded,body,size);
  FileWrite("C:/Home/ERROR.LOG",padded,size);
  Free(padded);
  Free(body);
}

class GuestCaseResult {
  U8 *path;
  I64 status;
};

U0 GuestCaseTask(U8 *data)
{
  GuestCaseResult *result=data;
  Cd("C:/Home");
  DocTermNew;
  try {
    ExeFile2(result->path);
    result->status=33;
  } catch {
    if (Fs->except_ch=='TILPANIC')
      result->status=35;
    else
      result->status=37;
    GuestSaveDiagnostics;
    Fs->catch_except=TRUE;
  }
}

U0 GuestRunCase(U8 *name,U8 *path,I64 expected_status)
{
  // ExeFile2 accepts a missing include as an empty program. A missing staged
  // input is a harness failure, even when this case expects a compiler error.
  if (!FileFind(path,NULL,FUF_JUST_FILES))
    throw('BADCASE');
  GuestCaseResult result;
  result.path=path;
  result.status=0;
  GuestReport("TILCASE:"); GuestReport(name); GuestReport(":BEGIN\n");
  CTask *task=Spawn(&GuestCaseTask,&result,"Til test",,Fs);
  F64 deadline=tS+120;
  while (TaskValidate(task) && tS<deadline)
    Sleep(1);
  if (TaskValidate(task)) {
    Kill(task);
    GuestReport("TILCASE:"); GuestReport(name); GuestReport(":TIMEOUT\n");
    OutU32(0xF4,0x12);
  }
  GuestReport("TILCASE:"); GuestReport(name);
  if (result.status==33) GuestReport(":PASS\n");
  else if (result.status==35) GuestReport(":PANIC\n");
  else GuestReport(":ERROR\n");
  if (result.status!=expected_status)
    OutU32(0xF4,0x12);
}

Cd("C:/Home");
GuestReport("TILTEST:BEGIN\n");
try {
  ExeFile2("TILTEST.HC");
  GuestReport("TILTEST:PASS\n");
  OutU32(0xF4,0x10);
} catch {
  if (Fs->except_ch=='TILPANIC') {
    GuestReport("TILTEST:PANIC\n");
    OutU32(0xF4,0x11);
  } else {
    GuestReport("TILTEST:ERROR\n");
    GuestSaveDiagnostics;
    OutU32(0xF4,0x12);
  }
  Fs->catch_except=TRUE;
}
