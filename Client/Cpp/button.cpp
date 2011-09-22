#include "button.h" 

/*
      typedef list<ALLOC_INFO*> AllocList;

      AllocList *allocList;

      void AddTrack(DWORD addr,  DWORD asize,  const char *fname, DWORD lnum)
      {
	      ALLOC_INFO *info;

	      if(!allocList) {
		      allocList = new(AllocList);
	      }

	      info = new(ALLOC_INFO);
	      info->address = addr;
	      strncpy(info->file, fname, 63);
	      info->line = lnum;
	      info->size = asize;
	      allocList->insert(allocList->begin(), info);
      };

      void RemoveTrack(DWORD addr)
      {
	      AllocList::iterator i;

	      if(!allocList)
		      return;
	      for(i = allocList->begin(); i != allocList->end(); i++)
	      {
		      if((*i)->address == addr)
		      {
			      allocList->remove((*i));
			      break;
		      }
	      }
      };*/