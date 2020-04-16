#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct monoidCtx {
    void *( *const empty )();
    void *( *const append )( const void *, const void * );
    void ( *const free )( void * );
};

#ifdef __cplusplus
}
#endif // __cplusplus
