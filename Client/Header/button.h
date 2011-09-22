
/*
#ifdef _DEBUG


inline void * __cdecl operator new(unsigned int size, 
                                 const char *file, int line)
{
};

inline void __cdecl operator delete(void *p)
{
};
#endif

#ifdef _DEBUG
#define DEBUG_NEW new(__FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif
#define new DEBUG_NEW

#ifdef _DEBUG
inline void * __cdecl operator new(unsigned int size,
                                 const char *file, int line)
{
  void *ptr = (void *)malloc(size);
  AddTrack((DWORD)ptr, size, file, line);
  return(ptr);
};
inline void __cdecl operator delete(void *p)
{
  RemoveTrack((DWORD)p);
  free(p);
}
#endif

typedef struct 
{
  DWORD	address;
  DWORD	size;
  char	file[64];
  DWORD	line;
} ALLOC_INFO;


*/