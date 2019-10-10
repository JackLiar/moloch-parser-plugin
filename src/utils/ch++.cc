#include "ch++.h"

using namespace std;

// ====================================
ChScratch::ChScratch() {}

ChScratch::ChScratch(ChObj &obj) {
    ch_error_t ret = ch_alloc_scratch(obj.m_database, &(this->m_scratch));
    if (CH_SUCCESS != ret) {
        m_scratch = nullptr;
    }
}

ChScratch::~ChScratch() {
    if (m_scratch) {
        ch_error_t ret = ch_free_scratch(this->m_scratch);
    }
}

inline int ChScratch::free() { return ch_free_scratch(this->m_scratch); }
// ====================================
ChObj::~ChObj() {
    if (!m_database) {
        ch_free_database(m_database);
    }
    if (!m_scratch) {
        delete m_scratch;
    }
}

int ChObj::compile(const std::string expression, unsigned int mode) {
    ch_compile_error_t *compile_err;
    ch_error_t err;

    err = ch_compile(expression.c_str(), CH_FLAG_CASELESS | CH_FLAG_SINGLEMATCH, mode, nullptr,
                     &m_database, &compile_err);
    if (CH_SUCCESS != err) {
        if (compile_err->expression < 0) {
            fprintf(stderr, "ERROR: %s\n", compile_err->message);
        } else {
            fprintf(stderr, "ERROR: Chimera pattern '%s' failed compilation with error: %s\n",
                    expression.c_str(), compile_err->message);
        }
        ch_free_compile_error(compile_err);
        return -1;
    }

    m_scratch = new ChScratch(*this);
    if (m_scratch->m_scratch == nullptr) {
        fprintf(stderr, "ERROR: Chimera pattern '%s' failed scratch allocation\n",
                expression.c_str());
        return -1;
    }

    return err;
}

int ChObj::compile_multi(const vector<string> &expressions, const vector<unsigned> ids,
                         unsigned int mode) {
    ch_compile_error_t *compile_err;
    ch_error_t err;

    vector<const char *> char_arr_vec;
    vector<unsigned> flags;
    for (auto it = expressions.begin(); it != expressions.end(); it++) {
        char_arr_vec.push_back(it->c_str());
        flags.push_back(CH_FLAG_CASELESS);
    }

    err = ch_compile_multi(char_arr_vec.data(), flags.data(), ids.data(), expressions.size(), mode,
                           nullptr, &m_database, &compile_err);

    if (err != CH_SUCCESS) {
        if (compile_err->expression < 0) {
            fprintf(stderr, "ERROR: %s\n", compile_err->message);
        } else {
            fprintf(stderr, "ERROR: Chimera pattern '%s' failed compilation with error: %s\n",
                    expressions[compile_err->expression].c_str(), compile_err->message);
        }
        ch_free_compile_error(compile_err);
        return -1;
    }

    m_scratch = new ChScratch(*this);
    if (m_scratch->m_scratch == nullptr) {
        fprintf(stderr, "ERROR: Chimera failed scratch allocation\n");
        return -1;
    }

    return err;
}

inline int ChObj::scan(const char *input, int len, ch_match_event_handler on_match, void *ctx) {
    return scan(input, len, on_match, ctx, *m_scratch);
}

int ChObj::scan(const char *input, int len, ch_match_event_handler on_match, void *ctx,
                ChScratch &scratch) {
    ch_error_t err;
    err = ch_scan(m_database, input, len, 0, scratch.m_scratch, on_match, NULL, &ctx);
    if (CH_SUCCESS != err) {
        fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
        scratch.free();
        ch_free_database(m_database);
    }
    return err;
}
// ====================================