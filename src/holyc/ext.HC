// TempleOS runtime boundary for generated til HolyC.
// UPtr and raw byte counts are U64. The emitter supplies TIL_USIZE and
// the matching Str sentinels for the resolved source-level USize width.

public class TilStr {
  U8 *c_str;
  TIL_USIZE count;
  TIL_USIZE cap;
};

public class TilStrArray {
  TilStr *data;
  TIL_USIZE cap;
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

public U0 TilStrFromI64(TilStr *out,I64 value)
{
  U64 magnitude,rest;
  TIL_USIZE digits=1,count,index;
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
