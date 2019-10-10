#ifndef __HS_PLUS_PLUS__
#define __HS_PLUS_PLUS__

#include <set>
#include <string>
#include <vector>

#include "hs/hs.h"

// #pragma GCC visibility push(default)

class HsObj;
class HsScratch {
    friend class HsObj;

    hs_scratch_t *m_scratch = nullptr;

  public:
    HsScratch();
    HsScratch(HsObj &obj);
    HsScratch(HsScratch &scratch);
    ~HsScratch();
    int free();
};

class HsObj {
    friend class HsScratch;

    hs_database_t *m_database = nullptr;
    HsScratch *m_scratch = nullptr;

  public:
    ~HsObj();
    /*
     * Compile multiple regular expressions
     *
     * Simce all expressions in the udger database all use the same compile
     * flags, ignore flags in the api and do it inside the function
     *
     * @param expressions
     *      regular expressions
     * @param ids
     *      ids of regular expressions
     * @param mode
     *      hyperscan scan mode, default is block mode
     */
    int compile_multi(const std::vector<std::string> &expressions, const std::vector<unsigned> ids,
                      unsigned int mode = HS_MODE_BLOCK);
    int scan(const char *input, int len, match_event_handler on_match, void *ctx);
    int scan(const char *input, int len, match_event_handler on_match, void *ctx,
             HsScratch &scratch);
};

// #pragma GCC visibility pop

#endif