#include <cstdio>

#include "hs++.h"

using namespace std;

HsScratch::HsScratch() {}

HsScratch::HsScratch(HsObj &obj) {
    hs_error_t ret = hs_alloc_scratch(obj.m_database, &(this->m_scratch));
    if (HS_SUCCESS != ret) {
        m_scratch = nullptr;
    }
}

HsScratch::HsScratch(HsScratch &scratch) {
    hs_error_t ret = hs_clone_scratch(scratch.m_scratch, &m_scratch);
    if (HS_SUCCESS != ret) {
        m_scratch = nullptr;
    }
}

HsScratch::~HsScratch() {
    if (m_scratch) {
        hs_error_t ret = hs_free_scratch(this->m_scratch);
    }
}

inline int HsScratch::free() { return hs_free_scratch(this->m_scratch); }

HsObj::~HsObj() {
    if (!m_database) {
        hs_free_database(m_database);
    }
    if (!m_scratch) {
        delete m_scratch;
    }
}

// modified from
// https://github.com/intel/hyperscan/blob/master/examples/pcapscan.cc
int HsObj::compile_multi(const vector<string> &expressions, const vector<unsigned> ids,
                         unsigned int mode) {
    hs_compile_error_t *compile_err;
    hs_error_t err;

    vector<const char *> char_arr_vec;
    vector<unsigned> flags;
    for (auto it = expressions.begin(); it != expressions.end(); it++) {
        char_arr_vec.push_back(it->c_str());
        flags.push_back(HS_FLAG_CASELESS | HS_FLAG_SINGLEMATCH);
    }

    err = hs_compile_multi(char_arr_vec.data(), flags.data(), ids.data(), expressions.size(), mode,
                           nullptr, &m_database, &compile_err);

    if (err != HS_SUCCESS) {
        if (compile_err->expression < 0) {
            fprintf(stderr, "ERROR: %s\n", compile_err->message);
        } else {
            fprintf(stderr, "ERROR: Pattern '%s' failed compilation with error: %s\n",
                    expressions[compile_err->expression].c_str(), compile_err->message);
        }
        hs_free_compile_error(compile_err);
        return -1;
    }

    m_scratch = new HsScratch(*this);
    if (m_scratch->m_scratch == nullptr) {
        fprintf(stderr, "ERROR: hyperscan scratch allocation failed\n");
        return -1;
    }

    return err;
}

inline int HsObj::scan(const char *input, int len, match_event_handler on_match, void *ctx) {
    return scan(input, len, on_match, ctx, *m_scratch);
}

// modified from
// https://github.com/intel/hyperscan/blob/master/examples/singlegrep.c
int HsObj::scan(const char *input, int len, match_event_handler on_match, void *ctx,
                HsScratch &scratch) {
    hs_error_t err;
    err = hs_scan(m_database, input, len, 0, scratch.m_scratch, on_match, ctx);
    if (HS_SUCCESS != err) {
        fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
        scratch.free();
        hs_free_database(m_database);
    }
    return err;
}