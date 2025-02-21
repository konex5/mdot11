/// yet other file I/O

#include "fhmdot/include/file_header.hpp"


namespace fhmdot
{
    typedef enum
    {
        fhm_simulation = 1, // ZSTD_fast
        fhm_storage = 9     // ZSTD_btultra2
    } fhm_compression_strategy;


    int save(FILE *source, FILE *dest, int level)
    {

        // size_t ZSTD_compress( void* dst, size_t dstCapacity,
        //             const void* src, size_t srcSize,
        //                   int compressionLevel);
        return 0;
    }

    int load(FILE *source, FILE *dest, int level)
    {

        // size_t ZSTD_decompress( void* dst, size_t dstCapacity,
        //               const void* src, size_t compressedSize);
        return 0;
    }

} // namespace fhmdot