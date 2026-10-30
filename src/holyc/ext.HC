// TempleOS runtime boundary for generated til HolyC.
// UPtr and raw byte counts are U64. The emitter supplies TIL_USIZE and
// the matching Str sentinels for the resolved source-level USize width.

// HolyC has native F64, but no four-byte float storage type. F32 carries
// IEEE binary32 bits; x87 loads and stores implement widening and rounding.
#define F32 U32
public F64 TilF32Load(F32 bits)
{
  F64 noreg result;
  asm {
    FLD U32 SF_ARG1[RBP]
    FSTP U64 &result[RBP]
  }
  return result;
}

public F32 TilF32Round(F64 value)
{
  F32 noreg result;
  U16 noreg saved,noreg working;
  asm {
    FSTCW U16 &saved[RBP]
    MOV AX,U16 &saved[RBP]
    AND AX,~0x0C00
    OR AX,0x003F
    MOV U16 &working[RBP],AX
    FLDCW U16 &working[RBP]
    FLD U64 SF_ARG1[RBP]
    FSTP U32 &result[RBP]
    FCLEX
    FLDCW U16 &saved[RBP]
  }
  return result;
}

public F64 TilF64Div(F64 a,F64 b)
{
  F64 noreg result;
  U16 noreg saved,noreg working;
  asm {
    FSTCW U16 &saved[RBP]
    MOV AX,U16 &saved[RBP]
    AND AX,~0x0C00
    OR AX,0x003F
    MOV U16 &working[RBP],AX
    FLDCW U16 &working[RBP]
    FLD U64 SF_ARG1[RBP]
    FDIV ST0,U64 SF_ARG2[RBP]
    FSTP U64 &result[RBP]
    FCLEX
    FLDCW U16 &saved[RBP]
  }
  return result;
}

public F32 TilF32FromI64(I64 value)
{
  F32 noreg result;
  U16 noreg saved,noreg working;
  asm {
    FSTCW U16 &saved[RBP]
    MOV AX,U16 &saved[RBP]
    AND AX,~0x0C00
    OR AX,0x003F
    MOV U16 &working[RBP],AX
    FLDCW U16 &working[RBP]
    FILD U64 SF_ARG1[RBP]
    FSTP U32 &result[RBP]
    FCLEX
    FLDCW U16 &saved[RBP]
  }
  return result;
}

public F64 TilF64Bits(U64 bits)
{
  return bits(F64);
}

public Bool TilF64IsNaN(F64 value)
{
  U64 bits=value(U64);
  return (bits&0x7FF0000000000000)==0x7FF0000000000000 &&
    (bits&0x000FFFFFFFFFFFFF)!=0;
}

public I64 TilF64Compare(F64 a,F64 b,I64 op)
{
  if (TilF64IsNaN(a) || TilF64IsNaN(b)) {
    if (op==1) return TRUE;
    return 0;
  }
  switch (op) {
    case 0: return a==b;
    case 1: return a!=b;
    case 2: return a<b;
    case 3: return a>b;
    case 4: return a<=b;
    case 5: return a>=b;
    case 6: return (a>b)-(a<b);
  }
  throw('TILPANIC');
  return 0;
}

public F32 TilF32Math(F32 a,F32 b,I64 op)
{
  F64 x=TilF32Load(a),y=TilF32Load(b);
  switch (op) {
    case 0: return TilF32Round(x+y);
    case 1: return TilF32Round(x-y);
    case 2: return TilF32Round(x*y);
    case 3: return TilF32Round(TilF64Div(x,y));
  }
  throw('TILPANIC');
  return 0;
}

public F64 TilF64FromU64(U64 value)
{
  // Keep the low bit sticky when halving: ties still round correctly.
  if (value>I64_MAX) return ToF64((value>>1)|(value&1))*2.0;
  return ToF64(value);
}

public F32 TilF32FromU64(U64 value)
{
  if (value>I64_MAX)
    return TilF32Math(TilF32FromI64((value>>1)|(value&1)),0x40000000,2);
  return TilF32FromI64(value);
}

public class TilStr {
  U8 *c_str;
  TIL_USIZE count;
  TIL_USIZE cap;
};

public class TilStrArray {
  TilStr *data;
  TIL_USIZE cap;
};

// Function values share one descriptor shape; generated typed trampolines
// adapt the call field to each lowered signature. Static functions have no
// environment owner; capturing values own an environment and both callbacks.
public class TilClosure {
  U8 *call;
  U8 *env;
  U0 (*drop)(U8 *env);
  U8 *(*clone)(U8 *env);
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

public U0 TilFloatDelete(U8 *ptr,Bool call_free)
{
  if (call_free) Free(ptr);
}

public TilClosure *TilClosureNew(U8 *code,U8 *env,U8 *drop_fn,U8 *clone_fn)
{
  TilClosure *value=TilMAlloc(sizeof(TilClosure))(TilClosure *);
  value->call=code;
  value->env=env;
  value->drop=drop_fn;
  value->clone=clone_fn;
  return value;
}

public U0 TilClosureDelete(TilClosure *value)
{
  // Zeroed container slots and empty/moved callable fields are expected.
  if (value && value->drop) {
    value->drop(value->env);
    TilFree(value);
  }
}

public TilClosure *TilClosureClone(TilClosure *value)
{
  // Empty slots stay empty; static descriptors are shared, never freed.
  if (!value || !value->drop) return value;
  return TilClosureNew(value->call,value->clone(value->env),value->drop,value->clone);
}

public U0 TilClosureSlotDelete(TilClosure **slot)
{
  TilClosureDelete(*slot);
  *slot=NULL;
}

public U8 *TilClosureSlotClone(TilClosure **slot)
{
  TilClosure **out=TilMAlloc(sizeof(U8 *))(TilClosure **);
  *out=TilClosureClone(*slot);
  return out;
}

public U0 TilClosureSlotTake(TilClosure **slot,TilClosure *value)
{
  *slot=value;
}

public TilClosure *TilClosureSlotPop(TilClosure **slot)
{
  TilClosure *value=*slot;
  *slot=NULL;
  return value;
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

public U0 TilStrInitLit(TilStr *out,U8 *data,TIL_USIZE count)
{
  out->c_str=data;
  out->count=count;
  out->cap=TIL_STR_CAP_LIT;
}

public U0 TilStrCopyValue(TilStr *out,TilStr *src)
{
  out->c_str=src->c_str;
  out->count=src->count;
  out->cap=src->cap;
}

public U0 TilStrPrepareReturn(TilStr *out)
{
  if (out->cap==TIL_STR_CAP_LIT)
    out->cap=TIL_STR_CAP_VIEW;
}

public U0 TilStrWithCapacity(TilStr *out,TIL_USIZE cap)
{
  if (!cap) {
    TilStrInitLit(out,"",0);
    return;
  }
  if (cap>=TIL_STR_CAP_VIEW || cap>=I64_MAX)
    TilPanicZ("Str.with_capacity: capacity overflow\n");
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
  if (src->count>=TIL_STR_CAP_VIEW || src->count>=I64_MAX)
    TilPanicZ("Str.clone: size overflow\n");
  out->c_str=TilMAlloc(src->count+1);
  TilMemCpy(out->c_str,src->c_str,src->count);
  out->c_str[src->count]=0;
  out->count=src->count;
  out->cap=src->count;
}

public U0 TilStrSubstr(TilStr *out,TilStr *src,TIL_USIZE start,TIL_USIZE count)
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
  TIL_USIZE start=0;
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
  TIL_USIZE start=0,end=src->count;
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
  TIL_USIZE new_count;
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

Bool TilFileFind(TilStr *path,I64 flags)
{
  U64 count=path->count;
  U8 *name=TilMAlloc(count+1);
  Bool found;
  TilMemCpy(name,path->c_str,count);
  name[count]=0;
  found=FileFind(name,NULL,flags);
  TilFree(name);
  return found;
}

public Bool TilFileExists(TilStr *path)
{
  return TilFileFind(path,0);
}

public Bool TilFileIsFile(TilStr *path)
{
  return TilFileFind(path,FUF_JUST_FILES);
}

public Bool TilFileIsDir(TilStr *path)
{
  return TilFileFind(path,FUF_JUST_DIRS);
}

class TilFileHandle {
  CFile *file;
  I64 cursor;
  I64 mode;
};

CFile *TilNativeFileOpen(U8 *name,I64 mode)
{
  CFile *file=NULL;
  CDirContext *parent;
  Bool valid,exists;
  I64 preallocate=0;
  if (!mode)
    return FOpen(name,"r");
  parent=DirContextNew(name);
  if (!parent)
    return NULL;
  valid=FileNameChk(parent->mask);
  if (parent->dv->fs_type==FSt_REDSEA)
    preallocate=1;
  DirContextDel(parent);
  if (!valid || FileFind(name,NULL,FUF_JUST_DIRS))
    return NULL;
  exists=FileFind(name,NULL,FUF_JUST_FILES);
  if (mode==2 && !exists)
    return NULL;
  if (mode==1)
    file=FOpen(name,"w",preallocate);
  else
    file=FOpen(name,"w+",preallocate);
  if (file) {
    if (mode==1 || !exists) {
      file->de.size=0;
      parent=DirContextNew(file->de.full_name);
      DirNew(parent->dv,Fs->cur_dir,&file->de,FALSE);
      DirContextDel(parent);
      file->flags&=~FF_NEW_FILE;
      if (!FileFind(name,NULL,FUF_JUST_FILES))
        TilPanicZ("cfile_open: could not create directory entry\n");
    } else
      file->flags&=~FF_NEEDS_WRITE;
  }
  return file;
}

public U8 *TilFileOpen(TilStr *path,I64 mode)
{
  U8 *name=TilMAlloc(path->count+1);
  CFile *file;
  TilFileHandle *handle;
  TilMemCpy(name,path->c_str,path->count);
  name[path->count]=0;
  file=TilNativeFileOpen(name,mode);
  if (!file) {
    if (mode==2) TilRawWrite("cfile_open_update: could not open '",35);
    else if (mode==3) TilRawWrite("cfile_open_append: could not open '",35);
    else TilRawWrite("cfile_open: could not open '",28);
    TilRawWrite(name,path->count);
    TilFree(name);
    TilPanicZ("'\n");
  }
  TilFree(name);
  handle=TilCAlloc(1,sizeof(TilFileHandle));
  handle->file=file;
  handle->mode=mode;
  if (mode==3) handle->cursor=FSize(file);
  return handle;
}

public U0 TilFileClose(U8 *raw)
{
  TilFileHandle *handle=TilCheckPtr(raw)(TilFileHandle *);
  FClose(handle->file);
  TilFree(handle);
}

public I64 TilFileTell(U8 *raw)
{
  return TilCheckPtr(raw)(TilFileHandle *)->cursor;
}

public U0 TilFileSeek(U8 *raw,I64 offset,I64 origin)
{
  TilFileHandle *handle=TilCheckPtr(raw)(TilFileHandle *);
  I64 base=0;
  if (origin==1) base=handle->cursor;
  else if (origin==2) base=FSize(handle->file);
  if ((offset>=0 && base>I64_MAX-offset) ||
      (offset<0 && (offset==I64_MIN || base < -offset)))
    TilPanicZ("cfile_seek: invalid position\n");
  handle->cursor=base+offset;
}

public U0 TilFileReadN(TilStr *out,U8 *raw,I64 count)
{
  TilFileHandle *handle=TilCheckPtr(raw)(TilFileHandle *);
  I64 size=FSize(handle->file),got,left,block,offset,take;
  U8 *sector;
  if (handle->mode==1 || handle->mode==3)
    TilPanicZ("cfile_read_n: file opened for writing\n");
  if (count<0) count=0;
  if (count(U64)>=TIL_STR_CAP_VIEW || count>=I64_MAX)
    TilPanicZ("cfile_read_n: size overflow\n");
  out->c_str=TilMAlloc(count+1);
  out->count=0;
  out->cap=count;
  got=0;
  if (handle->cursor<size) {
    left=size-handle->cursor;
    if (left>count) left=count;
    sector=TilMAlloc(BLK_SIZE);
    while (left>0) {
      block=handle->cursor/BLK_SIZE;
      offset=handle->cursor%BLK_SIZE;
      take=BLK_SIZE-offset;
      if (take>left) take=left;
      if (!FBlkRead(handle->file,sector,block,1))
        TilPanicZ("cfile_read_n: read failed\n");
      TilMemCpy(out->c_str+got,sector+offset,take);
      handle->cursor+=take;
      got+=take;
      left-=take;
    }
    TilFree(sector);
  }
  out->c_str[got]=0;
  out->count=got;
}

public U0 TilFileReadAll(TilStr *out,U8 *raw)
{
  TilFileHandle *handle=TilCheckPtr(raw)(TilFileHandle *);
  handle->cursor=0;
  TilFileReadN(out,raw,FSize(handle->file));
}

U0 TilFileGrow(CFile *file,I64 needed)
{
  I64 old_blocks,new_blocks,new_clus,i;
  U8 *sector;
  if (file->dv->fs_type!=FSt_REDSEA || needed<=file->max_blk+1)
    return;
  old_blocks=file->max_blk+1;
  new_blocks=needed;
  new_clus=ClusAlloc(file->dv,0,new_blocks,TRUE);
  sector=TilMAlloc(BLK_SIZE);
  i=0;
  while (i<old_blocks) {
    if (!BlkRead(file->dv,sector,file->de.clus+i,1) ||
        !BlkWrite(file->dv,sector,new_clus+i,1))
      TilPanicZ("cfile_write_str: grow failed\n");
    i++;
  }
  TilFree(sector);
  if (old_blocks) RedSeaFreeClus(file->dv,file->de.clus,old_blocks);
  file->de.clus=new_clus;
  file->max_blk=new_blocks-1;
  file->flags|=FF_NEEDS_WRITE;
}

U0 TilFileWriteBytes(TilFileHandle *handle,U8 *data,I64 count,Bool zero_fill)
{
  I64 block,offset,take,old_size,live;
  U8 *sector=TilCAlloc(1,BLK_SIZE);
  TilFileGrow(handle->file,(handle->cursor+count+BLK_SIZE-1)/BLK_SIZE);
  while (count>0) {
    old_size=FSize(handle->file);
    block=handle->cursor/BLK_SIZE;
    offset=handle->cursor%BLK_SIZE;
    take=BLK_SIZE-offset;
    if (take>count) take=count;
    TilMemSet(sector,0,BLK_SIZE);
    if (block*BLK_SIZE<old_size) {
      if (!FBlkRead(handle->file,sector,block,1))
        TilPanicZ("cfile_write_str: read failed\n");
      live=old_size-block*BLK_SIZE;
      if (live<BLK_SIZE) TilMemSet(sector+live,0,BLK_SIZE-live);
    }
    if (zero_fill) TilMemSet(sector+offset,0,take);
    else TilMemCpy(sector+offset,data,take);
    if (!FBlkWrite(handle->file,sector,block,1))
      TilPanicZ("cfile_write_str: write failed\n");
    handle->cursor+=take;
    count-=take;
    if (!zero_fill) data+=take;
    if (handle->cursor>old_size) old_size=handle->cursor;
    handle->file->de.size=old_size;
    handle->file->flags|=FF_NEEDS_WRITE;
  }
  TilFree(sector);
}

public U0 TilFileWriteStr(U8 *raw,TilStr *content)
{
  TilFileHandle *handle=TilCheckPtr(raw)(TilFileHandle *);
  I64 size,cursor;
  if (!handle->mode)
    TilPanicZ("cfile_write_str: file not opened for writing\n");
  if (!content->count) return;
  if (handle->mode==3) handle->cursor=FSize(handle->file);
  if (handle->cursor>I64_MAX-BLK_SIZE ||
      content->count>I64_MAX-BLK_SIZE-handle->cursor)
    TilPanicZ("cfile_write_str: size overflow\n");
  size=FSize(handle->file);
  if (handle->cursor>size) {
    cursor=handle->cursor;
    handle->cursor=size;
    TilFileWriteBytes(handle,NULL,cursor-size,TRUE);
  }
  TilFileWriteBytes(handle,content->c_str,content->count,FALSE);
}

public U0 TilFileRead(TilStr *out,TilStr *path)
{
  U64 count=path->count;
  U8 *name=TilMAlloc(count+1);
  I64 size,blocks;
  CFile *file;
  U8 *data;
  TilMemCpy(name,path->c_str,count);
  name[count]=0;
  // FOpen uses the exact name: FileRead also searches parents and .Z names
  // and expands compressed content, unlike til's binary file API.
  file=FOpen(name,"r");
  if (!file) {
    TilRawWrite("cfile_open: could not open '",28);
    TilRawWrite(name,count);
    TilFree(name);
    TilPanicZ("'\n");
  }
  TilFree(name);
  size=FSize(file);
  if (size<0 || size(U64)>=TIL_STR_CAP_VIEW || size>I64_MAX-BLK_SIZE) {
    FClose(file);
    TilPanicZ("File.readfile: file too large\n");
  }
  blocks=(size+BLK_SIZE-1)/BLK_SIZE;
  data=TilCAlloc(blocks*BLK_SIZE+1,1);
  if (blocks && !FBlkRead(file,data,0,blocks)) {
    TilFree(data);
    FClose(file);
    TilPanicZ("File.readfile: read failed\n");
  }
  FClose(file);
  data[size]=0;
  out->c_str=data;
  out->count=size;
  out->cap=size;
}

public U0 TilFileWrite(TilStr *path,TilStr *content)
{
  U64 count=path->count;
  U8 *name=TilMAlloc(count+1);
  CFile *file=NULL;
  TilFileHandle handle;
  TilMemCpy(name,path->c_str,count);
  name[count]=0;
  file=TilNativeFileOpen(name,1);
  if (!file) {
    TilRawWrite("File.writefile: could not write '",33);
    TilRawWrite(name,count);
    TilFree(name);
    TilPanicZ("'\n");
  }
  TilFree(name);
  if (content->count>I64_MAX-BLK_SIZE) {
    FClose(file);
    TilPanicZ("File.writefile: file too large\n");
  }
  handle.file=file;
  handle.cursor=0;
  handle.mode=1;
  TilFileWriteStr(&handle,content);
  FClose(file);
}

class TilDirHandle {
  CDirEntry *entries;
  CDirEntry *next;
};

public U8 *TilDirOpen(TilStr *path)
{
  U8 *name=TilMAlloc(path->count+1);
  CDirContext *dir;
  TilDirHandle *handle;
  TilMemCpy(name,path->c_str,path->count);
  name[path->count]=0;
  if (!path->count || !IsDir(name)) {
    TilRawWrite("cdir_open: could not open '",27);
    TilRawWrite(name,path->count);
    TilFree(name);
    TilPanicZ("'\n");
  }
  dir=DirContextNew(name,TRUE);
  TilFree(name);
  handle=TilCAlloc(1,sizeof(TilDirHandle));
  handle->entries=FilesFind(dir->mask,0);
  handle->next=handle->entries;
  DirContextDel(dir);
  return handle;
}

public U0 TilDirNext(TilStr *out,U8 *raw)
{
  TilDirHandle *handle=TilCheckPtr(raw)(TilDirHandle *);
  CDirEntry *entry;
  I64 count;
  while (handle->next) {
    entry=handle->next;
    handle->next=entry->next;
    if (StrCmp(entry->name,".") && StrCmp(entry->name,"..")) {
      count=StrLen(entry->name);
      out->c_str=TilMAlloc(count+1);
      TilMemCpy(out->c_str,entry->name,count+1);
      out->count=count;
      out->cap=count;
      return;
    }
  }
  TilStrInitLit(out,"",0);
  TilStrPrepareReturn(out);
}

public U0 TilDirClose(U8 *raw)
{
  TilDirHandle *handle=TilCheckPtr(raw)(TilDirHandle *);
  DirTreeDel(handle->entries);
  TilFree(handle);
}

public U0 TilFileRemove(TilStr *path)
{
  U8 *name=TilMAlloc(path->count+1);
  I64 removed;
  TilMemCpy(name,path->c_str,path->count);
  name[path->count]=0;
  if (FileFind(name,NULL,FUF_JUST_DIRS)) {
    TilFree(name);
    TilPanicZ("cfile_remove: cannot remove a directory\n");
  }
  if (!FileFind(name,NULL,FUF_JUST_FILES)) {
    TilFree(name);
    return;
  }
  removed=Del(name,FALSE,FALSE,FALSE);
  TilFree(name);
  if (removed!=1) TilPanicZ("cfile_remove: removal failed\n");
}

public I32 TilRemoveTree(TilStr *path)
{
  U8 *name=TilMAlloc(path->count+1);
  CDirContext *dir;
  CDirEntry *entries,*entry;
  TilStr child;
  I64 removed;
  TilMemCpy(name,path->c_str,path->count); name[path->count]=0;
  if (FileFind(name,NULL,FUF_JUST_DIRS)) {
    dir=DirContextNew(name,TRUE);
    entries=FilesFind(dir->mask,0);
    DirContextDel(dir);
    entry=entries;
    while (entry) {
      if (StrCmp(entry->name,".") && StrCmp(entry->name,"..")) {
        TilStrInitLit(&child,entry->full_name,StrLen(entry->full_name));
        if (TilRemoveTree(&child)) { DirTreeDel(entries); TilFree(name); return 1; }
      }
      entry=entry->next;
    }
    DirTreeDel(entries);
    Del(name,FALSE,TRUE,FALSE);
    removed=IsDir(name);
    TilFree(name);
    return removed;
  }
  if (!FileFind(name,NULL,FUF_JUST_FILES)) { TilFree(name); return 0; }
  removed=Del(name,FALSE,FALSE,FALSE);
  TilFree(name);
  if (removed==1) return 0;
  return 1;
}

public I32 TilMakeDirs(TilStr *path)
{
  U8 *name=TilMAlloc(path->count+1),*saved;
  Bool made;
  if (!path->count) { TilFree(name); return 1; }
  TilMemCpy(name,path->c_str,path->count);
  name[path->count]=0;
  saved=DirCur;
  made=Cd(name,TRUE);
  if (!Cd(saved)) TilPanicZ("mkdir_p: could not restore directory\n");
  TilFree(saved);
  TilFree(name);
  if (made) return 0;
  return 1;
}

extern I32 TilFileRename(TilStr *src,TilStr *dst);

I32 TilDirectoryRename(U8 *src,U8 *dst)
{
  CDirContext *dir;
  CDirEntry *entries,*entry;
  U8 *child_dst;
  TilStr child_src_path,child_dst_path;
  if (FileFind(dst,NULL,FUF_JUST_FILES)) return 1;
  if (IsDir(dst)) {
    dir=DirContextNew(dst,TRUE);
    entries=FilesFind(dir->mask,0);
    DirContextDel(dir);
    entry=entries;
    while (entry) {
      if (StrCmp(entry->name,".") && StrCmp(entry->name,"..")) {
        DirTreeDel(entries);
        return 1;
      }
      entry=entry->next;
    }
    DirTreeDel(entries);
    Del(dst,FALSE,TRUE,FALSE);
  }
  if (!DirMk(dst)) return 1;
  dir=DirContextNew(src,TRUE);
  entries=FilesFind(dir->mask,0);
  DirContextDel(dir);
  entry=entries;
  while (entry) {
    if (StrCmp(entry->name,".") && StrCmp(entry->name,"..")) {
      child_dst=MStrPrint("%s/%s",dst,entry->name);
      TilStrInitLit(&child_src_path,entry->full_name,StrLen(entry->full_name));
      TilStrInitLit(&child_dst_path,child_dst,StrLen(child_dst));
      if (TilFileRename(&child_src_path,&child_dst_path)) {
        TilFree(child_dst);
        DirTreeDel(entries);
        return 1;
      }
      TilFree(child_dst);
    }
    entry=entry->next;
  }
  DirTreeDel(entries);
  Del(src,FALSE,TRUE,FALSE);
  if (IsDir(src)) return 1;
  return 0;
}

public I32 TilFileRename(TilStr *src,TilStr *dst)
{
  U8 *a=TilMAlloc(src->count+1),*b=TilMAlloc(dst->count+1);
  U8 *abs_a,*abs_b,*in_raw,*out_raw;
  CDirContext *parent;
  CFile *in_file,*out_file;
  TilFileHandle in_handle,out_handle;
  TilStr part;
  I64 removed;
  Bool valid,is_dir;
  I32 result;
  TilMemCpy(a,src->c_str,src->count); a[src->count]=0;
  TilMemCpy(b,dst->c_str,dst->count); b[dst->count]=0;
  is_dir=FileFind(a,NULL,FUF_JUST_DIRS);
  if (!is_dir && !FileFind(a,NULL,FUF_JUST_FILES)) { TilFree(a); TilFree(b); return 1; }
  abs_a=FileNameAbs(a); abs_b=FileNameAbs(b);
  if (!StrCmp(abs_a,abs_b)) {
    TilFree(abs_a); TilFree(abs_b); TilFree(a); TilFree(b); return 0;
  }
  if (is_dir) {
    parent=DirContextNew(b);
    if (!parent) { TilFree(abs_a); TilFree(abs_b); TilFree(a); TilFree(b); return 1; }
    valid=parent->dv==Let2Drv(*abs_a) && FileNameChk(parent->mask);
    DirContextDel(parent);
    if (!StrNCmp(abs_a,abs_b,StrLen(abs_a)) && abs_b[StrLen(abs_a)]=='/') valid=FALSE;
    result=1;
    if (valid) result=TilDirectoryRename(a,b);
    TilFree(abs_a); TilFree(abs_b); TilFree(a); TilFree(b);
    return result;
  }
  in_file=FOpen(a,"r");
  parent=DirContextNew(b);
  if (!parent) { FClose(in_file); TilFree(abs_a); TilFree(abs_b); TilFree(a); TilFree(b); return 1; }
  valid=parent->dv==in_file->dv && FileNameChk(parent->mask);
  DirContextDel(parent);
  if (!valid || FileFind(b,NULL,FUF_JUST_DIRS)) {
    FClose(in_file); TilFree(abs_a); TilFree(abs_b); TilFree(a); TilFree(b); return 1;
  }
  // TempleOS Move is copy-and-delete, not a POSIX atomic rename. Use the
  // counted raw stream path so .Z suffixes never transform the contents.
  out_file=TilNativeFileOpen(b,1);
  if (!out_file) { FClose(in_file); TilFree(abs_a); TilFree(abs_b); TilFree(a); TilFree(b); return 1; }
  in_handle.file=in_file; in_handle.cursor=0; in_handle.mode=0;
  out_handle.file=out_file; out_handle.cursor=0; out_handle.mode=1;
  in_raw=&in_handle; out_raw=&out_handle;
  while (in_handle.cursor<FSize(in_file)) {
    TilFileReadN(&part,in_raw,65536);
    TilFileWriteStr(out_raw,&part);
    TilStrDelete(&part,FALSE);
  }
  FClose(out_file); FClose(in_file);
  removed=Del(a,FALSE,FALSE,FALSE);
  TilFree(abs_a); TilFree(abs_b); TilFree(a); TilFree(b);
  if (removed!=1) TilPanicZ("crename_path: could not remove source\n");
  return 0;
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
  TIL_USIZE i=0;
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

U0 TilStrFromMagnitude(TilStr *out,U64 magnitude,Bool negative)
{
  U64 rest;
  TIL_USIZE digits=1,count,index;
  U8 *data;
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

public U0 TilStrFromI64(TilStr *out,I64 value)
{
  U64 magnitude;
  Bool negative=value<0;
  if (negative)
    magnitude=-(value+1)+1;
  else
    magnitude=value;
  TilStrFromMagnitude(out,magnitude,negative);
}

public U0 TilStrFromU64(TilStr *out,U64 value)
{
  TilStrFromMagnitude(out,value,FALSE);
}

public U0 TilStrFromBool(TilStr *out,Bool value)
{
  if (value) TilStrInitLit(out,"true",4);
  else TilStrInitLit(out,"false",5);
  TilStrPrepareReturn(out);
}

public Bool TilStrEq(TilStr *a,TilStr *b)
{
  if (a->count!=b->count)
    return FALSE;
  return TilMemCmp(a->c_str,b->c_str,a->count)==0;
}

public I64 TilStrCmp(TilStr *a,TilStr *b)
{
  TIL_USIZE count=a->count;
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

public U0 TilStrArrayNew(TilStrArray *out,TIL_USIZE cap)
{
  out->data=TilCAlloc(cap,sizeof(TilStr));
  out->cap=cap;
}

public U0 TilStrArraySet(TilStrArray *array,TIL_USIZE index,TilStr *value)
{
  TilStr *slot;
  if (index>=array->cap)
    TilPanicZ("Array.set: index out of bounds\n");
  slot=&array->data[index];
  TilStrDelete(slot,FALSE);
  TilStrCopyValue(slot,value);
  value->c_str=NULL;
  value->count=0;
  value->cap=TIL_STR_CAP_VIEW;
}

public U0 TilStrArrayDelete(TilStrArray *array)
{
  TIL_USIZE i=0;
  while (i<array->cap) {
    TilStrDelete(&array->data[i],FALSE);
    i++;
  }
  TilFree(array->data);
  array->data=NULL;
  array->cap=0;
}

public U0 TilPrint(TilStrArray *parts)
{
  TIL_USIZE i=0;
  while (i<parts->cap) {
    TilStrWrite(&parts->data[i]);
    i++;
  }
  TilStrArrayDelete(parts);
}

public U0 TilPrintln(TilStrArray *parts)
{
  TilPrint(parts);
  TilRawWrite("\n",1);
}

public U0 TilStrTakeBox(TilStr *out,TilStr *box)
{
  TilStrCopyValue(out,box);
  TilFree(box);
}

public U0 TilFormat(TilStr *out,TilStrArray *parts)
{
  TIL_USIZE total=0,i=0;
  while (i<parts->cap) {
    if (parts->data[i].count>=TIL_STR_CAP_VIEW-total)
      TilPanicZ("format: size overflow\n");
    total+=parts->data[i].count;
    i++;
  }
  TilStrWithCapacity(out,total);
  i=0;
  while (i<parts->cap) {
    TilStrPush(out,&parts->data[i]);
    i++;
  }
  TilStrArrayDelete(parts);
}

// Exact finite IEEE values are integers times a power of two. Base-10^9
// limbs keep their decimal expansions small (at most 768 decimal digits,
// including adjacent-value midpoints). No host libc or approximate Pow10
// participates in parsing or rounding.
class TilFloatDecimal {
  U32 limb[90];
  I64 count;
  I64 digits;
  I64 power;
};

U64 TilFloatPow10(I64 n)
{
  U64 result=1;
  while (n--) result*=10;
  return result;
}

U0 TilFloatDecimalMul(TilFloatDecimal *d,U64 factor)
{
  U64 carry=0,value;
  I64 i=0;
  while (i<d->count) {
    value=d->limb[i]*factor+carry;
    d->limb[i]=value%1000000000;
    carry=value/1000000000;
    i++;
  }
  while (carry) {
    d->limb[d->count++]=carry%1000000000;
    carry/=1000000000;
  }
}

U0 TilFloatDecimalMake(TilFloatDecimal *d,U64 mantissa,I64 binary_power)
{
  I64 left,shift=0;
  U64 high;
  d->count=0;
  do {
    d->limb[d->count++]=mantissa%1000000000;
    mantissa/=1000000000;
  } while (mantissa);
  if (binary_power>=0) {
    left=binary_power;
    while (left>=29) { TilFloatDecimalMul(d,536870912); left-=29; }
    if (left) TilFloatDecimalMul(d,1<<left);
  } else {
    shift=binary_power;
    left=-binary_power;
    while (left>=13) { TilFloatDecimalMul(d,1220703125); left-=13; }
    high=1;
    while (left--) high*=5;
    TilFloatDecimalMul(d,high);
  }
  high=d->limb[d->count-1];
  d->digits=9*(d->count-1)+1;
  while (high>=10) { high/=10; d->digits++; }
  d->power=d->digits-1+shift;
}

U0 TilFloatUnpack(U64 bits,I64 width,U64 *mantissa,I64 *power)
{
  U64 exponent;
  if (width==32) {
    exponent=(bits>>23)&255;
    *mantissa=bits&0x7FFFFF;
    *power=-149;
    if (exponent) { *mantissa|=0x800000; *power=exponent(I64)-150; }
  } else {
    exponent=(bits>>52)&2047;
    *mantissa=bits&0xFFFFFFFFFFFFF;
    *power=-1074;
    if (exponent) { *mantissa|=0x10000000000000; *power=exponent(I64)-1075; }
  }
}

I64 TilFloatDecimalDigit(TilFloatDecimal *d,I64 ordinal)
{
  // Comparisons pad a shorter significant digit string with trailing zeros.
  if (ordinal>=d->digits) return 0;
  I64 place=d->digits-ordinal-1;
  return (d->limb[place/9]/TilFloatPow10(place%9))%10;
}

Bool TilFloatDecimalTail(TilFloatDecimal *d,I64 low_digits)
{
  I64 whole=low_digits/9,i=0;
  while (i<whole) { if (d->limb[i++]) return TRUE; }
  return d->limb[whole]%TilFloatPow10(low_digits%9)!=0;
}

public U64 TilF64Word(F64 value)
{
  return value(U64);
}

public U0 TilStrFromFloat(TilStr *out,U64 bits,I64 width,I64 precision)
{
  U64 magnitude,exponent,fraction,mantissa;
  I64 binary_power,i,n,keep,next,pos,place;
  Bool negative,round_up;
  TilFloatDecimal d;
  U8 digits[20],*text;
  if (width==32) {
    negative=(bits&0x80000000)!=0;
    magnitude=bits&0x7FFFFFFF;
    exponent=magnitude>>23;
    fraction=magnitude&0x7FFFFF;
  } else {
    negative=(bits&0x8000000000000000)!=0;
    magnitude=bits&0x7FFFFFFFFFFFFFFF;
    exponent=magnitude>>52;
    fraction=magnitude&0xFFFFFFFFFFFFF;
  }
  TilStrWithCapacity(out,64);
  text=out->c_str;
  n=0;
  if (negative) text[n++]='-';
  if ((width==32 && exponent==255) || (width==64 && exponent==2047)) {
    if (fraction) { MemCpy(text+n,"nan",3); n+=3; }
    else { MemCpy(text+n,"inf",3); n+=3; }
  } else if (!magnitude) {
    text[n++]='0';
  } else {
    TilFloatUnpack(magnitude,width,&mantissa,&binary_power);
    TilFloatDecimalMake(&d,mantissa,binary_power);
    keep=d.digits;
    if (keep>precision) keep=precision;
    i=0;
    while (i<keep) { digits[i]=TilFloatDecimalDigit(&d,i); i++; }
    if (d.digits>keep) {
      next=TilFloatDecimalDigit(&d,keep);
      round_up=next>5 || next==5 &&
        (TilFloatDecimalTail(&d,d.digits-keep-1) || (digits[keep-1]&1));
      if (round_up) {
        i=keep-1;
        while (i>=0 && digits[i]==9) { digits[i]=0; i--; }
        if (i>=0) digits[i]++;
        else { digits[0]=1; d.power++; }
      }
    }
    while (keep>1 && !digits[keep-1]) keep--;
    if (d.power<-4 || d.power>=precision) {
      text[n++]=digits[0]+'0';
      if (keep>1) {
        text[n++]='.';
        i=1;
        while (i<keep) text[n++]=digits[i++]+'0';
      }
      text[n++]='e';
      place=d.power;
      if (place<0) { text[n++]='-'; place=-place; }
      else text[n++]='+';
      if (place>=100) { text[n++]=place/100+'0'; place%=100; }
      text[n++]=place/10+'0';
      text[n++]=place%10+'0';
    } else if (d.power<0) {
      text[n++]='0'; text[n++]='.';
      pos=-d.power-1;
      while (pos--) text[n++]='0';
      i=0;
      while (i<keep) text[n++]=digits[i++]+'0';
    } else {
      i=0;
      while (i<=d.power) {
        if (i<keep) text[n++]=digits[i]+'0';
        else text[n++]='0';
        i++;
      }
      if (i<keep) {
        text[n++]='.';
        while (i<keep) text[n++]=digits[i++]+'0';
      }
    }
  }
  text[n]=0;
  out->count=n;
}

I64 TilFloatDecimalCompare(U8 *digits,I64 count,I64 power,TilFloatDecimal *d)
{
  I64 i=0,a,b,end=count;
  if (d->count==1 && !d->limb[0]) return 1;
  if (power<d->power) return -1;
  if (power>d->power) return 1;
  if (d->digits>end) end=d->digits;
  while (i<end) {
    a=0;
    if (i<count) a=digits[i]-'0';
    b=TilFloatDecimalDigit(d,i);
    if (a<b) return -1;
    if (a>b) return 1;
    i++;
  }
  return 0;
}

I64 TilFloatExponent(U8 *p,I64 limit)
{
  Bool negative=FALSE;
  I64 value=0,digit;
  if (*p=='+' || *p=='-') { negative=*p=='-'; p++; }
  while ('0'<=*p<='9') {
    digit=*p++-'0';
    // Exponents beyond the complete mantissa length plus IEEE's range
    // cannot cancel back to a finite value. Saturation retains that sign.
    if (value>(limit-digit)/10) value=limit;
    else value=value*10+digit;
  }
  if (negative) return -value;
  return value;
}

I64 TilFloatHexDigit(U8 ch)
{
  if ('0'<=ch<='9') return ch-'0';
  ch=ToUpper(ch);
  if ('A'<=ch<='F') return ch-'A'+10;
  return -1;
}

U64 TilFloatParseHex(U8 *p,I64 width,I64 length)
{
  U8 *start=p,*q;
  I64 total=0,fraction=0,first=-1,leading=0,digit,exponent,want;
  I64 precision=53,bias=1023,min_exponent=-1022,max_exponent=1023;
  I64 seen=0,j,top;
  U64 mantissa=0,bit,infinity_bits=0x7FF0000000000000;
  Bool point=FALSE,started=FALSE,guard=FALSE,sticky=FALSE;
  if (width==32) { precision=24; bias=127; min_exponent=-126; max_exponent=127; infinity_bits=0x7F800000; }
  while (TRUE) {
    digit=TilFloatHexDigit(*p);
    if (digit>=0) {
      if (digit && first<0) { first=total; leading=digit; }
      total++;
      if (point) fraction++;
      p++;
    } else if (*p=='.' && !point) { point=TRUE; p++; }
    else break;
  }
  if (first<0) return 0;
  exponent=0;
  if (ToUpper(*p)=='P') exponent=TilFloatExponent(p+1,4*length+4096);
  top=0;
  while (leading>=2) { leading>>=1; top++; }
  exponent+=4*(total-first-1-fraction)+top;
  if (exponent>max_exponent) return infinity_bits;
  if (exponent<min_exponent-precision) return 0;
  want=precision;
  if (exponent<min_exponent) want+=exponent-min_exponent;
  q=start;
  while (q<p) {
    if (*q=='.') q++;
    else {
      digit=TilFloatHexDigit(*q++);
      j=3;
      while (j>=0) {
        bit=(digit>>j--)&1;
        if (bit || started) {
          started=TRUE;
          if (seen<want) mantissa=mantissa<<1|bit;
          else if (seen==want) guard=bit;
          else if (bit) sticky=TRUE;
          seen++;
        }
      }
    }
  }
  if (seen<want) mantissa<<=want-seen;
  if (guard && (sticky || (mantissa&1))) mantissa++;
  if (exponent<min_exponent) return mantissa;
  if (mantissa==1<<precision) { mantissa>>=1; exponent++; }
  if (exponent>max_exponent) return infinity_bits;
  return (exponent+bias)(U64)<<(precision-1) | (mantissa&((1<<(precision-1))-1));
}

public U64 TilFloatParse(TilStr *source,I64 width,Bool separators)
{
  U8 *text,*p,*digits,*q;
  I64 length=0,i=0,count=0,fraction=0,first,power=0,binary_power,comparison;
  I64 max_power=308,min_power=-324;
  U64 sign=0,infinity_bits=0x7FF0000000000000,nan_bits=0x7FF8000000000000;
  U64 lo=0,hi=0x7FEFFFFFFFFFFFFF,mid,mantissa,result;
  Bool point=FALSE;
  TilFloatDecimal d;
  if (width==32) { infinity_bits=0x7F800000; nan_bits=0x7FC00000; hi=0x7F7FFFFF; max_power=38; min_power=-46; }
  text=TilMAlloc(source->count+1);
  while (i<source->count && source->c_str[i]) {
    if (!separators || source->c_str[i]!='_') text[length++]=source->c_str[i];
    i++;
  }
  text[length]=0;
  p=text;
  while (*p==' ' || *p=='\t' || *p=='\r' || *p=='\n' || *p==11 || *p==12) p++;
  if (*p=='+' || *p=='-') {
    if (*p=='-') {
      if (width==32) sign=0x80000000;
      else sign=0x8000000000000000;
    }
    p++;
  }
  if (ToUpper(p[0])=='I' && ToUpper(p[1])=='N' && ToUpper(p[2])=='F') {
    TilFree(text); return sign|infinity_bits;
  }
  if (ToUpper(p[0])=='N' && ToUpper(p[1])=='A' && ToUpper(p[2])=='N') {
    TilFree(text); return sign|nan_bits;
  }
  if (p[0]=='0' && ToUpper(p[1])=='X') {
    q=p+2;
    if (*q=='.') q++;
    if (TilFloatHexDigit(*q)>=0) {
      result=TilFloatParseHex(p+2,width,length);
      TilFree(text); return sign|result;
    }
  }
  digits=TilMAlloc(length+1);
  while (TRUE) {
    if ('0'<=*p<='9') {
      digits[count++]=*p++;
      if (point) fraction++;
    } else if (*p=='.' && !point) { point=TRUE; p++; }
    else break;
  }
  if (!count) { TilFree(digits); TilFree(text); return 0; }
  if (ToUpper(*p)=='E') power=TilFloatExponent(p+1,length+4096);
  first=0;
  while (first<count && digits[first]=='0') first++;
  if (first==count) { TilFree(digits); TilFree(text); return sign; }
  power+=count-first-1-fraction;
  q=digits+first;
  count-=first;
  while (count>1 && q[count-1]=='0') count--;
  if (power>max_power) { TilFree(digits); TilFree(text); return sign|infinity_bits; }
  if (power<min_power) { TilFree(digits); TilFree(text); return sign; }
  // Positive IEEE bit patterns are ordered numerically. Find the exact
  // lower neighbor, then compare with its exact midpoint and round to even.
  while (lo<hi) {
    mid=lo+(hi-lo+1)/2;
    TilFloatUnpack(mid,width,&mantissa,&binary_power);
    TilFloatDecimalMake(&d,mantissa,binary_power);
    comparison=TilFloatDecimalCompare(q,count,power,&d);
    if (comparison>=0) lo=mid;
    else hi=mid-1;
  }
  TilFloatUnpack(lo,width,&mantissa,&binary_power);
  TilFloatDecimalMake(&d,2*mantissa+1,binary_power-1);
  comparison=TilFloatDecimalCompare(q,count,power,&d);
  if (comparison>0 || comparison==0 && (lo&1)) lo++;
  TilFree(digits);
  TilFree(text);
  return sign|lo;
}

// Metadata dispatchers are generated from the same loaded definitions as
// ordinary methods. Names remain counted strings, not C-string lookups.
public Bool TilStrNameEq(TilStr *name,U8 *literal)
{
  I64 count=StrLen(literal);
  return name->count==count && (!count || !MemCmp(name->c_str,literal,count));
}

public U0 TilReflectMissing(U8 *who,TilStr *name)
{
  TilRawWrite(who,StrLen(who));
  TilRawWrite(": type '",8);
  TilStrWrite(name);
  TilRawWrite("' not found\n",12);
  TilPanicZ("  note: unknown type, or dropped as unused -- reflection keeps a type when its name is a literal here, or the type is used elsewhere\n");
}

public U0 TilReflectIndex(U8 *who,TilStr *name,I64 index)
{
  TilStr text;
  TilRawWrite(who,StrLen(who));
  TilRawWrite(": type '",8);
  TilStrWrite(name);
  TilRawWrite("' index ",8);
  TilStrFromI64(&text,index);
  TilStrWrite(&text);
  TilStrDelete(&text,FALSE);
  TilPanicZ(" out of range\n");
}

public I64 TilClockMs()
{
  return ToI64(tS*1000.0);
}

public U0 TilSleepMs(I64 ms)
{
  if (ms>0) Sleep(ms);
}

public Bool TilReadLine(TilStr *line)
{
  U8 *input=GetStr;
  TIL_USIZE count;
  count=StrLen(input);
  // GetStr returns an allocated line without its newline, including for
  // blank input. TempleOS's interactive console has no stream EOF.
  TilStrDelete(line,FALSE);
  line->c_str=input;
  line->count=count;
  line->cap=count;
  return TRUE;
}

// Minimal mode-gui bridge. Color and Image use the existing facade's layouts;
// opaque pointers keep these helpers independent of generated class names.
class TilGuiColor { U8 r,g,b,a; };
class TilGuiImage { U8 *data; I32 width,height,mipmaps,format; };
class TilGuiVector2 { F32 x,y; };
CDC *TilGuiFront=NULL,*TilGuiBack=NULL;
I64 TilGuiWidth=GR_WIDTH,TilGuiHeight=GR_HEIGHT;
I64 TilGuiViewX=0,TilGuiViewY=0,TilGuiViewWidth=GR_WIDTH,TilGuiViewHeight=GR_HEIGHT;
I64 TilGuiFrameMs=0,TilGuiOldLeft,TilGuiOldRight,TilGuiOldTop,TilGuiOldBottom;
I64 TilGuiOldInhibit,TilGuiMouseX=0,TilGuiMouseY=0;
CCtrl *TilGuiWheelControl=NULL;
I64 TilGuiWheelPending=0;
F32 TilGuiWheelMove=0;
Bool TilGuiWheelFocused=FALSE;
Bool TilGuiDrawing=FALSE,TilGuiOldBorder;
U8 TilGuiOldTitle[STR_LEN];
U0 (*TilGuiOldDraw)(CTask *task,CDC *dc);
TilGuiOldDraw=NULL;

// Raylib-compatible frame snapshots and separate, consuming key/text queues.
// These are not a unified ordered event stream. ScanMsg supplies both key
// directions; ScanChar/ScanKey would discard releases (and ScanChar can block).
U8 TilGuiKeys[512],TilGuiPreviousKeys[512],TilGuiRepeatKeys[512];
U8 TilGuiMouseButtons[3],TilGuiPreviousMouseButtons[3];
Bool TilGuiMiddlePhysical=FALSE,TilGuiMiddleOwned=FALSE;
I32 TilGuiKeyQueue[32],TilGuiCharQueue[32];
I64 TilGuiKeyCount=0,TilGuiKeyRead=0,TilGuiCharCount=0,TilGuiCharRead=0;
I64 TilGuiExitKey=256;
Bool TilGuiShouldClose=FALSE;
Bool TilGuiScissorActive=FALSE;
I64 TilGuiScissorLeft,TilGuiScissorTop,TilGuiScissorRight,TilGuiScissorBottom;

I64 TilGuiKeyCode(I64 scan)
{
  // The upper scan-code half retains physical left/right/keypad identity.
  I64 raw=scan>>32,code=raw&0x7F,ch;
  if (raw&SCF_E0_PREFIX) {
    switch (code) {
      case 0x1C: return 335; // keypad enter
      case 0x1D: return 345; // right control
      case 0x35: return 331; // keypad divide
      case 0x37: return 283; // print screen
      case 0x38: return 346; // right alt
      case 0x47: return 268; // home
      case 0x48: return 265; // up
      case 0x49: return 266; // page up
      case 0x4B: return 263; // left
      case 0x4D: return 262; // right
      case 0x4F: return 269; // end
      case 0x50: return 264; // down
      case 0x51: return 267; // page down
      case 0x52: return 260; // insert
      case 0x53: return 261; // delete
      case 0x5B: return 343; // left super
      case 0x5C: return 347; // right super
      case 0x5D: return 348; // menu
    }
    // E0 synthetic shift packets have no corresponding facade key.
    return 0;
  }
  switch (code) {
    case 0x01: return 256;
    case 0x0E: return 259;
    case 0x0F: return 258;
    case 0x1C: return 257;
    case 0x1D: return 341;
    case 0x2A: return 340;
    case 0x36: return 344;
    case 0x37: return 332; // keypad multiply
    case 0x38: return 342;
    case 0x3A: return 280;
    case 0x45: return 282;
    case 0x46: return 281;
    case 0x47: return 327;
    case 0x48: return 328;
    case 0x49: return 329;
    case 0x4A: return 333;
    case 0x4B: return 324;
    case 0x4C: return 325;
    case 0x4D: return 326;
    case 0x4E: return 334;
    case 0x4F: return 321;
    case 0x50: return 322;
    case 0x51: return 323;
    case 0x52: return 320;
    case 0x53: return 330;
    case 0x57: return 300;
    case 0x58: return 301;
  }
  if (code>=SC_F1 && code<=SC_F10) return 290+code-SC_F1;
  ch=ScanCode2Char(code);
  if (ch>='a' && ch<='z') return ch-'a'+'A';
  if (ch>=32 && ch<=126) return ch;
  // Unknown/non-key scan packets do not produce a facade key.
  return 0;
}

U0 TilGuiPollInput()
{
  I64 message,ch,scan,key,raw,wheel_delta;
  Bool focused,was_focused,middle_down;
  U8 physical_keys[512];
  MemCpy(TilGuiPreviousKeys,TilGuiKeys,sizeof(TilGuiKeys));
  MemCpy(TilGuiPreviousMouseButtons,TilGuiMouseButtons,sizeof(TilGuiMouseButtons));
  MemSet(TilGuiRepeatKeys,0,sizeof(TilGuiRepeatKeys));
  TilGuiKeyCount=0; TilGuiKeyRead=0;
  TilGuiCharCount=0; TilGuiCharRead=0;
  while (message=ScanMsg(&ch,&scan,(1<<MSG_KEY_DOWN)|(1<<MSG_KEY_UP)|
        (1<<MSG_MS_MOVE)|(1<<MSG_MS_L_DOWN)|(1<<MSG_MS_L_UP)|
        (1<<MSG_MS_L_D_DOWN)|(1<<MSG_MS_L_D_UP)|(1<<MSG_MS_R_DOWN)|
        (1<<MSG_MS_R_UP)|(1<<MSG_MS_R_D_DOWN)|(1<<MSG_MS_R_D_UP))) {
    if (message==MSG_KEY_DOWN || message==MSG_KEY_UP) {
      key=TilGuiKeyCode(scan);
      if (key) {
        if (message==MSG_KEY_UP) TilGuiKeys[key]=0;
        else if (TilGuiKeys[key]) TilGuiRepeatKeys[key]=1;
        else {
          TilGuiKeys[key]=1;
          if (TilGuiKeyCount==32) TilPanicZ("GUI key queue overflow\n");
          TilGuiKeyQueue[TilGuiKeyCount++]=key;
          if (key==TilGuiExitKey) TilGuiShouldClose=TRUE;
        }
      }
      if (message==MSG_KEY_DOWN && !(scan&(SCF_CTRL|SCF_ALT))) {
        if (ch==CH_SHIFT_SPACE) ch=' ';
        // Control/non-text messages never become printable input. TempleOS
        // extended screen codes are not Unicode scalars: reject them explicitly.
        if (ch>126) TilPanicZ("GUI input POC requires printable ASCII\n");
        if (ch>=32) {
          if (TilGuiCharCount==32) TilPanicZ("GUI character queue overflow\n");
          TilGuiCharQueue[TilGuiCharCount++]=ch;
        }
      }
    } else {
      switch (message) {
        case MSG_MS_L_DOWN: case MSG_MS_L_D_DOWN: TilGuiMouseButtons[0]=1; break;
        case MSG_MS_L_UP: case MSG_MS_L_D_UP: TilGuiMouseButtons[0]=0; break;
        case MSG_MS_R_DOWN: case MSG_MS_R_D_DOWN: TilGuiMouseButtons[1]=1; break;
        case MSG_MS_R_UP: case MSG_MS_R_D_UP: TilGuiMouseButtons[1]=0; break;
      }
    }
  }
  // Match the facade's client coordinates, not DolDoc's scrolled coordinates
  // carried by MSG_MS_MOVE. Position is sampled once for consistent X/Y/Vector2.
  TilGuiMouseX=(ms.pos.x-Fs->pix_left-TilGuiViewX)*TilGuiWidth/TilGuiViewWidth;
  TilGuiMouseY=(ms.pos.y-Fs->pix_top-TilGuiViewY)*TilGuiHeight/TilGuiViewHeight;
  // Wheel callbacks run in the window manager. Publish one non-consuming
  // snapshot per application frame, discarding input across observed blur.
  PUSHFD
  CLI
  wheel_delta=TilGuiWheelPending;
  TilGuiWheelPending=0;
  focused=sys_focus_task==Fs;
  was_focused=TilGuiWheelFocused;
  TilGuiWheelFocused=focused;
  middle_down=ms_hard.bttns[2];
  if (!middle_down) {
    TilGuiMiddleOwned=FALSE;
    TilGuiMiddlePhysical=FALSE;
  } else if (!focused) TilGuiMiddleOwned=FALSE;
  TilGuiMouseButtons[2]=TilGuiMiddleOwned;
  POPFD
  TilGuiWheelMove=0;
  if (focused && was_focused)
    TilGuiWheelMove=TilF32FromI64(wheel_delta);
  if (!focused) {
    // TempleOS delivers releases to the task focused when the release occurs,
    // not necessarily the one that received the press. Blur releases our held
    // keys once, without inventing key/text queue entries.
    MemSet(TilGuiKeys,0,sizeof(TilGuiKeys));
    MemSet(TilGuiRepeatKeys,0,sizeof(TilGuiRepeatKeys));
    MemSet(TilGuiMouseButtons,0,sizeof(TilGuiMouseButtons));
  } else {
    // A loss and regain can both happen between polls. Reconcile existing
    // held keys with the physical bitmap so a release elsewhere is not lost.
    // Do not promote background-held keys into new GUI presses on refocus.
    MemSet(physical_keys,0,sizeof(physical_keys));
    for (raw=0;raw<256;raw++)
      if (Bt(kbd.down_bitmap2,raw)) {
        key=TilGuiKeyCode(raw<<32);
        if (key) physical_keys[key]=1;
      }
    for (key=1;key<512;key++)
      TilGuiKeys[key]&=physical_keys[key];
    TilGuiMouseButtons[0]&=ms.lb;
    TilGuiMouseButtons[1]&=ms.rb;
  }
}

Bool TilGuiMouseButtonValid(I64 button)
{
  if (button<0 || button>=8) return FALSE;
  if (button>2) TilPanicZ("GUI mouse POC supports left/right/middle buttons\n");
  return TRUE;
}

public Bool TilGuiIsMouseButtonDown(I64 button)
{
  return TilGuiMouseButtonValid(button) && TilGuiMouseButtons[button];
}

public Bool TilGuiIsMouseButtonUp(I64 button)
{
  return TilGuiMouseButtonValid(button) && !TilGuiMouseButtons[button];
}

public Bool TilGuiIsMouseButtonPressed(I64 button)
{
  return TilGuiMouseButtonValid(button) && TilGuiMouseButtons[button] && !TilGuiPreviousMouseButtons[button];
}

public Bool TilGuiIsMouseButtonReleased(I64 button)
{
  return TilGuiMouseButtonValid(button) && !TilGuiMouseButtons[button] && TilGuiPreviousMouseButtons[button];
}

public I32 TilGuiGetMouseX()
{
  return TilGuiMouseX;
}

public I32 TilGuiGetMouseY()
{
  return TilGuiMouseY;
}

public U0 TilGuiGetMousePosition(U8 *out)
{
  TilGuiVector2 *position=out(TilGuiVector2 *);
  position->x=TilF32FromI64(TilGuiMouseX);
  position->y=TilF32FromI64(TilGuiMouseY);
}

U0 TilGuiUpdateMiddle(CCtrl *control)
{
  Bool physical,focused;
  // Middle has no task message. The existing control hook runs on every
  // WinMgr task-derived update, even when our GUI is covered or not polling.
  PUSHFD
  CLI
  physical=ms_hard.bttns[2];
  focused=sys_focus_task==control->win_task;
  if (!(physical && focused)) TilGuiMiddleOwned=FALSE;
  else if (!TilGuiMiddlePhysical) TilGuiMiddleOwned=TRUE;
  TilGuiMiddlePhysical=physical;
  POPFD
}

U0 TilGuiWheelChanged(CCtrl *,I64 delta)
{
  // TempleOS's vertical axis increases downward; the facade is positive up.
  // Match raylib's last-event snapshot, without adding events or scaling ticks.
  PUSHFD
  CLI
  TilGuiWheelPending=-delta;
  POPFD
}

public F32 TilGuiGetMouseWheelMove()
{
  return TilGuiWheelMove;
}

public U0 TilGuiGetMouseWheelMoveV(U8 *out)
{
  TilGuiVector2 *move=out(TilGuiVector2 *);
  move->x=0;
  move->y=TilGuiWheelMove;
}

public Bool TilGuiIsKeyDown(I64 key)
{
  return key>0 && key<512 && TilGuiKeys[key];
}

public Bool TilGuiIsKeyUp(I64 key)
{
  return key>0 && key<512 && !TilGuiKeys[key];
}

public Bool TilGuiIsKeyPressed(I64 key)
{
  return key>0 && key<512 && TilGuiKeys[key] && !TilGuiPreviousKeys[key];
}

public Bool TilGuiIsKeyReleased(I64 key)
{
  return key>0 && key<512 && !TilGuiKeys[key] && TilGuiPreviousKeys[key];
}

public Bool TilGuiIsKeyPressedRepeat(I64 key)
{
  return key>0 && key<512 && TilGuiRepeatKeys[key];
}

public I32 TilGuiGetKeyPressed()
{
  if (TilGuiKeyRead==TilGuiKeyCount) return 0;
  return TilGuiKeyQueue[TilGuiKeyRead++];
}

public I32 TilGuiGetCharPressed()
{
  if (TilGuiCharRead==TilGuiCharCount) return 0;
  return TilGuiCharQueue[TilGuiCharRead++];
}

public Bool TilGuiWindowShouldClose()
{
  return TilGuiShouldClose;
}

public U0 TilGuiSetExitKey(I64 key)
{
  TilGuiExitKey=key;
}

U0 TilGuiDraw(CTask *task,CDC *dc)
{
  GrBlot(dc,0,0,TilGuiFront);
}

public U0 TilGuiInitWindow(I64 width,I64 height,U8 *title)
{
  if (width<=0 || height<=0) TilPanicZ("GUI requires positive window dimensions\n");
  // TempleOS has a fixed display. Preserve application coordinates and fit
  // larger canvases to it, with the inverse mapping used for mouse input.
  TilGuiWidth=width; TilGuiHeight=height;
  TilGuiViewWidth=MinI64(width,GR_WIDTH);
  TilGuiViewHeight=MaxI64(1,height*TilGuiViewWidth/width);
  if (TilGuiViewHeight>GR_HEIGHT) {
    TilGuiViewHeight=GR_HEIGHT;
    TilGuiViewWidth=MaxI64(1,width*GR_HEIGHT/height);
  }
  TilGuiViewX=(GR_WIDTH-TilGuiViewWidth)/2;
  TilGuiViewY=(GR_HEIGHT-TilGuiViewHeight)/2;
  MemSet(TilGuiKeys,0,sizeof(TilGuiKeys));
  MemSet(TilGuiPreviousKeys,0,sizeof(TilGuiPreviousKeys));
  MemSet(TilGuiRepeatKeys,0,sizeof(TilGuiRepeatKeys));
  MemSet(TilGuiMouseButtons,0,sizeof(TilGuiMouseButtons));
  MemSet(TilGuiPreviousMouseButtons,0,sizeof(TilGuiPreviousMouseButtons));
  TilGuiKeyCount=0; TilGuiKeyRead=0; TilGuiCharCount=0; TilGuiCharRead=0;
  TilGuiShouldClose=FALSE; TilGuiExitKey=256;
  TilGuiScissorActive=FALSE;
  FlushMsgs;
  TilGuiOldLeft=Fs->win_left; TilGuiOldRight=Fs->win_right;
  TilGuiOldTop=Fs->win_top; TilGuiOldBottom=Fs->win_bottom;
  MemCpy(TilGuiOldTitle,Fs->task_title,STR_LEN);
  MemSet(Fs->task_title,0,STR_LEN);
  MemCpy(Fs->task_title,title,MinI64(StrLen(title),STR_LEN-1));
  TilGuiOldDraw=Fs->draw_it;
  TilGuiOldInhibit=Fs->win_inhibit;
  // Deliver immediate left/right events, rather than DolDoc cursor movement,
  // double-click-to-Escape or Ctrl-drag panning of the native task window.
  Fs->win_inhibit|=WIF_SELF_MS_L|WIF_SELF_MS_R|WIF_SELF_GRAB_SCROLL|
    WIF_FOCUS_TASK_MS_L_D|WIF_FOCUS_TASK_MS_R_D;
  Fs->win_inhibit&=~(WIF_SELF_CTRLS|WIF_FOCUS_TASK_CTRLS);
  // The first wheel control receives task-routed wheel events and consumes
  // them before the console scrollbar can pan our drawing surface. It is
  // invisible and does not intercept pointer clicks.
  TilGuiWheelPending=0; TilGuiWheelMove=0; TilGuiWheelFocused=TRUE;
  TilGuiMiddlePhysical=ms_hard.bttns[2];
  TilGuiMiddleOwned=FALSE;
  TilGuiWheelControl=CAlloc(sizeof(CCtrl));
  TilGuiWheelControl->win_task=Fs;
  TilGuiWheelControl->type=CTRLT_GENERIC;
  TilGuiWheelControl->wheel_chg=&TilGuiWheelChanged;
  TilGuiWheelControl->update_derived_vals=&TilGuiUpdateMiddle;
  QueIns(TilGuiWheelControl,&Fs->next_ctrl);
  TilGuiFront=DCNew(GR_WIDTH,GR_HEIGHT);
  TilGuiBack=DCNew(GR_WIDTH,GR_HEIGHT);
  DCFill(TilGuiFront,BLACK); DCFill(TilGuiBack,BLACK);
  TilGuiOldBorder=WinBorder(OFF);
  WinHorz(0,TEXT_COLS-1);
  WinVert(0,TEXT_ROWS-1);
  Fs->draw_it=&TilGuiDraw;
  WinFocus;
  // Let WinMgr baseline its cumulative wheel axis before accepting GUI input.
  Refresh(2);
  TilGuiWheelPending=0;
  TilGuiMouseX=(ms.pos.x-Fs->pix_left-TilGuiViewX)*width/TilGuiViewWidth;
  TilGuiMouseY=(ms.pos.y-Fs->pix_top-TilGuiViewY)*height/TilGuiViewHeight;
}

public I32 TilGuiGetScreenWidth() { return TilGuiWidth; }
public I32 TilGuiGetScreenHeight() { return TilGuiHeight; }

public U0 TilGuiSetTargetFPS(I64 fps)
{
  if (fps>0) TilGuiFrameMs=1000/fps;
  else TilGuiFrameMs=0;
}

public U0 TilGuiBeginDrawing()
{
  TilGuiDrawing=TRUE;
}

public U0 TilGuiBeginScissorMode(I64 x,I64 y,I64 width,I64 height)
{
  if (width<0 || height<0) TilPanicZ("GUI scissor requires nonnegative extents\n");
  // The facade uses I32 coordinates/extents, so these sums fit in I64.
  // Like raylib, Begin replaces the clip; End disables it, without a stack.
  TilGuiScissorLeft=MaxI64(0,x);
  TilGuiScissorTop=MaxI64(0,y);
  TilGuiScissorRight=MinI64(TilGuiWidth,x+width);
  TilGuiScissorBottom=MinI64(TilGuiHeight,y+height);
  TilGuiScissorActive=TRUE;
}

public U0 TilGuiEndScissorMode()
{
  TilGuiScissorActive=FALSE;
}

extern I64 TilGuiPaletteColor(U8 *opaque);

U0 TilGuiFillRect(I64 x,I64 y,I64 width,I64 height,U8 *opaque=NULL)
{
  I64 right=MinI64(x+width,TilGuiWidth),bottom=MinI64(y+height,TilGuiHeight);
  I64 px,py,index,alpha;
  TilGuiColor *source=opaque(TilGuiColor *);
  TilGuiColor mixed;
  x=MaxI64(0,x); y=MaxI64(0,y);
  if (TilGuiScissorActive) {
    right=MinI64(right,TilGuiScissorRight);
    bottom=MinI64(bottom,TilGuiScissorBottom);
    x=MaxI64(x,TilGuiScissorLeft);
    y=MaxI64(y,TilGuiScissorTop);
  }
  // Empty/off-screen rectangles and subpixel spans draw no pixels.
  if (right<=x || bottom<=y) return;
  right=TilGuiViewX+right*TilGuiViewWidth/TilGuiWidth;
  bottom=TilGuiViewY+bottom*TilGuiViewHeight/TilGuiHeight;
  x=TilGuiViewX+x*TilGuiViewWidth/TilGuiWidth;
  y=TilGuiViewY+y*TilGuiViewHeight/TilGuiHeight;
  if (right<=x || bottom<=y) return;
  if (!source || source->a==255) { GrRect(TilGuiBack,x,y,right-x,bottom-y); return; }
  alpha=source->a;
  if (!alpha) return;
  mixed.a=255;
  for (py=y;py<bottom;py++)
    for (px=x;px<right;px++) {
      index=GrPeek(TilGuiBack,px,py);
      mixed.r=(source->r*alpha+(gr_palette_std[index].r>>8)*(255-alpha)+127)/255;
      mixed.g=(source->g*alpha+(gr_palette_std[index].g>>8)*(255-alpha)+127)/255;
      mixed.b=(source->b*alpha+(gr_palette_std[index].b>>8)*(255-alpha)+127)/255;
      TilGuiBack->color=TilGuiPaletteColor(&mixed);
      GrPlot(TilGuiBack,px,py);
    }
}

I64 TilGuiPaletteColor(U8 *opaque)
{
  TilGuiColor *color=opaque(TilGuiColor *);
  I64 i,distance,best=I64_MAX,result=0;
  for (i=0;i<COLORS_NUM;i++) {
    distance=SqrI64(color->r-(gr_palette_std[i].r>>8))+
      SqrI64(color->g-(gr_palette_std[i].g>>8))+
      SqrI64(color->b-(gr_palette_std[i].b>>8));
    if (distance<best) { best=distance; result=i; }
  }
  return result;
}

public U0 TilGuiClearBackground(U8 *color)
{
  I64 ink=TilGuiPaletteColor(color);
  if (TilGuiScissorActive) {
    TilGuiBack->color=ink;
    TilGuiFillRect(0,0,TilGuiWidth,TilGuiHeight);
  } else {
    DCFill(TilGuiBack,BLACK);
    TilGuiBack->color=ink;
    TilGuiFillRect(0,0,TilGuiWidth,TilGuiHeight);
  }
}

public U0 TilGuiDrawRectangle(I64 x,I64 y,I64 width,I64 height,U8 *color)
{
  TilGuiBack->color=TilGuiPaletteColor(color);
  TilGuiFillRect(x,y,width,height,color);
}

public U0 TilGuiDrawCircle(I64 x,I64 y,F32 radius,U8 *color)
{
  F64 r=TilF32Load(radius),square=r*r;
  I64 extent,dy,dx;
  if (r<=0) return;
  extent=ToI64(Ceil(r));
  for (dy=-extent;dy<=extent;dy++) {
    dx=extent;
    while (dx>=0 && dx*dx+dy*dy>square) dx--;
    if (dx>=0) {
      TilGuiBack->color=TilGuiPaletteColor(color);
      TilGuiFillRect(x-dx,y+dy,2*dx+1,1,color);
    }
  }
}

public U0 TilGuiDrawText(U8 *text,I64 x,I64 y,I64 font_size,U8 *color)
{
  CDC *glyph;
  I64 gx,gy,ink,start_x=x,ch,left,top,right,bottom;
  if (font_size<=0) TilPanicZ("GUI text requires a positive font size\n");
  ink=TilGuiPaletteColor(color);
  glyph=DCNew(FONT_WIDTH,FONT_HEIGHT);
  while (ch=*text++) {
    if (ch=='\n') { x=start_x; y+=font_size; }
    else {
      if (ch<32 || ch>126) TilPanicZ("GUI text POC requires printable ASCII\n");
      DCFill(glyph,TRANSPARENT);
      glyph->color=WHITE;
      GrPutChar(glyph,0,0,ch);
      TilGuiBack->color=ink;
      for (gy=0;gy<FONT_HEIGHT;gy++)
        for (gx=0;gx<FONT_WIDTH;gx++)
          if (GrPeek(glyph,gx,gy)==WHITE) {
            left=gx*font_size/FONT_HEIGHT; right=(gx+1)*font_size/FONT_HEIGHT;
            top=gy*font_size/FONT_HEIGHT; bottom=(gy+1)*font_size/FONT_HEIGHT;
            TilGuiBack->color=ink;
            TilGuiFillRect(x+left,y+top,right-left,bottom-top,color);
          }
      x+=FONT_WIDTH*font_size/FONT_HEIGHT;
    }
  }
  DCDel(glyph);
}

public U0 TilGuiEndDrawing()
{
  CDC *old=TilGuiFront;
  TilGuiFront=TilGuiBack;
  TilGuiBack=old;
  TilGuiDrawing=FALSE;
  if (TilGuiFrameMs) Sleep(TilGuiFrameMs);
  else Yield;
  TilGuiPollInput;
}

public U0 TilGuiLoadImageFromScreen(U8 *opaque)
{
  TilGuiImage *image=opaque(TilGuiImage *);
  CDC *source;
  I64 x,y,index;
  U8 *pixel;
  if (TilGuiDrawing) TilPanicZ("GUI POC captures after EndDrawing\n");
  // Capture the composited screen, exercising the window manager callback,
  // rather than merely reading back our off-screen drawing buffer.
  source=DCScrnCapture(FALSE);
  image->width=source->width; image->height=source->height;
  image->mipmaps=1; image->format=7; // PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
  image->data=TilMAlloc(source->width*source->height*4);
  for (y=0;y<source->height;y++)
    for (x=0;x<source->width;x++) {
      index=GrPeek(source,x,y);
      pixel=image->data+(y*source->width+x)*4;
      pixel[0]=gr_palette_std[index].r>>8;
      pixel[1]=gr_palette_std[index].g>>8;
      pixel[2]=gr_palette_std[index].b>>8;
      pixel[3]=255;
    }
  DCDel(source);
}

public U0 TilGuiGetImageColor(U8 *out,U8 *opaque,I64 x,I64 y)
{
  TilGuiImage *image=opaque(TilGuiImage *);
  if (image->format!=7) TilPanicZ("GUI POC requires RGBA8 images\n");
  if (x<0 || y<0 || x>=image->width || y>=image->height)
    TilPanicZ("image pixel out of bounds\n");
  TilMemCpy(out,image->data+(y*image->width+x)*4,4);
}

public U0 TilGuiUnloadImage(U8 *opaque)
{
  TilGuiImage *image=opaque(TilGuiImage *);
  TilFree(image->data);
}

public U0 TilGuiCloseWindow()
{
  QueRem(TilGuiWheelControl);
  Free(TilGuiWheelControl);
  TilGuiWheelControl=NULL;
  Fs->draw_it=TilGuiOldDraw;
  Fs->win_inhibit=TilGuiOldInhibit;
  DCDel(TilGuiFront); DCDel(TilGuiBack);
  TilGuiFront=NULL; TilGuiBack=NULL;
  WinBorder(TilGuiOldBorder);
  WinHorz(TilGuiOldLeft,TilGuiOldRight);
  WinVert(TilGuiOldTop,TilGuiOldBottom);
  MemCpy(Fs->task_title,TilGuiOldTitle,STR_LEN);
}
