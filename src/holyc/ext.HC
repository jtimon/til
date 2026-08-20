// TempleOS runtime boundary for generated til HolyC.
// UPtr and raw byte counts are U64; USize remains the source-level U32 alias.

public U0 TilRawWriteUnchecked(U8 *data,U64 count)
{
  U64 i=0;
  while (i<count) {
    PutChars(data[i]);
    i++;
  }
}

public U0 TilPanicZ(U8 *message)
{
  U64 count=0;
  if (!message)
    message="panic: null deref\n";
  while (message[count])
    count++;
  TilRawWriteUnchecked(message,count);
  throw('TILPANIC');
}

public I64 TilNativeCount(U64 count)
{
  if (count>I64_MAX)
    TilPanicZ("til: byte count exceeds TempleOS I64 range\n");
  return count;
}

public U0 TilPanic(U8 *data,U64 count)
{
  if (!data && count)
    TilPanicZ("panic: null deref\n");
  TilNativeCount(count);
  TilRawWriteUnchecked(data,count);
  throw('TILPANIC');
}

public U0 TilNullDeref()
{
  TilPanicZ("panic: null deref\n");
}

public U8 *TilCheckPtr(U8 *ptr)
{
  if (!ptr)
    TilNullDeref;
  return ptr;
}

public U0 TilRawWrite(U8 *data,U64 count)
{
  if (!count)
    return;
  TilCheckPtr(data);
  TilNativeCount(count);
  TilRawWriteUnchecked(data,count);
}

public U8 *TilMAlloc(U64 count)
{
  U8 *ptr=MAlloc(TilNativeCount(count));
  if (!ptr && count)
    TilPanicZ("til: allocation failed\n");
  return ptr;
}

public U8 *TilCAlloc(U64 nmemb,U64 size)
{
  U64 count;
  U8 *ptr;
  if (size && nmemb>I64_MAX/size)
    TilPanicZ("til: allocation size overflow\n");
  count=nmemb*size;
  ptr=CAlloc(TilNativeCount(count));
  if (!ptr && count)
    TilPanicZ("til: allocation failed\n");
  return ptr;
}

public U8 *TilReAlloc(U8 *ptr,U64 count)
{
  I64 old_count,copy_count,native_count=TilNativeCount(count);
  U8 *replacement;
  if (!ptr)
    return TilMAlloc(count);
  replacement=MAlloc(native_count);
  if (!replacement && count)
    TilPanicZ("til: allocation failed\n");
  old_count=MSize(ptr);
  copy_count=old_count;
  if (copy_count>native_count)
    copy_count=native_count;
  if (copy_count)
    MemCpy(replacement,ptr,copy_count);
  Free(ptr);
  return replacement;
}

public U0 TilFree(U8 *ptr)
{
  if (ptr)
    Free(ptr);
}

public U8 *TilMemCpy(U8 *dst,U8 *src,U64 count)
{
  if (!count)
    return dst;
  TilCheckPtr(dst);
  TilCheckPtr(src);
  return MemCpy(dst,src,TilNativeCount(count));
}

public U8 *TilMemMove(U8 *dst,U8 *src,U64 count)
{
  U64 i;
  if (!count || dst==src)
    return dst;
  TilCheckPtr(dst);
  TilCheckPtr(src);
  TilNativeCount(count);
  if (dst<src)
    return MemCpy(dst,src,count);
  i=count;
  while (i) {
    i--;
    dst[i]=src[i];
  }
  return dst;
}

public U8 *TilMemSet(U8 *dst,I64 value,U64 count)
{
  if (!count)
    return dst;
  TilCheckPtr(dst);
  return MemSet(dst,value&255,TilNativeCount(count));
}

public I32 TilMemCmp(U8 *a,U8 *b,U64 count)
{
  I64 result;
  if (!count)
    return 0;
  TilCheckPtr(a);
  TilCheckPtr(b);
  result=MemCmp(a,b,TilNativeCount(count));
  if (result<0)
    return -1;
  if (result>0)
    return 1;
  return 0;
}

public U8 *TilDeref(U8 **slot)
{
  if (!slot)
    TilNullDeref;
  return *slot;
}

public U0 TilWritePtr(U8 *slot,U8 *value)
{
  TilCheckPtr(slot);
  *(slot(U8 **))=value;
}
