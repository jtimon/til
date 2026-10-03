// One isolated guest program per VM. Compiler errors must not look like a
// successful expected Til panic; report both the exception and exit status.
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
