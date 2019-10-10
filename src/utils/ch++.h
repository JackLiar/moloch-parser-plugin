#ifndef __CH_PLUS_PLUS__
#define __CH_PLUS_PLUS__

#include <string>

#include "hs/ch.h"

#include "hs++.h"

#pragma GCC visibility push(default)

class ChObj;
class ChScratch {
    friend class ChObj;

    ch_scratch_t *m_scratch = nullptr;

  public:
    ChScratch();
    ChScratch(ChObj &obj);
    ~ChScratch();
    int free();
};

class ChObj {
    friend class ChScratch;

    ch_database_t *m_database = nullptr;
    ChScratch *m_scratch = nullptr;

  public:
    ~ChObj();
    /*
     * Compile single regular expressions
     *
     * @param expression
     *      regular expression
     * @param mode
     *      hyperscan scan mode, default is groups mode
     */
    int compile(const std::string expression, unsigned int mode = CH_MODE_GROUPS);
    /*
     * Compile multiple regular expressions
     *
     * Since all expressions in the udger database all use the same compile
     * flags, ignore flags in the api and do it inside the function
     *
     * @param expressions
     *      regular expressions
     * @param ids
     *      ids of regular expressions
     * @param mode
     *      hyperscan scan mode, default is groups mode
     */
    int compile_multi(const std::vector<std::string> &expressions, const std::vector<unsigned> ids,
                      unsigned int mode = CH_MODE_GROUPS);
    int scan(const char *input, int len, ch_match_event_handler on_match, void *ctx);
    int scan(const char *input, int len, ch_match_event_handler on_match, void *ctx,
             ChScratch &scratch);
};

#pragma GCC visibility pop

#endif
