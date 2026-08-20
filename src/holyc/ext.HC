// TempleOS runtime boundary for generated til HolyC.
// UPtr and raw byte counts are U64; USize remains the source-level U32 alias.

#define TIL_STR_CAP_LIT  0xFFFFFFFF
#define TIL_STR_CAP_VIEW 0xFFFFFFFE

public class TilStr {
  U8 *c_str;
  U32 count;
  U32 cap;
};

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

public U0 TilStrInitLit(TilStr *out,U8 *data,U32 count)
{
  out->c_str=data;
  out->count=count;
  out->cap=TIL_STR_CAP_LIT;
}

public U0 TilStrWithCapacity(TilStr *out,U32 cap)
{
  if (!cap) {
    TilStrInitLit(out,"",0);
    return;
  }
  out->c_str=TilMAlloc(cap+1);
  out->c_str[0]=0;
  out->count=0;
  out->cap=cap;
}

public U0 TilStrClone(TilStr *out,TilStr *src)
{
  if (!src->count) {
    TilStrInitLit(out,"",0);
    return;
  }
  out->c_str=TilMAlloc(src->count+1);
  TilMemCpy(out->c_str,src->c_str,src->count);
  out->c_str[src->count]=0;
  out->count=src->count;
  out->cap=src->count;
}

public U0 TilStrSubstr(TilStr *out,TilStr *src,U32 start,U32 count)
{
  if (start>src->count)
    start=src->count;
  if (count>src->count-start)
    count=src->count-start;
  out->c_str=src->c_str+start;
  out->count=count;
  out->cap=TIL_STR_CAP_VIEW;
}

public U0 TilStrBorrowedView(TilStr *out,TilStr *src)
{
  out->c_str=src->c_str;
  out->count=src->count;
  out->cap=TIL_STR_CAP_VIEW;
}

public U0 TilStrTrimStart(TilStr *out,TilStr *src)
{
  U32 start=0;
  U8 ch;
  while (start<src->count) {
    ch=src->c_str[start];
    if (ch!=32 && ch!=9 && ch!=10 && ch!=13)
      break;
    start++;
  }
  TilStrSubstr(out,src,start,src->count-start);
}

public U0 TilStrTrim(TilStr *out,TilStr *src)
{
  U32 start=0,end=src->count;
  U8 ch;
  while (start<end) {
    ch=src->c_str[start];
    if (ch!=32 && ch!=9 && ch!=10 && ch!=13)
      break;
    start++;
  }
  while (end>start) {
    ch=src->c_str[end-1];
    if (ch!=32 && ch!=9 && ch!=10 && ch!=13)
      break;
    end--;
  }
  TilStrSubstr(out,src,start,end-start);
}

public U0 TilStrPush(TilStr *dst,TilStr *src)
{
  U32 new_count;
  if (!src->count)
    return;
  if (dst->cap>=TIL_STR_CAP_VIEW)
    TilPanicZ("Str.push_str: cannot mutate a string view or literal\n");
  new_count=dst->count+src->count;
  if (new_count<dst->count || new_count>dst->cap)
    TilPanicZ("Str.push_str: capacity exceeded\n");
  TilMemCpy(dst->c_str+dst->count,src->c_str,src->count);
  dst->count=new_count;
  dst->c_str[new_count]=0;
}

public U0 TilStrDelete(TilStr *s,Bool call_free)
{
  if (s->cap<TIL_STR_CAP_VIEW)
    TilFree(s->c_str);
  s->c_str=NULL;
  s->count=0;
  s->cap=TIL_STR_CAP_VIEW;
  if (call_free)
    TilFree(s);
}

public I64 TilStrDigit(U8 ch)
{
  if (ch>=48 && ch<=57)
    return ch-48;
  if (ch>=97 && ch<=102)
    return ch-97+10;
  if (ch>=65 && ch<=70)
    return ch-65+10;
  return -1;
}

public I64 TilStrToI64(TilStr *s)
{
  U32 i=0;
  I64 base=10,digit,result=0;
  Bool negative=FALSE,any=FALSE;
  if (!s->count)
    TilPanicZ("Str.to_i64: empty string\n");
  if (s->c_str[i]==45) {
    negative=TRUE;
    i++;
  }
  if (i==s->count)
    TilPanicZ("Str.to_i64: no digits\n");
  if (s->c_str[i]==48 && i+1<s->count) {
    if (s->c_str[i+1]==120 || s->c_str[i+1]==88) {
      base=16;
      i+=2;
    } else if (s->c_str[i+1]==98 || s->c_str[i+1]==66) {
      base=2;
      i+=2;
    } else if (s->c_str[i+1]==111 || s->c_str[i+1]==79) {
      base=8;
      i+=2;
    }
  }
  if (i==s->count)
    TilPanicZ("Str.to_i64: no digits\n");
  while (i<s->count) {
    if (s->c_str[i]==95) {
      i++;
    } else {
      digit=TilStrDigit(s->c_str[i]);
      if (digit<0 || digit>=base)
        TilPanicZ("Str.to_i64: invalid char\n");
      result=result*base+digit;
      any=TRUE;
      i++;
    }
  }
  if (!any)
    TilPanicZ("Str.to_i64: no digits\n");
  if (negative)
    return -result;
  return result;
}

public U0 TilStrFromI64(TilStr *out,I64 value)
{
  U64 magnitude,rest;
  U32 digits=1,count,index;
  Bool negative=value<0;
  U8 *data;
  if (negative)
    magnitude=-(value+1)+1;
  else
    magnitude=value;
  rest=magnitude;
  while (rest>=10) {
    rest/=10;
    digits++;
  }
  count=digits+negative;
  data=TilMAlloc(count+1);
  data[count]=0;
  index=count;
  while (TRUE) {
    index--;
    data[index]=48+magnitude%10;
    magnitude/=10;
    if (!magnitude)
      break;
  }
  if (negative)
    data[0]=45;
  out->c_str=data;
  out->count=count;
  out->cap=count;
}

public Bool TilStrEq(TilStr *a,TilStr *b)
{
  if (a->count!=b->count)
    return FALSE;
  return TilMemCmp(a->c_str,b->c_str,a->count)==0;
}

public I64 TilStrCmp(TilStr *a,TilStr *b)
{
  U32 count=a->count;
  I32 result;
  if (b->count<count)
    count=b->count;
  result=TilMemCmp(a->c_str,b->c_str,count);
  if (result)
    return result;
  if (a->count<b->count)
    return -1;
  if (a->count>b->count)
    return 1;
  return 0;
}

public U0 TilStrWrite(TilStr *s)
{
  TilRawWrite(s->c_str,s->count);
}
